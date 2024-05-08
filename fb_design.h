/*
  Gloabl structures.
*/

#ifndef _FB_DESIGN_H
#define _FB_DESIGN_H

struct framebuffer {
  int fbfd;                         /* Framebuffer file descriptor. */
  long int screensize;              /* Figure out the size of screen in bytes. */

  char *fbp;                        /* Framebuffer pointer in vRAM. */
  char *dbp;                        /* Double buffer pointer. */

  unsigned short int p16;           /* Pixel in 16 bpp mode. */
  long int pxloffset;               /* Real offset of pixel in vRAM. */
  struct fb_var_screeninfo vinfo;   /* Framebuffer variable video information. */
  struct fb_fix_screeninfo finfo;   /* Framebuffer fixed video information. */
};

struct pixel {                      /* Structure for 1 pixel. */
  int x, y;                         /* Pixel (x,y). */  
  unsigned int r, g, b, a;          /* Pixel color in RGB-Alpha mode (Alpha = 0 => none). */
};

#endif