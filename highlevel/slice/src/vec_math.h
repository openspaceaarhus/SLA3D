#ifndef VEC_MATH_H_
#define VEC_MATH_H_
#include "structs.h"


vec3d vec3d_sub(vec3d v, vec3d u);
vec3d vec3d_add(vec3d v, vec3d u);

vec3d vec3d_mul(vec3d v, float s);
vec3d vec3d_div(vec3d v, float s);

vec3d vec3d_normalize(vec3d v);
vec3d vec3d_cross(vec3d v, vec3d u);
vec3d vec3d_cross_y(vec3d u);

float vec3d_dot(vec3d v, vec3d u);
float vec3d_len(vec3d v);

vec3d vec3d_create(float x, float y, float z);

char vec3d_zero(vec3d v);
char vec3d_compare(vec3d v, vec3d u);

#endif /* !VEC_MATH_H_ */
