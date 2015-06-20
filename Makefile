CFLAGS=-I./tlib -I./src/

pucpeopple:
	gcc `pkg-config --cflags --libs gtk+-3.0 clutter-1.0 clutter-gtk-1.0 gdk-pixbuf-2.0` -o main \
  tlib/*.c src/*.c \
	main.c \
	$(CFLAGS)
