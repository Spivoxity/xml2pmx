
#include "obx.h"
#include <ctype.h>
#include <math.h>

char *lib_version = 
  "Oxford Oberon-2 library version 3.1.0 [build 74f5d876f4d9+]";

void NEW(value *bp) {
     value *desc = valptr(bp[HEAD+0]);
     int size = bp[HEAD+1].i;
     ob_res.a = address(gc_alloc(desc, size, bp));
}

/*
Layout for flexible arrays:

	desc

q:	element 0
	...
	element n-1

desc:	map			desc = q + align(n*elsize)
	dim 1
        ...
	dim k

map:	-4
	desc-q
[	GC_REPEAT		if elmap != 0
	0
	n
	elsize
	GC_MAP
	elmap
	GC_END		]
	GC_END

size = align(n*elsize) + 4*k + 16 + (28 if elmap != 0)

Parameters NEWFLEX(elmap, elsize, k: INTEGER;
			dim_0, ..., dim_{k-1}: INTEGER): SYSTEM.PTR
*/

void NEWFLEX(value *bp) {
     value *elmap = valptr(bp[HEAD+0]);
     int elsize = bp[HEAD+1].i;
     int k = bp[HEAD+2].i;
     value *dim = &bp[HEAD+3];		/* Array of bounds */

     int size, arsize, i, n;
     value *q, *desc, *map;

     /* Compute no. of elements */
     n = 1;
     for (i = 0; i < k; i++) n *= dim[i].i;
     if (n < 0) liberror("allocating negative size");
     arsize = align(n * elsize, 4); 
     if (n == 0) elmap = NULL;

     /* Allocate the space */
     size = arsize + 4*k + 16;
     if (elmap != NULL) size += 28;

     q = (value * ) gc_alloc(NULL, size, bp);

     desc = q + arsize/4;
     map = desc + k + 1;
     q[-1].a = address(desc);

     /* Fill in the descriptor */
     desc[DESC_MAP].a = address(map);
     dim = &bp[HEAD+3];			/* In case our stack moved */
     for (i = 0; i < k; i++) desc[DESC_BOUND+i].i = dim[i].i;

     /* Fill in the map */
     map[0].i = -4;
     map[1].i = 4 * (desc-q);
     if (elmap == NULL)
          map[2].i = GC_END;
     else {
          map[2].i = GC_REPEAT;
	  map[3].i = 0;
	  map[4].i = n;
	  map[5].i = elsize;
	  map[6].i = GC_MAP;
	  map[7].a = address(elmap);
	  map[8].i = GC_END;
	  map[9].i = GC_END;
     }

     ob_res.a = address(q); 
}

void COMPARE(value *bp) {
     uchar *s1 = pointer(bp[HEAD+0]), *s2 = pointer(bp[HEAD+2]);
     int i = 0, n = min(bp[HEAD+1].i, bp[HEAD+3].i);

     while (i < n && s1[i] != '\0' && s1[i] == s2[i]) i++;
     if (i >= n) liberror("string is not null-terminated");
     ob_res.i = s1[i] - s2[i]; 
}

void COPY(value *bp) {
     obcopy((char * ) pointer(bp[HEAD+2]), bp[HEAD+3].i,
            (char * ) pointer(bp[HEAD+0]), bp[HEAD+1].i, bp);
}

void FLEXASSIGN(value *bp) {
     int size = bp[HEAD+0].i;
     int dim = bp[HEAD+1].i;
     uchar *src = pointer(bp[HEAD+2]), *dst = pointer(bp[HEAD+dim+3]);
     value *sbound = &bp[HEAD+3], *dbound = &bp[HEAD+dim+4];
     int i;

     for (i = 0; i < dim; i++) {
	  int sb = sbound[i].i, db = dbound[i].i;
	  if (sb > db || (i > 0 && sb < db)) 
	       liberror("bound mismatch in open array assignment");
	  size *= sb;
     }

     memmove(dst, src, size);
}

void sys_move(value *bp) {
     memmove(pointer(bp[HEAD+1]), pointer(bp[HEAD+0]), bp[HEAD+2].i);
}

void sys_liberror(value *bp) {
     value *bp1 = valptr(bp[BP]);
     error_stop((char * ) pointer(bp[HEAD+0]), 0, bp1, NULL);
}
