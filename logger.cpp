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

#include <chrono>
#include <iomanip>

#include "logger.h"

std::fstream Logger::sm_ofstream;

#if !WVT_LOGGER_NO_MUTEX
std::mutex Logger::sm_mutex;
#endif//!WVT_LOGGER_NO_MUTEX

const Logger & Logger::operator <<(std::ostream & (*_pFunc)(std::ostream &)) const
{
#if !WVT_LOGGER_NO_MUTEX
    MutexLockGuard guard(sm_mutex);
#endif//!WVT_LOGGER_NO_MUTEX

    _pFunc(std::cout);

    sm_ofstream.open(sm_filename,sm_openMode);

    if (sm_ofstream.is_open())
    {
        _pFunc(sm_ofstream);
    }//if (sm_ofstream.is_open())

    sm_ofstream.close();

    return *this;
}//operator << std::endl

//-----------------------------------------------------------------------------

void Logger::flush() const
{
#if !WVT_LOGGER_NO_MUTEX
    MutexLockGuard guard(sm_mutex);
#endif//!WVT_LOGGER_NO_MUTEX
    std::cout.flush();

    sm_ofstream.flush();
}//flush

//-----------------------------------------------------------------------------

void Logger::currentDatetime() const
{
    std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

    *this << std::put_time(std::localtime(&now),"%F %T") << std::endl;
}//currentDatetime

//-----------------------------------------------------------------------------
