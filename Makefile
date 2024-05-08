CC=gcc

#CFLAGS= -Wall -Wextra -Werror -g -ansi #-O3
CFLAGS= -Wall -Wextra -g #-ansi #-O3
#CFLAGS= -Wall -Wextra -g -O3
LDFLAGS=

TOBUILD=geometry

SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)

all: $(TOBUILD)

$(TOBUILD): $(OBJ)
	@$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	@$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean clean_all

clean:
	@rm *.o || true
	@rm *.*~ || true
	@rm *.~ || true
	@rm *~ || true

clean_all:
	@rm *.o $(TOBUILD) || true
	@rm *.*~ || true
	@rm *.~ || true
	@rm *~ || true
