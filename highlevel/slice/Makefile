CXX := g++
CC := gcc
LINK := g++

COMMONFLAGS += -Wall
COMMONFLAGS += -Werror
COMMONFLAGS += -lm
CFLAGS += -std=gnu99


# Common flags
ifeq ($(debug),1) 
 COMMONFLAGS += -g
endif

ifeq ($(release),1) 
 COMMONFLAGS += -O2
 COMMONFLAGS += -DNDEBUG
endif


ifeq ($(profile),1) 
 COMMONFLAGS += -pg
endif


BUILDDIR = build
BINDIR = bin
SRCDIR = src
#COMMONFLAGS += -lSDL
CXXFLAGS += $(COMMONFLAGS)
CFLAGS += $(COMMONFLAGS)
LFLAGS += $(COMMONFLAGS)


##the common objects to build
OBJS = read_stl.cpp main.cpp vec_math.cpp intersections.cpp svg.cpp	\
datastructures/red_black_tree.cpp datastructures/misc.cpp		\
datastructures/stack.cpp intersectplane.cpp event_queue.cpp		\
datastructures/linkedlist.cpp Layer.cpp

EXEC = slice


BUILD_OBJS =$(addprefix $(BUILDDIR)/, $(addsuffix .o, $(OBJS)))
LINKLINE = $(LINK) $(LFLAGS) $(BUILD_OBJS) 


.SUFFIXES: .c .cpp .o

$(BUILDDIR)/%.c.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@


$(BUILDDIR)/%.cpp.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(EXEC): $(BUILD_OBJS) 
	$(LINKLINE) -o $(BINDIR)/$(EXEC)

clean:
	rm $(BUILDDIR)/*.o $(BUILDDIR)/datastructures/*.o $(BINDIR)/$(EXEC)
