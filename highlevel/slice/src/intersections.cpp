#include "vec_math.h"
#include "intersections.h"
#include "read_stl.h"

#include <stdlib.h>
#include <math.h>
#include <assert.h>

vec3d get_vector(vertex  v1, vertex v2) {
  vec3d tmp;
  tmp.x = v2.x - v1.x;
  tmp.y = v2.y - v1.y;
  tmp.z = v2.z - v1.z;
  return tmp;
}


/* this really ought to project on the plane */
point *get_point_in_2d(vec3d v) {

  point *i;

  if (0 == (i = (point*) malloc(sizeof(point)))) {
    perror("no more mem\n");
  }

  /* this wil only be valid if normal is <0,1,0>? */
  i->x = v.x;
  i->y = v.z;
  /* printf("result=(%f, %f)\n", i->x, i->y); */
  return i;
}

/* https://secure.wikimedia.org/wikipedia/en/wiki/Line-plane_intersection */
point *intersection(vec3d start, vec3d v, float height) {
  float d, len;
  vec3d direction;
  float nom, denom;
  len = vec3d_len(v);
  direction = vec3d_div(v, len);

  /* nom = vec3d_dot(vec3d_sub(plane.p0, start), plane.normal); */
  /* denom = vec3d_dot(direction, plane.normal); */

  nom = height-start.y;
  denom = direction.y;
  /* printf("nom = %f, denom = %f\n", nom, denom); */

  /* do some checking.... */

  if (fabs(denom) < EPSILON) {
    if (fabs(nom) < EPSILON) {
      /* line lies within the plane */
      return get_point_in_2d(start);
    }
    /* no intersection */
    return NULL;
  }

  d = nom/denom;
  /* printf("nom/denom = %f\n", d); */
  if (d < EPSILON || d > (len+ EPSILON))
    return NULL;

  vec3d res;

  res = vec3d_add(start, vec3d_mul(direction, d));

  return get_point_in_2d(res);
}

vec3d from_vertex(vertex v) {
  vec3d tmp;
  tmp.x = v.x;
  tmp.y = v.y;
  tmp.z = v.z;
  return tmp;
}

line *convert_to_line(point *p1, point *p2) {
  line *l;
  if (0 == (l = (line*)malloc(sizeof(line)))) {
    perror("no more mem\n");
  }

  l->p1 = *p1;
  l->p2 = *p2;
  free(p1); free(p2);
  return l;
}

line *intersection_line(stl_face *f, float height) {

  point *p1, *p2;
  vec3d start, u, v;
  /* head under the arm implementation */

  start = from_vertex(f->v1);
  u = get_vector(f->v1, f->v2);
  p1 = intersection(start, u, height);


  v = get_vector(f->v1, f->v3);
  p2 = intersection(start, v, height);

  if ( NULL == p1 && NULL == p2) {
    /* printf("no intersect\n"); */
    return NULL;
  }

  if (p1 && p2) {
    return convert_to_line(p1,p2);
  }


  start = from_vertex(f->v2);
  v = get_vector(f->v2, f->v3);
  
  p1 = (NULL != p1) ? p1 : p2;
  p2 = NULL;
  assert(p1 != NULL);

  p2 = intersection(start, v, height);
  /* assert(p2 != NULL); */

  if (p1 && p2) {
    return convert_to_line(p1,p2);
  }

  return NULL;

}
