#include <stdio.h>
#include <stdlib.h>
#include "read_stl.h"

void print_vertex(vertex v) {
  printf("\t (%f,%f,%f)\n", v.x, v.y, v.z);
}

void print_stlface(stl_face f) {
  print_vertex( f.normal);
  print_vertex( f.v1);
  print_vertex( f.v2);
  print_vertex( f.v3);
  printf("bc = %x%x\n", f.bc[0], f.bc[1]);
  printf("\n");
}

void read_vertex(FILE *fp, vertex *v) {
  fread(v, 3*sizeof(float), 1, fp);
}

void parse_file(const char* filename, void (*handle_stlface)(stl_face)) {

  FILE *fp;
  fp = fopen(filename, "rb");

  char header[80];
  fread(header, 1, 80, fp);
  unsigned int len;
  fread(&len, 4, 1, fp);

  printf("we should have %u vertexes\n", len);

  stl_face f;
  
  for(unsigned int i = 0; i < len ; i++) {
    read_vertex(fp, &f.normal);
    read_vertex(fp, &f.v1);
    read_vertex(fp, &f.v2);
    read_vertex(fp, &f.v3); 
    fread(&f.bc, 2, 1, fp);

    handle_stlface(f);
  }

  fclose(fp);
}

