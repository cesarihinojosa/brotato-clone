CXX      := clang++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2
LDFLAGS  := $(shell pkg-config --libs raylib)

SRCDIRS  := core components entities
CPPFLAGS := $(shell pkg-config --cflags raylib) $(addprefix -I,$(SRCDIRS))

GIT_COMMIT := $(shell git rev-parse --short HEAD 2>/dev/null || echo unknown)

BUILDDIR := build
SRC      := main.cpp $(foreach d,$(SRCDIRS),$(wildcard $(d)/*.cpp))
OBJ      := $(SRC:%.cpp=$(BUILDDIR)/%.o)
DEP      := $(OBJ:.o=.d)
BIN      := brotato-clone

BENCH_BIN := brotato-bench
BENCH_SRC := main_bench.cpp bench/alloc_counter.cpp \
            $(foreach d,$(SRCDIRS),$(wildcard $(d)/*.cpp))
BENCH_OBJ := $(BENCH_SRC:%.cpp=$(BUILDDIR)/%.o)

all: $(BIN)

$(BIN): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(BUILDDIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -MMD -MP -c $< -o $@

-include $(DEP)

debug: CXXFLAGS := -std=c++17 -Wall -Wextra -g -O0 -DDEBUG
debug: clean $(BIN)

sanitize: CXXFLAGS := -std=c++17 -Wall -Wextra -g -O0 -DDEBUG -fsanitize=address
sanitize: LDFLAGS += -fsanitize=address
sanitize: clean $(BIN)

run: $(BIN)
	./$(BIN)

# Performance benchmark: release build, separate entry point, alloc counter
# linked in. Bakes the git commit and build mode into the binary so each CSV
# row knows which build produced it.
bench: CXXFLAGS := -std=c++17 -Wall -Wextra -O2 \
                   -DGIT_COMMIT=\"$(GIT_COMMIT)\" -DBUILD_MODE=\"release\"
bench: CPPFLAGS += -Ibench
bench: $(BENCH_BIN)
	@mkdir -p benchmarks
	./$(BENCH_BIN) --entities=$(or $(N),1000) --frames=$(or $(F),600)

$(BENCH_BIN): $(BENCH_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -rf $(BUILDDIR) $(BIN) $(BENCH_BIN)

docs:
	doxygen Doxyfile

.PHONY: all debug run bench clean docs
