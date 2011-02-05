/*
** svg.c
** 
** Made by (jacob toft pedersen)
** Login   <jacob@lisbeth>
** 
** Started on  Fri Aug 14 16:11:30 2009 jacob toft pedersen
** Last update Sun May 12 01:17:25 2002 Speed Blue
*/


#include <stdio.h>
#include <stdarg.h>
#include "svg.h"

FILE* out;

void svg_init(FILE *f) {
  out  =f;
  fprintf(out,"<?xml version=\"1.0\" standalone=\"no\"?>\n");
  fprintf(out,"<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n");
  fprintf(out,"<svg width=\"100%%\" height=\"100%%\"  version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\">\n"); /* viewbox=\"0 0 5 5\" */
  /* fprintf(out,"<g transform=\"scale(10)\" >\n"); */
  /* fprintf(out,"<g transform=\"translate(10,10)\" >\n"); */

}


void svg_footer(void) {
  /* fprintf(out,"</g>\n"); */
  /* fprintf(out,"</g>\n"); */
  fprintf(out,"</svg>\n");
}

void svg_circle(float x,float y, float r) {
  fprintf(out,"<circle cx=\"%f\" cy=\"%f\" r=\"%f\" stroke=\"none\" fill=\"black\"/>\n", x, y, r);
}


void svg_line(float x1, float y1,float x2, float y2) {
  fprintf(out,"<line x1=\"%f\"  y1=\"%f\" x2=\"%f\"  y2=\"%f\"  style=\"stroke:rgb(0,0,0); stroke-width:1\" />\n", x1, y1, x2, y2);
}

void svg_comment(const char* format, ...) {
  va_list args;
  fprintf(out, "\t<!--\n\t\t");
  va_start(args, format);
  vfprintf( out, format, args );
  va_end(args);
  fprintf(out, "\n\t-->\n");
}
