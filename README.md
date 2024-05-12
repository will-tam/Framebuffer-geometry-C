# Framebuffer colored clock (C version)

Just a drawing test directly on the Linux framebuffer.

## The best way to test :
- Create a Linux virtual machine (VM).
- In console mode:
  - Check and configure network between VM and your physical machine (PM).
  - install, configure and run the ssh server.
  - Log off or not, but the VM still active.
- Open a terminal on your PM.
  - Open a ssh connection with the VM.
  - Install and configure the C development kit (gcc + make + lib in debug/dev).
  - Install git.
  - Clone this repository.
  - Go to the newly created directory.
  - Just type ```make```.
  - If all is ok, the VM console shows you nice arts, while the ssh terminal shows some information.

Of course, you can try directly in your PM (in TTY1 for example - CTRL-ALT-F1 if you use X interface). 
**BUT if something wrong, prepare to reboot your PM**.

## Great thanks to
- **Framebuffer** :
  - [https://github.com/roddehugo/linuxfb?tab=readme-ov-file](https://github.com/roddehugo/linuxfb?tab=readme-ov-file)
  - [https://wiki.osdev.org/Drawing_In_a_Linear_Framebuffer](https://wiki.osdev.org/Drawing_In_a_Linear_Framebuffer)
  - [https://github.com/DirectFB/directfb/tree/master/systems/fbdev](https://github.com/DirectFB/directfb/tree/master/systems/fbdev)

- **Key events** :
  - [https://stackoverflow.com/questions/21091191/implementing-a-keypress-event-in-c](https://stackoverflow.com/questions/21091191/implementing-a-keypress-event-in-c)
  - [https://rosettacode.org/wiki/Keyboard_input/Keypress_check#C](https://rosettacode.org/wiki/Keyboard_input/Keypress_check#C)

- **Calling functions in an array** :
  - [https://stackoverflow.com/questions/1952175/how-can-i-call-a-function-using-a-function-pointer](https://stackoverflow.com/questions/1952175/how-can-i-call-a-function-using-a-function-pointer)

- **Line and circle algorithmes** :
  - [https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm](https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm)
  - [https://fr.wikipedia.org/wiki/Algorithme_de_trac%C3%A9_de_cercle_d'Andres](https://fr.wikipedia.org/wiki/Algorithme_de_trac%C3%A9_de_cercle_d'Andres)
  - [https://gist.github.com/bert/1085538](https://gist.github.com/bert/1085538)


# ENJOY