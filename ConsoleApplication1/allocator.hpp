#pragma once

#include "headers.hpp"
#include <assert.h>
#include <deque>
#include <vector>


_AN_BEGIN

class memory
{
	size_t m_allocations;
	size_t m_available;

	unsigned char * m_memory;
	std::deque <std::vector <unsigned char>> m_chunks;
public:
	void * allocate (const size_t &count)
	{
		if (count > m_available)
		{
			m_chunks.emplace_back (count);
			m_available = m_chunks.back.size ();
			m_memory = &m_chunks.back ().front ();
		}

		auto memory{ m_memory };

		m_available -= count;
		m_memory += count;

		++m_allocations;

		return memory;
	}

	void deallocate (void * ptr, const size_t &count)
	{
		assert (p);

		--m_allocations;
		auto memory{ static_cast <unsigned char *> (ptr) };

		if (memory + count == m_memory)
		{
			m_memory = memory;
			m_available += count;
		}
	}

	~memory ()
	{
		assert (m_allocations);
	}
};

class memory_allocator
{

};

_AN_END