#include <stdio.h>
#include <linux/fb.h>

#include "fb_design.h"
#include "circles.h"
#include "empty_circle.h"


/******* Variables *******/
extern struct framebuffer fb;   /* see fb_design.h */
extern struct pixel p;


void empty_circle()
{ 
  struct Circle {
    int xc, yc;
    int radius;
  } c;

  struct Circle circles[] = {
    {fb.vinfo.xres / 2, fb.vinfo.yres / 2, 100},
    {10, 10, 10},
    {30, 50, 70},
    {fb.vinfo.xres - 20, fb.vinfo.yres - 20, 233}
  };

  int i;      /* index of circle to read. */

  printf("Running empty_circle()\n");

  for (i = 0; i < (int)(sizeof(circles) / sizeof(c)); i++)
  {
    circle(circles[i].xc, circles[i].yc, circles[i].radius, 255, 128, 0, 0);
  }
}
