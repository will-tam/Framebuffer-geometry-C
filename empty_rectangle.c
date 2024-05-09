#include <stdio.h>
#include <linux/fb.h>

#include "fb_design.h"
#include "lines.h"
#include "empty_rectangle.h"


/******* Variables *******/
extern struct framebuffer fb;   /* see fb_design.h */
extern struct pixel p;


void empty_square()
{
  unsigned int x0, y0, x1, y1;
  
  printf("Running empty_square()\n");

  x0 = (fb.vinfo.xres / 2) + 100;
  y0 = (fb.vinfo.yres / 2) + 100;
  x1 = (fb.vinfo.xres / 2) - 100;
  y1 = (fb.vinfo.yres / 2) - 100;

  line(x0, y0, x1, y0, 255, 255, 255, 0);  
  line(x1, y1, x0, y1, 255, 255, 255, 0);  
  line(x0, y0, x0, y1, 255, 255, 255, 0);  
  line(x1, y1, x1, y0, 255, 255, 255, 0);
}
