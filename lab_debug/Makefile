EXE = sketchify

OBJS_DIR = .objs

OBJS_STUDENT = sketchify.o
OBJS_PROVIDED = main.o rgbapixel.o png.o

CXX = clang++
LD = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -g -O0 -w -MMD -MP -c
LDFLAGS = -std=c++1y -stdlib=libc++ -lpng -lc++abi

all: $(EXE)

# Pattern rules for object files
$(OBJS_DIR)/%.o: %.cpp | $(OBJS_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@

# Create directories
$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

$(EXE):
	$(LD) $^ $(LDFLAGS) -o $@

# Executable dependencies
$(EXE):      $(patsubst %.o, $(OBJS_DIR)/%.o,      $(OBJS_STUDENT)) $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS_PROVIDED))

# Include automatically generated dependencies
-include $(OBJS_DIR)/*.d

clean:
	rm -rf $(EXE) $(OBJS_DIR)

tidy: clean
	rm -rf doc out.png

.PHONY: all tidy clean
