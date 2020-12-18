#pragma once
#include <mutex>
#include <condition_variable>
#include <chrono>

class CEvent
{
public:
	CEvent(bool manual,bool init);
	~CEvent();

	void SetEvent();
	void ResetEvent();
	void Wait();
	bool WaitFor(std::chrono::milliseconds ms);

private:
	bool m_manual;
	std::mutex m_mutex;
	std::condition_variable m_cv;
	bool m_signaled;
};

