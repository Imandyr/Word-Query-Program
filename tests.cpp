// Tests.

#include <vector>
#include <sstream>
#include <fstream>
#include <map>
#include <string>
#include <iostream>

#include "./tqp.hpp"

using namespace std;
using test_function = bool(*)();

// "./" makes the .find_last_of() point on "./" if there weren't any other slashes inside.
const string file_path = "./" + string(__FILE__);
const string current_dir = file_path.substr(0, file_path.find_last_of("/\\"));
const string path_to_text = current_dir + "/text.txt";

#define TARGET_RESULT_INPUT_1  \
    vector<string> target = {"The first line.", "The second line.", "The third line."},  \
                   result;  \
    istringstream input("The first line.\nThe second line.\nThe third line.\n");

#define TARGET_RESULT_INPUT_2  \
    ostringstream target  \
    (  \
        "something occurs 3 times\n"  \
        "    (line 2) There is something in the dark for us to find.\n"  \
        "    (line 21) This someone who you referring to did something very, very terrible.\n"  \
        "    (line 321) Grassland totaling something over three hundred acres.\n"  \
    ),  \
                  result;  \
    string input_word = "something";  \
    size_t input_count = 3;  \
    map<size_t, string> input_map  \
    {  \
        {2, "There is something in the dark for us to find."},  \
        {21, "This someone who you referring to did something very, very terrible."},  \
        {321, "Grassland totaling something over three hundred acres."}  \
    };  \

#define TARGET_RESULT_INPUT_3  \
    map<size_t, string> target_map  \
    {  \
        {2, "something some other text"},  \
        {4, "some other text something"},  \
        {6, "put something in the middle"},  \
        {7, "another something after something"},  \
    },  \
                        result_map;  \
    size_t target_count_wa = 5,  \
           result_count_l = 1,  \
           result_count_wa = 0;  \
    istringstream input_stream  \
    (  \
        "There is nothing in the shadows,\n"  \
        "something some other text\n"  \
        "And I will be the one to die alone.\n"  \
        "some other text something\n"  \
        "Forgive me when I fall,\n"  \
        "put something in the middle\n"  \
        "another something after something\n"  \
        "And I will be the one to die alone.\n"  \
        "\n"  \
    );  \
    istream_line_iterator input_begin_iter(input_stream),  \
                          input_end_iter;  \
    string input_word = "something";  \

#define TARGET_RESULT_INPUT_4  \
    ostringstream target  \
    (  \
        "something occurs 5 times\n"  \
        "    (line 2) something some other text\n"  \
        "    (line 4) some other text something\n"  \
        "    (line 6) put something in the middle\n"  \
        "    (line 7) another something after something\n"  \
    ),  \
                  result;  \
    string input_word = "something";  \

#define TARGET_RESULT_INPUT_5  \
    TARGET_RESULT_INPUT_4  \
    ostringstream target_error,  \
                  result_error;  \
    int input_argc = 3;  \
    char* input_argv[] = {nullptr,  const_cast<char*>(path_to_text.c_str()),  \
                                const_cast<char*>(input_word.c_str())};  \

#define TARGET_RESULT_INPUT_6  \
    ostringstream target_output,  \
                  target_error("WordQueryProgramError: An invalid number of arguments is specified.\n"),  \
                  result_output,  \
                  result_error;  \
    int input_argc = 2;  \
    char* input_argv[] = {nullptr, const_cast<char*>(path_to_text.c_str())};  \


bool test_Line()
// A test for the Line class.
{
    TARGET_RESULT_INPUT_1
    Line<istringstream, string> line;

    // Read the input stream line by line.
    while(input >> line)
    {
        result.push_back(line);
    }

    return target == result;
}


bool test_istream_line_iterator()
// Checks the behavior of the istream_line_iterator made to iterate through an istringstream.
{
    TARGET_RESULT_INPUT_1

    istream_line_iterator begin(input), end;

    while (begin != end)
        { result.push_back(*begin++); }

    return target == result;
}


bool test_print_cl()
// Checks if print_cl prints the data in the right way.
{
    TARGET_RESULT_INPUT_2

    print_cl(result, input_word, input_count, input_map);

    return target.str() == result.str();
}


bool test_query_word_1()
// Checks if query_word works as intended.
{
    TARGET_RESULT_INPUT_3

    query_word(input_begin_iter, input_end_iter, input_word, result_count_l, result_count_wa, result_map);

    return target_map == result_map && target_count_wa == result_count_wa;
}


bool test_word_query_file()
// Tests if the main functional of the program works.
{
    TARGET_RESULT_INPUT_4

    word_query_file<map<size_t, string>>(result, path_to_text, input_word);

    return target.str() == result.str();
}


bool test_word_query_main_valid()
// Test of the CLI interface when the input is valid.
{
    TARGET_RESULT_INPUT_5

    word_query_main<map<size_t, string>>(result, result_error, input_argc, input_argv);

    return target.str() == result.str() && target_error.str() == result_error.str();
}


bool test_word_query_main_invalid()
// Test of the CLI interface when the input is invalid.
{
    TARGET_RESULT_INPUT_6

    word_query_main<map<size_t, string>>(result_output, result_error, input_argc, input_argv);

    return target_error.str() == result_error.str() && target_output.str() == result_output.str();
}


void exec_tests(vector<pair<string, test_function>> &tests)
// Executes given tests, and prints if they passed or failed.
{
    for (const auto &test : tests)
    {
        cout << "    " + test.first + ": " << (test.second() ? "Passed" : "Failed") << "\n";
    }
}


int main()
// Execution of all tests.
{
    cout << "Word-Query's Tests:\n";

    vector<pair<string, test_function>> tests =
    {
        {"test_Line", test_Line},
        {"test_istream_line_iterator", test_istream_line_iterator},
        {"test_print_cl", test_print_cl},
        {"test_query_word_1", test_query_word_1},
        {"test_word_query_file", test_word_query_file},
        {"test_word_query_main_valid", test_word_query_main_valid},
        {"test_word_query_main_invalid", test_word_query_main_invalid},
    };

    exec_tests(tests);

    return 0;
}

