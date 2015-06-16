CFLAGS=-I./tlib -I./src/

pucpeopple:
	gcc `pkg-config --cflags --libs gtk+-3.0` -o main \
  tlib/*.c src/*.c \
	main.c \
	$(CFLAGS)
