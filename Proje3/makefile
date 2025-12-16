all: derle bagla calistir

derle:
	g++ -c -I "./include" ./src/TreeNode.cpp -o ./lib/TreeNode.o
	g++ -c -I "./include" ./src/BinarySearchTree.cpp -o ./lib/BinarySearchTree.o
	g++ -c -I "./include" ./src/Hexagon.cpp -o ./lib/Hexagon.o
	g++ -c -I "./include" ./src/CircularHexagonList.cpp -o ./lib/CircularHexagonList.o
	g++ -c -I "./include" ./src/ConsolePrinter.cpp -o ./lib/ConsolePrinter.o
	g++ -c -I "./include" ./src/NodeStack.cpp -o ./lib/NodeStack.o
	g++ -c -I "./include" ./src/FileHandler.cpp -o ./lib/FileHandler.o
	g++ -c -I "./include" ./src/SimulationManager.cpp -o ./lib/SimulationManager.o
	g++ -c -I "./include" ./src/main.cpp -o ./lib/main.o

bagla:
	g++ ./lib/TreeNode.o ./lib/BinarySearchTree.o ./lib/Hexagon.o ./lib/CircularHexagonList.o ./lib/ConsolePrinter.o ./lib/NodeStack.o ./lib/FileHandler.o ./lib/SimulationManager.o ./lib/main.o -o ./bin/program

calistir:
	./bin/program
	