#pragma once

#include <mutex>
#include <condition_variable>
#include <chrono>

namespace blib
{
	class CSemaphore
	{
		CSemaphore(int count);
		~CSemaphore();

		void Wait();
		bool WaitFor(std::chrono::milliseconds ms);

		void Signal();

	private:
		std::mutex m_mutex;
		std::condition_variable m_cv;
		int m_count;
	};
} // namespace blib
