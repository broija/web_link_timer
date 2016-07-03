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

#include "timer.h"

Timer::~Timer()
{
    std::cout << "~Timer" << std::endl;

    if (m_stop.load(m_mem_order))
        std::cout << "STOPPED";
    else
        std::cout << "NOT STOPPED";

    std::cout << std::endl;

    stop();
}//~Timer

//------------------

void Timer::stop()
{
    if (!(m_stop.load(m_mem_order)) && m_thread.joinable())
    {
        m_stop.store(true,m_mem_order);

        m_thread.join();
    }//if (!(m_stop.load(m_mem_order)) && m_thread.joinable())
}//stop

//------------------

bool Timer::running()
{
    return m_thread.joinable();
}//running

//------------------

void Timer::resetCount()
{
    m_counter.store(0,m_mem_order);
}//resetCount

//------------------

Timer::Count Timer::getCount()
{
    return m_counter.load(m_mem_order);
}//getCount

//------------------
