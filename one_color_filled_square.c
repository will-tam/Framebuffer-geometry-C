#include <stdio.h>
#include <linux/fb.h>

#include "fb_design.h"
#include "pixel.h"
#include "one_color_filled_square.h"


/******* Variables *******/
extern struct framebuffer fb;   /* see fb_design.h */
extern struct pixel p;


void one_color_filled_square()
{
  printf("Running one_color_filled_square()\n");
  for (p.y = 0; (unsigned int)p.y < fb.vinfo.yres / 2; p.y++)
  {
    for (p.x = 0; (unsigned int)p.x < fb.vinfo.xres / 2; p.x++)
    {
      p.r = 255;
      p.g = 255;
      p.b = 255;
      p.a = 0;
      putpixel(fb, p);
    }
  }

  printf("Final pxloffset = %ld\n", fb.pxloffset);
  printf("/dev/fb0 has been painted successfully.\n\n");
}