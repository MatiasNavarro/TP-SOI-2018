CC=gcc
FLAGS=-c -Wall -pedantic -O2

all: malloc cppcheck

malloc: main.o 
	gcc main.o -o malloc

main.o: main.c libreria.h
	$(CC) $(FLAGS) $< -o $@

cppcheck:
	@echo
	@echo Realizando verificacion CppCheck
	@echo Los resultados de la misma se encuentran en err.txt
	cppcheck . 2> err.txt

clean:
	@echo Borrando archivos objeto, codigo compilado y log de errores
	rm -rf *o $(ODIR)/*.o malloc $(LDIR)/*.gch err.txt
