
#include "MemBlock.h"
#include <assert.h>
#include <memory>

blib::MemBlock::MemBlock(uint32_t size)
    : m_cap(size), m_end(0), m_dgpos(0), m_sgpos(0),
      m_begin(nullptr), m_extra(nullptr)
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
            //TODO: return a reason status.
            return false;
        }
    }

    if (m_cap - m_end < size)
    {
        m_cap = size / 2 * 3;
        uint8_t *tmp = new uint8_t[m_cap];
        if (!tmp)
        {
            //TODO: return a reason status.
            return false;
        }
        memcpy(tmp, m_begin, m_end);
        if (m_begin)
        {
            delete[] m_begin;
        }
        m_begin = tmp;
        tmp = nullptr;
    }
    memcpy(m_begin + m_end, data, size);
    m_end += size;
    return true;
}

void blib::MemBlock::Read(uint32_t want, uint8_t *buf, uint32_t &real)
{
    assert(buf != nullptr);

    real = want > m_end - m_dgpos ? m_end - m_dgpos : want;
    memcpy(buf, m_begin + m_dgpos, real);
    m_dgpos += real;
}

uint8_t *blib::MemBlock::Read(const uint32_t &want, uint32_t &real)
{
    real = want > m_end - m_dgpos ? m_end - m_dgpos : want;
    uint8_t *tmp = m_begin + m_sgpos;
    m_sgpos += real;
    return tmp;
}

//TODO:test
template <class T>
void blib::MemBlock::SetExtra(T &extra)
{
    if (m_extra)
    {
        delete[] m_extra;
    }
    m_extra = new uint8_t[sizeof(T)];
    memcpy(m_extra, &extra, sizeof(T));
}

template <class T>
T &blib::MemBlock::GetExtra()
{
    return reinterpret_cast<T *>(m_extra);
}
