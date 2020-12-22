#pragma once

#include <mutex>
#include <condition_variable>

namespace blib
{
	class CSemaphore
	{
	public:
		/**
		 * @brief constructor. \n
	     * @param[in] count  initial count of semaphore.
	     */
		CSemaphore(int count);

		/**
		 * @brief destructor. \n
		 */
		~CSemaphore();

		/**
		* @brief wait event signaled for ms ms,if no timeout specified,will wait infinitely. \n
		* @param[in] ms  timeout.
		* @return return wait status,true - event signaled during wait,false - timeout.
		*/
		bool Wait(uint32_t ms = -1);

		/**
		* @brief signal semaphore(s). \n
		* @param[in] increase  signal count,if no 'increase' specified,will increase 1.
		*/
		void Signal(uint32_t increase = 1);

	private:
		std::mutex m_mutex;
		std::condition_variable m_cv;
		int m_count;
	};
} // namespace blib
