/*!
    Copyright 2016 Broija

    This file is part of web_video_timer app.

    subdetection is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    subdetection is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with subdetection library.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "char_tools.h"

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <locale>
#include <algorithm>

#include <windows.h>

std::vector<std::string> split(const char * _string, char _delimiter, int _count)
{
    typedef std::string::size_type size_type;

    std::vector<std::string> result;

    std::string originalString = _string;

    std::string splitItem;

    size_type length = originalString.length();

    size_type pos = 0;

    while (_count && pos < length)
    {
        size_type delimPos = originalString.find(_delimiter,pos);

        //delimiter not found
        if (delimPos == std::string::npos)
        {
            if (pos<length)
            {
                splitItem = originalString.substr(pos,length-pos);

                result.push_back(splitItem);
            }//if (pos<length)

            pos = length;//no match, end the loop.
        }//if (delimPos == std::string::npos)
        else
        {
            if (delimPos != pos)
            {
                splitItem = originalString.substr(pos,delimPos-pos);
                result.push_back(splitItem);
            }//if (delimPos != pos)

            pos = delimPos +1;

            if (_count>0)
                _count--;

        }//if (delimPos == std::string::npos)...else
    }//while (_count && pos < length)

    if (pos < length)
    {
        splitItem = originalString.substr(pos,length-1);
        result.push_back(splitItem);
    }//if (pos < length)

    return result;
}//split const char *

//--------------------------------------

std::vector<std::string> split(std::string _string, char _delimiter, int _count)
{
    return split(_string.c_str(),_delimiter,_count);
}//split std::string

//--------------------------------------
//--------------------------------------

template <>
void printChars<char>(char * _chars, bool _endl)
{
    std::cout << _chars;
    if (_endl) std::cout << std::endl;
}//printChars

//--------------------------------------

template <>
void printChars<const char>(const char * _chars, bool _endl)
{
    std::cout << _chars;
    if (_endl) std::cout << std::endl;
}//printChars

//--------------------------------------

template <>
void printChars<WCHAR>(WCHAR * _chars, bool _endl)
{
    std::wcout << _chars;
    if (_endl) std::cout << std::endl;
}//printChars WCHAR

//--------------------------------------

template <>
void printChars<std::string>(const std::string & _string, bool _endl)
{
    printChars<const std::string::value_type>(_string.c_str(),_endl);
}//printChars

//--------------------------------------
//--------------------------------------

template <>
void printStrings<std::string>(const std::vector<std::string> & _strings)
{
    for (auto string: _strings) printChars(string);
}//printStrings std::string

//--------------------------------------

#if !defined(WVT_CYGWIN)
template <>
TCHAR convert<char,TCHAR>(char _source)
{
    TCHAR result;

    mbstowcs(&result,&_source,1);

    return result;
}//convert
#endif//!WVT_CYGWIN

//--------------------------------------
