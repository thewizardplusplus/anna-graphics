OBJECTS = source/main.o
CXXFLAGS += -std=c++03 -Wpedantic -Wall -Wextra -O2
LDFLAGS += -lAnnaGraphics -lX11 -lGL -pthread

.PHONY: clean

main: $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o main $(OBJECTS) $(LDFLAGS)

clean:
	find . -name "*.o" -type f -delete
