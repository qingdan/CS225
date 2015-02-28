EXE_OS = testStackQueue
EXE_FILLS = testFills

OBJS_DIR = .objs

OBJS_FILLS_STUDENT = testFills.o solidColorPicker.o gradientColorPicker.o rainbowColorPicker.o
OBJS_FILLS_PROVIDED = animation.o rgbapixel.o png.o gridColorPicker.o
OBJS_OS_STUDENT = testStackQueue.o
OBJS_OS_PROVIDED = 

CXX = clang++
LD = clang++
WARNINGS = -pedantic -Wall -Werror -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable
CXXFLAGS = -std=c++1y -stdlib=libc++ -g -O0 $(WARNINGS) -MMD -MP -c
LDFLAGS = -std=c++1y -stdlib=libc++ -lpng -lc++abi
ASANFLAGS = -fsanitize=address -fno-omit-frame-pointer

all: mp4.1 mp4.2
mp4.1: $(EXE_OS) $(EXE_OS)-asan
mp4.2: $(EXE_FILLS) $(EXE_FILLS)-asan

# Pattern rules for object files
$(OBJS_DIR)/%.o: %.cpp | $(OBJS_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@
$(OBJS_DIR)/%-asan.o: %.cpp | $(OBJS_DIR)
	$(CXX) $(CXXFLAGS) $(ASANFLAGS) $< -o $@

# Create directories
$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

# Rules for executables... we can use a pattern for the -asan versions, but, unfortunately, we can't use a pattern for the normal executables
$(EXE_OS):
	$(LD) $^ $(LDFLAGS) -o $@
$(EXE_FILLS):
	$(LD) $^ $(LDFLAGS) -o $@
%-asan:
	$(LD) $^ $(LDFLAGS) $(ASANFLAGS) -o $@


# Executable dependencies
$(EXE_OS):         $(patsubst %.o, $(OBJS_DIR)/%.o,      $(OBJS_OS_STUDENT)) $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS_OS_PROVIDED))
$(EXE_OS)-asan:    $(patsubst %.o, $(OBJS_DIR)/%-asan.o, $(OBJS_OS_STUDENT)) $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS_OS_PROVIDED))
$(EXE_FILLS):      $(patsubst %.o, $(OBJS_DIR)/%.o,      $(OBJS_FILLS_STUDENT)) $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS_FILLS_PROVIDED))
$(EXE_FILLS)-asan: $(patsubst %.o, $(OBJS_DIR)/%-asan.o, $(OBJS_FILLS_STUDENT)) $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS_FILLS_PROVIDED))

# Include automatically generated dependencies
-include $(OBJS_DIR)/*.d

clean:
	rm -rf $(EXE_OS) $(EXE_OS)-asan $(EXE_FILLS) $(EXE_FILLS)-asan $(OBJS_DIR)

tidy: clean
	rm -rf images frames doc testStackQueue.out testFills.out

.PHONY: all mp4.1 mp4.2 tidy clean
