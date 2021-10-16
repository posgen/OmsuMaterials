CXXFLAGS += -std=c++17 -Wall -Wextra -pedantic -pedantic-errors
INCL_DIR = ./include
SRC_DIR = ./src

lect3: main.o liblect3.o
	$(CXX) -o lect3 main.o liblect3.o

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -I$(INCL_DIR) -c main.cpp

liblect3.o: $(INCL_DIR)/liblect3.h $(SRC_DIR)/liblect3.cpp
	$(CXX) $(CXXFLAGS) -I$(INCL_DIR) -c $(SRC_DIR)/liblect3.cpp

clean:
	rm main.o liblect3.o lect3

.PHONY: lect3
