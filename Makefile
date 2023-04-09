CC=g++
CFLAGS=-Wextra -Wall -std=c++17 -pthread -O3

LDFLAGS= -L/usr/local/opt/openssl@3/lib -L/usr/local/opt/libomp/lib
CPPFLAGS=-I/usr/local/opt/openssl@3/include -I/usr/local/opt/libomp/include -Xclang -fopenmp
LINKER=-lcrypto -lomp

SRCS=PrimeHasher.cc
SRCH=$(subst .cc,.hh,$(SRCS))
OBJS=$(subst .cc,.o,$(SRCS))

TSTS=./__TESTS__/PrimeHasher.spec.cc

TMPC += $(SRCS:.cc=.cc~)
TMPC += $(TSTS:.spec.cc=.spec.cc~)
TMPH =  $(SRCH:.hh=.hh~)

RM=rm -f

all:
	$(CC) $(CFLAGS) $(SRCS) $(CPPFLAGS) -c

compile-tests:
	$(CC) $(CFLAGS) $(OBJS) $(TSTS) $(CPPFLAGS) $(LDFLAGS) $(LINKER)

test:
	make clean && make && make compile-tests && time ./a.out

clean:
	$(RM) $(OBJS) $(TMPC) $(TMPH) Makefile~ ./a.out
