trajet: main.o Catalogue.o ComposedTrip.o List.o Node.o SimpleTrip.o Trip.o
	g++ -ansi -pedantic -Wall -std=c++11 -o trajet main.o Catalogue.o ComposedTrip.o List.o Node.o SimpleTrip.o Trip.o

main.o: Main.cpp
	g++ -ansi -pedantic -Wall -std=c++11 -o main.o -c main.cpp

Catalogue.o: Catalogue.cpp
	g++ -ansi -pedantic -Wall -std=c++11 -o Catalogue.o -c Catalogue.cpp

ComposedTrip.o: ComposedTrip.cpp
	g++ -ansi -pedantic -Wall -std=c++11 -o ComposedTrip.o -c ComposedTrip.cpp

List.o: List.cpp
	g++ -ansi -pedantic -Wall -std=c++11 -o List.o -c List.cpp

Node.o: Node.cpp
	g++ -ansi -pedantic -Wall -std=c++11 -o Node.o -c Node.cpp

SimpleTrip.o: SimpleTrip.cpp
	g++ -ansi -pedantic -Wall -std=c++11 -o SimpleTrip.o -c SimpleTrip.cpp

Trip.o: Trip.cpp
	g++ -ansi -pedantic -Wall -std=c++11 -o Trip.o -c Trip.cpp

clean:
	rm -f prog *.o 