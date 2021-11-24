CXXFLAGS += -std=c++17 -Wall -Wextra -pedantic -pedantic-errors
INCL_DIR = ./include
SRC_DIR = ./src

lect5: main.o liblect5.o
	$(CXX) -o lect5 main.o liblect5.o

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -I$(INCL_DIR) -c main.cpp

liblect5.o: $(INCL_DIR)/liblect5.h $(SRC_DIR)/liblect5.cpp
	$(CXX) $(CXXFLAGS) -I$(INCL_DIR) -c $(SRC_DIR)/liblect5.cpp

clean:
	rm -f main.o liblect5.o lect5

.PHONY: lect3
