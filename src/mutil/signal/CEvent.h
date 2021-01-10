/**
* @file CEvent.h
* @brief event for thread synchronous
*/

#ifndef _BLIB_CEVENT_H_
#define _BLIB_CEVENT_H_

#include <mutex>
#include <condition_variable>

namespace blib
{
	class CEvent
	{
	public:
		/**
		 * @brief constructor. \n
	     * @param[in] manual  Whether to reset manually,if false, reset event after wait.
	     * @param[in] init    Whether event is signaled when it initalizetrue.
	     */
		CEvent(bool manual, bool init);

		/**
		 * @brief destructor. \n
		 */
		~CEvent();

		/** 
         * @brief signed event. \n
         */
		void Set();

		/**
	 	 * @brief unsigned event. \n
		 */
		void Reset();

		/**
		* @brief wait event signaled for ms ms,if no timeout specified,will wait infinitely. \n
		* @param[in] ms  timeout.
		* @return return wait status,true - event signaled during wait,false - timeout.
		*/
		bool Wait(uint32_t ms = -1);

		/**
		 * @brief get event status. \n
		 * @return true - event is signaled,falst - not signaled
		 */
		bool Signaled();

	private:
		std::mutex m_mutex;
		std::condition_variable m_cv;
		bool m_manual;
		bool m_signaled;
	};

} // namespace Blib

#endif