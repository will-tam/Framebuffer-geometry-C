//#include <stdio.h>
#include <stdlib.h>
#include <linux/fb.h>

#include "fb_design.h"
#include "pixel.h"
#include "line.h"


/******* Variables *******/
extern struct framebuffer fb;
extern struct pixel p;


void line(int x0, int y0, int x1, int y1, 
          unsigned int r, unsigned int g, unsigned int b, unsigned int alpha)
{  
  int dx;         /* diff beetween x coordinates. */
  int sx;         /* According the starting x, add or sub 1 to the next x. */
  int dy;         /* diff beetween y coordinates. */
  int sy;         /* According the starting y, add or sub 1 to the next y. */

  int err;        /* Error beetween real line and the pixel to draw it. */
  int e2;         /* err * 2. */
 
  dx = abs(x1 - x0);
  dy = -abs(y1 - y0);
  sx = x0 < x1 ? 1 : -1;
  sy = y0 < y1 ? 1 : -1;

  err = dx + dy;

  p.r = r;
  p.g = g;
  p.b = b;
  p.a = alpha;
  p.x = x0;
  p.y = y0;

  for (;;){

    putpixel(fb, p);

    if (p.x == x1 && p.y == y1) break;
    e2 = err + err;     /* Better add than mul, for only by 2 - also could use <<1. */
    if (e2 >= dy)       /* err * 2 + delta_x > 0. */
    { 
      err += dy;
      p.x += sx; 
    }
    if (e2 <= dx)       /* err * 2 + delta_y < 0. */
    {
      err += dx;
      p.y += sy;
    }
  }
}