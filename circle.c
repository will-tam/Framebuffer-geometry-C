//#include <stdio.h>
//#include <stdlib.h>
#include <linux/fb.h>

#include "fb_design.h"
#include "pixel.h"
#include "circle.h"


/******* Variables *******/
extern struct framebuffer fb;
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
    p.x = xc - x;
    p.y = yc + y;
    putpixel(fb, p);
    p.x = xc + x;
    p.y = yc - y;
    putpixel(fb, p);
    p.x = xc - x;
    p.y = yc - y;
    putpixel(fb, p);
    p.x = xc + y;
    p.y = yc + x;
    putpixel(fb, p);
    p.x = xc - y;
    p.y = yc + x;
    putpixel(fb, p);
    p.x = xc + y;
    p.y = yc - x;
    putpixel(fb, p);
    p.x = xc - y;
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