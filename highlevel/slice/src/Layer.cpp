#include "structs.h"
#include <vector>
#include "Layer.h"			
#include "intersections.h"


Layer::Layer(linkedlist *ll, float height) {
  candidates = ll;
  this->height = height;
  // init the datastructures
  poly = new std::vector<point*>;
  segments = new std::vector<line*>;
  
  create_segments();
  create_polys();
  
}


void Layer::create_polys() {


}

/* utilise normal from stl face to order the segment correctly */
/* cross(line.p2 - line.p1, face.normal) > 0 */
/*            ^                */
/*           /                 */
/*          / Normal           */
/* P1 ------------------> P2   */
void Layer::create_segments() {

  
  for(linkedlistnode *it = candidates->first; it != NULL; it = it->next ) {
    stl_face *f = (stl_face*) it->payload;
    line *l = intersection_line(f, this->height);
    if (l == 0)
      continue;
    // the vector from p1 to p2
    const point p1p2 = {l->p2.x - l->p1.x, l->p2.y - l->p1.y};
    // project onto zx plane, and well call z for y 
    const point normal = {f->normal.x, f->normal.z}; 

    // we can calculate this as z = 0;
    float cross = p1p2.x*normal.x - p1p2.y * normal.y; 
    // change the order so we are sure that p1 is the first point in a CCW polygon
    if (cross < 0) {
      /* swap p1 and p2 */
      point tmp = l->p1;
      l->p1 = l->p2;
      l->p2 = tmp;
    }
    segments->push_back(l);
  }

}

// generate a svg			
void Layer::save_svg(const char filename) {


}


// saves the points
void Layer::save_pts(const char filename) {


}


