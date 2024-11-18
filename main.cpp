// The main file of the program.

#include <map>

#include "tqp.hpp"


int main(int argc, char* argv[])
{
    return word_query_main<std::map<size_t, std::string>>(std::cout, std::cerr, argc, argv);
}
