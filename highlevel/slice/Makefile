CXX := g++
CC := gcc
LINK := g++

COMMONFLAGS += -Wall
COMMONFLAGS += -lm	


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
OBJS = read_stl.c main.c vec_math.c intersections.c svg.c	\
datastructures/red_black_tree.c datastructures/misc.c		\
datastructures/stack.c intersectplane.c event_queue.c		\
datastructures/linkedlist.c

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
