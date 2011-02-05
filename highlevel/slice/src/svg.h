/*
** svg.h
** 
** Made by jacob toft pedersen
** Login   <jacob@lisbeth>
** 
** Started on  Fri Aug 14 16:10:12 2009 jacob toft pedersen
** Last update Fri Aug 14 16:10:12 2009 jacob toft pedersen
*/

#ifndef   	SVG_H_
# define   	SVG_H_
void svg_comment(const char *format, ...);
void svg_init(FILE *f);
void svg_footer(void);
void svg_circle(float x,float y, float r);
void svg_line(float x1, float y1,float x2, float y2);
#endif 	    /* !SVG_H_ */
