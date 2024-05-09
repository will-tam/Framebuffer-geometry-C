#include <stdlib.h>
#include <linux/fb.h>

#include "fb_design.h"
#include "pixel.h"
#include "lines.h"


/******* Variables *******/
extern struct framebuffer fb;   /* see fb_design.h */
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

void hline(int x0, int x1, int y, 
          unsigned int r, unsigned int g, unsigned int b, unsigned int alpha)
{
  int d;  /* Distance between x0 and x1 */

/* Everybody inside the display. */
  if (y < 0) { y = 0; }
  if (x0 < 0) { x0 = 0; }
  if (x1 < 0) { x1 = 0; }
  if ((unsigned int)x0 > fb.vinfo.xres) { x0 = fb.vinfo.xres; }
  if ((unsigned int)x1 > fb.vinfo.xres) { x1 = fb.vinfo.xres; }
  if ((unsigned int)y > fb.vinfo.yres) { y = fb.vinfo.yres; }

  p.x = x0 < x1 ? x0 : x1;    /* Which is the the 1st ? */ 
  p.y = y;
  
  d = abs(x1 - x0);
  
  /* 1st offset */
  fb.pxloffset = (p.x + fb.vinfo.xoffset) * (fb.vinfo.bits_per_pixel >> 3) + 
                 ((p.y + fb.vinfo.yoffset) * fb.finfo.line_length);

  for (; d > 0; d--)
  {
    if (fb.vinfo.bits_per_pixel == 32)    /* Using -O3 will optimize speed reducing asm */
    {
      *(fb.dbp + fb.pxloffset) = b;
      *(fb.dbp + fb.pxloffset + 1) = g;
      *(fb.dbp + fb.pxloffset + 2) = r;
      *(fb.dbp + fb.pxloffset + 3) = alpha;
  
      fb.pxloffset = fb.pxloffset + 4;
    }
    else  /* Assume 16 bpp - Never tried. */
    {
      fb.p16 = p.r<<11 | p.g << 5 | p.b;
      *((unsigned short int*)(fb.dbp + fb.pxloffset)) = fb.p16;
      
      fb.pxloffset = fb.pxloffset + 1;
    }
  }


}