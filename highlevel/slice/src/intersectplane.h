#ifndef INTERSECTPLANE_H_
#define INTERSECTPLANE_H_
#include "datastructures/red_black_tree.h"
#include "event_queue.h"
#include "structs.h"
#include "vec_math.h"

slicer *create_slicer();

void add_face_toQ(slicer *, stl_face f);

void advance_plane(slicer *,float height);

void get_intersections(slicer *);

int face_compare(stl_face *f1, stl_face *f2);

/* intersection plane funtions */
int IP_Compare(const void* a, const void* b); 
void IP_DestroyKey (void* a);

#endif /* !INTERSECTPLANE_H_ */
