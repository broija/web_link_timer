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

#include <windows.h>

#include "char_tools.h"
#include "keyboardinputsender.h"

namespace
{
  static const HKL kbLayout = GetKeyboardLayout(0);
}//

void KeyboardInputSender::append(char _char)
{
    INPUT input;

    appendInput(input,KEYEVENTF_UNICODE,0,_char);
    appendInput(input,KEYEVENTF_UNICODE | KEYEVENTF_KEYUP,0,_char);
}//append char

//----------

void KeyboardInputSender::append(const char * _text)
{
    std::size_t size = strlen(_text);

    for (std::size_t i = 0; i < size; ++i)
    {
        append(_text[i]);
    }//for (std::size_t i = 0; i < size; ++i)
}//append const char *

//----------

void KeyboardInputSender::append(Modifiers _modifiers, char _char)
{
    appendModifiers(_modifiers,false);

#if !defined(WVT_CYGWIN)
    TCHAR vkChar = VkKeyScanEx(convert<char,TCHAR>(_char),kbLayout);
#else
    TCHAR vkChar = VkKeyScanEx(_char,kbLayout);
#endif//!WVT_CYGWIN...else

    appendVirtualKey(vkChar,false);
    appendVirtualKey(vkChar,true);

    appendModifiers(_modifiers,true);
}//append Modifiers _char

//----------

void KeyboardInputSender::appendVirtualKey(int _vk)
{
    appendVirtualKey(_vk,false);
    appendVirtualKey(_vk,true);
}//appendVirtualKey

//----------

void KeyboardInputSender::appendFx(uint8_t _number)
{
    int vk;

    switch (_number)
    {
    case 1: vk = VK_F1; break;
    case 2: vk = VK_F2; break;
    case 3: vk = VK_F3; break;
    case 4: vk = VK_F4; break;
    case 5: vk = VK_F5; break;
    case 6: vk = VK_F6; break;
    case 7: vk = VK_F7; break;
    case 8: vk = VK_F8; break;
    case 9: vk = VK_F9; break;
    case 10: vk = VK_F10; break;
    case 11: vk = VK_F11; break;
    case 12: vk = VK_F12; break;
    default: vk = 0; break;
    }//switch (_number)

    if (vk)
    {
        appendVirtualKey(vk);
    }//if (vk)
}//appendFx

//----------

void KeyboardInputSender::appendFx(Modifiers _modifiers, uint8_t _number)
{
    appendModifiers(_modifiers,false);

    appendFx(_number);

    appendModifiers(_modifiers,true);
}//appendFx Modifiers

//----------

void KeyboardInputSender::clear()
{
    m_inputs.clear();
}//clear

//----------

bool KeyboardInputSender::fire(bool _clear)
{
    UINT sent_count;
    std::size_t input_count = m_inputs.size();

    sent_count = SendInput(static_cast<UINT>(input_count), m_inputs.data(), m_input_size);

    if (_clear) clear();

    return sent_count == input_count;
}//fire

//----------

void KeyboardInputSender::appendInput(INPUT & _input, DWORD _flags, WORD _vk, char _scan, DWORD _time, ULONG_PTR _extraInfo)
{
    _input.type = INPUT_KEYBOARD;
    _input.ki.dwFlags = _flags;
    _input.ki.wVk = _vk;

#if !defined(WVT_CYGWIN)
    _input.ki.wScan = _scan ? convert<char,TCHAR>(_scan) : 0;
#else
    _input.ki.wScan = _scan ? _scan : 0;
#endif//!WVT_CYGWIN...else

    _input.ki.time = _time;
    _input.ki.dwExtraInfo = _extraInfo;

    m_inputs.push_back(_input);
}//appendInput

//----------

void KeyboardInputSender::appendModifier(Modifier _modifier, bool _release)
{
    INPUT input;

    DWORD flags = KEYEVENTF_SCANCODE;
    if (_release) flags |= KEYEVENTF_KEYUP;

    WORD scan = 0;

    switch (_modifier)
    {
    case Modifier::Ctrl: scan = 0x1d; break;
    case Modifier::Shift: scan = 0x2a; break;
    case Modifier::Alt: scan = 0x38; break;
    }//switch (_modifier)

    appendInput(input,flags,0,scan);
}//appendModifier

//----------

void KeyboardInputSender::appendModifiers(Modifiers _modifiers, bool _release)
{
    if (_modifiers & Modifier::Ctrl)
    {
        appendModifier(Modifier::Ctrl,_release);
    }//if (_modifiers & Modifier::Ctrl)

    if (_modifiers & Modifier::Shift)
    {
        appendModifier(Modifier::Shift,_release);
    }//if (_modifiers & Modifier::Shift)

    if (_modifiers & Modifier::Alt)
    {
        appendModifier(Modifier::Alt,_release);
    }//if (_modifiers & Modifier::Alt)
}//appendModifiers

//----------

void KeyboardInputSender::appendVirtualKey(int _vk, bool _release)
{
    INPUT input;

    appendInput(input,(_release ? KEYEVENTF_KEYUP : 0),_vk,0);
}//appendVirtualKey

//----------

