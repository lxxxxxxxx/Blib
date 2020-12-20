
#include "BufferQueue.h"

blib::MemBlock::MemBlock(uint32_t size)
    : m_cap(size), m_end(0), m_gpos(0), m_begin(nullptr),
      m_extra(nullptr)
{
}

blib::MemBlock::~MemBlock()
{
    if (m_begin)
    {
        delete[] m_begin;
        m_begin = nullptr;
    }
}

uint32_t blib::MemBlock::Capacity()
{
    return m_cap;
}

uint32_t blib::MemBlock::Size()
{
    return m_end;
}

uint8_t *blib::MemBlock::Data()
{
    return m_begin;
}

bool blib::MemBlock::Write(uint8_t *data, uint32_t size)
{
    if (!m_begin)
    {
        m_begin = new uint8_t[m_cap];
        if (!m_begin)
        {
            return false;
        }
    }
}

void blib::MemBlock::Read(uint8_t *begin, uint32_t size, uint8_t *buf, uint32_t &real);

uint8_t *blib::MemBlock::Read(const uint32_t &want, uint32_t &real);

void *blib::MemBlock::GetExtra();

void blib::MemBlock::SetExtra(void *extra, uint32_t size);
