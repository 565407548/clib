cc=gcc
cflags= -g -I./include

obj=obj/zcj_disjointSets.o obj/zcj_stack.o

bin=bin/test_disjointSets bin/test_stack

image:$(bin)

clear:
	-rm $(bin) $(obj)
obj/zcj_disjointSets.o:src/zcj_disjointSets.c include/zcj_disjointSets.h
	cc $(cflags) -c -o $@ $<
obj/zcj_stack.o:src/zcj_stack.c include/zcj_stack.h
	cc $(cflags) -c -o $@ $<

bin/test_disjointSets:src/test_disjointSets.c $(obj)
	cc $(cflags) -o $@ $< $(obj)
bin/test_stack:src/test_stack.c $(obj)
	cc $(cflags) -o $@ $< $(obj)
