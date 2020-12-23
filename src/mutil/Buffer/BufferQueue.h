/**
 * @file BufferQueue.h 
 * @brief A memory buffer queue.
 * @pre need CSemaphore.h and MemBlock.h include
 */

#ifndef _BLIB_BUFFER_QUEUE_H_
#define _BLIB_BUFFER_QUEUE_H_

#include <stdint.h>
#include <queue>
#include <mutex>
#include "../CSemaphore/CSemaphore.h"
#include "MemBlock.h"

namespace blib
{
    class BufferQueue
    {
    public:
        /**
        * @brief constructor of BufferQueue. \n
	    * @param[in] _max   the maximum number of memory blocks that can be buffered.
	    */
        BufferQueue(uint32_t _max);

        /**
        * @brief destructor of BufferQueue. \n
        */
        ~BufferQueue();

        /**
        * @brief get a new memory block. \n
	    * @param[in] size  size of memory block.
        * @return pointer of new memory block.
	    */
        blib::MemBlock *NewBlock(uint32_t size);

        /**
        * @brief push a memory block to queue tail. \n
	    * @param[in] block  memory block.
        * @return push result,if size of queue large than max limit,will return false.
	    */
        bool Push(blib::MemBlock *block);

        /**
        * @brief get the front memory block of queue. \n
	    * @return front memory block.
	    */
        blib::MemBlock *Front();

        /**
        * @brief pop front memory block from queue. \n
	    */
        void Pop();

        /**
        * @brief get size of queue. \n
	    * @return size of queue.
	    */
        uint32_t Size();

        /**
        * @brief get whether the queue is empty . \n
        * @return whether the queue is empty
	    */
        bool Empty();

        /**
        * @brief clear queue. \n
        * @return clear result.
	    */
        bool Clear();

        /**
        * @brief get buffer queue total size in bytes. \n
        * @return buffer queue total size in bytes
	    */
        uint32_t Bytes();

        /**
        * @brief wait for a semaphore ms millisecond. \n
	    * @param[in] ms  wait time,if ms is -1,will wait infinite
        * @return wait result,if semaphore > 0 during wait,return true,else wait false.
	    */
        bool Wait(uint32_t ms = -1);

    private:
        std::queue<blib::MemBlock *> m_queue;
        std::mutex m_mutex;
        blib::CSemaphore m_sem;
        uint32_t m_max;
        uint32_t m_bytes;
    };

} // namespace blib

#endif