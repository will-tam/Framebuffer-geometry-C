#include <linux/fb.h>

#include "fb_design.h"
#include "pixel.h"
#include "circles.h"
#include "lines.h"

/******* Variables *******/
extern struct framebuffer fb;   /* see fb_design.h */
extern struct pixel p;


void circle(int xc, int yc, int radius,
            unsigned int r, unsigned int g, unsigned int b, unsigned int alpha)
{
  int x, y;       /* (x,y) of the circle it-self. */
  int err;        /* Error beetween real circle and the pixel to draw it. */
	
  x = 0;
	y = radius;
	err = radius - 1;

  p.r = r;
  p.g = g;
  p.b = b;
  p.a = alpha;
	
	while (y >= x)
	{
		/* Drawing all 8 pixels present in circle by symmetric position. */
    p.x = xc + x;
    p.y = yc + y;
    putpixel(fb, p);
    p.y = yc - y;
    putpixel(fb, p);

    p.x = xc + y;
    p.y = yc - x;
    putpixel(fb, p);
    p.y = yc + x;
    putpixel(fb, p);

    p.x = xc - x;
    p.y = yc + y;
    putpixel(fb, p);
    p.y = yc - y;
    putpixel(fb, p);

    p.x = xc - y;
    p.y = yc + x;
    putpixel(fb, p);
    p.y = yc - x;
    putpixel(fb, p);

		/* Checking next (x, y) position to draw circle. */
		if (err >= (x << 1))
		{
			err = err - (x << 1) - 1;
			x++;
		}
		else if (err < ((radius - y) << 1))
		{
			err = err + (y << 1) - 1;
			y--;
		}
			else
			{
				err = err + ((y - x - 1) << 1);
				y--;
				x++;
			}
	}
}

void circlef(int xc, int yc, int radius,
            unsigned int r, unsigned int g, unsigned int b, unsigned int alpha)
{
  int x, y;       /* (x,y) of the circle it-self. */
  int err;        /* Error beetween real circle and the pixel to draw it. */
  int x0, x1, yl;  /* (x0,yl)-(x1,yl) horizontal line to paint. */

	
  x = 0;
	y = radius;
	err = radius - 1;

  while (y >= x)
	{
		/* Drawing only 4 areas to color circle by symmetric position. */
    
    x0 = xc - x;
    x1 = xc + x;
    yl = yc - y;
    hline(x0, x1, yl, r, g, b, alpha);

    yl = yc + y;
    hline(x0, x1, yl, r, g, b, alpha);

    x0 = xc - y;
    x1 = xc + y;
    yl = yc + x;
    hline(x0, x1, yl, r, g, b, alpha);

    yl = yc - x;
    hline(x0, x1, yl, r, g, b, alpha);

		/* Checking next (x, y) position to draw circle. */
		if (err >= (x << 1))
		{
			err = err - (x << 1) - 1;
			x++;
		}
		else if (err < ((radius - y) << 1))
		{
			err = err + (y << 1) - 1;
			y--;
		}
			else
			{
				err = err + ((y - x - 1) << 1);
				y--;
				x++;
			}
	}
}