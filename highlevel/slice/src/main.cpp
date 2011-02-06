#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "read_stl.h"
#include "intersections.h"
#include "intersectplane.h"
#include "vec_math.h"
#include "svg.h"
#include "Layer.h"

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
    // print_plane(slice_number);
    char buf[512];
    sprintf(buf, "%s%05d.svg", "segments", slice_number);
    Layer L(slicern->IP, height);
    L.save_svg(buf);
    sprintf(buf, "%s%05d.segs", "dumps", slice_number);
    L.dump_segments(buf);
    slice_number++;
    height = slicern->bounding_box.min.y + slice_dist*slice_number; 
  }
  
  return 1;
}
