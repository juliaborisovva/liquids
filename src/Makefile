APP_NAME = app
APP_NAME_TEST = test

BUILD_DIR = build
BIN_DIR = bin

SRC_EXT = cpp
CXX = g++
CXXFLAGS =-Wall -Wextra -Werror -Wpedantic -std=c++17 -I src -I googletest/googletest/include -MP -MMD

APP_PATH = $(BUILD_DIR)/$(BIN_DIR)/$(APP_NAME)
APP_TEST_PATH = $(BUILD_DIR)/$(BIN_DIR)/$(APP_NAME_TEST)

APP_SRCS = liquid.cpp main.cpp
TEST_SRCS = liquid.cpp test.cpp

APP_OBJS = $(APP_SRCS:%.$(SRC_EXT)=$(BUILD_DIR)/%.o)
TEST_OBJS = $(TEST_SRCS:%.$(SRC_EXT)=$(BUILD_DIR)/%.o)

APP_DEPS = $(APP_OBJS:.o=.d)
TEST_DEPS = $(TEST_OBJS:.o=.d)

OS=$(shell uname)
ifeq ($(OS), Linux)
  LIBS=
  CHECK_LEAKS=CK_FORK=no valgrind --leak-check=full -s --log-file=log.txt
else ifeq ($(OS), Darwin)
  LIBS=
  CHECK_LEAKS=no leaks -atExit --
endif

.PHONY: all
all: mk_dirs $(APP_PATH)

.PHONY: mk_dirs
mk_dirs:
	mkdir -p -v $(BUILD_DIR)/$(BIN_DIR)

-include $(APP_DEPS)

rebuild: clean all

run: all
	./$(APP_PATH)

$(APP_PATH): $(APP_OBJS)
	$(CXX) $(CXXFLAGS) $(APP_OBJS) -o $@

$(BUILD_DIR)/%.o: %.$(SRC_EXT) libliquids.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: style
style:
	cp ../.clang-format .
	clang-format -n *.$(SRC_EXT) *.hpp
	clang-format -i *.$(SRC_EXT) *.hpp
	rm .clang-format

.PHONY: clean
clean:
	rm -rf build

.PHONY: clean_lib
clean_lib:
	rm -rf googletest

#GTEST LIB
GTEST_DIR = googletest
GTEST_REPO = https://github.com/google/googletest.git
GTEST_BUILD_DIR = $(GTEST_DIR)/build
GTEST_LIB = $(GTEST_BUILD_DIR)/lib/libgtest.a
GTEST_MAIN = $(GTEST_BUILD_DIR)/lib/libgtest_main.a
CXXFLAGS_GTEST = -I $(GTEST_DIR)/googletest/include

$(GTEST_DIR):
	git clone --depth=1 $(GTEST_REPO) $(GTEST_DIR)

$(GTEST_LIB): | $(GTEST_DIR)
	mkdir -p $(GTEST_BUILD_DIR)
	cd $(GTEST_BUILD_DIR) && cmake .. && make -j$(nproc)

.PHONY: test
test: mk_dirs $(APP_TEST_PATH)
	./$(APP_TEST_PATH)

-include $(TEST_DEPS)

$(APP_TEST_PATH): $(GTEST_LIB) $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) $(CXXFLAGS_GTEST) $(TEST_OBJS) -o $@ $(GTEST_LIB) $(GTEST_MAIN) -pthread

leaks: $(APP_PATH)
	$(CHECK_LEAKS) $(APP_PATH)
