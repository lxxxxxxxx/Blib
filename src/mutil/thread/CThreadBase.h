/**
* @file CThreadBase.h
* @brief a simple thread basic class
*/

#ifndef _BLIB_CTHREAD_BASE_H_
#define _BLIB_CTHREAD_BASE_H_

#include <thread>
#include <string>
#include <atomic>

namespace blib
{
	class CThread
	{
	public:
		/**
		 * @brief constructor. \n
	     * @param[in] name  a string name for tab this thread.
	     */
		CThread(std::string name);

		/**
		 * @brief destructor. \n
		 */
		virtual ~CThread();

		/**
		 * @brief run this thread. \n
		 * @return run status.
		 */
		bool Run();

		/**
		 * @brief stop this htread. \n
		 *@return stop status 
		 */
		bool Quit();

		/**
		 * @brief should this thread continue to run,using at a loop . \n
		 * @return running status 
		 */
		bool Looping();

		/**
		 * @brief get thread id. \n
		 * @return thread id 
		 */
		std::string Id();

	protected:
		/**
		 * @brief running function should implement by child class. \n
		 */
		virtual void Running();

	private:
		std::string m_name;
		std::thread m_thread;
		std::thread::id m_id;
		std::atomic_bool m_exit;
	};
} // namespace blib

#endif
