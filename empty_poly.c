#include <stdio.h>
#include <linux/fb.h>

#include "fb_design.h"
#include "line.h"
#include "empty_poly.h"


/******* Variables *******/
extern struct framebuffer fb;   /* see fb_design.h */
extern struct pixel p;


void empty_poly()
{
  struct Coords {
    int x0, y0;
    int x1, y1;
  } coords;

  struct Coords polygone0[] = {
    {0, 0, 100, 50},
    {100, 50, 40, 100},
    {40, 100, 0, 0}
  };

  struct Coords polygone1[] = {
    {fb.vinfo.xres / 2 - 50, fb.vinfo.yres / 2 - 50, fb.vinfo.xres / 2, fb.vinfo.yres / 2 - 100},
    {fb.vinfo.xres / 2, fb.vinfo.yres / 2 - 100, fb.vinfo.xres / 2 + 50 , fb.vinfo.yres / 2 - 50},
    {fb.vinfo.xres / 2 + 50, fb.vinfo.yres / 2 - 50, fb.vinfo.xres / 2 + 50 , fb.vinfo.yres / 2 + 50},
    {fb.vinfo.xres / 2 + 50, fb.vinfo.yres / 2 + 50, fb.vinfo.xres / 2 - 50 , fb.vinfo.yres / 2 + 50},
    {fb.vinfo.xres / 2 - 50, fb.vinfo.yres / 2 + 50, fb.vinfo.xres / 2 - 50 , fb.vinfo.yres / 2 - 50},
  };

  struct Coords polygone2[] = {
    {111, 104, 120, 50},
    {120, 50, 216, 217},
    {216, 217, 172, 198},
    {172, 198, 148, 123},
    {148, 123, 312, 104},
    {312, 104, 111, 104},
  };

  struct Coords polygone3[] = {
    {-20, 513, 613, 528},
    {613, 528, 745, -50},
    {745, -50, fb.vinfo.xres + 10 , fb.vinfo.yres + 20},
    {fb.vinfo.xres + 10 , fb.vinfo.yres + 20, -20, 513},
    
  };

  struct Coords *polygones[] = {
    polygone0,
    polygone1,
    polygone2,
    polygone3
  };

  unsigned int polynbpts[] = {
    sizeof(polygone0) / sizeof(coords),
    sizeof(polygone1) / sizeof(coords),
    sizeof(polygone2) / sizeof(coords),
    sizeof(polygone3) / sizeof(coords)
  };

  unsigned int i, j;    /* i = index of point to read for the j-th polygon. */
  int x0, y0;           /* First point. */
  int x1, y1;           /* Last point. */
  
  printf("Running empty_poly()\n");

  for (j = 0; j < sizeof(polygones) / (sizeof(int*)); j++)
  {
    printf("%p ==> %d\n", polygones[j], polynbpts[j]);
    for (i = 0; i < polynbpts[j]; i++)
    {
      printf("(%d;%d)-(%d,%d) / ", polygones[j][i].x0, polygones[j][i].y0, polygones[j][i].x1, polygones[j][i].y1);
      x0 = polygones[j][i].x0;
      y0 = polygones[j][i].y0;
      x1 = polygones[j][i].x1;
      y1 = polygones[j][i].y1;
      line(x0, y0, x1, y1, 255, 255 * j * 9 / 10, 255 * j * 3 / 10, 0);
    }
    printf("\n\n");
  }
}