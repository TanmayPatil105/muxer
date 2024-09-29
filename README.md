# muxer

Share output of one process to multiple processes

## Usage
process 1
```
$ cat Makefile | muxer -c 2
1364263253
```
process 2
```
$ muxer 1364263253
TARGET = muxer
SRCS = utils.c shm.c client.c helper.c main.c
OBJS = $(SRCS:.c=.o)

INSTALL = /usr/bin/install -c -D
BIN_DIR = /bin
...
```
process 3
```
$ muxer 1364263253
TARGET = muxer
SRCS = utils.c shm.c client.c helper.c main.c
OBJS = $(SRCS:.c=.o)

INSTALL = /usr/bin/install -c -D
BIN_DIR = /bin
...
```
