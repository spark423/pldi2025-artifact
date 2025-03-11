CC = g++

FLAGS  = -lmpfr -lgmp

all:  Cosh-RN Cosh-RZ Cosh-MULTI Cospi-RN Cospi-RZ Cospi-MULTI CosSmall CosP1-RN CosP2-RZ CosP2-MULTI CosP2-RN CosP2-RZ CosP2-MULTI \
  Log-RN Log-RZ Log-MULTI Log2-RN Log2-RZ Log2-MULTI Log10-RN Log10-RZ Log10-MULTI \
  Exp-RN Exp-RZ Exp-MULTI Exp2-RN Exp2-RZ Exp2-MULTI Exp10-RN Exp10-RZ Exp10-MULTI \
  Sinh-RN Sinh-RZ Sinh-MULTI Sinpi-RN Sinpi-RZ Sinpi-MULTI SinSmall SinP1-RN SinP1-RZ SinP1-MULTI SinP2-RN SinP2-RZ SinP2-MULTI

Cosh-RN: Cosh.cpp
	$(CC) -O3 -frounding-math -fsignaling-nans -I../helper -I../include Cosh.cpp -o Cosh-RN $(FLAGS)

Cosh-RZ: Cosh.cpp
	$(CC) -O3 -frounding-math -fsignaling-nans -DRNDZ -I../helper -I../include Cosh.cpp -o Cosh-RZ $(FLAGS)

Cosh-MULTI: Cosh.cpp
	$(CC) -O3 -frounding-math -fsignaling-nans -DRNDZ -DMULTI -I../helper -I../include Cosh.cpp -o Cosh-MULTI $(FLAGS)

Cospi-RN: Cospi.cpp
	$(CC) -O3 -frounding-math -fsignaling-nans -I../helper -I../include Cospi.cpp -o Cospi-RN $(FLAGS)

Cospi-RZ: Cospi.cpp
	$(CC) -O3 -frounding-math -fsignaling-nans -DRNDZ -I../helper -I../include Cospi.cpp -o Cospi-RZ $(FLAGS)

Cospi-MULTI: Cospi.cpp
	$(CC) -O3 -frounding-math -fsignaling-nans -DRNDZ -DMULTI -I../helper -I../include Cospi.cpp -o Cospi-MULTI $(FLAGS)

CosSmall: CosSmall.cpp
	$(CC) -O3 -frounding-math -fsignaling-nans -I../helper -I../include CosSmall.cpp -o CosSmall $(FLAGS)

CosP1-RN: CosP1.cpp
	$(CC) -O3 -frounding-math -fsignaling-nans -I../helper -I../include CosP1.cpp -o CosP1-RN $(FLAGS)

CosP1-RZ: CosP1.cpp
	$(CC) -O3 -frounding-math -fsignaling-nans -DRNDZ -I../helper -I../include CosP1.cpp -o CosP1-RZ $(FLAGS)

CosP1-MULTI: CosP1.cpp
	$(CC) -O3 -frounding-math -fsignaling-nans -DRNDZ -DMULTI -I../helper -I../include CosP1.cpp -o CosP1-MULTI $(FLAGS)

CosP2-RN: CosP2.cpp
	$(CC) -O3 -frounding-math -fsignaling-nans -I../helper -I../include CosP2.cpp -o CosP2-RN $(FLAGS)

CosP2-RZ: CosP2.cpp
	$(CC) -O3 -frounding-math -fsignaling-nans -DRNDZ -I../helper -I../include CosP2.cpp -o CosP2-RZ $(FLAGS)

CosP2-MULTI: CosP2.cpp
	$(CC) -O3 -frounding-math -fsignaling-nans -DRNDZ -DMULTI -I../helper -I../include CosP2.cpp -o CosP2-MULTI $(FLAGS)

Exp-RN: Exp.cpp
	$(CC) -O3 -frounding-math -fsignaling-nans -I../helper -I../include Exp.cpp -o Exp-RN $(FLAGS)

Exp-RZ: Exp.cpp
	$(CC) -O3 -frounding-math -fsignaling-nans -DRNDZ -I../helper -I../include Exp.cpp -o Exp-RZ $(FLAGS)

Exp-MULTI: Exp.cpp
	$(CC) -O3 -frounding-math -fsignaling-nans -DRNDZ -DMULTI -I../helper -I../include Exp.cpp -o Exp-MULTI $(FLAGS)

Exp2-RN: Exp2.cpp
	$(CC) -O3 -frounding-math -fsignaling-nans -I../helper -I../include Exp2.cpp -o Exp2-RN $(FLAGS)

Exp2-RZ: Exp2.cpp
	$(CC) -O3 -frounding-math -fsignaling-nans -DRNDZ -I../helper -I../include Exp2.cpp -o Exp2-RZ $(FLAGS)

Exp2-MULTI: Exp2.cpp
	$(CC) -O3 -frounding-math -fsignaling-nans -DRNDZ -DMULTI -I../helper -I../include Exp2.cpp -o Exp2-MULTI $(FLAGS)

Exp10-RN: Exp10.cpp
	$(CC) -O3 -frounding-math -fsignaling-nans -I../helper -I../include Exp10.cpp -o Exp10-RN $(FLAGS)

Exp10-RZ: Exp10.cpp
	$(CC) -O3 -frounding-math -fsignaling-nans -DRNDZ -I../helper -I../include Exp10.cpp -o Exp10-RZ $(FLAGS)

Exp10-MULTI: Exp10.cpp
	$(CC) -O3 -frounding-math -fsignaling-nans -DRNDZ -DMULTI -I../helper -I../include Exp10.cpp -o Exp10-MULTI $(FLAGS)

Log-RN: Log.cpp
	$(CC) -O3 -frounding-math -fsignaling-nans -I../helper -I../include Log.cpp -o Log-RN $(FLAGS)

Log-RZ: Log.cpp
	$(CC) -O3 -frounding-math -fsignaling-nans -DRNDZ -I../helper -I../include Log.cpp -o Log-RZ $(FLAGS)

Log-MULTI: Log.cpp 
	$(CC) -O3 -frounding-math -fsignaling-nans -DRNDZ -DMULTI -I../helper -I../include Log.cpp -o Log-MULTI $(FLAGS)

Log2-RN: Log2.cpp
	$(CC) -O3 -frounding-math -fsignaling-nans -I../helper -I../include Log2.cpp -o Log2-RN $(FLAGS)

Log2-RZ: Log2.cpp
	$(CC) -O3 -frounding-math -fsignaling-nans -DRNDZ -I../helper -I../include Log2.cpp -o Log2-RZ $(FLAGS)

Log2-MULTI: Log2.cpp
	$(CC) -O3 -frounding-math -fsignaling-nans -DRNDZ -DMULTI -I../helper -I../include Log2.cpp -o Log2-MULTI $(FLAGS)

Log10-RN: Log10.cpp
	$(CC) -O3 -frounding-math -fsignaling-nans -I../helper -I../include Log10.cpp -o Log10-RN $(FLAGS)

Log10-RZ: Log10.cpp
	$(CC) -O3 -frounding-math -fsignaling-nans -DRNDZ -I../helper -I../include Log10.cpp -o Log10-RZ $(FLAGS)

Log10-MULTI: Log10.cpp
	$(CC) -O3 -frounding-math -fsignaling-nans -DRNDZ -DMULTI -I../helper -I../include Log10.cpp -o Log10-MULTI $(FLAGS)

Sinh-RN: Sinh.cpp
	$(CC) -O3 -frounding-math -fsignaling-nans -I../helper -I../include Sinh.cpp -o Sinh-RN $(FLAGS)

Sinh-RZ: Sinh.cpp
	$(CC) -O3 -frounding-math -fsignaling-nans -DRNDZ -I../helper -I../include Sinh.cpp -o Sinh-RZ $(FLAGS)

Sinh-MULTI: Sinh.cpp
	$(CC) -O3 -frounding-math -fsignaling-nans -DRNDZ -DMULTI -I../helper -I../include Sinh.cpp -o Sinh-MULTI $(FLAGS)

Sinpi-RN: Sinpi.cpp
	$(CC) -O3 -frounding-math -fsignaling-nans -I../helper -I../include Sinpi.cpp -o Sinpi-RN $(FLAGS)

Sinpi-RZ: Sinpi.cpp
	$(CC) -O3 -frounding-math -fsignaling-nans -DRNDZ -I../helper -I../include Sinpi.cpp -o Sinpi-RZ $(FLAGS)

Sinpi-MULTI: Sinpi.cpp
	$(CC) -O3 -frounding-math -fsignaling-nans -DRNDZ -DMULTI -I../helper -I../include Sinpi.cpp -o Sinpi-MULTI $(FLAGS)

SinSmall: SinSmall.cpp
	$(CC) -O3 -frounding-math -fsignaling-nans -I../helper -I../include SinSmall.cpp -o SinSmall $(FLAGS)

SinP1-RN: SinP1.cpp
	$(CC) -O3 -frounding-math -fsignaling-nans -I../helper -I../include SinP1.cpp -o SinP1-RN $(FLAGS)

SinP1-RZ: SinP1.cpp
	$(CC) -O3 -frounding-math -fsignaling-nans -DRNDZ -I../helper -I../include SinP1.cpp -o SinP1-RZ $(FLAGS)

SinP1-MULTI: SinP1.cpp
	$(CC) -O3 -frounding-math -fsignaling-nans -DRNDZ -DMULTI -I../helper -I../include SinP1.cpp -o SinP1-MULTI $(FLAGS)

SinP1-MULTI-FMA: SinP1.cpp
	$(CC) -O3 -march=native -frounding-math -fsignaling-nans -DRNDZ -DMULTI -DFMA -I../helper -I../include SinP1.cpp -o SinP1-MULTI-FMA $(FLAGS)

SinP2-RN: SinP2.cpp
	$(CC) -O3 -frounding-math -fsignaling-nans -I../helper -I../include SinP2.cpp -o SinP2-RN $(FLAGS)

SinP2-RZ: SinP2.cpp
	$(CC) -O3 -frounding-math -fsignaling-nans -DRNDZ -I../helper -I../include SinP2.cpp -o SinP2-RZ $(FLAGS)

SinP2-MULTI: SinP2.cpp
	$(CC) -O3 -frounding-math -fsignaling-nans -DRNDZ -DMULTI -I../helper -I../include SinP2.cpp -o SinP2-MULTI $(FLAGS)

clean:
	rm -rf *-RN *-RZ *-MULTI *Small *~
