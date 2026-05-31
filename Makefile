CXX      := clang++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2
LDFLAGS  := $(shell pkg-config --libs raylib)
CPPFLAGS := $(shell pkg-config --cflags raylib)

BUILDDIR := build
SRC      := $(wildcard *.cpp)
OBJ      := $(SRC:%.cpp=$(BUILDDIR)/%.o)
DEP      := $(OBJ:.o=.d)
BIN      := brotato-clone

all: $(BIN)

$(BIN): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(BUILDDIR)/%.o: %.cpp | $(BUILDDIR)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -MMD -MP -c $< -o $@

-include $(DEP)

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

debug: CXXFLAGS := -std=c++17 -Wall -Wextra -g -O0 -DDEBUG
debug: clean $(BIN)

sanitize: CXXFLAGS := -std=c++17 -Wall -Wextra -g -O0 -DDEBUG -fsanitize=address
sanitize: LDFLAGS += -fsanitize=address
sanitize: clean $(BIN)

run: $(BIN)
	./$(BIN)

clean:
	rm -rf $(BUILDDIR) $(BIN)

.PHONY: all debug run clean
