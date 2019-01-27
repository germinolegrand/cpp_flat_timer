#pragma once

#include <chrono>
#include <functional>

class flat_timer
{
public:
    using clock = std::chrono::steady_clock;
    using duration = clock::duration;
    using time_point = clock::time_point;
    using function = std::function<void()>;

    void set_timeout(function func, duration delay, time_point start = clock::now());
    void set_interval(function func, duration interval, time_point start = clock::now());
    void stop();

    auto execution_point() -> time_point const { return m_exec_point; }
    auto remainder(time_point since = clock::now()) const -> duration { return m_exec_point - since; }

    void update(time_point now = clock::now());

private:
    time_point m_exec_point;
    duration m_exec_interval = duration::zero();
    function m_exec_func;
};
