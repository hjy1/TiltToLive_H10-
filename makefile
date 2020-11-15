CXX = g++ -std=c++11 -pedantic -Wall -Wextra -g

Circle.o: Circle.cpp Circle.h
	$(CXX) -c $< -o $@

Vector.o: Vector.cpp Vector.h
	$(CXX) -c $< -o $@

clean:
	rm *.o *.exe