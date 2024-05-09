#ifndef COLOR_FILLED_SQUARE_H
#define COLOR_FILLED_SQUARE_H

/*
  Just fill a full white rectangle,
  from point(0; 0) to point(fb.vinfo.xres / 2; fb.vinfo.yres / 2).
  First example to show how to display picture on FB.
*/

/* Type 1, by putpixel(). */
void color_filled_rectangle_t1();

/* Type 2, by hline(). */
void color_filled_rectangle_t2();

#endif