#include <future>
#include <iostream>
#include <string>
#include "stack.hpp"
#include "vector.hpp"


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

std::future <bool> form_run (const std::string& form)
{
	return std::async (std::launch::async, [](const std::string& form) -> bool
	{
		point <ipoint> point (5ui16, 5ui16);

		an::stack <std::unique_ptr <custom>> stack;
		an::vector <std::unique_ptr <custom>> vector;

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
			std::cout << "el[" << q << "]: " << el->x << '\n';
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

		point += 10;
		point = point + 5;

		std::cout << "Form element: " << form << "\n";
		return true;
	}, form);
}

void main () noexcept
{
	if (form_run ("window").get ())
	{
		std::cout << "good\n";
	}

	system ("pause");
}