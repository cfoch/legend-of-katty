CFLAGS=-I./tlib -I./src/

pucpeopple:
	gcc -o main \
  tlib/*.c src/*.c \
	main.c \
	$(CFLAGS)
