CXXFLAGS += -std=c++03 -Wpedantic -Wall -Wextra -O2 -I../build/headers/
LDFLAGS += -L../build/libraries/anna/graphics -lAnnaGraphics -lX11 -lGL -pthread

main: main.o
	$(CXX) $(CXXFLAGS) -o main main.o $(LDFLAGS)

clean:
	find . -name "*.o" -type f -delete
