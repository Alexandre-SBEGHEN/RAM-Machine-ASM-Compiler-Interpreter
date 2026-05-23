CC      = gcc
CFLAGS  = -Wall -Wextra -std=c11 -Iinclude -MMD -MP
LDFLAGS =

SRC_DIR   = src
BUILD_DIR = build

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))
DEPS = $(OBJS:.o=.d)

TARGET = $(BUILD_DIR)/ram_machine

# ── Règles ────────────────────────────────────────────────────────────────────

all: $(BUILD_DIR) $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)

re: clean all

.PHONY: all clean re

-include $(DEPS)