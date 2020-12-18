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

void Blib::CEvent::Wait()
{
	std::unique_lock<std::mutex> lock(m_mutex);
	m_cv.wait(lock, [this]() { return m_signaled; });
	if (!m_manual)
	{
		m_signaled = false;
	}
}
bool Blib::CEvent::WaitFor(uint32_t ms)
{
	std::unique_lock<std::mutex> lock(m_mutex);
	if (m_cv.wait_for(lock, std::chrono::milliseconds(ms), [this]() { return m_signaled; }))
	{
		if (!m_manual)
		{
			m_signaled = false;
		}
		return true;
	}
	return false;
}