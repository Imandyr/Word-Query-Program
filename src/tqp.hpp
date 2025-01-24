#ifndef TQP
#define TQP


#include <iterator>
#include <iostream>
#include <fstream>
#include <string>


template<typename IStream, typename Data> class Line
// Reads a line from an IStream into the inner _Data when "IStream >> Line" is called.
{
public:
    operator Data() const {return data;}

    friend IStream& operator>>(IStream &istream, Line &line)
    {
        getline(istream, line.data);
        return istream;
    }
private:
    Data data;
};


// An istream_iterator that applies the iterator interface to the Line class.
using istream_line_iterator = std::istream_iterator<Line<std::basic_istream<char>, std::string>>;


template<typename OStream, typename String, typename Count, typename LMap>
    void print_cl(OStream &ostream, const String &word, Count count, const LMap &f_lines)
// Writes the word, count, and the strings from the lmap with their keys attached, into the ostream.
{
    ostream << word << " occurs " << count << " times\n";

    for (auto &i : f_lines)
    {
        ostream << "    (line " << i.first << ") " << i.second << "\n";
    }
}


template<typename SIter, typename String, typename Count1, typename Count2, typename LMap>
    void query_word(SIter begin, SIter end, const String &word, Count1 &count_l, Count2 &count_wa, LMap &f_lines)
// Iterates strings from the begin:end iterator range, counts strings into count_l, counts word's appearances into count_wa,
//   and writes string where it found the word into f_lines, using the number of this string as the key.
// Arguments:
//   begin: the input iterator that yields String objects.
//   end: the end iterator.
//   word: the target word as the String.
//   count_l: The lines' count.
//   count_wa: The word's appearances' count.
//   f_lines: the map for found lines, which uses Count1 as the key, and String as the value.
{
    for (; begin != end; ++begin, ++count_l)
    {
        const String &i = *begin;
        Count2 count_wa_l = 0, pos = 0;

        while ((pos = i.find(word, pos)) != String::npos)
        {
            ++pos;
            ++count_wa_l;
        }

        if (count_wa_l > 0)
        {
            count_wa += count_wa_l;
            f_lines[count_l] = i;
        }
    }
}


template<typename LMap, typename OStream, typename String>
    void word_query_file(OStream &ostream, const String &file_path, const String &word)
// Queries the word from the specified file, and prints the result into the output stream.
{
    std::ifstream f(file_path);
    istream_line_iterator begin(f), end;
    size_t count_l = 1, count_wa = 0;
    LMap f_lines;

    query_word(begin, end, word, count_l, count_wa, f_lines);

    print_cl(ostream, word, count_wa, f_lines);
}


template<typename LMap, typename OStream, typename EStream>
    int word_query_main(OStream &ostream, EStream &estream, int argc, char* argv[])
// The main function for the word query program with a CLI interface. It internally calls the word_query_file().
// The first CLI argument is the target word, and the second is the path to the target file.
//  The program won't work without both CLI arguments specified when run.
{
    if (argc != 3)
    {
        estream << "WordQueryProgramError: An invalid number of arguments is specified.\n";
        return 1;
    }

    std::string file_path = argv[1];
    std::string word = argv[2];

    word_query_file<LMap>(ostream, file_path, word);

    return 0;
}


#endif
