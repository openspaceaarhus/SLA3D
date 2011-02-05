#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "read_stl.h"
#include "intersections.h"
#include "intersectplane.h"
#include "vec_math.h"
#include "svg.h"


void intersect_print(stl_face f, float height) {
  line *l;
  /* vec3d v = vec3d_cross_y(from_vertex(f.normal)); */
  /* if ( vec3d_zero(v) ) { */
  /*   /\* triangle is parallel to the plane, discard it*\/ */
  /*   return; */
  /* } */
  
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
  float height = slicern->bounding_box.min.y + slice_dist*slice_number; 

  while (height < slicern->bounding_box.max.y) {
    advance_plane(slicern, height);
    print_plane(slice_number);
    slice_number++;
    height = slicern->bounding_box.min.y + slice_dist*slice_number; 
  }
  
  return 1;
}
