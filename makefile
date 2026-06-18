IDIR = include
SDIR = src
ODIR = obj

CC=gcc
CFLAGS=-I $(IDIR) -Wall -Wextra -O2

_DEPS = calcMedia.h calculation.h list.h utils.h storage.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = calcMedia.o calculation.o list.o utils.o storage.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


calc: $(OBJ)
	$(CC) -o $@ $^ 

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	@mkdir -p $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean

clean: 
	rm -rf $(ODIR)/*.o calc *~ core
