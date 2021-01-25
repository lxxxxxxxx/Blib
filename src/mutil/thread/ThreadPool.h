
#include <stdint.h>
#include <queue>

class ThreadPool
{

private:
    int m_coreSize;              //core thread number
    int m_maxSize;               //max thread number
    uint32_t m_keepTime;         //no-core thread keep alive time
    std::queue<Runable> m_tasks; //tasks queue
    ThreadFectory m_fectory;     //thread fectory
    RejectedHandler m_rejector;  //rejector policy
};