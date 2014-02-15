#include "timer.h"

std::set<Timer*> Timer::timers_;

Timer::Timer(milliseconds expiration_time) :
    current_time_{expiration_time.count() + 1},
    expiration_time_{expiration_time}
{
    timers_.insert(this);
}

Timer::~Timer()
{
    timers_.erase(this);
}

void Timer::reset()
{
    current_time_ = current_time_.zero();
}

bool Timer::is_active() const
{
    return current_time_ < expiration_time_;
}

bool Timer::is_expired() const
{
    return !is_active();
}

milliseconds Timer::current_time() const
{
    return current_time_;
}

void Timer::updateAll(milliseconds elapsed_time)
{
    for (auto timer: timers_) {
        timer->update(elapsed_time);
    }
}

void Timer::update(milliseconds elapsed_time)
{
    if (is_active()) {
        current_time_ += elapsed_time;
    }
}
