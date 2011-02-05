#ifndef READ_STL_H_
#define READ_STL_H_
#include <stdio.h>
#include "structs.h"

void print_vertex(vertex v);
void print_stlface(stl_face f);
void read_vertex(FILE *fp, vertex *v);
void parse_file(const char* filename, void (*handle_stlface)(stl_face));





#endif /* !READ_STL_H_ */
