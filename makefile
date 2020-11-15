CXX = g++ -std=c++11 -pedantic -Wall -Wextra -g

Circle.o: Circle.cpp Circle.h
	$(CXX) -c $< -o $@

clean:
	rm *.o *.exe