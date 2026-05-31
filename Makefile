CXX      := clang++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2
LDFLAGS  := $(shell pkg-config --libs raylib)
CPPFLAGS := $(shell pkg-config --cflags raylib)

BUILDDIR := build
SRC      := $(wildcard *.cpp)
OBJ      := $(SRC:%.cpp=$(BUILDDIR)/%.o)
BIN      := brotato-clone

all: $(BIN)

$(BIN): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(BUILDDIR)/%.o: %.cpp | $(BUILDDIR)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

run: $(BIN)
	./$(BIN)

clean:
	rm -rf $(BUILDDIR) $(BIN)

.PHONY: all run clean
