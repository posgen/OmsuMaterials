CXXFLAGS += -std=c++17 -Wall -Wextra -pedantic -pedantic-errors
INCL_DIR = ./include

exec: main.o 
	$(CXX) -o exec main.o

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -I$(INCL_DIR) -c main.cpp

clean:
	rm main.o exec

.PHONY: exec
