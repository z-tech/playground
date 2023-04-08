CC=gcc
CFLAGS=-Wextra -Wall -std=c17

LDFLAGS= -L/usr/local/opt/openssl@3/lib -L/usr/local/opt/libomp/lib
CPPFLAGS=-I/usr/local/opt/openssl@3/include -I/usr/local/opt/libomp/include
LINKER=-lcrypto -lomp

SRCS=PrimeHasher.c
SRCH=$(subst .c,.h,$(SRCS))
OBJS=$(subst .c,.o,$(SRCS))

TSTS=./__TESTS__/PrimeHasher.spec.c

TMPC += $(SRCS:.c=.c~)
TMPC += $(TSTS:.c=.c~)
TMPH =  $(SRCH:.h=.h~)

RM=rm -f

all:
	gcc $(CFLAGS) $(SRCS) $(CPPFLAGS) -c

compile-tests:
	gcc $(CFLAGS) $(OBJS) $(TSTS) $(CPPFLAGS) $(LDFLAGS) $(LINKER)

clean:
	$(RM) $(OBJS) $(TMPC) $(TMPH) Makefile~ ./a.out
