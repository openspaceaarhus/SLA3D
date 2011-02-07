#include "structs.h"
#include <vector>
#include "Layer.h"			
#include "intersections.h"
#include "svg.h"
#include <cmath>
#include <assert.h>

Layer::Layer(linkedlist *ll, float height) {
  candidates = ll;
  this->height = height;
  // init the datastructures
  poly = new std::vector< std::vector<point*> >;
  segments = new std::vector<line*>;
  
  create_segments();
  create_polys();
}

Layer::~Layer() {
  // TODO is this alright? or should it iterate throug the polys?
  delete segments;
  delete poly;
}


// todo move somewhere nice
bool point_compare(point p1, point p2) {
  double xs = p1.x-p2.x ;
  double ys = p1.y-p2.y ;
  xs = std::abs(xs);
  ys = std::abs(ys);
  return  (xs < EPSILON) && (ys < EPSILON);
}



// find the cycles representing each polygon in the layer
// this is a naive O(n^2) implementaion, it will benefit greatly from a scanline aproach
void Layer::create_polys() {
  
  std::vector<line*> candidates (segments->begin(), segments->end());
  
  while (!candidates.empty()) {
    line *cur_start = candidates.at(0);
    point *poly_start = &(cur_start->p1);
    point *look_for = &(cur_start->p2);
    
    // REMOVE the start poly from the candidates
    candidates.erase(candidates.begin());
    
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
    // there should be a cycle, insert look_for ? and
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


    // the vector from p1 to p2
    const point p1p2 = {l->p2.x - l->p1.x, l->p2.y - l->p1.y};

    // should to short segments be skipped?, yes
    if (std::abs(p1p2.x * p1p2.x + p1p2.y * p1p2.y) < EPSILON * EPSILON) 
      continue;

    assert(std::abs(p1p2.x * p1p2.x + p1p2.y * p1p2.y) > EPSILON*EPSILON);
    // project onto zx plane, and well call z for y 
    const point normal = {f->normal.x, f->normal.z}; 
    assert(std::abs(normal.x * normal.x + normal.y * normal.y) > EPSILON*EPSILON);

    // we can calculate this as z = 0;
    float cross = p1p2.x*normal.y - p1p2.y * normal.x; 
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

 FILE *f;
  
 f = fopen(filename, "w");
 fprintf(f, "#slice in for height=%f %d segments as CCW polygons\n", height, segments->size());
  
 int poly_no = 1;
 for(std::vector< std::vector<point*> >::iterator it = poly->begin(); it != poly->end(); it++) {
   fprintf(f, "# polygon %d\n", poly_no++);
     std::vector<point*> cycle  = *it;
     for(std::vector<point*>::iterator jt = cycle.begin(); jt != cycle.end(); jt++) {
       point *p = *jt;
       fprintf(f, "%f %f\n", p->x, p->y);
     }
 }

  fclose(f);



}


