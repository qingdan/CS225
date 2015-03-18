EXE_ANAGRAM = anagram_finder
EXE_FIB = fib_generator
EXE_FAC = fac
EXE_HOMOPHONE = homophone_puzzle
EXE_COMMON_WORDS = find_common_words

OBJS_DIR = .objs

OBJS_ANAGRAM_STUDENT = anagram_dict.o
OBJS_ANAGRAM_PROVIDED = anagram_finder.o
OBJS_FIB_STUDENT = fib.o
OBJS_FIB_PROVIDED = fib_generator.o
OBJS_FAC_STUDENT =
OBJS_FAC_PROVIDED = fac.o
OBJS_HOMOPHONE_STUDENT = pronounce_dict.o cartalk_puzzle.o
OBJS_HOMOPHONE_PROVIDED = homophone_puzzle.o
OBJS_COMMON_WORDS_STUDENT = common_words.o
OBJS_COMMON_WORDS_PROVIDED = find_common_words.o


CXX = clang++
LD = clang++
WARNINGS = -pedantic -Wall -Werror -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable
CXXFLAGS = -std=c++1y -stdlib=libc++ -g -O0 $(WARNINGS) -MMD -MP -c
LDFLAGS = -std=c++1y -stdlib=libc++ -lpng -lc++abi
ASANFLAGS = -fsanitize=address -fno-omit-frame-pointer

all: $(EXE_ANAGRAM) $(EXE_ANAGRAM)-asan \
	$(EXE_FIB) $(EXE_FIB)-asan \
	$(EXE_FAC) $(EXE_FAC)-asan \
	$(EXE_HOMOPHONE) $(EXE_HOMOPHONE)-asan \
	$(EXE_COMMON_WORDS) $(EXE_COMMON_WORDS)-asan

# Pattern rules for object files
$(OBJS_DIR)/%.o: %.cpp | $(OBJS_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@
$(OBJS_DIR)/%-asan.o: %.cpp | $(OBJS_DIR)
	$(CXX) $(CXXFLAGS) $(ASANFLAGS) $< -o $@

# Create directories
$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

# Rules for executables... we can use a pattern for the -asan versions, but, unfortunately, we can't use a pattern for the normal executables
$(EXE_ANAGRAM):
	$(LD) $^ $(LDFLAGS) -o $@
$(EXE_FIB):
	$(LD) $^ $(LDFLAGS) -o $@
$(EXE_FAC):
	$(LD) $^ $(LDFLAGS) -o $@
$(EXE_HOMOPHONE):
	$(LD) $^ $(LDFLAGS) -o $@
$(EXE_COMMON_WORDS):
	$(LD) $^ $(LDFLAGS) -o $@
%-asan:
	$(LD) $^ $(LDFLAGS) $(ASANFLAGS) -o $@

# Executable dependencies
$(EXE_ANAGRAM):           $(patsubst %.o, $(OBJS_DIR)/%.o,      $(OBJS_ANAGRAM_STUDENT)) $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS_ANAGRAM_PROVIDED))
$(EXE_ANAGRAM)-asan:      $(patsubst %.o, $(OBJS_DIR)/%-asan.o, $(OBJS_ANAGRAM_STUDENT)) $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS_ANAGRAM_PROVIDED))
$(EXE_FIB):               $(patsubst %.o, $(OBJS_DIR)/%.o,      $(OBJS_FIB_STUDENT)) $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS_FIB_PROVIDED))
$(EXE_FIB)-asan:          $(patsubst %.o, $(OBJS_DIR)/%-asan.o, $(OBJS_FIB_STUDENT)) $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS_FIB_PROVIDED))
$(EXE_FAC):               $(patsubst %.o, $(OBJS_DIR)/%.o,      $(OBJS_FAC_STUDENT)) $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS_FAC_PROVIDED))
$(EXE_FAC)-asan:          $(patsubst %.o, $(OBJS_DIR)/%-asan.o, $(OBJS_FAC_STUDENT)) $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS_FAC_PROVIDED))
$(EXE_HOMOPHONE):         $(patsubst %.o, $(OBJS_DIR)/%.o,      $(OBJS_HOMOPHONE_STUDENT)) $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS_HOMOPHONE_PROVIDED))
$(EXE_HOMOPHONE)-asan:    $(patsubst %.o, $(OBJS_DIR)/%-asan.o, $(OBJS_HOMOPHONE_STUDENT)) $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS_HOMOPHONE_PROVIDED))
$(EXE_COMMON_WORDS):      $(patsubst %.o, $(OBJS_DIR)/%.o,      $(OBJS_COMMON_WORDS_STUDENT)) $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS_COMMON_WORDS_PROVIDED))
$(EXE_COMMON_WORDS)-asan: $(patsubst %.o, $(OBJS_DIR)/%-asan.o, $(OBJS_COMMON_WORDS_STUDENT)) $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS_COMMON_WORDS_PROVIDED))

# Include automatically generated dependencies
-include $(OBJS_DIR)/*.d

clean:
	rm -rf $(EXE_ANAGRAM) $(EXE_ANAGRAM)-asan \
		$(EXE_FIB) $(EXE_FIB)-asan \
		$(EXE_FAC) $(EXE_FAC)-asan \
		$(EXE_HOMOPHONE) $(EXE_HOMOPHONE)-asan \
		$(EXE_COMMON_WORDS) $(EXE_COMMON_WORDS)-asan \
		$(OBJS_DIR)

tidy: clean
	rm -rf doc

.PHONY: all tidy clean
