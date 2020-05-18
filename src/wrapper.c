/* wrapper.c -- Copyright (c) 2020 J. M. Spivey */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int xmain(int argc, char **argv);

int main(int argc, char **argv) {
     char **args;

     if (argc > 2 && strcmp(argv[2], "--help") == 0) {
          fprintf(stderr, "Help is at hand\n");
          exit(1);
     }

     args = calloc(argc+2, sizeof(char *));
     args[0] = argv[0];
     args[1] = "./xml2pmx.x";
     for (int i = 1; i < argc; i++)
          args[i+1] = argv[i];
     args[argc+1] = NULL;
     return xmain(argc+1, args);
}
    
