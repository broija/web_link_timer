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

#ifndef WVT_LOGGER_H
#define WVT_LOGGER_H

#define WVT_LOGGER_NO_MUTEX 1

#include <fstream>
#include <iostream>

#if !WVT_LOGGER_NO_MUTEX
#include <mutex>
#endif//!WVT_LOGGER_NO_MUTEX

/*! Singleton log class. */
class Logger
{
public:
    static constexpr const Logger & getUniqueInstance() {return *sm_instance;}

    static constexpr const char * filename() {return sm_filename;}

    constexpr Logger(const Logger &){}

    template <typename T_>
    const Logger & operator <<(T_ _value) const;

    /// operator << for std::endl
    const Logger & operator <<(std::ostream & (*_pFunc)(std::ostream &)) const;

    void flush() const;

    void currentDatetime() const;

private:
#if !WVT_LOGGER_NO_MUTEX
    using MutexLockGuard = std::lock_guard<std::mutex>;
#endif//!WVT_LOGGER_NO_MUTEX

    constexpr Logger(){}
    Logger & operator =(Logger & _other) = delete;

    static constexpr const Logger * sm_instance = {};

    static constexpr const char * sm_filename = "wlt.log";

    // Log file open mode
    static constexpr const std::ios_base::openmode sm_openMode = std::ios_base::out | std::ios_base::app;

    static std::fstream sm_ofstream;
#if !WVT_LOGGER_NO_MUTEX
    static std::mutex sm_mutex;
#endif//!WVT_LOGGER_NO_MUTEX
};//Logger

//-----------------------------------------------------------------------------

static constexpr const Logger sGlobLogger(Logger::getUniqueInstance());

//-----------------------------------------------------------------------------

template <typename T_>
const Logger & Logger::operator <<(T_ _value) const
{
#if !WVT_LOGGER_NO_MUTEX
    MutexLockGuard guard(sm_mutex);
#endif//!WVT_LOGGER_NO_MUTEX

    std::cout << _value;

    sm_ofstream.open(sm_filename,sm_openMode);

    if (sm_ofstream.is_open())
    {
        sm_ofstream << _value;
    }//if (sm_ofstream.is_open())

    sm_ofstream.close();

    return *this;
}//operator <<

//-----------------------------------------------------------------------------

#endif // WVT_LOGGER_H
