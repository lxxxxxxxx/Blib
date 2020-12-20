#include "CSemaphore.h"

blib::CSemaphore::CSemaphore(int count) : m_count(count)
{
}
blib::CSemaphore::~CSemaphore()
{
}

void blib::CSemaphore::Wait()
{
	std::unique_lock<std::mutex> lock(m_mutex);

	m_cv.wait(lock, [this]() { return m_count > 0; });
	m_count--;
}

bool blib::CSemaphore::WaitFor(std::chrono::milliseconds ms)
{
	std::unique_lock<std::mutex> lock(m_mutex);
	if (m_cv.wait_for(lock, ms, [this]() { return m_count > 0; }))
	{
		m_count--;
		return true;
	}
	return false;
}

void blib::CSemaphore::Signal()
{
	std::unique_lock<std::mutex> lock(m_mutex);
	m_count++;
	m_cv.notify_one();
}