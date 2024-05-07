/* 
  Put pixel in framebuffer fb, 
  at position (p.x; p.y), 
  with RGB-Alpha color p.r, p.g, p.b, p.a
*/

#ifndef _PIXEL_H
#define _PIXEL_H

void putpixel(struct framebuffer fb, struct pixel p);

#endif