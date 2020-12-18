#include "CEvent.h"


CEvent::CEvent(bool manual,bool init):m_manual(manual),m_signaled(init){}
CEvent::~CEvent(){}

void CEvent::SetEvent()
{
	std::unique_lock<std::mutex> lock(m_mutex);
	m_signaled = true;
	m_cv.notify_all();
}
void CEvent::ResetEvent()
{
	if (!m_manual)
	{
		return;
	}
	std::unique_lock<std::mutex> lock(m_mutex);
	m_signaled = false;
}

void CEvent::Wait()
{
	std::unique_lock<std::mutex> lock(m_mutex);
	m_cv.wait(lock, [this]() {return m_signaled; });
	if (!m_manual)
	{
		m_signaled = false;
	}
}
bool CEvent::WaitFor(std::chrono::milliseconds ms)
{
	std::unique_lock<std::mutex> lock(m_mutex);
	if (m_cv.wait_for(lock, ms, [this]() {return m_signaled; }))
	{
		if (!m_manual) {
			m_signaled = false;
		}
		return true;
	}
	return false;
}