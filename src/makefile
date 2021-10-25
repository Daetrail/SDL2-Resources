# For temporary use only. I am probably going to upgrade this into a CMakeLists.txt file

# Change debug/release to debug/release for whichever one you need
type = debug

main: main.o renderwindow.o entity.o util.o text.o menu.o animation.o sound.o music.o timer.o
	g++ ../bin/$(type)/*.o -I ../include/ -m64 -Wall -O3 -o ../main -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

main.o: main.cpp
	g++ -c main.cpp -o ../bin/$(type)/main.o -I ../include/

renderwindow.o: renderwindow.cpp
	g++ -c renderwindow.cpp -o ../bin/$(type)/renderwindow.o -I ../include/ -I ../include/SDL2

entity.o: entity.cpp
	g++ -c entity.cpp -o ../bin/$(type)/entity.o -I ../include/ -I ../include/SDL2

util.o: util.cpp
	g++ -c util.cpp -o ../bin/$(type)/util.o -I ../include/ -I ../include/SDL2

text.o: text.cpp
	g++ -c text.cpp -o ../bin/$(type)/text.o -I ../include/ -I ../include/SDL2

menu.o: menu.cpp
	g++ -c menu.cpp -o ../bin/$(type)/menu.o -I ../include/ -I ../include/SDL2

animation.o: animations.cpp
	g++ -c animations.cpp -o ../bin/$(type)/animations.o -I ../include/ -I ../include/SDL2

sound.o: sound.cpp
	g++ -c sound.cpp -o ../bin/$(type)/sound.o -I ../include/ -I ../include/SDL2
	
music.o: music.cpp
	g++ -c music.cpp -o ../bin/$(type)/music.o -I ../include/ -I ../include/SDL2

timer.o: timer.cpp
	g++ -c timer.cpp -o ../bin/$(type)/timer.o -I ../include/ -I ../include/SDL2

clean:
	rm ../bin/$(type)/*.o ../bin/$(type)/main