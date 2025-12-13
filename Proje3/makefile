all: derle bagla calistir

derle:
	g++ -c -I "./include" ./src/TreeNode.cpp -o ./lib/TreeNode.o
	g++ -c -I "./include" ./src/BinarySearchTree.cpp -o ./lib/BinarySearchTree.o
	g++ -c -I "./include" ./src/Hexagon.cpp -o ./lib/Hexagon.o
	g++ -c -I "./include" ./src/CircularHexagonList.cpp -o ./lib/CircularHexagonList.o
	g++ -c -I "./include" ./src/ConsolePrinter.cpp -o ./lib/ConsolePrinter.o
	g++ -c -I "./include" ./src/NodeStack.cpp -o ./lib/NodeStack.o

	g++ -c -I "./include" ./src/main.cpp -o ./lib/main.o

bagla:
	g++ ./lib/TreeNode.o ./lib/BinarySearchTree.o ./lib/Hexagon.o ./lib/CircularHexagonList.o ./lib/ConsolePrinter.o ./lib/NodeStack.o ./lib/main.o -o ./bin/program

calistir:
	./bin/program

# Test nesnesi
./lib/Test.o: ./src/Test.cpp
	g++ -c -I "./include" ./src/Test.cpp -o ./lib/Test.o

# Test programını bağla (main.o HARİÇ diğerleri ile)
test_bagla: ./lib/TreeNode.o ./lib/BinarySearchTree.o ./lib/Hexagon.o ./lib/CircularHexagonList.o ./lib/ConsolePrinter.o ./lib/NodeStack.o ./lib/Test.o
	g++ ./lib/TreeNode.o ./lib/BinarySearchTree.o ./lib/Hexagon.o ./lib/CircularHexagonList.o ./lib/ConsolePrinter.o ./lib/NodeStack.o ./lib/Test.o -o ./bin/test_program

# Testi çalıştır
test: derle ./lib/Test.o test_bagla
	./bin/test_program

# --- DEBUG DISTRIBUTION MODULU ---
./lib/DebugDistribution.o: ./src/DebugDistribution.cpp
	g++ -c -I "./include" ./src/DebugDistribution.cpp -o ./lib/DebugDistribution.o

debug_dagitim_bagla: ./lib/TreeNode.o ./lib/BinarySearchTree.o ./lib/Hexagon.o ./lib/CircularHexagonList.o ./lib/ConsolePrinter.o ./lib/NodeStack.o ./lib/DebugDistribution.o
	g++ ./lib/TreeNode.o ./lib/BinarySearchTree.o ./lib/Hexagon.o ./lib/CircularHexagonList.o ./lib/ConsolePrinter.o ./lib/NodeStack.o ./lib/DebugDistribution.o -o ./bin/debug_dagitim

debug_dagitim: derle ./lib/DebugDistribution.o debug_dagitim_bagla
	./bin/debug_dagitim

# --- DEBUG FULL GRID ---
./lib/DebugAllHexagons.o: ./src/DebugAllHexagons.cpp
	g++ -c -I "./include" ./src/DebugAllHexagons.cpp -o ./lib/DebugAllHexagons.o

debug_full_bagla: ./lib/TreeNode.o ./lib/BinarySearchTree.o ./lib/Hexagon.o ./lib/CircularHexagonList.o ./lib/ConsolePrinter.o ./lib/NodeStack.o ./lib/DebugAllHexagons.o
	g++ ./lib/TreeNode.o ./lib/BinarySearchTree.o ./lib/Hexagon.o ./lib/CircularHexagonList.o ./lib/ConsolePrinter.o ./lib/NodeStack.o ./lib/DebugAllHexagons.o -o ./bin/debug_full

# Çalıştırmak için: mingw32-make debug_full_run
debug_full_run: derle ./lib/DebugAllHexagons.o debug_full_bagla
	./bin/debug_full