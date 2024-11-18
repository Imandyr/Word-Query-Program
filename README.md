# The Word-Query Program
A program that reads a file, and prints lines in which it found the target word.

tqp.hpp contains the main code of the program — tests.cpp contains and runs tests for the program's code — main.cpp runs the program — build.sh builds main.cpp using GCC — use.sh uses the executable built by build.sh.

The first CLI argument of the program is the path to the target file, and the second argument is the word for which it will search. The program returns an error if more or less arguments are specified.
