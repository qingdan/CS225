EXE_BTREE = test_btree
EXE_RACER = dict_racer

OBJS_DIR = .objs
RESULTS_DIR = results

OBJS_BTREE_STUDENT = test_btree.o
OBJS_BTREE_PROVIDED =
OBJS_RACER_STUDENT =
OBJS_RACER_PROVIDED = dict_racer.o

CXX = clang++
LD = clang++
WARNINGS = -pedantic -Wall -Werror -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable
CXXFLAGS = -std=c++1y -stdlib=libc++ -g -O0 $(WARNINGS) -MMD -MP -c
LDFLAGS = -std=c++1y -stdlib=libc++ -lpng -lc++abi
ASANFLAGS = -fsanitize=address -fno-omit-frame-pointer

all: $(EXE_BTREE) $(EXE_BTREE)-asan \
	$(EXE_RACER)

# Pattern rules for object files
$(OBJS_DIR)/%.o: %.cpp | $(OBJS_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@
$(OBJS_DIR)/%-asan.o: %.cpp | $(OBJS_DIR)
	$(CXX) $(CXXFLAGS) $(ASANFLAGS) $< -o $@

# Create directories
$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

$(RESULTS_DIR):
	@mkdir -p $(RESULTS_DIR)

# Rules for executables... we can use a pattern for the -asan versions, but, unfortunately, we can't use a pattern for the normal executables
$(EXE_BTREE):
	$(LD) $^ $(LDFLAGS) -o $@
$(EXE_RACER): | $(RESULTS_DIR)
	$(LD) $^ $(LDFLAGS) -O3 -o $@
%-asan:
	$(LD) $^ $(LDFLAGS) $(ASANFLAGS) -o $@

# Executable dependencies
$(EXE_BTREE):           $(patsubst %.o, $(OBJS_DIR)/%.o,      $(OBJS_BTREE_STUDENT)) $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS_BTREE_PROVIDED))
$(EXE_BTREE)-asan:      $(patsubst %.o, $(OBJS_DIR)/%-asan.o, $(OBJS_BTREE_STUDENT)) $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS_BTREE_PROVIDED))
$(EXE_RACER):               $(patsubst %.o, $(OBJS_DIR)/%.o,      $(OBJS_RACER_STUDENT)) $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS_RACER_PROVIDED))

# Include automatically generated dependencies
-include $(OBJS_DIR)/*.d

clean:
	rm -rf $(EXE_BTREE) $(EXE_BTREE)-asan \
		$(EXE_RACER) \
		$(OBJS_DIR) \
		$(RESULTS_DIR)

tidy: clean
	rm -rf doc

.PHONY: all tidy clean
