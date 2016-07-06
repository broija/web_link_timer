/*!
    Copyright 2016 Broija

    This file is part of web_link_timer app.

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

#ifndef WVT_CHAR_TOOLS_H
#define WVT_CHAR_TOOLS_H

#include <vector>
#include <string>

/*! split _string with _delimiter _count times.
 * if _count = -1, the string is splitted entirely. */
std::vector<std::string> split(const char * _string, char _delimiter, int _count = -1);
std::vector<std::string> split(std::string _string, char _delimiter, int _count = -1);

//--------------------------

template <typename T>
void printChars(T * _chars, bool _endl = true);

template <class T>
void printChars(const T & _string, bool _endl = true);

//--------------------------

template <class T>
void printStrings(const std::vector<T> & _strings);

//--------------------------
//--------------------------

template <typename Source_, typename Destination_>
Destination_ convert(Source_ _source);

#endif // WVT_CHAR_TOOLS_H
