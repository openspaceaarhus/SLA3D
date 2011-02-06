#ifndef STICHER_H_
#define STICHER_H_
#include "structs.h"
#include <vector>


class Layer {

 public:
  Layer(linkedlist *, float height);
  ~Layer();
  /* std::vector<point> getPolygons(); */
  /* std::vector<line> getSegments(); */
  
  void save_svg(const char *filename);
  void save_pts(const char *filename);
  void dump_segments(const char *filename);
 private:
  void create_segments();
  void create_polys();
  /* std::vector<point*> *poly; */
  std::vector< std::vector<point*> > *poly;
  std::vector<line*> *segments;  
  linkedlist *candidates;
  float height;

};



#endif /* !STICHER_H_ */
