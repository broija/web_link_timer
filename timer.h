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

#ifndef WVT_TIMER_H
#define WVT_TIMER_H

#include <thread>
#include <atomic>

#include <iostream>

/*! Timer class which can be started at construction time only.
 *  \todo Timer template class which can be restarted at will.
 * Interval_ is a std::ratio which is "saved" is a typedef.
 * _interval value is saved in a member var.
 * _func is saved in a std::function<void(void)> member var.
 * Additional template parameters could be added to allow function calls with multiple args.
 * Add another construtor with Interval only.
 * Or constructor does init only and thread launching is a template start method. */
class Timer
{
public:
    using Count = uint32_t;
    using StopFlag = std::atomic_bool;
    using AtomicCount = std::atomic<Count>;

    template <class Interval_>
    Timer(const Interval_ & _interval);

    template <class Interval_, class TimeOutFunc_>
    Timer(const Interval_ & _interval, TimeOutFunc_ && _func);

    ~Timer();

    void stop();

    bool running();///< Returns true if the timer is running.

    void resetCount();///< Resets tic counter.
    Count getCount();//< Returns tic counter value.

protected:
    StopFlag m_stop;
    AtomicCount m_counter;

    std::thread m_thread;
    std::memory_order m_mem_order = std::memory_order_relaxed;
};//Timer

//------------------------------------------------------------------------------

template <class Interval_>
Timer::Timer(const Interval_ & _interval):
    m_stop(false),
    m_counter(0),
    m_thread([=](StopFlag * _pStop, AtomicCount * _pCounter)
             {
                 while (!_pStop->load(m_mem_order))
                 {
                     std::this_thread::sleep_for(_interval);
                     std::cout << "Timer thread : tic" << std::endl;

                     ++(*_pCounter);
                 }//while (!_pStop->load(m_mem_order))
             },&m_stop,&m_counter)
{
}//Timer

//------------------------------------------------------------------------------

template <class Interval_, class TimeOutFunc_>
Timer::Timer(const Interval_ & _interval, TimeOutFunc_ && _func):
    m_stop(false),
    m_counter(0),
    m_thread([=](StopFlag * _pStop, AtomicCount * _pCounter)
             {
                 while (!_pStop->load(m_mem_order))
                 {
                     std::this_thread::sleep_for(_interval);
                     std::cout << "Timer thread : tic" << std::endl;

                     ++(*_pCounter);
                     _func();
                 }//while (!_pStop->load())
             },&m_stop,&m_counter)
{
}//Timer

//--------------------

#endif // WVT_TIMER_H
