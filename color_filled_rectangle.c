#include <stdlib.h>
#include <stdio.h>
#include <linux/fb.h>

#include "fb_design.h"
#include "pixel.h"
#include "lines.h"
#include "color_filled_rectangle.h"


/******* Variables *******/
extern struct framebuffer fb;   /* see fb_design.h */
extern struct pixel p;


void color_filled_rectangle_t1()
{
  struct Coords {
    int x0, y0;
    int x1, y1;
  } coords;

  struct Coords squares[] = {
    {-10, -10, fb.vinfo.xres / 2, fb.vinfo.yres / 2},
    {fb.vinfo.xres / 2 + 5, fb.vinfo.yres / 2 - 4, fb.vinfo.xres + 10, fb.vinfo.yres / 2 - 4},
    {fb.vinfo.xres / 2 - 5, fb.vinfo.yres / 2 + 10, fb.vinfo.xres + 10, fb.vinfo.yres + 10},
    {fb.vinfo.xres / 2 - 10, fb.vinfo.yres + 10, - 2, fb.vinfo.yres / 2 + 10} /* Should NOT be displayed */
  };

  unsigned int i;      /* index of squares to read. */


  printf("Running one_color_filled_square()\n");

  p.r = 0xff;
  p.g = 0xee;
  p.b = 0xdd;
  p.a = 0;

  for (i = 0; i < (int)(sizeof(squares) / sizeof(coords)); i++)
  {
    for (p.y = squares[i].y0; p.y <= squares[i].y1; p.y++)
    {
      for (p.x = squares[i].x0; p.x < squares[i].x1; p.x++)
      {
        putpixel(fb, p);
      }
    }
  }

  //printf("Final pxloffset = %ld\n", fb.pxloffset);
  printf("/dev/fb0 has been painted successfully.\n\n");
}

void color_filled_rectangle_t2()
{
  struct Coords {
    int x0, y0;
    int x1, y1;
  } coords;

  struct Coords squares[] = {
    {-10, -10, fb.vinfo.xres / 2, fb.vinfo.yres / 2},
    {fb.vinfo.xres / 2 + 5, fb.vinfo.yres / 2 - 4, fb.vinfo.xres + 10, fb.vinfo.yres / 2 - 4},
    {fb.vinfo.xres / 2 - 5, fb.vinfo.yres / 2 + 10, fb.vinfo.xres + 10, fb.vinfo.yres + 10},
    {fb.vinfo.xres / 2 - 10, fb.vinfo.yres + 10, - 2, fb.vinfo.yres / 2 + 10}
  };

  unsigned int i;       /* index of squares to read. */
  int y0, y1;           /* To check if y0 < y1 or not */ 

  printf("Running one_color_filled_rectangle()\n");

  /* Don't really need, but struct p is already declared */
  p.r = 0xdd;
  p.g = 0xee;
  p.b = 0xff;
  p.a = 0;

  for (i = 0; i < (int)(sizeof(squares) / sizeof(coords)); i++)
  {
    y0 = squares[i].y0 < squares[i].y1 ? squares[i].y0 : squares[i].y1; /* Which is the the 1st ? */
    y1 = squares[i].y0 < squares[i].y1 ? squares[i].y1 : squares[i].y0; /* Which is the the 2nd ? */

    for (; y0 <= y1; y0++)
    {
      hline(squares[i].x0, squares[i].x1, y0, p.r, p.g, p.b, p.a);
    }
  }

  //printf("Final pxloffset = %ld\n", fb.pxloffset);
  printf("/dev/fb0 has been painted successfully.\n\n");
}
