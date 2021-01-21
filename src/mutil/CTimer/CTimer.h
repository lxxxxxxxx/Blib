
#include <functional>
#include <stdint.h>
#include <chrono>

class CTimer
{

    enum TIME_UNIT
    {
        UNIT_NANO = 0,
        UNIT_MICRO = 1,
        UNIT_MILLI = 2,
        UNIT_SECOND = 3,
        UNIT_MIN = 4,
        UINT_HOUR = 5,
        UINT_DAY = 6,
        UINT_WEEK = 7,
        UNIT_MOUTH = 8,
        UNIT_YEAR = 9,
    };

public:
    CTimer();

    ~CTimer();

    uint32_t Now();

    void Reset();

    void Timeout(uint32_t t, TIME_UNIT unit, std::function<void()> callback);

    /**
     * @brief create a crontab, call func at ragular intervals. \n
     * @param[in] us ragular interval
     * @param[in] func crantab task
     */
    static void Crontab(uint32_t t, TIME_UNIT unit, std::function<void()> func);

private:
    std::chrono::duration m_dur;
}