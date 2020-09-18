CC=gcc
FLAGS=-c -Wall -pedantic -O2

obj-m+=$(SRCDIR)/charEncryptor.o
obj-m+=$(SRCDIR)/charDesencryptor.o
 
all: kernel userInterface.o cppcheck

kernel:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) modules

userInterface.o: userInterface.c colores.h
	$(CC) $(FLAGS) $< -o $@
	$(CC) $@ -o userInterface

clean:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) clean
	rm userInterface
	rm -rf *o $(ODIR)/*.o userInterface $(LDIR)/*.gch err.txt $(LDIR)/builtins


