export TEMP := ./.git/info/tmp
export TMP := ./.git/info/tmp

CC = gcc
CFLAGS = -O3 -fopenmp
NAME=a
LIB_DIR = lib
SRC_DIR = src
OBJ_DIR = obj

LIB_DIRS = $(shell find $(LIB_DIR) -type d -name "*link")
LIBS = $(patsubst %, -L./%, $(LIB_DIRS)) -L./dlls -lws2_32 -lglfw3dll -lOpenAL32 -lsndfile
INCLUDE_DIRS = $(shell find $(LIB_DIR) -type d -name "*include")
INCLUDES = $(patsubst %, -I./%, $(INCLUDE_DIRS))
SRCS = $(shell find $(SRC_DIR) $(LIB_DIR) -name "*.c")
OBJS = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRCS))

all: $(OBJS)
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBS) -o $(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(shell dirname $@)
	@$(CC) $(CFLAGS) $(LIBS) $(INCLUDES) -c $^ -o $@

clean:
	rm -r $(OBJ_DIR) a.exe

.PHONY: clean