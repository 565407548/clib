cc=gcc
cflags= -g -I./include

obj=obj/zcj_util.o obj/zcj_disjointSets.o obj/zcj_stack.o obj/zcj_queue.o obj/zcj_tree.o obj/zcj_list.o obj/zcj_graph.o obj/zcj_heapSort.o

bin=bin/test_disjointSets bin/test_stack bin/test_queue bin/test_tree bin/test_list bin/test_graph bin/test_heapSort bin/test_jumpHorse

hfile=include/zcj_const.h include/zcj_disjointSets.h include/zcj_graph.h include/zcj_list.h include/zcj_stack.h include/zcj_tree.h include/zcj_type.h include/zcj_util.h

libfile=lib/libzcj.a lib/libzcj.so 

image:$(libfile) $(bin)

install:
	sudo cp $(hfile) /usr/include/zcj
	sudo cp $(libfile) /usr/lib/zcj
	sudo ldconfig
clear:
	-rm $(bin) $(obj)

obj/zcj_util.o:src/zcj_util.c
	cc $(cflags) -c -o $@ $<
obj/zcj_disjointSets.o:src/zcj_disjointSets.c include/zcj_disjointSets.h
	cc $(cflags) -c -o $@ $<
obj/zcj_stack.o:src/zcj_stack.c include/zcj_stack.h
	cc $(cflags) -c -o $@ $<
obj/zcj_queue.o:src/zcj_queue.c include/zcj_queue.h
	cc $(cflags) -c -o $@ $<
obj/zcj_tree.o:src/zcj_tree.c include/zcj_tree.h
	cc $(cflags) -c -o $@ $<
obj/zcj_list.o:src/zcj_list.c include/zcj_list.h
	cc $(cflags) -c -o $@ $<
obj/zcj_graph.o:src/zcj_graph.c include/zcj_graph.h
	cc $(cflags) -c -o $@ $<
obj/zcj_heapSort.o:src/zcj_heapSort.c include/zcj_heapSort.h
	cc $(cflags) -c -o $@ $<

lib/libzcj.a:$(obj)
	ar rcs $@ $(obj)

lib/libzcj.so:
	gcc -shared -o $@ $(obj)

bin/test_disjointSets:src/test_disjointSets.c $(obj)
	cc $(cflags) -o $@ $< $(obj)
bin/test_stack:src/test_stack.c $(obj)
	cc $(cflags) -o $@ $< $(obj)
bin/test_queue:src/test_queue.c $(obj)
	cc $(cflags) -o $@ $< $(obj)
bin/test_tree:src/test_tree.c $(obj)
	cc $(cflags) -o $@ $< $(obj)
bin/test_list:src/test_list.c $(obj)
	cc $(cflags) -o $@ $< $(obj)
bin/test_graph:src/test_graph.c $(obj)
	cc $(cflags) -o $@ $< $(obj)
bin/test_heapSort:src/test_heapSort.c $(obj)
	cc $(cflags) -o $@ $< $(obj)
bin/test_jumpHorse:src/test_jumpHorse.c $(obj)
	cc $(cflags) -o $@ $< $(obj)
