# компилятор и базовые флаги
CXX = g++
CXXFLAGS = -Wall

# precompiled headers file
PCHPATH = pch.hpp

# исходные файлы
SRCS = main.cpp \
	   weight_combinator_class.cpp
SRCS_TEST = test.cpp \
			weight_combinator_class.cpp

# заменить суффиксы для получения имён объектных файлов
OBJS = $(SRCS:.cpp=.o)
OBJS_TEST = $(SRCS_TEST:.cpp=.o)

# имя исполняемого файла
EXE = executable

# debug build settings
DBGDIR = debug
DBGEXE = $(DBGDIR)/$(EXE)
DBGOBJS = $(addprefix $(DBGDIR)/, $(OBJS))
DBGCXXFLAGS = -g -O0 -DDEBUG

# Release build settings
RELDIR = release
RELEXE = $(RELDIR)/$(EXE)
RELOBJS = $(addprefix $(RELDIR)/, $(OBJS))
RELCXXFLAGS = -O3 -DNDEBUG

# tests build settings
TESTDIR = tests
TESTEXE = $(TESTDIR)/$(EXE)
TESTOBJS = $(addprefix $(TESTDIR)/, $(OBJS_TEST))
TESTCXXFLAGS = -g -O0 -DDEBUG

.PHONY: all clean debug prep release test remake pch

# Default build
all: prep release

#
# Debug rules
# 
debug: prep $(DBGEXE)

$(DBGEXE): $(DBGOBJS)
	$(CXX) $(CXXFLAGS) $(DBGCXXFLAGS) -o $(DBGEXE) $^

$(DBGDIR)/%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $(DBGCXXFLAGS) -o $@ $<

#
# Release rules
# 
release: $(RELEXE)

$(RELEXE): $(RELOBJS)
	$(CXX) $(CXXFLAGS) $(RELCXXFLAGS) -o $(RELEXE) $^

$(RELDIR)/%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $(RELCXXFLAGS) -o $@ $<

#
# Tests rules
#
test: prep $(TESTEXE)

$(TESTEXE): $(TESTOBJS)
	$(CXX) $(CXXFLAGS) $(TESTCXXFLAGS) -o $(TESTEXE) $^

$(TESTDIR)/%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $(TESTCXXFLAGS) -o $@ $<

#
# Other rules
#
prep:
	@mkdir -p $(DBGDIR) $(RELDIR) $(TESTDIR)

pch: $(PCHPATH)
	$(CXX) -x c++-header $<

remake: clean all

# удалить всё компилируемое
clean:
	rm -rf $(DBGEXE) $(DBGOBJS) $(DBGDIR) $(RELEXE) $(RELOBJS) $(RELDIR) $(TESTEXE) $(TESTOBJS) $(TESTDIR)
