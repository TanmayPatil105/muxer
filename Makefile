TARGET = muxer
SRCS = utils.c shm.c client.c helper.c main.c
OBJS = $(SRCS:.c=.o)

INSTALL = /usr/bin/install -c -D
BIN_DIR = /bin

CC := gcc
CXX := gcc
CXXFLAGS := -g -Wall -Wextra --pedantic-errors

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

install:
	@echo "Installing $(BIN_DIR)/$(TARGET) ..."
	$(INSTALL) $(TARGET) "$(BIN_DIR)/$(TARGET)"

clean:
	rm -f $(OBJS) $(TARGET)
