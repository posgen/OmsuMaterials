CXXFLAGS += -std=c++17 -Wall -Wextra -pedantic -pedantic-errors
INCL_DIR = ./include
SRC_DIR = ./src

lect6: main.o liblect6.o
	$(CXX) -o lect6 main.o liblect6.o

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -I$(INCL_DIR) -c main.cpp

liblect6.o: $(INCL_DIR)/liblect6.h $(SRC_DIR)/liblect6.cpp
	$(CXX) $(CXXFLAGS) -I$(INCL_DIR) -c $(SRC_DIR)/liblect6.cpp

clean:
	rm -f main.o liblect6.o lect6

.PHONY: lect3
