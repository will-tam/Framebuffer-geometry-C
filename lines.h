#ifndef _LINE_H
#define _LINE_H

/*
  Draw line from (x0; y0) to (x1; y1), 
  with RGB-Alpha color r, g, b, and alpha.
*/
void line(int x0, int y0, int x1, int y1, 
          unsigned int r, unsigned int g, unsigned int b, unsigned int alpha);

/*
  Draw horizontal line from (x0; y) to (x1; y), 
  with RGB-Alpha color r, g, b, and alpha.
*/
void hline(int x0, int x1, int y, 
          unsigned int r, unsigned int g, unsigned int b, unsigned int alpha);

#endif