TARGET = muxer
SRCS = utils.c shm.c client.c helper.c main.c
OBJS = $(SRCS:.c=.o)

CC := gcc
CXX := gcc
CXXFLAGS := -g -Wall -Wextra --pedantic-errors

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

clean:
	rm -f $(OBJS) $(TARGET)
