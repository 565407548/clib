cc=gcc
cflags= -g -I./include

obj=obj/zcj_disjointSets.o

bin=bin/test_disjointSets

image:$(bin)

obj/zcj_disjointSets.o:src/zcj_disjointSets.c include/zcj_disjointSets.h
	cc $(cflags) -c -o $@ $<

bin/test_disjointSets:src/test_disjointSets.c $(obj)
	cc $(cflags) -o $@ $< $(obj)
