all: assign1.out

assign1.out: assign1.o
	 gcc -o assign1.out assign1.o

assign1.o: assign1.c
	 gcc -c assign1.c
     
clean:
	 rm assign1.o assign1.out
