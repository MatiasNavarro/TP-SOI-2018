#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define BUFFSIZE 256  //lo defino como una longitud arbitraria de longitudes de lineas de texto extraidas de archivos

void cabecera();
void printHostName();
void printFechaHora();
void matchear(char*, char*, char*);
