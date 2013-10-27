CC      = clang++
CFLAGS  = -O0 -g3 -c -Wall -pedantic -std=c++11 -stdlib=libc++

LDFLAGS = -stdlib=libc++ -L../.libs -lde
SRCS    = basic.cpp data.cpp

OBJS := $(SRCS:.cpp=.o)
BINS := $(SRCS:%.cpp=test_%)
DEPS := $(OBJS:.o=.d)

.PHONY: all clean

all: $(BINS)
	@for t in $^; do DYLD_LIBRARY_PATH=../.libs ./$$t; done

# The actual build target.
# Dependency files are generated for each object file built.
# Also adds empty targets for real files so that a removal
# of any such file wont exit with failure (but rather rebuild the target)
%.o: %.cpp Makefile
	$(CC) $(CFLAGS) $< -o $@
	$(CC) -MM $(CFLAGS) $< > $*.d
	@mv -f $*.d $*.d.tmp
	@sed -e 's|.*:|$*.o:|' < $*.d.tmp > $*.d
	@cp -f $*.d $*.d.tmp
	@sed -e 's/.*://' -e 's/\\$$//' < $*.d.tmp | fmt -1 | \
		sed -e 's/^ *//' -e 's/$$/:/' >> $*.d
	@rm -f $*.d.tmp

test_%: %.o
	$(CC) $(LDFLAGS) $^ -o $@

clean:
	rm -f $(OBJS) $(DEPS) $(BINS)

-include $(DEPS)
