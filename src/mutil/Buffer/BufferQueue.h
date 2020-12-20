/**
 * file BufferQueue.h 
 * A memory buffer queue.
 * @pre need CSemaphore.h include
 */

#ifndef _BUFFER_QUEUE_H_
#define _BUFFER_QUEUE_H_

#include <stdint.h>
#include <queue>
#include <mutex>
#include "../CSemaphore/CSemaphore.h"

namespace blib
{
    class MemBlock
    {
    public:
        /**
        * @brief constructor of MemBlock. \n
	    * @param[in] size   the initial capacity of memory block.
	    */
        MemBlock(uint32_t size);

        /**
        * @brief destructor of MemBlock. \n
        */
        ~MemBlock();

        /**
        * @brief get capacity. \n
        */
        uint32_t Capacity();

        /**
        * @brief get real data size. \n
        */
        uint32_t Size();

        /**
        * @brief get block begin pointer. \n
        */
        uint8_t *Data();

        /**
        * @brief additional writing to block. \n
        * @param[in] data  data to be writen.
        * @param[in] size  size of data to be writen.
        * @return write status,true/false
        */
        bool Write(uint8_t *data, uint32_t size);

        /**
        * @brief copy read data from this block. \n
        * @param[in] begin  beginning position to be read.
        * @param[in] size  size want to read.
        * @param[out] buf  destination buffer pointer.
        * @param[out] real  real size read.
        */
        void Read(uint8_t *begin, uint32_t size, uint8_t *buf, uint32_t &real);

        /**
        * @brief additional and shallow copy reading,only return read pointer. \n
        * @param[in] want  size want to be read.
        * @param[in] real  size real read.
        * @return a internal maintained pointer to remember read position.
        */
        uint8_t *Read(const uint32_t &want, uint32_t &real);

        /**
        * @brief get extra data. \n
        */
        template <class T>
        T &&GetExtra();

        /**
        * @brief set extra data to tab this block. \n
        * @param[in] extra  extra data pointer.
        * @param[in] size  size of extra data.
        */
        template <class T>
        void SetExtra(T &extra);

    private:
        uint32_t m_cap;
        uint8_t *m_begin;
        uint32_t m_end;
        uint32_t m_gpos; //read position.
        uint8_t *m_extra;
    };

} // namespace blib

#endif