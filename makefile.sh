CC = g++
PRJ_DIR=/home/pi/Parser
OBJ_DIR=/home/pi/Parser/obj
INCLUDE_DIR=/home/pi/Parser/classes /home/pi/Parser/get_data


INCLUDE = -I./ $(INCLUDE_DIR)
OTHERDIR=get_data/
TARGET=Parser
FLAGS= -lpthread

LDFLAGS	= -L/usr/local/lib
LDLIBS    = -lpthread -lm

VPATH=$(OTHERDIR)

###########
all: $(TARGET)
	@true

$(TARGET): main.o parse_data.o receive_data.o save_data.o
	@echo "BUILD TARGET"
	@$(CC) -o $@ $^ $(LDFLAGS) $(LDLIBS)
	@echo --Link Finished--

%.o : %.c
	@$(CC) -Wall -g -c -std=c++11 $< -o $@ 

.PHONY: clean

clean:
	rm -f *.o
