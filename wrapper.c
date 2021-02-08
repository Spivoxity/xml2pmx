/* wrapper.c -- Copyright (c) 2020 J. M. Spivey */

#include "config.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#undef main

int xmain(int argc, char **argv);

int main(int argc, char **argv) {
     if (argc >= 2 && strcmp(argv[1], "--help") == 0) {
          fprintf(stderr, "Help is at hand!\n");
          exit(1);
     }

     if (argc >= 2 && strcmp(argv[1], "--version") == 0) {
          fprintf(stderr, "%s version %s\n",
                  PACKAGE_NAME, PACKAGE_VERSION);
          exit(1);
     }

     return xmain(argc, argv);
}
    
