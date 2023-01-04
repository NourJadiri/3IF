//
// Created by Nour on 04/01/2023.
//

#include "CatalogueUtils.h"

using namespace std;


int countSeparators(string & s , char separator)
{

    int count = 0;

    for (char i : s)
        if (i == separator) count++;

    return count;
}

string * split (string & str, char seperator)
{
    // Creating the string array that will hold our strings after splitting
    // hard coded 5 as a value because our format gives exactly 5 splitted strings (optimization)
    // the possibility to use a more generic separation can be considered by using :
    // string * strings = new string[countSparators(str,',') + 1]
    string * strings = new string[5];

    int currIndex = 0, i = 0;
    int startIndex = 0, endIndex;

    while (i <= str.size())
    {
        // if we reach the separator or the end of the string to split
        if (str[i] == seperator || i == str.size())
        {
            // our new string ends at the separator
            endIndex = i;
            string subStr;

            subStr.append(str, startIndex, endIndex - startIndex);

            strings[currIndex] = subStr;
            currIndex += 1;

            // We update the starting index
            startIndex = endIndex + 1;
        }
        i++;
    }

    return strings;
}