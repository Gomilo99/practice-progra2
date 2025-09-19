CXX = g++
CXXFLAGS = -Wall -g -Ilib # Añade -std=c++11 si usas características de C++11
TARGET = ejecutable
SOURCES = main.cpp #lista.cpp nodo.cpp
HEADERS = $(wildcard lib/*.hpp)
OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)
	./$(TARGET)

main.o: main.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c main.cpp

clean:
	rm -f $(TARGET) $(OBJECTS)