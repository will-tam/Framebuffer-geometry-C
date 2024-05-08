#include <stdio.h>
#include <linux/fb.h>

#include "fb_design.h"
#include "pixel.h"

void putpixel(struct framebuffer fb, struct pixel p)
{
  if (((p.x >= 0) && 
       (p.y >= 0)) &&   
     (((unsigned int)p.x < fb.vinfo.xres) && 
      ((unsigned int)p.y < fb.vinfo.yres)))      /* Everybody inside the display. */
  {
    fb.pxloffset = (p.x + fb.vinfo.xoffset) * (fb.vinfo.bits_per_pixel >> 3) + 
                   ((p.y + fb.vinfo.yoffset) * fb.finfo.line_length);

    if (fb.vinfo.bits_per_pixel == 32) /* Using -O3 will optimize speed reducing asm */
    {
      *(fb.dbp + fb.pxloffset) = p.b;
      *(fb.dbp + fb.pxloffset + 1) = p.g;
      *(fb.dbp + fb.pxloffset + 2) = p.r;
      *(fb.dbp + fb.pxloffset + 3) = p.a;
    }
    else  /* Assume 16 bpp - Never tried. */
    {
      fb.p16 = p.r << 11 | p.g << 5 | p.b;
      *((unsigned short int*)(fb.dbp + fb.pxloffset)) = fb.p16;
    }
  }
}