all: shop

shop: main.o SupportFunc.o 
	g++ -std=c++11 main.o SupportFunc.o -o shop

main.o: main.cpp
	g++ -std=c++11  main.cpp

SupportFunc.o: SupportFunc.h
	g++ -std=c++11  SupportFunc.cpp


clean:
	rm -rf *.o 