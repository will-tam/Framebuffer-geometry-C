#ifndef _PIXEL_H
#define _PIXEL_H

/* 
  Put pixel in framebuffer fb, 
  at position (p.x; p.y), 
  with RGB-Alpha color p.r, p.g, p.b, p.a

  struct : see fb_design.h
*/
void putpixel(struct framebuffer fb, struct pixel p);

#endif