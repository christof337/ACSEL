LDIR=/opt/lib/
LDIR2=lib
SDIR=src
LDIR3=/usr/include
LDIR4=/usr/local/include

all: matrice_grad_CADNA

matrice_grad_CADNA.o: $(SDIR)/matrice_grad_CADNA.cpp
	g++ -g -c $(SDIR)/matrice_grad_CADNA.cpp -I$(LDIR2) -I$(LDIR3) -I$(LDIR4)
	
matrice_grad_CADNA: $(SDIR)/matrice_grad_CADNA.o $(LDIR2)/SAM_to.o $(LDIR2)/SAM_add.o $(LDIR2)/SAM_sub.o $(LDIR2)/SAM_mul.o \
    $(LDIR2)/SAM_div.o $(LDIR2)/SAM_eq.o $(LDIR2)/SAM_ge.o $(LDIR2)/SAM_gt.o $(LDIR2)/SAM_le.o \
    $(LDIR2)/SAM_lt.o $(LDIR2)/SAM_ne.o $(LDIR2)/SAM_intr.o $(LDIR2)/SAM_math.o \
    $(LDIR2)/SAM_convert.o $(LDIR2)/SAM_str.o $(LDIR2)/SAM_type.o $(LDIR2)/SAM_random.o \
    $(LDIR2)/SAM_digitnumber.o $(LDIR2)/SAM_computedzero.o $(LDIR2)/SAM_unstab.o
	
	g++ $(SDIR)/matrice_grad_CADNA.o $(LDIR2)/SAM_to.o $(LDIR2)/SAM_add.o $(LDIR2)/SAM_sub.o $(LDIR2)/SAM_mul.o $(LDIR2)/SAM_div.o $(LDIR2)/SAM_eq.o $(LDIR2)/SAM_ge.o $(LDIR2)/SAM_gt.o $(LDIR2)/SAM_le.o $(LDIR2)/SAM_lt.o $(LDIR2)/SAM_ne.o $(LDIR2)/SAM_intr.o $(LDIR2)/SAM_math.o $(LDIR2)/SAM_convert.o $(LDIR2)/SAM_str.o $(LDIR2)/SAM_type.o $(LDIR2)/SAM_random.o $(LDIR2)/SAM_digitnumber.o $(LDIR2)/SAM_computedzero.o $(LDIR2)/SAM_unstab.o $(LDIR)libmpfr.a $(LDIR)libgmp.a -o matrice_grad_CADNA

clean:
	rm -f $(LDIR2)/*.o $(SDIR)/*.o matrice_grad_CADNA
