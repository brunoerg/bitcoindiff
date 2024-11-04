all: module.a

CXXFLAGS += -Wall -Wextra -std=c++20 -I ../../include

# Add cleanse.o to module.a
module.a: module.o cleanse.o
	ar rcs module.a module.o cleanse.o
	ranlib module.a

module.o: module.cpp module.h
	$(CXX) $(CXXFLAGS) -I . -fPIC -c module.cpp -o module.o

# Compile cleanse.o if support/cleanse.cpp exists
cleanse.o: support/cleanse.cpp
	$(CXX) $(CXXFLAGS) -I . -fPIC -c support/cleanse.cpp -o cleanse.o

clean:
	rm -rf *.o module.a