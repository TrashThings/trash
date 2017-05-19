#pragma once

#include "headers.hpp"
#include <iterator>
#include <memory>
#include <assert.h>


_AN_BEGIN

template <typename T>
class stack
{
	std::unique_ptr <T[]> m_ptr;
	size_t m_size;
public:
	void push (T && el) noexcept
	{
		std::unique_ptr <T[]> ptr{ new T [m_size + 1] };
		assert (ptr.get ());

		ptr[m_size] = std::move (el);
		const auto src_begin{ m_ptr.get () };
		std::move (src_begin, std::next (src_begin, m_size), stdext::checked_array_iterator <T *> (ptr.get (), m_size + 1));
				
		m_ptr = std::move (ptr);

		++m_size;
	}

	T pop (void) noexcept
	{
		assert (m_size);

		--m_size;

		auto el{ m_ptr[m_size] };

		std::unique_ptr <T[]> ptr{ new T[m_size] };
		assert (ptr.get ());
		
		const auto src_begin{ m_ptr.get () };
		std::move (src_begin, std::next (src_begin, m_size), stdext::checked_array_iterator <T *> (ptr.get (), m_size));

		m_ptr = std::move (ptr);

		return el;
	}
	stack () noexcept : m_size{ 0 } {}
};

_AN_END