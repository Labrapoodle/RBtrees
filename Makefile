CFLAGS = -Wall -Werror -Wextra
CPPFLAGS =  -MMD

.PHONY: all
all: RBTree

-include main.d rbtree.d

RBTree: main.o librbtree.a
	gcc  $(CFLAGS) $^ -o $@
	rm main.o;
	rm main.d;
	rm rbtree.o;
	rm rbtree.d ;

main.o: main.c
	gcc -c $(CFLAGS) $(CPPFLAGS) $< -o $@

librbtree.a: rbtree.o
	ar rcs $@ $^

rbtree.o: rbtree.c
	gcc -c $(FLAGS) $(CPPFLAGS) $< -o $@

.PHONY: clean
clean:
	rm main.o;
	rm main.d;
	rm rbtree.o;
	rm rbtree.d ;