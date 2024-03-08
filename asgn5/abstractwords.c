#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include <string.h>

void * abstractwords(int iters, void *ds, void (*dsdo)(void *, char *, int))
{
    ssize_t read;
    char *line = NULL;
    size_t len = 0;
    int i = 0;

    for (int times=0; times < iters; times++) {
        FILE *fp = fopen("/usr/share/dict/words", "r");
        if (fp == NULL) {
            perror("no dictionary file\n");
	    return NULL;
        }
        while ((read = getline(&line, &len, fp)) != -1) {
            line[read-1] = '\0';
	    //adding each i to ds, which is l
        dsdo(ds, line, i);
	    i++;
        }
	fclose(fp);
    }

    free(line);
    return ds;
}
