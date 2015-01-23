# build an executable named index from index.c
all: index
index: index.c
	gcc `pkg-config --cflags --libs glib-2.0` -lpthread -o index index.c
clean:
	$(RM) index