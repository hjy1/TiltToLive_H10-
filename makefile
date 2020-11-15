CXX = g++ -std=c++11 -pedantic -Wall -Wextra -g

GameEngine.o: GameEngine.cpp GameEngine.h Redpoint.h Arrow.h
	$(CXX) -c $< -o $@

Redpoint.o: Redpoint.cpp Object.h Constants.h
	$(CXX) -c $< -o $@

Object.o: Object.cpp Object.h Constants.h
	$(CXX) -c $< -o $@

Circle.o: Circle.cpp Circle.h
	$(CXX) -c $< -o $@

Vector.o: Vector.cpp Vector.h
	$(CXX) -c $< -o $@

clean:
	rm *.o *.exe