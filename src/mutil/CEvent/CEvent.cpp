#include "CEvent.h"

Blib::CEvent::CEvent(bool manual, bool init)
	: m_manual(manual), m_signaled(init) {}

Blib::CEvent::~CEvent() {}

void Blib::CEvent::Set()
{
	std::unique_lock<std::mutex> lock(m_mutex);
	m_signaled = true;
	m_cv.notify_all();
}
void Blib::CEvent::Reset()
{
	if (!m_manual)
	{
		return;
	}
	std::unique_lock<std::mutex> lock(m_mutex);
	m_signaled = false;
}

bool Blib::CEvent::Wait(uint32_t ms)
{
	std::unique_lock<std::mutex> lock(m_mutex);
	if (-1 == ms)
	{
		m_cv.wait(lock, [this]() { return m_signaled; });
	}
	else
	{
		if (!m_cv.wait_for(lock, std::chrono::milliseconds(ms), [this]() { return m_signaled; }))
		{
			return false;
		}
	}
	if (!m_manual)
	{
		m_signaled = false;
	}

	return true;
}
