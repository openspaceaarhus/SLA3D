#include "intersectplane.h"
#include "event_queue.h"
#include "structs.h"
#include "vec_math.h"
#include "datastructures/linkedlist.h"
#include <assert.h>
#include <stdlib.h>


#define MIN(X, Y) ((X<Y) ? X : Y)
#define MAX(X, Y) ((X>Y) ? X : Y)


slicer *create_slicer() {
  slicer *tmp;

  tmp = (slicer*) malloc(sizeof(slicer));

  tmp->Q = make_event_queue();

  tmp->IP = linkedlist_make();

  return tmp;

}

/* returns min in vec */
static inline vec3d min_vertex(vec3d vec, vertex v) {
  vec.x = MIN(vec.x, v.x);
  vec.y = MIN(vec.y, v.y);
  vec.z = MIN(vec.z, v.z);
  return vec;
}

/* returns max in vec */
static inline vec3d max_vertex(vec3d vec, vertex v) {
  vec.x = MAX(vec.x, v.x);
  vec.y = MAX(vec.y, v.y);
  vec.z = MAX(vec.z, v.z);
  return vec;
}


void update_boundingbox(slicer *slicer, stl_face* f) {
  slicer->bounding_box.min = min_vertex(slicer->bounding_box.min, f->v1);
  slicer->bounding_box.min = min_vertex(slicer->bounding_box.min, f->v2);
  slicer->bounding_box.min = min_vertex(slicer->bounding_box.min, f->v3);

  slicer->bounding_box.max = max_vertex(slicer->bounding_box.max, f->v1);
  slicer->bounding_box.max = max_vertex(slicer->bounding_box.max, f->v2);
  slicer->bounding_box.max = max_vertex(slicer->bounding_box.max, f->v3);
}


void sort_vertexes(stl_face *f) {
  vertex tmp;

  if ( f->v1.y < f->v2.y ) {
    tmp = f->v1;
    f->v1 = f->v2;
    f->v2 = tmp;
  }

  if (f->v1.y < f->v3.y) {
    tmp = f->v1;
    f->v1 = f->v3;
    f->v3 = tmp;
  }

  if (f->v2.y < f->v3.y) {
    tmp = f->v2;
    f->v2 = f->v3;
    f->v3 = tmp;
  }
  assert(f->v1.y >= f->v2.y);
  assert(f->v2.y >= f->v3.y);
}

void insert_ev_points(event_queue *Q, stl_face *f) {
  ev_point *start, *end;
  start = (ev_point*) SafeMalloc(sizeof(ev_point));
  end = (ev_point*) SafeMalloc(sizeof(ev_point));

  start->type = EV_START;
  start->info.face = f;
  start->height = f->v3.y;

  ev_insert(Q, start);

  end->type = EV_STOP;
  end->height = f->v1.y;

  ev_insert(Q, end);

  end->twin = start;
  start->twin = end;

  assert(end->height >= start->height);

}


void add_face_toQ(slicer *slicer, stl_face face) {
  stl_face *f;
  /* TODO make sure that this is correct */
//   if ( abs(face.normal.x) < EPSILON && abs(face.normal.z) < EPSILON) {
// //     printf("dead normal\n");
//     return;
//   }

  f = (stl_face*) SafeMalloc(sizeof(stl_face));
  *f = face;
  sort_vertexes(f);
  update_boundingbox(slicer, f);
  insert_ev_points(slicer->Q, f);
}

void advance_plane(slicer * slicer, float height) {
  assert(height >= slicer->cur_height);
  ev_point *e;
  IP_node *ipn;

  e = ev_peek(slicer->Q);
  while (e != NULL && e->height <= height) {
    switch(e->type) {
    case EV_START:
      ipn = ll_insert(slicer->IP, e->info.face);
      e->twin->info.ip_node = ipn;
      break;
    case EV_STOP:
      linkedlist_remove(slicer->IP, e->info.ip_node);
      break;
    default:
      printf("UNKNOWN TYPE IN Q\n");
      exit(42);
    }
    
    ev_pop(slicer->Q);
    e = ev_peek(slicer->Q);
  }
  slicer->cur_height = height;
}

void get_intersections(slicer *s ) {

}



/* intersection plane funtions */
int IP_Compare(const void* a, const void* b) {
  return face_compare( (stl_face*) a, (stl_face*) b);
}
void IP_DestroyKey (void* a) {
  free( (stl_face*) a);
}


int face_compare(stl_face *f1, stl_face *f2) {
  assert(f1->v1.y >= f1->v2.y);
  assert(f1->v2.y >= f1->v3.y);
 
  assert(f2->v1.y >= f2->v2.y);
  assert(f2->v2.y >= f2->v3.y);


  /* y coordinates */
  if (f1->v1.y > f2->v1.y)
    return 1;

  if (f1->v1.y < f2->v1.y)
    return -1;

  if (f1->v2.y > f2->v2.y)
    return 1;

  if (f1->v2.y < f2->v2.y)
    return -1;

  if (f1->v3.y > f2->v3.y)
    return 1;

  if (f1->v3.y < f2->v3.y)
    return -1;

  /* x coordinates */
  if (f1->v1.x > f2->v1.x)
    return 1;

  if (f1->v1.x < f2->v1.x)
    return -1;

  if (f1->v2.x > f2->v2.x)
    return 1;

  if (f1->v2.x < f2->v2.x)
    return -1;

  if (f1->v3.x > f2->v3.x)
    return 1;

  if (f1->v3.x < f2->v3.x)
    return -1;

  return 0;
}
