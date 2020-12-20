

#include "BufferQueue.h"

blib::BufferQueue::BufferQueue(uint32_t _max) : m_max(_max), m_sem(0)
{
}

blib::BufferQueue::~BufferQueue()
{
}

blib::MemBlock *blib::BufferQueue::NewBlock(uint32_t size)
{
}

bool blib::BufferQueue::Push(blib::MemBlock *block)
{
}

blib::MemBlock *blib::BufferQueue::Front()
{
}

void blib::BufferQueue::Pop()
{
}

uint32_t blib::BufferQueue::Size()
{
}

bool blib::BufferQueue::Empty()
{
}

bool blib::BufferQueue::Clear()
{
}

bool blib::BufferQueue::Wait(uint32_t ms = -1)
{
}
