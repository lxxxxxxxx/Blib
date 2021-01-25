
#include "CTimer.h"
#include <thread>

blib::CTimer::CTimer() {}

blib::CTimer::~CTimer() {}

void blib::CTimer::Reset()
{
    m_begin = std::chrono::high_resolution_clock::now();
}

uint32_t blib::CTimer::Now(TIME_UNIT unit)
{
    switch (unit)
    {
    case UNIT_NANO:
        return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - m_begin).count();
    case UNIT_MICRO:
        return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - m_begin).count();
    case UNIT_MILLI:
        return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - m_begin).count();
    case UNIT_SECOND:
        return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - m_begin).count();
    case UNIT_MIN:
        return std::chrono::duration_cast<std::chrono::minutes>(std::chrono::high_resolution_clock::now() - m_begin).count();
    case UNIT_HOUR:
        return std::chrono::duration_cast<std::chrono::hours>(std::chrono::high_resolution_clock::now() - m_begin).count();
    default:
        return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - m_begin).count();
    }
}

void blib::CTimer::Timeout(uint32_t t, TIME_UNIT unit, std::function<void()> callback)
{
    std::thread([=]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(t));
        callback();
    }).detach();
}

void blib::CTimer::Crontab(uint32_t t, TIME_UNIT unit, std::function<void()> func)
{
    std::thread([=]() {
        //TODO:exit condition
        while (true)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(t));
            func();
        }
    }).detach();
}