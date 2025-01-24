# The Word-Query Program
A program that reads a file, and prints lines in which it found the target word.

src/tqp.hpp contains the main code of the program — src/tests.cpp contains and runs tests for the program's code — src/main.cpp runs the program — Makefile builds src/main.cpp using GCC into the bin/main executable — MakefileTests builds src/tests.cpp into bin/tests — use.sh uses the executable built by Makefile — devlog.txt is my thoughts during the program development.

The first CLI argument of the program is the path to the target file, and the second argument is the word for which it will search. The program returns an error if more or less arguments are specified.

### An Example of How the Program Works:
```ruby
$ bin/main text.txt something
something occurs 5 times
    (line 2) something some other text
    (line 4) some other text something
    (line 6) put something in the middle
    (line 7) another something after something
```
