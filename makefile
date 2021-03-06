CXX = g++
CXXFLAGS = -g

obj_files = main.o read_variable.o regex.o stack.o instruction.o
smiley: $(obj_files)
	$(CXX) $(CXXFLAGS) -o smiley $(obj_files)

main.o: main.cpp read_variable.h regex.h stack.h instruction.h

read_variables.o: regex.h read_variable.h

regex.o: regex.h read_variable.h

stack.o: stack.h read_variable.h regex.h

instruction.o: instruction.h stack.h read_variable.h regex.h

