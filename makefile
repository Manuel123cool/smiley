files = main.cpp read_variable.cpp regex.cpp
smiley: $(files)
	g++ -o smiley $(files) -I.
