#pragma once

#include <assert.h>


_AN_BEGIN

template <typename T>
class list
{
public:
	class node
	{
	public:
		T data;

		node * next;

		node () : next{ nullptr } {}
	};
private:
	node * m_root;
public:
	node * get () const { return m_root; }

	void push (T && args) noexcept
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

	void pop ()
	{
		node * temp = this->get ();
		assert (temp);

		m_root = temp->next;
		delete temp;
	}

	list () noexcept : m_root{ nullptr } {}
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