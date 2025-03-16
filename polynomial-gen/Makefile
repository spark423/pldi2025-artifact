objects = SinSmall-RLIBM SinSmall-RI-Outputs SinSmall-RI-Inputs Sin-RLIBM Sin-RI-Outputs Sin-RI-Inputs \
	  CosSmall-RLIBM CosSmall-RI-Outputs CosSmall-RI-Inputs Cos-RLIBM Cos-RI-Outputs Cos-RI-Inputs \
	  Log-RLIBM Log-RI-Outputs Log-RI-Inputs \
	  Log2-RLIBM Log2-RI-Outputs Log2-RI-Inputs \
	  Log10-RLIBM Log10-RI-Outputs Log10-RI-Inputs \
	  Exp-RLIBM Exp-RI-Outputs Exp-RI-Inputs \
	  Exp2-RLIBM Exp2-RI-Outputs Exp2-RI-Inputs \
	  Exp10-RLIBM Exp10-RI-Outputs Exp10-RI-Inputs

CC=g++

SOPLEX_INCLUDE=$(SOPLEX_PATH)/src/
SOPLEX_LIB=$(SOPLEX_PATH)/build/lib/libsoplex.a
INCLUDE=-I$(SOPLEX_INCLUDE)
CPP_FLAGS=-O3 -frounding-math -I../helper/ -I../helper/polynomial-gen/
LD_FLAGS=$(SOPLEX_LIB) -lmpfr -lgmp -lz -lm

all: $(objects)

SinSmall-RLIBM.o: SinSmall.cpp
	$(CC) $(CPP_FLAGS) -DEXIT_ON_THRESHOLD -c $< -o $@ $(INCLUDE)

SinSmall-RLIBM: %: ../helper/polynomial-gen/PolyGen.o SinSmall-RLIBM.o 
	$(CC) $^ $(LD_FLAGS) -o $@

SinSmall-RI-Outputs.o: SinSmall.cpp
	$(CC) $(CPP_FLAGS) -DRNDZ -DEXIT_ON_THRESHOLD -c $< -o $@ $(INCLUDE)

SinSmall-RI-Outputs: %: ../helper/polynomial-gen/PolyGen.o SinSmall-RI-Outputs.o 
	$(CC) $^ $(LD_FLAGS) -o $@

SinSmall-RI-Inputs.o: SinSmall.cpp
	$(CC) $(CPP_FLAGS) -DMULTI -DEXIT_ON_THRESHOLD -c $< -o $@ $(INCLUDE)

SinSmall-RI-Inputs: %: ../helper/polynomial-gen/PolyGen.o SinSmall-RI-Inputs.o 
	$(CC) $^ $(LD_FLAGS) -o $@

CosSmall-RLIBM.o: CosSmall.cpp
	$(CC) $(CPP_FLAGS) -DEXIT_ON_THRESHOLD -c $< -o $@ $(INCLUDE)

CosSmall-RLIBM: %: ../helper/polynomial-gen/PolyGen.o CosSmall-RLIBM.o 
	$(CC) $^ $(LD_FLAGS) -o $@

CosSmall-RI-Outputs.o: CosSmall.cpp
	$(CC) $(CPP_FLAGS) -DRNDZ -DEXIT_ON_THRESHOLD -c $< -o $@ $(INCLUDE)

CosSmall-RI-Outputs: %: ../helper/polynomial-gen/PolyGen.o CosSmall-RI-Outputs.o 
	$(CC) $^ $(LD_FLAGS) -o $@

CosSmall-RI-Inputs.o: CosSmall.cpp
	$(CC) $(CPP_FLAGS) -DMULTI -DEXIT_ON_THRESHOLD -c $< -o $@ $(INCLUDE)

CosSmall-RI-Inputs: %: ../helper/polynomial-gen/PolyGen.o CosSmall-RI-Inputs.o 
	$(CC) $^ $(LD_FLAGS) -o $@

Sin-RLIBM.o: Sin.cpp
	$(CC) $(CPP_FLAGS) -DEXIT_ON_THRESHOLD -c $< -o $@ $(INCLUDE)

Sin-RLIBM: %: ../helper/polynomial-gen/PolyGen.o Sin-RLIBM.o 
	$(CC) $^ $(LD_FLAGS) -o $@

Sin-RI-Outputs.o: Sin.cpp
	$(CC) $(CPP_FLAGS) -DRNDZ -DEXIT_ON_THRESHOLD -c $< -o $@ $(INCLUDE)

Sin-RI-Outputs: %: ../helper/polynomial-gen/PolyGen.o Sin-RI-Outputs.o 
	$(CC) $^ $(LD_FLAGS) -o $@

Sin-RI-Inputs.o: Sin.cpp
	$(CC) $(CPP_FLAGS) -DMULTI -DEXIT_ON_THRESHOLD -c $< -o $@ $(INCLUDE)

Sin-RI-Inputs: %: ../helper/polynomial-gen/PolyGen.o Sin-RI-Inputs.o 
	$(CC) $^ $(LD_FLAGS) -o $@

Cos-RLIBM.o: Cos.cpp
	$(CC) $(CPP_FLAGS) -DEXIT_ON_THRESHOLD -c $< -o $@ $(INCLUDE)

Cos-RLIBM: %: ../helper/polynomial-gen/PolyGen.o Cos-RLIBM.o 
	$(CC) $^ $(LD_FLAGS) -o $@

Cos-RI-Outputs.o: Cos.cpp
	$(CC) $(CPP_FLAGS) -DRNDZ -DEXIT_ON_THRESHOLD -c $< -o $@ $(INCLUDE)

Cos-RI-Outputs: %: ../helper/polynomial-gen/PolyGen.o Cos-RI-Outputs.o 
	$(CC) $^ $(LD_FLAGS) -o $@

Cos-RI-Inputs.o: Cos.cpp
	$(CC) $(CPP_FLAGS) -DMULTI -DEXIT_ON_THRESHOLD -c $< -o $@ $(INCLUDE)

Cos-RI-Inputs: %: ../helper/polynomial-gen/PolyGen.o Cos-RI-Inputs.o 
	$(CC) $^ $(LD_FLAGS) -o $@

Log-RLIBM.o: LogRLIBM.cpp
	$(CC) $(CPP_FLAGS) -DEXIT_ON_THRESHOLD -c $< -o $@ $(INCLUDE)

Log-RLIBM: %: ../helper/polynomial-gen/PolyGen.o Log-RLIBM.o 
	$(CC) $^ $(LD_FLAGS) -o $@

Log-RI-Outputs.o: Log.cpp
	$(CC) $(CPP_FLAGS) -DRNDZ -DEXIT_ON_THRESHOLD -c $< -o $@ $(INCLUDE)

Log-RI-Outputs: %: ../helper/polynomial-gen/PolyGen.o Log-RI-Outputs.o 
	$(CC) $^ $(LD_FLAGS) -o $@

Log-RI-Inputs.o: Log.cpp
	$(CC) $(CPP_FLAGS) -DMULTI -DEXIT_ON_THRESHOLD -c $< -o $@ $(INCLUDE)

Log-RI-Inputs: %: ../helper/polynomial-gen/PolyGen.o Log-RI-Inputs.o 
	$(CC) $^ $(LD_FLAGS) -o $@

Log2-RLIBM.o: Log2.cpp
	$(CC) $(CPP_FLAGS) -DEXIT_ON_THRESHOLD -c $< -o $@ $(INCLUDE)

Log2-RLIBM: %: ../helper/polynomial-gen/PolyGen.o Log2-RLIBM.o 
	$(CC) $^ $(LD_FLAGS) -o $@

Log2-RI-Outputs.o: Log2.cpp
	$(CC) $(CPP_FLAGS) -DRNDZ -DEXIT_ON_THRESHOLD -c $< -o $@ $(INCLUDE)

Log2-RI-Outputs: %: ../helper/polynomial-gen/PolyGen.o Log2-RI-Outputs.o 
	$(CC) $^ $(LD_FLAGS) -o $@

Log2-RI-Inputs.o: Log2.cpp
	$(CC) $(CPP_FLAGS) -DMULTI -DEXIT_ON_THRESHOLD -c $< -o $@ $(INCLUDE)

Log2-RI-Inputs: %: ../helper/polynomial-gen/PolyGen.o Log2-RI-Inputs.o 
	$(CC) $^ $(LD_FLAGS) -o $@

Log10-RLIBM.o: Log.cpp
	$(CC) $(CPP_FLAGS) -DEXIT_ON_THRESHOLD -c $< -o $@ $(INCLUDE)

Log10-RLIBM: %: ../helper/polynomial-gen/PolyGen.o Log10-RLIBM.o 
	$(CC) $^ $(LD_FLAGS) -o $@

Log10-RI-Outputs.o: Log.cpp
	$(CC) $(CPP_FLAGS) -DRNDZ -DEXIT_ON_THRESHOLD -c $< -o $@ $(INCLUDE)

Log10-RI-Outputs: %: ../helper/polynomial-gen/PolyGen.o Log10-RI-Outputs.o 
	$(CC) $^ $(LD_FLAGS) -o $@

Log10-RI-Inputs.o: Log.cpp
	$(CC) $(CPP_FLAGS) -DMULTI -DEXIT_ON_THRESHOLD -c $< -o $@ $(INCLUDE)

Log10-RI-Inputs: %: ../helper/polynomial-gen/PolyGen.o Log10-RI-Inputs.o 
	$(CC) $^ $(LD_FLAGS) -o $@

Exp-RLIBM.o: Exp.cpp
	$(CC) $(CPP_FLAGS) -DEXIT_ON_THRESHOLD -c $< -o $@ $(INCLUDE)

Exp-RLIBM: %: ../helper/polynomial-gen/PolyGen.o Exp-RLIBM.o 
	$(CC) $^ $(LD_FLAGS) -o $@

Exp-RI-Outputs.o: Exp.cpp
	$(CC) $(CPP_FLAGS) -DRNDZ -DEXIT_ON_THRESHOLD -c $< -o $@ $(INCLUDE)

Exp-RI-Outputs: %: ../helper/polynomial-gen/PolyGen.o Exp-RI-Outputs.o 
	$(CC) $^ $(LD_FLAGS) -o $@

Exp-RI-Inputs.o: Exp.cpp
	$(CC) $(CPP_FLAGS) -DMULTI -DEXIT_ON_THRESHOLD -c $< -o $@ $(INCLUDE)

Exp-RI-Inputs: %: ../helper/polynomial-gen/PolyGen.o Exp-RI-Inputs.o 
	$(CC) $^ $(LD_FLAGS) -o $@

Exp2-RLIBM.o: Exp2.cpp
	$(CC) $(CPP_FLAGS) -DEXIT_ON_THRESHOLD -c $< -o $@ $(INCLUDE)

Exp2-RLIBM: %: ../helper/polynomial-gen/PolyGen.o Exp2-RLIBM.o 
	$(CC) $^ $(LD_FLAGS) -o $@

Exp2-RI-Outputs.o: Exp2.cpp
	$(CC) $(CPP_FLAGS) -DRNDZ -DEXIT_ON_THRESHOLD -c $< -o $@ $(INCLUDE)

Exp2-RI-Outputs: %: ../helper/polynomial-gen/PolyGen.o Exp2-RI-Outputs.o 
	$(CC) $^ $(LD_FLAGS) -o $@

Exp2-RI-Inputs.o: Exp2.cpp
	$(CC) $(CPP_FLAGS) -DMULTI -DEXIT_ON_THRESHOLD -c $< -o $@ $(INCLUDE)

Exp2-RI-Inputs: %: ../helper/polynomial-gen/PolyGen.o Exp2-RI-Inputs.o 
	$(CC) $^ $(LD_FLAGS) -o $@

Exp10-RLIBM.o: Exp2.cpp
	$(CC) $(CPP_FLAGS) -DEXIT_ON_THRESHOLD -c $< -o $@ $(INCLUDE)

Exp10-RLIBM: %: ../helper/polynomial-gen/PolyGen.o Exp10-RLIBM.o 
	$(CC) $^ $(LD_FLAGS) -o $@

Exp10-RI-Outputs.o: Exp2.cpp
	$(CC) $(CPP_FLAGS) -DRNDZ -DEXIT_ON_THRESHOLD -c $< -o $@ $(INCLUDE)

Exp10-RI-Outputs: %: ../helper/polynomial-gen/PolyGen.o Exp10-RI-Outputs.o 
	$(CC) $^ $(LD_FLAGS) -o $@

Exp10-RI-Inputs.o: Exp2.cpp
	$(CC) $(CPP_FLAGS) -DMULTI -DEXIT_ON_THRESHOLD -c $< -o $@ $(INCLUDE)

Exp10-RI-Inputs: %: ../helper/polynomial-gen/PolyGen.o Exp10-RI-Inputs.o 
	$(CC) $^ $(LD_FLAGS) -o $@

clean:
	rm -rf *.o ../helper/polynomial-gen/*.o $(objects) *~ *.dSYM dump.lp
