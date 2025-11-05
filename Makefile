CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic
TARGET = calculator
OBJECTS = main.o calculator.o

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

main.o: main.cpp calculator.h
	$(CXX) $(CXXFLAGS) -c main.cpp

calculator.o: calculator.cpp calculator.h
	$(CXX) $(CXXFLAGS) -c calculator.cpp

clean:
	rm -f $(OBJECTS) $(TARGET)

run: $(TARGET)
	./$(TARGET) input.txt

.PHONY: all clean run