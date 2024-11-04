all: bitcoinfuzz

CXXFLAGS += -fsanitize=address,fuzzer -Wall -Wextra -std=c++20 -I include -I . -DBITCOIN_CORE -DRUST_BITCOIN
MODULES := $(wildcard modules/*/module.a)

bitcoinfuzz: main.cpp driver.o include/bitcoinfuzz/basemodule.o
	$(CXX) $(CXXFLAGS) main.cpp $(MODULES) driver.o include/bitcoinfuzz/basemodule.o -o bitcoinfuzz

driver.o: driver.cpp driver.h
	$(CXX) $(CXXFLAGS) -c driver.cpp -o driver.o

include/bitcoinfuzz/basemodule.o: include/bitcoinfuzz/basemodule.cpp include/bitcoinfuzz/basemodule.h
	$(CXX) $(CXXFLAGS) -c include/bitcoinfuzz/basemodule.cpp -o include/bitcoinfuzz/basemodule.o

clean:
	rm -rf *.o module.a bitcoinfuzz include/bitcoinfuzz/*.o $(MODULES)
