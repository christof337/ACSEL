LDIR=/opt/lib/
LDIR3=/usr/include
LDIR4=/usr/local/include

all: trap simp romb

SAM_to.o: SAM_to.cpp
	g++ -g -c SAM_to.cpp -I$(LDIR3) -I$(LDIR4)

SAM_add.o: SAM_add.cpp
	g++ -g -c SAM_add.cpp -I $(LDIR3) -I $(LDIR4)

SAM_sub.o: SAM_sub.cpp 
	g++ -g -c SAM_sub.cpp -I $(LDIR3) -I $(LDIR4)

SAM_mul.o: SAM_mul.cpp
	g++ -g -c SAM_mul.cpp -I $(LDIR3) -I $(LDIR4)

SAM_div.o: SAM_div.cpp
	g++ -g -c SAM_div.cpp -I $(LDIR3) -I $(LDIR4)

SAM_eq.o: SAM_eq.cpp
	g++ -g -c SAM_eq.cpp -I $(LDIR3) -I $(LDIR4)

SAM_ge.o: SAM_ge.cpp
	g++ -g -c SAM_ge.cpp -I $(LDIR3) -I $(LDIR4)

SAM_gt.o: SAM_gt.cpp
	g++ -g -c SAM_gt.cpp -I $(LDIR3) -I $(LDIR4)

SAM_le.o: SAM_le.cpp
	g++ -g -c SAM_le.cpp -I $(LDIR3) -I $(LDIR4)

SAM_lt.o: SAM_lt.cpp
	g++ -g -c SAM_lt.cpp -I $(LDIR3) -I $(LDIR4)

SAM_ne.o: SAM_ne.cpp
	g++ -g -c SAM_ne.cpp -I $(LDIR3) -I $(LDIR4)

SAM_intr.o: SAM_intr.cpp
	g++ -g -c SAM_intr.cpp -I $(LDIR3) -I $(LDIR4)

SAM_math.o: SAM_math.cpp
	g++ -g -c SAM_math.cpp -I $(LDIR3) -I $(LDIR4)

SAM_convert.o: SAM_convert.cpp
	g++ -g -c SAM_convert.cpp -I $(LDIR3) -I $(LDIR4)

SAM_str.o: SAM_str.cpp
	g++ -g -c SAM_str.cpp -I $(LDIR3) -I $(LDIR4)

SAM_type.o: SAM_type.cpp
	g++ -g -c SAM_type.cpp -I $(LDIR3) -I $(LDIR4)

SAM_random.o: SAM_random.cpp
	g++ -g -c SAM_random.cpp -I $(LDIR3) -I $(LDIR4)

SAM_digitnumber.o: SAM_digitnumber.cpp
	g++ -g -c SAM_digitnumber.cpp -I $(LDIR3) -I $(LDIR4)

SAM_computedzero.o: SAM_computedzero.cpp
	g++ -g -c SAM_computedzero.cpp -I $(LDIR3) -I $(LDIR4)

SAM_unstab.o: SAM_unstab.cpp
	g++ -g -c SAM_unstab.cpp -I $(LDIR3) -I $(LDIR4)

trap.o: trap.cpp
	g++ -c trap.cpp -I $(LDIR3) -I $(LDIR4)

simp.o: simp.cpp
	g++ -c simp.cpp -I $(LDIR3) -I $(LDIR4)

romb.o: romb.cpp
	g++ -c romb.cpp -I $(LDIR3) -I $(LDIR4)

trap: trap.o SAM_to.o SAM_add.o SAM_sub.o SAM_mul.o \
    SAM_div.o SAM_eq.o SAM_ge.o SAM_gt.o SAM_le.o \
    SAM_lt.o SAM_ne.o SAM_intr.o SAM_math.o \
    SAM_convert.o SAM_str.o SAM_type.o SAM_random.o \
    SAM_digitnumber.o SAM_computedzero.o SAM_unstab.o

	g++ trap.o SAM_to.o SAM_add.o SAM_sub.o SAM_mul.o SAM_div.o SAM_eq.o SAM_ge.o SAM_gt.o SAM_le.o SAM_lt.o SAM_ne.o SAM_intr.o SAM_math.o SAM_convert.o SAM_str.o SAM_type.o SAM_random.o SAM_digitnumber.o SAM_computedzero.o SAM_unstab.o $(LDIR)libmpfr.a $(LDIR)libgmp.a -o trap

simp: simp.o SAM_to.o SAM_add.o SAM_sub.o SAM_mul.o \
    SAM_div.o SAM_eq.o SAM_ge.o SAM_gt.o SAM_le.o \
    SAM_lt.o SAM_ne.o SAM_intr.o SAM_math.o \
    SAM_convert.o SAM_str.o SAM_type.o SAM_random.o \
    SAM_digitnumber.o SAM_computedzero.o SAM_unstab.o

	g++ simp.o SAM_to.o SAM_add.o SAM_sub.o SAM_mul.o SAM_div.o SAM_eq.o SAM_ge.o SAM_gt.o SAM_le.o SAM_lt.o SAM_ne.o SAM_intr.o SAM_math.o SAM_convert.o SAM_str.o SAM_type.o SAM_random.o SAM_digitnumber.o SAM_computedzero.o SAM_unstab.o $(LDIR)libmpfr.a $(LDIR)libgmp.a -o simp

romb: romb.o SAM_to.o SAM_add.o SAM_sub.o SAM_mul.o \
SAM_div.o SAM_eq.o SAM_ge.o SAM_gt.o SAM_le.o \
SAM_lt.o SAM_ne.o SAM_intr.o SAM_math.o \
SAM_convert.o SAM_str.o SAM_type.o SAM_random.o \
SAM_digitnumber.o SAM_computedzero.o SAM_unstab.o

	g++ romb.o SAM_to.o SAM_add.o SAM_sub.o SAM_mul.o SAM_div.o SAM_eq.o SAM_ge.o SAM_gt.o SAM_le.o SAM_lt.o SAM_ne.o SAM_intr.o SAM_math.o SAM_convert.o SAM_str.o SAM_type.o SAM_random.o SAM_digitnumber.o SAM_computedzero.o SAM_unstab.o $(LDIR)libmpfr.a $(LDIR)libgmp.a -o romb


clean:
	rm -f *.o trap simp romb
