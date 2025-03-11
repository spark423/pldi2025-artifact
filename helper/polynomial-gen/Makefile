CC=g++
CPP_FLAGS= -O3 -frounding-math -I../helper/ -I../helper/polynomial-gen/
SOPLEX_PATH = /research/projects/apl/soplex-4.0.1/
INCLUDE=$(SOPLEX_PATH)/src/

all: PolyGen.o

%.o: %.cpp
	$(CC) $(CPP_FLAGS) -c $< -o $@ -I$(INCLUDE)
	
clean:
	rm -rf *.o *.lp *~ *.dSYM
