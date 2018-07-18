//Issue during interview: See lines 39 and 40.
//Space: O(m), max line length can be at most the total number of chars in the file n for overall complexity O(n). However, we assume m is much smaller than n.
//Time: O(n), in the worst case we go over each char twice (once with getline, and once in the for loop).

#include <fstream>
#include <iostream>
using namespace std;

int main()
{
    int lines = 0;
    int words = 0;
    int chars = 0;

    string line;
    ifstream myfile("libatomic.so");

    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            lines++;
            chars += line.length() + 1;

            bool word = false;
            for (int i = 0; i < line.length(); i++)
            {
                if (line[i] == ' ' || line[i] == '\n' || line[i] == '\r' || line[i] == '\t')
                {
                    if (word)
                    {
                        word = false;
                        words++;
                    }
                }
                else
                    word = true;
            }
            if (word)
                words++;
        }

        myfile.close();
    }

    cout << lines << " " << words << " " << chars << endl;
    return 0;
}