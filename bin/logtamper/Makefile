CC=gcc
LDFLAGS=
SHLDFLAGS=
RM=rm -rf

all: logtamper

logtamper:logtamper.c reserve_time.c str2time.c
	$(CC) -o $@ logtamper.c reserve_time.c str2time.c

static:logtamper.c reserve_time.c str2time.c
	$(CC) -static -o logtamper-static logtamper.c reserve_time.c str2time.c
clean:
	$(RM) *.o logtamper
