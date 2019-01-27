#include "flat_timer.h"

void flat_timer::set_timeout(function func, duration delay, time_point start)
{
    m_exec_point = start + delay;
    m_exec_interval = duration(-1);
    if(func){
        m_exec_func = std::move(func);
    }
}

void flat_timer::set_interval(function func, duration interval, time_point start)
{
    m_exec_point = start + interval;
    m_exec_interval = interval;
    if(func){
        m_exec_func = std::move(func);
    }
}

void flat_timer::stop()
{
    m_exec_point = time_point();
    m_exec_interval = duration::zero();
    m_exec_func = nullptr;
}

void flat_timer::update(time_point now)
{
    if(m_exec_func && now >= m_exec_point){
        if(m_exec_interval == duration(-1)){
            m_exec_interval = duration(-2);
        } else if(m_exec_interval == duration(-2)){
            m_exec_func = nullptr;
            return;
        }
        m_exec_point += m_exec_interval;
        m_exec_func();
    }
}
