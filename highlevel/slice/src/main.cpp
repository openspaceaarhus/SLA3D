#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "read_stl.h"
#include "intersections.h"
#include "intersectplane.h"
#include "vec_math.h"
#include "svg.h"


void intersect_print(stl_face f, float height) {
  line *l;

  l = intersection_line(&f, height);
  if (l) {
    svg_line(l->p1.x, l->p1.y, l->p2.x, l->p2.y);
  }
}

void print_vec3d(vec3d v) {
  printf("(%f, %f, %f)", v.x, v.y, v.z);
}

/* aaargh global var */
slicer *slicern;
void slice_filling(stl_face f) {
  add_face_toQ(slicern, f);
}


void print_plane(int level) {
 char buf[512];
 FILE *file;
 linkedlistnode *it;
 stl_face *f;
 sprintf(buf, "level%05d.svg", level);
  
 file = fopen(buf, "w");
 svg_init(file);
 svg_comment("slice in for height=%f", slicern->cur_height);
  
  it = slicern->IP->first;

  while(it != NULL) {
    f = (stl_face*) it->payload;
    intersect_print(*f, slicern->cur_height); 
    it = it->next;
  }

  svg_footer();
  fclose(file);

}

/* utilise normal from stl face to order the segment correctly */
/* cross(line.p2 - line.p1, face.normal) > 0 */
/*            ^                */
/*           /                 */
/*          / Normal           */
/* P1 ------------------> P2   */
line *create_polysegments() {

  line *segments;
  segments = (line*) malloc(slicern->IP->size * (sizeof(line)));
  int idx = 0;

  for(linkedlistnode *it = slicern->IP->first; it != NULL; it = it->next ) {
    stl_face *f = (stl_face*) it->payload;
    line *l = intersection_line(f, slicern->cur_height);
    if (l == NULL)
      continue;
    /* TODO make sure this math is correct */
    vec3d p1p2 = vec3d_create(l->p2.x-l->p1.x, l->p2.y-l->p1.y, 0);
    vec3d norm_proj = vec3d_create(f->normal.x, f->normal.z, 0); /* project
								    int
								    xz plane */
    vec3d cross = vec3d_cross(norm_proj, p1p2);
    if (cross.z < 0) {
      /* swap p1 and p2 */
      point tmp = l->p1;
      l->p1 = l->p2;
      l->p2 = tmp;
    }

    segments[idx++]= *l;


  }
  printf("idx = %d, size = %d\n", idx, slicern->IP->size);
  return segments;
}


char point_compare(point p1, point p2) {
  return abs(p1.x-p2.x) < EPISILON &&
    abs(p1.y-p2.y) < EPISILON;
}

point *create_polylist(line *segments) {
  int size = slicern->IP->size; 
  point *poly;
  poly = (point*) malloc( size * sizeof(point)); /* AARGH use a c++ vector! */
  
  int idx = 0;
  poly[idx] = segments[idx].p1;
  point lookfor = segments[idx].p2;

  idx++;
  while(idx < size) {

    for(int i = 0; i < size; i++) {
      if (point_compare(lookfor, segments[i].p1)) {
	poly[idx] = lookfor;
	lookfor = segments[i].p2;
	idx++;
	break;
      }
    }
  }

  return poly;
}

void save_poly(point *poly, char const *filename, int level) {
  int size = slicern->IP->size; 
  char buf[512];
  sprintf(buf, "%s%05d.pts", filename, level);
  FILE *f = fopen(buf, "w");
  fprintf(f, "# %d\n", size);
  for(int i = 0; i < size; i++) {
    fprintf(f, "%f %f\n", poly[i].x, poly[i].y);
  }
  fclose(f);
}


int main(int argc, char**args) {

  if (argc<3) {
    printf("usage : %s inputfile slice_dist\n", args[0]);
    return 42;
  }


  slicern = create_slicer();

  parse_file(args[1], slice_filling);


  printf("bounding box: ");
  print_vec3d(slicern->bounding_box.min);
  print_vec3d(slicern->bounding_box.max);
  printf("\n");



 
  float slice_dist = atof(args[2]);
  printf("slice_dist = %f\n", slice_dist);

  int slice_number = 0;
  ev_start_iterator(slicern->Q);
  float height = slicern->bounding_box.min.y;
  slicern->cur_height = height;
  
  while (height < slicern->bounding_box.max.y) {
    advance_plane(slicern, height);
    print_plane(slice_number);

    line *segments = create_polysegments();
    point *polylist = create_polylist(segments);
    save_poly(polylist, "polys", slice_number);
    free(segments);
    free(polylist);
    slice_number++;
    height = slicern->bounding_box.min.y + slice_dist*slice_number; 
  }
  
  return 1;
}
