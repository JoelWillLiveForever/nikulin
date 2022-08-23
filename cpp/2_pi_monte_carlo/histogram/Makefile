# компилятор и базовые флаги
CXX = g++
CXXFLAGS = -Wall

# исходные файлы
SRCS = main.cpp \
	   xor_shift_64__generator_class.cpp \
	   xor_shift_1024__generator_class.cpp \
	   mt19937__sample_class.cpp \
	   xor_shift_64__sample_class.cpp \
	   xor_shift_1024__sample_class.cpp

# заменить суффиксы для получения имён объектных файлов
OBJS = $(SRCS:.cpp=.o)

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

.PHONY: all clean debug prep release remake

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
# Other rules
#
prep:
	@mkdir -p $(DBGDIR) $(RELDIR)

remake: clean all

# удалить всё компилируемое
clean:
	rm -rf $(DBGEXE) $(RELEXE) $(DBGOBJS) $(RELOBJS) $(DBGDIR) $(RELDIR) *.csv
