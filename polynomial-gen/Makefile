objects = LogSmall-RLIBM LogSmall-RI-Outputs LogSmall-RI-Input-Bounds

CC=g++

SOPLEX_INCLUDE=$(SOPLEX_PATH)/src/
SOPLEX_LIB=$(SOPLEX_PATH)/build/lib/libsoplex.a
INCLUDE=-I$(SOPLEX_INCLUDE)
CPP_FLAGS=-O3 -frounding-math -I../helper/ -I../helper/polynomial-gen/
LD_FLAGS=$(SOPLEX_LIB) -lmpfr -lgmp -lz -lm

all: $(objects)

LogSmall-RLIBM.o: LogSmall.cpp
	$(CC) $(CPP_FLAGS) -c $< -o $@ $(INCLUDE)

LogSmall-RLIBM: %: ../helper/polynomial-gen/PolyGen.o LogSmall-RLIBM.o 
	$(CC) $^ $(LD_FLAGS) -o $@

LogSmall-RI-Outputs.o: LogSmall.cpp
	$(CC) $(CPP_FLAGS) -DRNDZ -c $< -o $@ $(INCLUDE)

LogSmall-RI-Outputs: %: ../helper/polynomial-gen/PolyGen.o LogSmall-RI-Outputs.o 
	$(CC) $^ $(LD_FLAGS) -o $@

LogSmall-RI-Input-Bounds.o: LogSmall.cpp
	$(CC) $(CPP_FLAGS) -DMULTI -c $< -o $@ $(INCLUDE)

LogSmall-RI-Input-Bounds: %: ../helper/polynomial-gen/PolyGen.o LogSmall-RI-Input-Bounds.o 
	$(CC) $^ $(LD_FLAGS) -o $@

clean:
	rm -rf *.o ../helper/polynomial-gen/*.o $(objects) *~ *.dSYM dump.lp
