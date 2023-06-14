###########################################################
#
# Makefile: threadfun2
#
###########################################################
.SUFFIXES: .c .cpp .o

CC = gcc
CXX = g++
CFLAGS = -g 
LIBS = -lm -lpthread
RM = /bin/rm
RMFLAGS = -rf

all: tokenid threadarray pthreadstatcalc sudokuvalidator

EXE = threadarray
EXE2 = tokenid
EXE3 = pthreadstatcalc
EXE4 = sudokuvalidator

OBJS = threadarray.o 
OBJS2 = tokenid.o
OBJS3 = pthreadstatcalc.o  
OBJ4 = sudokuvalidator.o


$(EXE): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

$(EXE2): $(OBJS2)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

.c.o:
	$(CC) $(CFLAGS) -c $<


clean:
	$(RM) $(RMFLAGS) *.o *~ all