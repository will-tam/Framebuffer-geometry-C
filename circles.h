#ifndef _CIRCLE_H
#define _CIRCLE_H

/* 
  Draw circle from at center (xc; yc) with some radius, 
  with RGB-Alpha color r, g, b, and alpha.
*/
void circle(int xc, int yc, int radius,
            unsigned int r, unsigned int g, unsigned int b, unsigned int alpha);

/* 
  Draw filled circle from at center (xc; yc) with some radius, 
  with RGB-Alpha color r, g, b, and alpha.
*/
void circlef(int xc, int yc, int radius,
            unsigned int r, unsigned int g, unsigned int b, unsigned int alpha);

#endif