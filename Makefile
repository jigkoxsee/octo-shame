# build an executable named index from index.c
#index: index.c
#	gcc `pkg-config --cflags --libs glib-2.0` -lpthread -o index index.c
	#g++  -o index index.cpp
all: index
index: index.cpp
	g++ --std=c++11 -lpthread -o index index.cpp
clean:
	$(RM) index 
