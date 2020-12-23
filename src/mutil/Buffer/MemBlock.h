/**
 * @file MemBlock.h 
 * @brief A memory block class.
 */

#ifndef _BLIB_MEM_BLOCK_H_
#define _BLIB_MEM_BLOCK_H_

#include <stdint.h>

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
        * @brief try to read 'want' bytes to buf from m_dgpos,output real read size. \n
        * @param[in] want  size want to read.
        * @param[out] buf  destination buffer pointer.
        * @param[out] real  real size read.
        */
        void Read(uint32_t want, uint8_t *buf, uint32_t &real);

        /**
        * @brief additional and shallow copy reading,only return read pointer. \n
        * @param[in] want  size want to read.
        * @param[in] real  size real read.
        * @return a internal maintained pointer to remember read position.
        */
        uint8_t *Read(const uint32_t &want, uint32_t &real);

        /**
        * @brief set extra data to tab this block. \n
        * @param[in] extra  extra data pointer.
        * @param[in] size  size of extra data.
        */
        template <class T>
        void SetExtra(T &extra);

        /**
        * @brief get extra data. \n
        */
        template <class T>
        T &GetExtra();

    private:
        uint32_t m_cap;
        uint8_t *m_begin;
        uint32_t m_end;
        uint32_t m_dgpos; //deep copy read position.
        uint32_t m_sgpos; //shallow copy read position.
        uint8_t *m_extra;
    };

} // namespace blib

#endif