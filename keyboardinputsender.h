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

#ifndef WVT_KEYBOARDINPUTSENDER_H
#define WVT_KEYBOARDINPUTSENDER_H

#include <windows.h>
#include <vector>

#include "flags.h"

/*! Windows keyboard input sender. */
class KeyboardInputSender
{
public:
    enum class Modifier {Alt = 0x1,
                         Ctrl = 0x2,
                         Shift = 0x4};

    using Modifiers = Flags<Modifier>;

    KeyboardInputSender(){}

    void append(char _char);///< Appends _char input.
    void append(const char * _text);///< Appends _text as inputs. Each char is pressed and released immediately.
    void append(Modifiers _modifiers, char _char);///< Appends _char input with specified modifiers.
    void appendVirtualKey(int _vk);///< Appends virtual key input.

    void appendFx(uint8_t _number);
    void appendFx(Modifiers _modifiers, uint8_t _number);
    void appendEnter() {appendVirtualKey(VK_RETURN);}
    void appendPageUp() {appendVirtualKey(VK_PRIOR);}
    void appendPageDown() {appendVirtualKey(VK_NEXT);}
    void appendSpace() {appendVirtualKey(VK_SPACE);}

    void clear();///< Clear all stored inputs.
    bool fire(bool _clear = false);///< Sends all stored inputs in order. \return true if all inputs were sent.

protected:
    void appendVirtualKey(int _vk, bool _release);///< Appends virtual key input. _release tells whether the key must be release.
    void appendInput(INPUT & _input, DWORD _flags, WORD _vk, char _scan, DWORD _time = 0, ULONG_PTR _extraInfo = 0);

    void appendModifier(Modifier _modifier, bool _release);
    void appendModifiers(Modifiers _modifiers, bool _release);

    std::vector<INPUT> m_inputs;
    int m_input_size = sizeof(INPUT);
};//KeyboardInputSender

#endif // WVT_KEYBOARDINPUTSENDER_H
