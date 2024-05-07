/*
Thanks to 
- Framebuffer :
  - https://github.com/roddehugo/linuxfb?tab=readme-ov-file
  - https://wiki.osdev.org/Drawing_In_a_Linear_Framebuffer
  - https://github.com/DirectFB/directfb/tree/master/systems/fbdev

- Key events :
  - https://stackoverflow.com/questions/21091191/implementing-a-keypress-event-in-c
  - https://rosettacode.org/wiki/Keyboard_input/Keypress_check#C

- Calling functions in an array :
  - https://stackoverflow.com/questions/1952175/how-can-i-call-a-function-using-a-function-pointer

- Line and circle algorithmes :
  - https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
  - https://fr.wikipedia.org/wiki/Algorithme_de_trac%C3%A9_de_cercle_d'Andres
  - https://gist.github.com/bert/1085538

(c) GPL v3 - FREE to use or modify, but don't an IT manager-like, THANK back all of us.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>                /* General terminal interface: tcgetattr, tcsetattr, tcflush. */
#include <fcntl.h>
#include <unistd.h>                 /* Synchronous I/O multiplexing: select, FD_CLR, FD_ISSET, FD_SET, FD_ZERO. */
#include <linux/fb.h>
#include <sys/ioctl.h>
#include <sys/mman.h>

#include "fb_design.h"
#include "pixel.h"
#include "line.h"
#include "circle.h"
#include "one_color_filled_square.h"
/*
#include "empty_square.h"
#include "empty_poly.h"
#include "empty_circle.h"
*/


/******* Variables *******/
int i;                            /* Some index. */
int rc;                           /* Return code to simplify tuto. */
int ch;                           /* a key pressed. */

struct framebuffer fb;
struct pixel p;


/******* Functions *******/
void set_non_canonical_mode(int ncm)
{
  struct termios info;          /* Get and set  terminal attributes, line control, get and set baud rate. */

  if (ncm)
  {
    tcgetattr(0, &info);          /* Get current terminal attirbutes; 0 is the file descriptor for stdin. */
    info.c_lflag &= ~(ICANON|ECHO);      /* Disable canonical mode. */
    info.c_cc[VMIN] = 1;          /* Wait until at least one keystroke available. */
    info.c_cc[VTIME] = 0;         /* No timeout. */
    tcsetattr(0, TCSANOW, &info); /* Set immediately. */
  }
  else
  {
    tcgetattr(0, &info);
    info.c_lflag |= (ICANON|ECHO);
    tcsetattr(0, TCSANOW, &info);
  }
}

void empty_square()
{
  unsigned int x0, y0, x1, y1;
  
  printf("Running empty_square()\n");

  x0 = (fb.vinfo.xres / 2) + 100;
  y0 = (fb.vinfo.yres / 2) + 100;
  x1 = (fb.vinfo.xres / 2) - 100;
  y1 = (fb.vinfo.yres / 2) - 100;

  line(x0, y0, x1, y0, 255, 255, 255, 0);  
  line(x1, y1, x0, y1, 255, 255, 255, 0);  
  line(x0, y0, x0, y1, 255, 255, 255, 0);  
  line(x1, y1, x1, y0, 255, 255, 255, 0);
}

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

void empty_circle()
{ 
  struct Circle {
    int xc, yc;
    int radius;
  } c;

  struct Circle circles[] = {
    {fb.vinfo.xres / 2, fb.vinfo.yres / 2, 100},
    {10, 10, 10},
    {30, 50, 70},
    {fb.vinfo.xres - 20, fb.vinfo.yres - 20, 233}
  };

  int i;      /* index of circle to read. */

  printf("Running empty_circle()\n");

  for (i = 0; i < (int)(sizeof(circles) / sizeof(c)); i++)
  {
    circle(circles[i].xc, circles[i].yc, circles[i].radius, 255, 128, 0, 0);
  }
}


int main()
{
  /* Functions array to display some geometry. */
  typedef void (*fptr)(void);
  fptr geom_funcaddr[] = {
    one_color_filled_square,
    empty_square,
    empty_poly,
    empty_circle
  };    /* List of function drawing geometric fig one after one. */


  set_non_canonical_mode(1);      /* Prepare for C keypressed-like     set_non_canonical_mode(1);(). */

  for (i = 0; i < (int)(sizeof(geom_funcaddr) / sizeof(void*)); i++)
  {
    printf("%p\n",geom_funcaddr[i]);    
  }

  /* Open the fb devive file for R/W. */
  fb.fbfd = open("/dev/fb0", O_RDWR);    /* Ecpect the first FB is allowed. */

  if (fb.fbfd == -1)
  {
    perror("Fail to open /dev/fb0");
    exit(1);
  }
  printf("/dev/fb0 opened.\n");

  /* Get fixed informations about screen. */
  rc = ioctl(fb.fbfd, FBIOGET_FSCREENINFO, &fb.finfo);
  printf("\nioctl(fb.fbfd, FBIOGET_FSCREENINFO, &fb.finfo) rc = %d\n", rc);
  if (rc)
  {
    close(fb.fbfd);
    perror("Fail to read screen fixed informations");
    exit(2);
  }

  /* Get variable informations about screen. */
  rc = ioctl(fb.fbfd, FBIOGET_VSCREENINFO, &fb.vinfo);
  printf("\nioctl(fb.fbfd, FBIOGET_VSCREENINFO, &fb.vinfo) rc = %d\n", rc);
  if (rc)
  {
    close(fb.fbfd);
    perror("Fail to read screen variable informations");
    exit(3);
  }

  fb.screensize = fb.vinfo.xres_virtual * fb.vinfo.yres * fb.vinfo.bits_per_pixel >> 3;

  printf("(x; y) res = %d X %d, %d bpp\n", fb.vinfo.xres, fb.vinfo.yres, fb.vinfo.bits_per_pixel);
  printf("(x; y) virtual res = %d X %d, %d bpp\n", fb.vinfo.xres_virtual, fb.vinfo.yres_virtual, fb.vinfo.bits_per_pixel);
  printf("screensize = %ld\n", fb.screensize);
  printf("line_length = %d\n", fb.finfo.line_length);
  printf("rotate = %d\n", fb.vinfo.rotate);
  printf("activate = %d\n", fb.vinfo.activate);

  /* Map /dev/fb0 to vRAM. */
  fb.fbp = (char *) mmap(0, fb.screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fb.fbfd, 0);
  if ((long) fb.fbp == -1)
  {
    rc = close(fb.fbfd);
    if (rc == -1)
    {
      perror("Coundn't close /dev/fb0");
    }
    else
    {
      printf("/dev/fb0 closed\n");
    }
    perror("Fail to map /dev/fb0 to vRAM");
    exit(4);
  }
  printf("/dev/fb0 is mapped to vRAM\n\n");

  /* Display all examples. */ 
  for (i = 0; i < (int)(sizeof(geom_funcaddr) / sizeof(void*)); i++)
  {

    /* Clear screen. */
    memset(fb.fbp, 0, fb.screensize);

    /* Print something on screen according. */
    geom_funcaddr[i]();


    printf("\nESC to continue\n\n");
    while((ch = getchar()) != 27 ) /* ascii ESC. */
    {
        /* Just wait a ESC-presskey. */
    }
  }

  /* Close memory mapped and file descriptor. */
  munmap(fb.fbp, fb.screensize);

  rc = close(fb.fbfd);
  if (rc == -1)
  {
    perror("Coundn't close /dev/fb0");
  }
  else
  {
    printf("/dev/fb0 closed\n");
  }

  set_non_canonical_mode(0);    /* Return normal mode for terminal echo. */

  return 0;
}
