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
//#include "pixel.h"
//#include "line.h"
//#include "circle.h"
#include "one_color_filled_square.h"
#include "empty_square.h"
#include "empty_poly.h"
#include "empty_circle.h"


/******* Variables *******/
struct framebuffer fb;
struct pixel p;

int i;                            /* Some index. */
int rc;                           /* Return code to simplify tuto. */
int ch;                           /* a key pressed. */


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


int main()
{
  /* Functions array to display some geometry. */
  typedef void (*fptr)(void);
  fptr geom_funcaddr[] = {
    one_color_filled_square,
    one_color_filled_rectangle,
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
    perror("/dev/fb0 can't be mapped");
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

  fb.dbp = calloc(fb.screensize, sizeof(char));
  if (fb.dbp == NULL)
  {
    perror("Double buffer allocation error");
  
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
    perror("Fail to map /dev/fb0 to vRAM");
    exit(4);
  }

  /* Display all examples. */ 
  for (i = 0; i < (int)(sizeof(geom_funcaddr) / sizeof(void*)); i++)
  {

    /* Clear screen. */
    //memset(fb.fbp, 0, fb.screensize);
    memset(fb.dbp, 0, fb.screensize);

    /* Print something on screen according. */
    geom_funcaddr[i]();

    memcpy(fb.fbp, fb.dbp, fb.screensize);

    printf("\nESC to continue\n\n");
    while((ch = getchar()) != 27 ) /* ascii ESC. */
    {
        /* Just wait a ESC-presskey. */
    }
  }

  /* Close memory mapped and file descriptor. */
  free(fb.dbp);
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
