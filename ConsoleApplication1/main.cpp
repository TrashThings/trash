#include <future>
#include <iostream>
#include <string>
#include <array>

#include "stack.hpp"
#include "vector.hpp"
#include "list.hpp"


template <typename T> class point : public T
{
public:
	template <typename V> point <T> operator+ (const V &o)
	{
		return point <T> (x + o, y + o);
	}
	template <typename V> point <T> & operator+= (const V &o)
	{
		x += o;
		y += o;
		return *this;
	}

	template <typename ... ARGS> point (ARGS &&... args) : T{ std::forward <ARGS> (args)... } {}
};

class ipoint
{
public:
	uint16_t x;
	uint16_t y;

	ipoint (const uint16_t &_x, const uint16_t &_y) : x{ _x }, y{ _y } {}
	ipoint () {}
};

class custom
{
public:
	int x;
	~custom () {}
};

void kiss_miss ()
{
	std::cout << "my:\n";
	for (uint16_t q = 1; q <= 100; ++q)
	{
		if (0 == q % 3)
		{
			if (0 == q % 5)
			{
				std::cout << "MissKiss";
			}
			else
			{
				std::cout << "Miss";
			}
		}
		else if (0 == q % 5)
		{
			std::cout << "Kiss";
		}
		else
		{
			std::cout << q;
		}

		std::cout << ", ";

		std::this_thread::sleep_for (std::chrono::milliseconds (50));
	}

	std::cout << "\n\nn my:\n";
	for (uint16_t q = 1; q <= 100; ++q)
	{
		const std::array <std::string, 4> text{ std::to_string (q), "Miss", "Kiss", "MissKiss" };

		const bool three{ 0 == q % 3 };
		const bool five{ 0 == q % 5 };


		std::cout << text[three + five * 2] << ", ";

		std::this_thread::sleep_for (std::chrono::milliseconds (50));
	}
}

std::future <bool> form_run (const std::string& form)
{
	return std::async (std::launch::async, [](const std::string& form) -> bool
	{
		point <ipoint> point (5ui16, 5ui16);

		an::stack <std::unique_ptr <custom>> stack;
		an::vector <std::unique_ptr <custom>> vector;
		an::list <int> list;

		// stack
		for (int q{ 0 }; q != 5; ++q)
		{
			std::unique_ptr <custom> c (new custom);
			c->x = q;
			stack.push (std::forward <std::unique_ptr <custom>> (c));
		}
		for (int q{ 0 }; q != 5; ++q)
		{
			auto el{ std::move (stack.pop ()) };
			std::cout << "stack[" << q << "]: " << el->x << '\n';
		}

		// vector
		for (int q{ 0 }; q != 5; ++q)
		{
			std::unique_ptr <custom> c (new custom);
			c->x = q;
			vector.push_back (std::forward <std::unique_ptr <custom>> (c));
		}
		for (size_t q{ 0 }, s{ vector.size () }; q != s; ++q)
		{
			std::cout << "vector[" << q << "]: " << vector[0]->x << '\n';
			vector.erase (0);
		}

		// list
		for (int q{ 0 }; q != 5; ++q)
		{
			list.push (std::move (q));
		}

		{
			an::list <int>::node * node = list.get ();
			int q{ 0 };
			while (nullptr != node)
			{
				std::cout << "list [" << q++ << "]: " << node->data << '\n';
				node = node->next;
			}
		}
		list.reverse ();
		{
			an::list <int>::node * node = list.get ();
			int q{ 0 };
			while (nullptr != node)
			{
				std::cout << "list [" << q++ << "]: " << node->data << '\n';
				node = node->next;
			}
		}
		/*for (size_t q{ 0 }, c{ list.size () }; q < c; ++q)
		{
			list.pop ();
		}*/
		{
			an::list <int>::node * node = list.get ();
			int q{ 0 };
			while (nullptr != node)
			{
				std::cout << "p list [" << q++ << "]: " << node->data << '\n';
				node = node->next;
			}
		}

		point += 10;
		point = point + 5;

		std::cout << "Form element: " << form << "\n";

		kiss_miss ();
		return true;
	}, form);
}

void main () noexcept
{
	// list
	an::list <int> list;

	for (int q{ 0 }; q != 5; ++q)
	{
		list.push (std::move (q));
	}

	{
		an::list <int>::node * node = list.get ();
		int q{ 0 };
		while (nullptr != node)
		{
			std::cout << "list [" << q++ << "]: " << node->data << '\n';
			node = node->next;
		}
	}
	list.reverse ();
	{
		an::list <int>::node * node = list.get ();
		int q{ 0 };
		while (nullptr != node)
		{
			std::cout << "list [" << q++ << "]: " << node->data << '\n';
			node = node->next;
		}
	}

	//if (form_run ("window").get ()) { std::cout << "good\n"; }
	
	system ("pause");
}