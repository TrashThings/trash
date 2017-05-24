#pragma once

#include "headers.hpp"
#include <iterator>
#include <memory>
#include <assert.h>


_AN_BEGIN

template <typename T>
class list
{
	size_t m_size;
public:
	class node
	{
	public:
		T data;

		node * next;

		node () : next{ nullptr } {}
	};
private:
	node * m_head;
public:
	const size_t size () const { return m_size; }

	node * get () const { return m_head; }

	void push (T && args) noexcept
	{
		node * item = new node;
		item->data = args;

		if (nullptr == m_head)
		{
			m_head = item;
		}
		else
		{
			item->next = m_head;
			m_head = item;
		}

		++m_size;
	}

	void pop ()
	{
		node * temp = this->get ();
		assert (temp);

		m_head = temp->next;
		delete temp;

		--m_size;
	}

	list () noexcept : m_size{ 0 }, m_head{ nullptr } {}
	~list ()
	{
		node * temp = nullptr;
		node * node = this->get ();

		while (nullptr != node)
		{
			temp = node;
			node = node->next;
			delete temp;
		}
	}
};

_AN_END