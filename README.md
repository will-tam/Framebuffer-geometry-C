# Framebuffer Geometry (C version)

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

# ENJOY