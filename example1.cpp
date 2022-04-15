// compile with: g++ -o ex1 -g -Wall -pedantic -Wextra -std=c++14 example1.cpp
// sample data at the bottom

// Request: Given a string s, find the length of the longest substring without
// repeating characters.

#include <libgen.h>
#include <stdint.h>
#include <string>
#include <iostream>

using std::string;
using std::cout;
using std::endl;

static uint32_t SearchNonRepeaters(const string& s)
{
    // empty string
    if (s.length() == 0)
        return (0);

    string current, answer;
    char last_ch = '\0';

    for (char ch : s)
    {
        if (ch != last_ch)
        {
            current += ch;
        }
        else 
        {
            if (current.length() > answer.length())
                answer = current;

            current = ch;
        }

        last_ch = ch;
    }

    return (current.length() > answer.length() ?
            current.length() : // the last or only string was the longest
            answer.length());  // the last string was not the longest
}

static void Usage(const char *p_appname)
{
    cout << "Usage: " << p_appname << " SOME_STRING" << endl;
}

int main(int argc, char* argv[])
{
    const char* p_appname = basename(argv[0]);
    if (argc == 2)
    {
        string s(argv[1]);
        uint32_t res = SearchNonRepeaters(s);
        cout << p_appname << ": the longest string " << res << endl;
    }
    else
        Usage(p_appname);

    return (0);
}

// Sample data:
//     a
//     ''      # forces non-null empty string (assumes bash)
//     ababababababababa
//     abcdeffghijklmnnopqrstuvwxxx
//     abbcdeeefff
