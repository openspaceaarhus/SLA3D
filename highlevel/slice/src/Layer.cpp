#include "structs.h"
#include <vector>
#include "Layer.h"			
#include "intersections.h"
#include "svg.h"

Layer::Layer(linkedlist *ll, float height) {
  candidates = ll;
  this->height = height;
  // init the datastructures
  poly = new std::vector< std::vector<point*> >;

  segments = new std::vector<line*>;
  
  create_segments();
  dump_segments("debug");
  create_polys();
}

Layer::~Layer() {
  // TODO is this alright?
  delete segments;
  delete poly;
}


// todo move somewhere nice
bool point_compare(point p1, point p2) {
  return abs(p1.x-p2.x) < EPISILON &&
    abs(p1.y-p2.y) < EPISILON;
}



// find the cycles representing each polygon in the layer
// this is a naive O(n^2) implementaion, it will benefit gratly from a scanline aproach
void Layer::create_polys() {
  
  std::vector<line*> candidates (segments->begin(), segments->end());
  
  while (!candidates.empty()) {
    line *cur_start = candidates.at(0);
    point *poly_start = &(cur_start->p1);
    point *look_for = &(cur_start->p2);
    std::vector<point*> *cur_poly = new std::vector<point*>;
    cur_poly->push_back(poly_start);

    // follow this polygon around
    while ( !point_compare(*look_for, *poly_start) ) {

      for(std::vector<line*>::iterator it = candidates.begin(); it != candidates.end(); it++) { 
	line *l = *it;
	if (point_compare(l->p1, *look_for)) {
	  // we found the other end
	  cur_poly->push_back(look_for);
	  // update what wer are looking 
	  look_for = &(l->p2);
	  // never look at this again.
	  candidates.erase(it);
	  break;
	}
      }
    }
    poly->push_back(*cur_poly);
  }
  


}

/* utilise normal from stl face to order the segment correctly */
// for CCW polygons
/*            ^                */
/*           /                 */
/*          / Normal           */
/* P1 ------------------> P2   */
// CCW means that in this example we must swap p1 and p2
void Layer::create_segments() {
  for(linkedlistnode *it = candidates->first; it != NULL; it = it->next ) {
    stl_face *f = (stl_face*) it->payload;
    line *l = intersection_line(f, this->height);
    if (l == 0)
      continue;

    // FATAL FIXME THIS IS WRONG !!!!!!

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
void Layer::save_svg(const char *filename) {
 FILE *file;
  
 file = fopen(filename, "w");
 svg_init(file);
 svg_comment("slice in for height=%f", height);
  
 
 for(std::vector<line*>::iterator it = segments->begin(); it != segments->end(); it++) {
   line *l = *it;
   svg_line(l->p1.x, l->p1.y, l->p2.x, l->p2.y);
 }

  svg_footer();
  fclose(file);



}


void Layer::dump_segments(const char *filename) {
 FILE *f;
  
 f = fopen(filename, "w");
 fprintf(f, "#slice in for height=%f %d segments\n", height, segments->size());
  
 
 for(std::vector<line*>::iterator it = segments->begin(); it != segments->end(); it++) {
   line *l = *it;
   fprintf(f, "%.13e %.13e %.13e %.13e \n", l->p1.x, l->p1.y, l->p2.x, l->p2.y); 
 }

  fclose(f);

}


// saves the points
void Layer::save_pts(const char *filename) {


}


