.PHONY = all clean

CC := g++
LINKERFLAG := -lm # Flags used with compiler

# Recursively find all .cpp files
SRCS := $(shell find . -name '*.cpp') 
BINS := $(SRCS:.cpp=) # Replace .cpp with nothing to get executable names in the same directories

all: ${BINS}

# Rule to create executables, where $@ is the target (executable name)
%: %.cpp
	@echo "Building $@ from $<..."
	${CC} $< ${LINKERFLAG} -o $@

clean:
	@echo "Cleaning up..."
	rm -rvf ${BINS}
