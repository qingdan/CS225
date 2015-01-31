EXENAME = testimage
OBJS = testimage.o  png.o rgbapixel.o image.o

CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lpng -lc++abi

all : $(EXENAME)

$(EXENAME) : $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)
testimage.o : testimage.cpp png.h rgbapixel.h image.h
	$(CXX) $(CXXFLAGS) testimage.cpp

image.o : image.cpp image.h rgbapixel.h png.h
	$(CXX) $(CXXFLAGS) image.cpp

png.o : png.cpp png.h rgbapixel.h
	$(CXX) $(CXXFLAGS) png.cpp

rgbapixel.o : rgbapixel.cpp rgbapixel.h
	$(CXX) $(CXXFLAGS) rgbapixel.cpp



clean :
	-rm -f *.o $(EXENAME)
