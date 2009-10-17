######################################################################
## $Id: Makefile,v 1.3 1998/02/05 22:08:53 dmartin Exp $
######################################################################

PROG := membench

CC := gcc
CFLAGS := -lrt 
#CFLAGS := -fast -xO4 -xdepend -xarch=v8plusa -xchip=ultra -xCC

.PHONY: default clean

default: $(PROG).ps

$(PROG).ps: $(PROG).gp $(PROG).out
	gnuplot < $(PROG).gp > $(PROG).ps

$(PROG).out: $(PROG)
	./$(PROG) > $(PROG).out

$(PROG): $(PROG).c
	$(CC) $(CFLAGS) -o $(PROG) $(PROG).c   

clean:
	rm -f $(PROG) $(PROG).ps $(PROG).out

######################################################################
## $Log: Makefile,v $
## Revision 1.3  1998/02/05 22:08:53  dmartin
## eps --> ps
##
## Revision 1.2  1998/02/01 22:11:26  dmartin
## *** empty log message ***
##
## Revision 1.1  1998/01/19 00:47:39  dmartin
## Initial revision
##
######################################################################
