CC = g++

funcNames = Cos Cosh Cospi Exp Exp2 Exp10 Log Log2 Log10 Sin Sinh Sinpi

src = $(patsubst %, %.c, $(funcNames))
obj = $(patsubst %, %, $(funcNames))

all: $(obj)

%: %.cpp
	$(CC) -O3 -I../helper/ -I../include $^ -lm -lmpfr -lgmp -o $@

clean:
	rm -rf $(obj) *.dSYM
