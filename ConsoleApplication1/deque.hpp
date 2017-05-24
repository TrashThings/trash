#pragma once

#include "headers.hpp"
#include <assert.h>


_AN_BEGIN

template <typename T>
class deque
{
public:
	class node
	{
	public:
		T data;

		node * next;
		node * prev;

		node () : next{ nullptr } {}
	};
private:
	node * m_root;
	node * m_tail;
public:
	node * get () const { return m_root; }

	void push_back (T && args) noexcept
	{
		node * item = new node;
		item->data = args;

		if (nullptr == m_root)
		{
			m_tail = m_root = item;
			m_tail->next = m_root;
			m_root->prev = m_tail;

			return;
		}

		item->next = m_root;
		m_root = item;
	}
	void push_front (T && args) noexcept
	{
		node * item = new node;
		item->data = args;

		if (nullptr == m_root)
		{
			m_root = item;
			return;
		}

		item->next = m_root;
		m_root = item;
	}
	void reverse ()
	{
		node * new_root = nullptr;

		while (m_root)
		{
			node * next{ m_root->next };
			m_root->next = new_root;
			new_root = m_root;
			m_root = next;
		}
		m_root = new_root;
	}

	deque () noexcept : m_root{ nullptr } {}
	~deque ()
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