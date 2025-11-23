Tum: baglama calistirma


derleme:
	g++ -c -I "./include"  ./src/dugum.cpp -o ./lib/dugum.o
	g++ -c -I "./include"  ./src/basamak.cpp -o ./lib/basamak.o
	g++ -c -I "./include"  ./src/sayi.cpp -o ./lib/sayi.o
	g++ -c -I "./include"  ./src/sayilarListesi.cpp -o ./lib/sayilarListesi.o
	g++ -c -I "./include"  ./src/main.cpp -o ./lib/main.o

baglama: derleme
	g++ ./lib/main.o ./lib/sayi.o ./lib/dugum.o ./lib/sayilarListesi.o ./lib/basamak.o -o ./bin/program


calistirma:
	./bin/program