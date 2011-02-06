#ifndef STRUCTS_H_
#define STRUCTS_H_
#include "datastructures/red_black_tree.h"
#include "datastructures/linkedlist.h"


typedef struct {
  float x,y;
} point;

typedef struct {
  point p1, p2;
} line;

typedef struct {
  float x,y,z;
} vec3d;


typedef struct {
  vec3d p0;
  vec3d normal;
} plane;


typedef struct {
  vec3d min, max;
} box;


typedef struct {
  float x,y,z;
} vertex;

typedef struct {
  vertex normal;
  vertex v1, v2, v3;
  char bc[2];
} stl_face;


/* link to a IP node, allow for different storage. */
typedef linkedlistnode IP_node;

typedef union {
  stl_face *face;
  IP_node *ip_node;
} ev_info;


struct event_point {
  char type;
  float height;
  struct event_point *twin; 	/* start <=> stop */
  ev_info info;
};

typedef struct event_point ev_point;

#define EV_START 0
#define EV_STOP 1

typedef struct {
  rb_red_blk_tree *Q;
  rb_red_blk_node *cur;
} event_queue;


typedef struct {
  event_queue *Q;
  linkedlist *IP;
  box bounding_box;
  float cur_height;
} slicer;


#define EPISILON 1e-9


#endif /* !STRUCTS_H_ */
