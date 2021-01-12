
#include <functional>
#include <stdint.h>
#include <chrono>

class CTimer
{
public:
    CTimer();

    ~CTimer();

    void Start();

    uint32_t Now();

    void Reset();

    /**
     * @brief create a crontab, call func at ragular intervals. \n
     * @param[in] us ragular interval
     * @param[in] func crantab task
     */
    static void Crontab(uint32_t us, std::function<void()> func);

private:
    std::chrono::duration m_dur;
}