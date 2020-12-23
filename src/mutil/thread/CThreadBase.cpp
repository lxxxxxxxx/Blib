#include "CThreadBase.h"
#include <sstream>

blib::CThread::CThread(std::string name) : m_name(name), m_exit(false) {}

blib::CThread::~CThread() {}

bool blib::CThread::Run()
{
    if (m_thread.joinable())
    {
        return true;
    }
    m_exit = false;
    m_thread = std::thread(&CThread::Running, this);
    return m_thread.joinable();
}

bool blib::CThread::Quit()
{
    m_exit = true;
    if (m_thread.joinable())
    {
        m_thread.join();
    }
    return true;
}

bool blib::CThread::Looping()
{
    return !m_exit;
}

std::string blib::CThread::Id()
{
    std::ostringstream oss;
    oss << m_id;
    return oss.str();
}