all: derle bagla calistir

derle:
	g++ -c -I"./include" src/main.cpp -o lib/main.o
	g++ -c -I"./include" src/Screen.cpp -o lib/Screen.o
	g++ -c -I"./include" src/Shape.cpp -o lib/Shape.o
	g++ -c -I"./include" src/Triangle.cpp -o lib/Triangle.o
	g++ -c -I"./include" src/Rectangle.cpp -o lib/Rectangle.o
	g++ -c -I"./include" src/Star.cpp -o lib/Star.o
	g++ -c -I"./include" src/ShapeNode.cpp -o lib/ShapeNode.o
	g++ -c -I"./include" src/ShapeList.cpp -o lib/ShapeList.o
	g++ -c -I"./include" src/MainNode.cpp -o lib/MainNode.o
	g++ -c -I"./include" src/MainList.cpp -o lib/MainList.o
	g++ -c -I"./include" src/FileManager.cpp -o lib/FileManager.o
	g++ -c -I"./include" src/RandomUtil.cpp -o lib/RandomUtil.o
	g++ -c -I"./include" src/ClampUtil.cpp -o lib/ClampUtil.o
	g++ -c -I"./include" src/ProgramManager.cpp -o lib/ProgramManager.o

bagla:
	g++ lib/main.o lib/Screen.o lib/Shape.o lib/Triangle.o lib/Rectangle.o lib/Star.o lib/ShapeNode.o lib/ShapeList.o lib/MainNode.o lib/MainList.o lib/FileManager.o lib/RandomUtil.o lib/ClampUtil.o lib/ProgramManager.o -o bin/program

calistir:
	bin/program