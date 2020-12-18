/*
* file CEvent.h
* event for thread synchronous
*/

#ifndef _BLIB_CEVENT_H_
#define _BLIB_CEVENT_H_

#include <mutex>
#include <condition_variable>

namespace Blib
{
	class CEvent
	{
	public:
		/*
	    * @param[in] manual  Whether to reset manually,if false, reset event after wait.
	    * @param[in] init    Whether event is signaled when it initalizetrue.
	    */
		CEvent(bool manual, bool init);

		~CEvent();

		/*
        * @brief signed event. \n
        */
		void Set();

		/*
		* @brief unsigned event. \n
		*/
		void Reset();

		/*
		* @brief wait for event signed forever. \n
		*/
		void Wait();

		/*
		* @brief wait event signaled for ms ms. \n
		* @param[in] ms  wait time.
		* @return return wait status,true - event signaled during wait,false - otherwise(timeout or unsigned).
		*/
		bool WaitFor(uint32_t ms);

	private:
		std::mutex m_mutex;
		std::condition_variable m_cv;
		bool m_manual;
		bool m_signaled;
	};

} // namespace Blib

#endif