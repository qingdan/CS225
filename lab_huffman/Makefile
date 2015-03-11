EXE_DECODER = decoder
EXE_ENCODER = encoder
EXE_PRINTER = print_as_ascii

OBJS_DIR = .objs

OBJS_ENCODER_STUDENT = huffman_tree.o
OBJS_ENCODER_PROVIDED = frequency.o encoder.o encoder_prog.o binary_file_writer.o binary_file_reader.o
OBJS_DECODER_STUDENT = huffman_tree.o
OBJS_DECODER_PROVIDED = frequency.o decoder.o decoder_prog.o binary_file_writer.o binary_file_reader.o
OBJS_PRINTER_STUDENT =
OBJS_PRINTER_PROVIDED = binary_file_reader.o print_as_ascii.o

CXX = clang++
LD = clang++
WARNINGS = -pedantic -Wall -Werror -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable
CXXFLAGS = -std=c++1y -stdlib=libc++ -g -O0 $(WARNINGS) -MMD -MP -c
LDFLAGS = -std=c++1y -stdlib=libc++ -lpng -lc++abi
ASANFLAGS = -fsanitize=address -fno-omit-frame-pointer

all: $(EXE_ENCODER) $(EXE_ENCODER)-asan \
	$(EXE_DECODER) $(EXE_DECODER)-asan \
	$(EXE_PRINTER) $(EXE_PRINTER)-asan

data:
	svn export https://subversion.ews.illinois.edu/svn/sp15-cs225/_shared/lab_huffman_data data

# Pattern rules for object files
$(OBJS_DIR)/%.o: %.cpp | $(OBJS_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@
$(OBJS_DIR)/%-asan.o: %.cpp | $(OBJS_DIR)
	$(CXX) $(CXXFLAGS) $(ASANFLAGS) $< -o $@

# Create directories
$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

# Rules for executables... we can use a pattern for the -asan versions, but, unfortunately, we can't use a pattern for the normal executables
$(EXE_DECODER):
	$(LD) $^ $(LDFLAGS) -o $@
$(EXE_ENCODER):
	$(LD) $^ $(LDFLAGS) -o $@
$(EXE_PRINTER):
	$(LD) $^ $(LDFLAGS) -o $@
%-asan:
	$(LD) $^ $(LDFLAGS) $(ASANFLAGS) -o $@


# Executable dependencies
$(EXE_DECODER):      $(patsubst %.o, $(OBJS_DIR)/%.o,      $(OBJS_DECODER_STUDENT)) $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS_DECODER_PROVIDED))
$(EXE_DECODER)-asan: $(patsubst %.o, $(OBJS_DIR)/%-asan.o, $(OBJS_DECODER_STUDENT)) $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS_DECODER_PROVIDED))
$(EXE_ENCODER):      $(patsubst %.o, $(OBJS_DIR)/%.o,      $(OBJS_ENCODER_STUDENT)) $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS_ENCODER_PROVIDED))
$(EXE_ENCODER)-asan: $(patsubst %.o, $(OBJS_DIR)/%-asan.o, $(OBJS_ENCODER_STUDENT)) $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS_ENCODER_PROVIDED))
$(EXE_PRINTER):      $(patsubst %.o, $(OBJS_DIR)/%.o,      $(OBJS_PRINTER_STUDENT)) $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS_PRINTER_PROVIDED))
$(EXE_PRINTER)-asan: $(patsubst %.o, $(OBJS_DIR)/%-asan.o, $(OBJS_PRINTER_STUDENT)) $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS_PRINTER_PROVIDED))

# Include automatically generated dependencies
-include $(OBJS_DIR)/*.d

clean:
	rm -rf $(EXE_ENCODER) $(EXE_ENCODER)-asan \
		$(EXE_DECODER) $(EXE_DECODER)-asan \
		$(EXE_PRINTER) $(EXE_PRINTER)-asan \
		$(OBJS_DIR)

tidy: clean
	rm -rf doc *.bin *.txt *.huff

.PHONY: all tidy clean
