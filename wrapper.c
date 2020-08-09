/* wrapper.c -- Copyright (c) 2020 J. M. Spivey */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int xmain(int argc, char **argv);

int main(int argc, char **argv) {
     if (argc > 2 && strcmp(argv[2], "--help") == 0) {
          fprintf(stderr, "Help is at hand!\n");
          exit(1);
     }

     return xmain(argc, argv);
}
    
