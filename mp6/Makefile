EXE = photomosaic
EXE_KDTREE = testkdtree
EXE_MAPTILES = testmaptiles

OBJS_DIR = .objs
OBJS_DIR_STUDENT = $(OBJS_DIR)/student
OBJS_DIR_PROVIDED = $(OBJS_DIR)/provided

OBJS_STUDENT = maptiles.o
OBJS_PROVIDED = photomosaic.o util.o mosaiccanvas.o sourceimage.o  rgbapixel.o png.o coloredout.o tileimage.o
OBJS_KDTREE_STUDENT = testkdtree.o
OBJS_KDTREE_PROVIDED = coloredout.o
OBJS_MAPTILES_STUDENT = testmaptiles.o
OBJS_MAPTILES_PROVIDED = mosaiccanvas.o sourceimage.o maptiles.o rgbapixel.o png.o coloredout.o tileimage.o

CXX = clang++
LD = clang++
WARNINGS = -pedantic -Wall -Werror -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable
CXXFLAGS = -std=c++1y -stdlib=libc++ -g -O0 $(WARNINGS) -MMD -MP -msse2 -c
CXXFLAGS_PROVIDED = -O2
CXXFLAGS_STUDENT = -O0
LDFLAGS = -std=c++1y -stdlib=libc++ -lpng -lc++abi
ASANFLAGS = -fsanitize=address -fno-omit-frame-pointer


all: mp6.1 mp6.2
mp6.1: $(EXE_KDTREE) $(EXE_KDTREE)-asan
mp6.2: $(EXE_MAPTILES) $(EXE_MAPTILES)-asan $(EXE) $(EXE)-asan

# Pattern rules for object files
$(OBJS_DIR_STUDENT)/%-asan.o: %.cpp | $(OBJS_DIR_STUDENT)
	$(CXX) $(CXXFLAGS) $(CXXFLAGS_STUDENT) $(ASANFLAGS) $< -o $@
$(OBJS_DIR_PROVIDED)/%-asan.o: %.cpp | $(OBJS_DIR_PROVIDED)
	$(CXX) $(CXXFLAGS) $(CXXFLAGS_PROVIDED) $(ASANFLAGS) $< -o $@
$(OBJS_DIR_STUDENT)/%.o: %.cpp | $(OBJS_DIR_STUDENT)
	$(CXX) $(CXXFLAGS) $(CXXFLAGS_STUDENT) $< -o $@
$(OBJS_DIR_PROVIDED)/%.o: %.cpp | $(OBJS_DIR_PROVIDED)
	$(CXX) $(CXXFLAGS) $(CXXFLAGS_PROVIDED) $< -o $@

# Create directories
$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)
$(OBJS_DIR_STUDENT):
	@mkdir -p $(OBJS_DIR_STUDENT)
$(OBJS_DIR_PROVIDED):
	@mkdir -p $(OBJS_DIR_PROVIDED)

# Rules for executables... we can use a pattern for the -asan versions, but, unfortunately, we can't use a pattern for the normal executables
$(EXE):
	$(LD) $^ $(LDFLAGS) -o $@
$(EXE_KDTREE):
	$(LD) $^ $(LDFLAGS) -o $@
$(EXE_MAPTILES):
	$(LD) $^ $(LDFLAGS) -o $@
%-asan:
	$(LD) $^ $(LDFLAGS) $(ASANFLAGS) -o $@


# Executable dependencies
$(EXE):               $(patsubst %.o, $(OBJS_DIR_STUDENT)/%.o,      $(OBJS_STUDENT))          $(patsubst %.o, $(OBJS_DIR_PROVIDED)/%.o, $(OBJS_PROVIDED))
$(EXE)-asan:          $(patsubst %.o, $(OBJS_DIR_STUDENT)/%-asan.o, $(OBJS_STUDENT))          $(patsubst %.o, $(OBJS_DIR_PROVIDED)/%.o, $(OBJS_PROVIDED))
$(EXE_KDTREE):        $(patsubst %.o, $(OBJS_DIR_STUDENT)/%.o,      $(OBJS_KDTREE_STUDENT))   $(patsubst %.o, $(OBJS_DIR_PROVIDED)/%.o, $(OBJS_KDTREE_PROVIDED))
$(EXE_KDTREE)-asan:   $(patsubst %.o, $(OBJS_DIR_STUDENT)/%-asan.o, $(OBJS_KDTREE_STUDENT))   $(patsubst %.o, $(OBJS_DIR_PROVIDED)/%.o, $(OBJS_KDTREE_PROVIDED))
$(EXE_MAPTILES):      $(patsubst %.o, $(OBJS_DIR_STUDENT)/%.o,      $(OBJS_MAPTILES_STUDENT)) $(patsubst %.o, $(OBJS_DIR_PROVIDED)/%.o, $(OBJS_MAPTILES_PROVIDED))
$(EXE_MAPTILES)-asan: $(patsubst %.o, $(OBJS_DIR_STUDENT)/%-asan.o, $(OBJS_MAPTILES_STUDENT)) $(patsubst %.o, $(OBJS_DIR_PROVIDED)/%.o, $(OBJS_MAPTILES_PROVIDED))


# Include automatically generated dependencies
-include $(OBJS_DIR_STUDENT)/*.d
-include $(OBJS_DIR_PROVIDED)/*.d

clean:
	rm -rf $(EXE) $(EXE)-asan $(EXE_KDTREE) $(EXE_KDTREE)-asan $(EXE_MAPTILES) $(EXE_MAPTILES)-asan $(OBJS_DIR)

tidy: clean
	rm -rf doc

.PHONY: all mp6.1 mp6.2 tidy clean check
