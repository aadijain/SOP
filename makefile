exec: drawer.o parser.o predictor.o driver.o
	g++ -o exec drawer.o parser.o predictor.o driver.o

drawer.o: commondefs.hpp drawer.cpp
	g++ -c drawer.cpp

parser.o: commondefs.hpp parser.cpp
	g++ -c parser.cpp

predictor.hpp: commondefs.hpp drawer.hpp parser.hpp

predictor.o: predictor.hpp
	g++ -c predictor.cpp

driver.o: predictor.hpp
		g++ -c driver.cpp

clean:
	@rm -f *.o
	@rm -f exec
