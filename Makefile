CC=g++
CFLAGS=-Wextra -Wall -std=c++17 -pthread -O3

LDFLAGS= -L/usr/local/opt/openssl@3/lib
CPPFLAGS=-I/usr/local/opt/openssl@3/include
LINKER=-lcrypto

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
	make clean && make && make compile-tests && ./a.out

clean:
	$(RM) $(OBJS) $(TMPC) $(TMPH) Makefile~ ./a.out
