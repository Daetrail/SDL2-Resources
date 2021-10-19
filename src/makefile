# For temporary use only. I am probably going to upgrade this into a CMakeLists.txt file

# Change debug/release to debug/release for whichever one you need
type = debug

main: main.o renderwindow.o entity.o util.o
	g++ ../bin/$(type)/*.o -I ../include/ -m64 -Wall -O3 -o ../bin/$(type)/main -lSDL2main -lSDL2 -lSDL2_image

main.o: main.cpp
	g++ -c main.cpp -o ../bin/$(type)/main.o -I ../include/

renderwindow.o: renderwindow.cpp
	g++ -c renderwindow.cpp -o ../bin/$(type)/renderwindow.o -I ../include/ -I ../include/SDL2

entity.o: entity.cpp
	g++ -c entity.cpp -o ../bin/$(type)/entity.o -I ../include/ -I ../include/SDL2

util.o: util.cpp
	g++ -c util.cpp -o ../bin/$(type)/util.o -I ../include/ -I ../include/SDL2

clean:
	rm ../bin/$(type)/*.o ../bin/$(type)/main -I ../include/ -I ../include/SDL2