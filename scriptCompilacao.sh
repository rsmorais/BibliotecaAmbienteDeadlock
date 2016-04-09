#!/bin/bash
gcc -c deadlock.c -o deadlock.o ;
ar rcs libdeadlock.a deadlock.o;
nm -s --defined-only libdeadlock.a;
gcc exemp.c -L. libdeadlock.a -o exemp.bin -lpthread;