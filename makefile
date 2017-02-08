exec: drawer.o parser.o predictor.o driver.o
	g++ -o exec drawer.o parser.o predictor.o driver.o `pkg-config opencv --cflags --libs`

drawer.o: commondefs.hpp drawer.cpp drawer.hpp
	g++ -c drawer.cpp

parser.o: commondefs.hpp parser.cpp parser.hpp
	g++ -c parser.cpp

predictor.hpp: commondefs.hpp drawer.hpp parser.hpp

predictor.o: predictor.cpp predictor.hpp
	g++ -c predictor.cpp

driver.o: driver.cpp predictor.hpp
		g++ -c driver.cpp
clean:
	@rm -f *.o
	@rm -f exec
