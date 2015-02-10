EXENAME1 = testimage
EXENAME2 = testscene

OBJS1 = testimage.o  png.o rgbapixel.o image.o
OBJS2 = testscene.o scene.o png.o rgbapixel.o image.o
ifdef asan
ASANFLAGS = -fsanitize = address
endif

CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lpng -lc++abi

all : testimage testscene

$(EXENAME1) : $(OBJS1)
	$(LD) $(OBJS1) $(LDFLAGS) -o $(EXENAME1)
$(EXENAME2) : $(OBJS2)
	$(LD) $(OBJS2) $(LDFLAGS) -o $(EXENAME2)

testscene.o : testscene.cpp scene.h png.h rgbapixel.h image.h
	$(CXX) $(CXXFLAGS) testscene.cpp

testimage.o : testimage.cpp png.h rgbapixel.h image.h
	$(CXX) $(CXXFLAGS) testimage.cpp

scene.o : scene.cpp scene.h image.h rgbapixel.h png.h
	$(CXX) $(CXXFLAGS) scene.cpp

image.o : image.cpp image.h rgbapixel.h png.h
	$(CXX) $(CXXFLAGS) image.cpp

png.o : png.cpp png.h rgbapixel.h
	$(CXX) $(CXXFLAGS) png.cpp

rgbapixel.o : rgbapixel.cpp rgbapixel.h
	$(CXX) $(CXXFLAGS) rgbapixel.cpp


clean :
	-rm -f *.o $(EXENAME1)
	-rm -f *.o $(EXENAME2)
