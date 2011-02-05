#ifndef INTERSECTIONS_H_
#define INTERSECTIONS_H_
#include "vec_math.h"
#include "read_stl.h"


line *intersection_line(stl_face *f, float height);
vec3d get_vector(vertex  v1, vertex v2);
point *intersects(vec3d start, vec3d direction, float );
point *get_point_in_2d(vec3d v);
vec3d from_vertex(vertex v);
line *convert_to_line(point *p1, point *p2);

#endif /* !INTERSECTIONS_H_ */
