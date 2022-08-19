# компилятор и базовые флаги
CXX = g++
CXXFLAGS = -Wall

# исходные файлы
SRCS = main.cpp \
	   pi_convergence_check_class.cpp \
	   pi_monte_carlo_points_generator_class.cpp \
	   true_pi_selector_class.cpp

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
	rm -rf $(DBGEXE) $(RELEXE) $(DBGOBJS) $(RELOBJS) $(DBGDIR) $(RELDIR)
