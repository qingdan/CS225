EXE_DSETS = testdsets
EXE_SQUAREMAZE = testsquaremaze

OBJS_DIR = .objs

OBJS_DSETS_STUDENT = dsets.o
OBJS_DSETS_PROVIDED = testdsets.o
OBJS_SQUAREMAZE_STUDENT = dsets.o maze.o
OBJS_SQUAREMAZE_PROVIDED = testsquaremaze.o rgbapixel.o png.o

CXX = clang++
LD = clang++
WARNINGS = -pedantic -Wall -Werror -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable
CXXFLAGS = -std=c++1y -stdlib=libc++ -g -O0 $(WARNINGS) -MMD -MP -c
LDFLAGS = -std=c++1y -stdlib=libc++ -lpng -lc++abi
ASANFLAGS = -fsanitize=address -fno-omit-frame-pointer

all: mp7.1 mp7.2
mp7.1: $(EXE_DSETS) $(EXE_DSETS)-asan
mp7.2: $(EXE_SQUAREMAZE) $(EXE_SQUAREMAZE)-asan

# Pattern rules for object files
$(OBJS_DIR)/%.o: %.cpp | $(OBJS_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@
$(OBJS_DIR)/%-asan.o: %.cpp | $(OBJS_DIR)
	$(CXX) $(CXXFLAGS) $(ASANFLAGS) $< -o $@

# Create directories
$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

# Rules for executables... we can use a pattern for the -asan versions, but, unfortunately, we can't use a pattern for the normal executables
$(EXE_DSETS):
	$(LD) $^ $(LDFLAGS) -o $@
$(EXE_SQUAREMAZE):
	$(LD) $^ $(LDFLAGS) -o $@
%-asan:
	$(LD) $^ $(LDFLAGS) $(ASANFLAGS) -o $@


# Executable dependencies
$(EXE_DSETS):           $(patsubst %.o, $(OBJS_DIR)/%.o,      $(OBJS_DSETS_STUDENT))        $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS_DSETS_PROVIDED))
$(EXE_DSETS)-asan:      $(patsubst %.o, $(OBJS_DIR)/%-asan.o, $(OBJS_DSETS_STUDENT))        $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS_DSETS_PROVIDED))
$(EXE_SQUAREMAZE):      $(patsubst %.o, $(OBJS_DIR)/%.o,      $(OBJS_SQUAREMAZE_STUDENT))   $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS_SQUAREMAZE_PROVIDED))
$(EXE_SQUAREMAZE)-asan: $(patsubst %.o, $(OBJS_DIR)/%-asan.o, $(OBJS_SQUAREMAZE_STUDENT))   $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS_SQUAREMAZE_PROVIDED))

# Include automatically generated dependencies
-include $(OBJS_DIR)/*.d

clean:
	rm -rf $(EXE_DSETS) $(EXE_DSETS)-asan $(EXE_SQUAREMAZE) $(EXE_SQUAREMAZE)-asan $(OBJS_DIR)

tidy: clean
	rm -rf doc solved.png unsolved.png

.PHONY: all mp7.1 mp7.2 tidy clean
