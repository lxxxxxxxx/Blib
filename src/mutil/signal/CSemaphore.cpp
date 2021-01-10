#include "CSemaphore.h"

blib::CSemaphore::CSemaphore(int count) : m_count(count)
{
}
blib::CSemaphore::~CSemaphore()
{
}

bool blib::CSemaphore::Wait(uint32_t ms)
{
	std::unique_lock<std::mutex> lock(m_mutex);
	if (-1 == ms)
	{
		m_cv.wait(lock, [this]() { return m_count > 0; });
	}
	else
	{
		if (!m_cv.wait_for(lock, std::chrono::milliseconds(ms), [this]() { return m_count > 0; }))
		{
			return false;
		}
	}
	m_count--;
	return true;
}

void blib::CSemaphore::Signal(uint32_t increase)
{
	std::unique_lock<std::mutex> lock(m_mutex);
	m_count += increase;
	//TODO:bug - should notify 'increase' number.
	m_cv.notify_one();
}

uint32_t blib::CSemaphore::Count()
{
	std::lock_guard<std::mutex> lock(m_mutex);
	return m_count;
}
