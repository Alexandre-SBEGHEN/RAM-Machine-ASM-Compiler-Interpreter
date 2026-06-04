CC      = gcc
CFLAGS  = -Wall -Wextra -std=c11 -Iinclude -MMD -MP
LDFLAGS =

SRC_DIR   = src
BUILD_DIR = build
TEST_DIR  = tests

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))
DEPS = $(OBJS:.o=.d)

TEST_SRCS = $(wildcard $(TEST_DIR)/*.c)
TEST_BINS = $(patsubst $(TEST_DIR)/%.c, $(BUILD_DIR)/%, $(TEST_SRCS))

TARGET = $(BUILD_DIR)/ram_machine

# ── Règles ────────────────────────────────────────────────────────────────────

all: $(BUILD_DIR) $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%: $(TEST_DIR)/%.c $(filter-out $(BUILD_DIR)/main.o, $(OBJS))
	$(CC) $(CFLAGS) $^ -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

test: $(BUILD_DIR) $(OBJS) $(TEST_BINS)
	@for t in $(TEST_BINS); do echo "── $$t ──"; ./$$t; echo; done

clean:
	rm -rf $(BUILD_DIR)

re: clean all

.PHONY: all test clean re

-include $(DEPS)