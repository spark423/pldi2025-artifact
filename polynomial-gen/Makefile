SOPLEX_INCLUDE=/research/projects/apl/soplex-4.0.1/src/
SOPLEX_LIB=/research/projects/apl/soplex-4.0.1/build/lib/libsoplex.a

all: polygen polygen-rndz polygen-multi-rnd 

polygen: main.cpp
	g++ -O3 -frounding-math -I$(SOPLEX_INCLUDE) main.cpp $(SOPLEX_LIB) -o polygen -lgmp -lz -lm

polygen-rndz: main.cpp
	g++ -O3 -frounding-math -DRNDZ -I$(SOPLEX_INCLUDE) main.cpp $(SOPLEX_LIB) -o polygen-rndz -lgmp -lz -lm

polygen-multi-rnd: main_multi_rnd.cpp
	g++ -O3 -frounding-math -I$(SOPLEX_INCLUDE) main_multi_rnd.cpp $(SOPLEX_LIB) -o polygen-multi-rnd -lgmp -lz -lm

clean:
	rm -f polygen* *~ 

