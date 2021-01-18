

#include "BufferQueue.h"

blib::BufferQueue::BufferQueue(uint32_t _max) : m_max(_max), m_sem(0), m_bytes(0)
{
}

blib::BufferQueue::~BufferQueue()
{
    Clear();
}

blib::MemBlock *blib::BufferQueue::NewBlock(uint32_t size)
{
    MemBlock *block = new MemBlock(size);
    if (!block)
    {
        //TODO:return status.
        return nullptr;
    }
    return block;
}

bool blib::BufferQueue::Push(blib::MemBlock *block)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (m_queue.size() > m_max)
    {
        if (block)
        {
            delete block;
            block = nullptr;
        }
        //TODO:return status
        return false;
    }
    m_queue.push(block);
    m_bytes += block->Capacity();
    m_sem.Signal(1);
    return true;
}

blib::MemBlock *blib::BufferQueue::Front()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_queue.empty() ? nullptr : m_queue.front();
}

void blib::BufferQueue::Pop()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (m_queue.empty())
    {
        return;
    }
    MemBlock *block = m_queue.front();
    if (block)
    {
        delete block;
        block = nullptr;
    }
    m_bytes -= m_queue.front()->Capacity();
    m_queue.pop();
}

uint32_t blib::BufferQueue::Size()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_queue.size();
}

bool blib::BufferQueue::Empty()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_queue.empty();
}

bool blib::BufferQueue::Clear()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    while (m_queue.size())
    {
        MemBlock *block = m_queue.front();
        if (block)
        {
            delete block;
            block = nullptr;
        }
        m_queue.pop();
    }
    return true;
}

uint32_t blib::BufferQueue::Bytes()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_bytes;
}

bool blib::BufferQueue::Wait(uint32_t ms = -1)
{
    return m_sem.Wait();
}
