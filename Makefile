WIDTH ?= 40
HEIGHT ?= 30
SRULE ?= 1
EXTRA = -Wall -Wextra
CFLAGS = $(EXTRA) -std=c99 -g3
LDFLAGS = -lm
SANDWICH_FLAGS = -DWIDTH=$(WIDTH) -DHEIGHT=$(HEIGHT) -DSET_OF_RULES=$(SRULE) 

SOURCES =  $(wildcard src/*.c)
RULES = $(wildcard src/rules/*.c)
SIMULATION = $(wildcard src/simulation/*.c)
TOOLS = $(wildcard src/tools/*.c)
WORLDS = $(wildcard src/world/*.c)

ALLC = $(SOURCES) $(RULES) $(SIMULATION) $(TOOLS) $(WORLDS)

SOURCES_EXPECT = src/celltype.c src/rule.c
TSTS = $(wildcard tst/*.c) $(WORLDS) $(SOURCES_EXPECT) $(RULES)  $(TOOLS) $(SIMULATION)

TEX = $(wildcard report/*.tex)

all: project

project: src/project.c
		gcc $(CFLAGS) $(SANDWICH_FLAGS) $(ALLC) -o src/project $(LDFLAGS)
test: 
		make subtest SRULE=0
		make subtest SRULE=1
		make subtest SRULE=2
subtest: tst/test.c
		gcc $(CFLAGS) $(SANDWICH_FLAGS) $(TSTS) -o tst/test_project $(LDFLAGS) 
		./tst/test_project
clean:
		rm -f src/project tst/test_project *.pdf
