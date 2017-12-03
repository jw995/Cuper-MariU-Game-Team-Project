CC = g++
CFLAGS = -std=c++11 -g -Wall -framework OpenGL -framework Cocoa
MKFLAGS = mkdir -p


All:  main.cpp 
	$(CC) -c fssimplewindowobjc.m
	$(CC) -c yssimplesound_macosx_objc.m
	$(CC) $(CFLAGS) -o product fssimplewindowcpp.cpp fssimplewindowobjc.o yspng.cpp main.cpp gamesetting.cpp Ground.cpp SteadyObjects.cpp Mario.cpp monster.cpp yssimplesound.cpp yssimplesound_macosx_cpp.cpp yssimplesound_macosx_objc.o
	$(MKFLAGS) product.app/Contents/MacOS
	mv product product.app/Contents/MacOS
	product.app/Contents/MacOS/product


clean:
	rm -f *.o 
	rm -rf *.dSYM
	(cd traces; rm -f *~)

