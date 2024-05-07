CC=gcc
#CFLAGS= -Wall -Wextra -Werror -g -ansi #-O3
CFLAGS= -Wall -Wextra -g #-ansi #-O3
LIBS=

.c.o:
	$(CC) $(CFLAGS) -c $<

PRG=geometry

OBJ=$(PRG).o

all: $(OBJ)
	$(CC) $(OBJ) $(LIBS) -o $(PRG)
	
$(OBJ): $(PRG).c

clean:
	@rm *.o || true
	@rm *.*~ || true
	@rm *.~ || true
	@rm *~ || true

clean_all:
	@rm *.o $(PRG) || true
	@rm *.*~ || true
	@rm *.~ || true
	@rm *~ || true
