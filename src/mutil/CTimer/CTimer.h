
#include <functional>
#include <stdint.h>
#include <chrono>

namespace blib
{
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

        /**
     * @brief Reset or start timer. \n
     */
        void Reset();

        /**
         * @brief Get time interval since Reset(). \n
         */
        uint32_t Now(TIME_UNIT unit = UNIT_MILLI);

        /**
     * @brief call function when timeout. \n
     * @param[in] t time
     * @param[in] unit time unit
     * @param[in] callback callback function
     */
        static void Timeout(uint32_t t, TIME_UNIT unit, std::function<void()> callback);

        /**
     * @brief create a crontab, call func at ragular intervals. \n
     * @param[in] t ragular interval
     * @param[in] unit time unit
     * @param[in] func crantab task function
     */
        static void Crontab(uint32_t t, TIME_UNIT unit, std::function<void()> func);

    private:
        std::chrono::time_point<std::chrono::high_resolution_clock> m_begin;
    }
} // namespace blib