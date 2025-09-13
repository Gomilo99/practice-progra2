SHELL = powershell.exe
CXX = g++
CXXFLAGS = -Wall -g -Ilib
TARGET = main
SOURCES = main.cpp
HEADERS = $(wildcard lib/*.hpp)
OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)
	Get-Content -Path bigInput.txt | .\$(TARGET) > salida.txt

main.o: main.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c main.cpp

clean:
	rm -f $(TARGET) $(OBJECTS)