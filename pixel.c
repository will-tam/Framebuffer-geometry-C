#include <linux/fb.h>

#include "fb_design.h"
#include "pixel.h"

void putpixel(struct framebuffer fb, struct pixel p)
{
  if (((p.x >= 0) && 
       (p.y >= 0)) &&   
     (((unsigned int)p.x <= fb.vinfo.xres - 1) && 
      ((unsigned int)p.y <= fb.vinfo.yres - 1)))      /* Everybody inside the display. */
  {
    fb.pxloffset = (p.x + fb.vinfo.xoffset) * (fb.vinfo.bits_per_pixel >> 3) + ((p.y + fb.vinfo.yoffset) * fb.finfo.line_length);

    if (fb.vinfo.bits_per_pixel == 32)
    {
      *(fb.fbp + fb.pxloffset) = p.b;
      *(fb.fbp + fb.pxloffset + 1) = p.g;
      *(fb.fbp + fb.pxloffset + 2) = p.r;
      *(fb.fbp + fb.pxloffset + 3) = p.a;
    }
    else  /* Assume 16 bpp - Never tried. */
    {
      fb.p = p.r<<11 | p.g << 5 | p.b;
      *((unsigned short int*)(fb.fbp + fb.pxloffset)) = fb.p;
    }
  }
}
