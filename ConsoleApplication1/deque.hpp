#pragma once

#include "headers.hpp"
#include <iterator>
#include <memory>
#include <assert.h>

/*
_AN_BEGIN

template <typename T>
class deque
{
	size_t m_size;
	
	class node
	{
	public:
		std::unique_ptr <T> next;
		std::unique_ptr <T> prew;

		deque () : prev{ nullptr }, next{ nullptr } {}
	};

	std::unique_ptr <T> m_begin;
	std::unique_ptr <T> m_end;
public:
	const size_t size () const { return m_size; }

	template <typename ... ARGS> void push_back (ARGS &&... args) noexcept
	{
		std::unique_ptr <T[]> ptr{ new T[m_size + 1] };
		assert (ptr.get ());

		ptr[m_size] = std::move (T (std::forward <ARGS> (args)...));
		const auto src_begin{ m_ptr.get () };
		std::move (src_begin, std::next (src_begin, m_size), stdext::checked_array_iterator <T *> (ptr.get (), m_size + 1));

		m_ptr = std::move (ptr);

		++m_size;
	}

	void erase (const size_t &iter) noexcept
	{
		assert (m_size >= iter + 1);

		--m_size;

		std::unique_ptr <T[]> ptr{ new T[m_size] };
		assert (ptr.get ());

		auto src_begin{ m_ptr.get () };
		std::move (src_begin, std::next (src_begin, iter), stdext::checked_array_iterator <T *> (ptr.get (), m_size));

		src_begin = m_ptr.get () + iter + 1;
		std::move (src_begin, std::next (src_begin, m_size - iter), stdext::checked_array_iterator <T *> (ptr.get (), m_size));

		m_ptr = std::move (ptr);
	}

	vector () noexcept : m_size{ 0 } {}
};

_AN_END*/