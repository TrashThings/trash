#include <future>
#include <iostream>
#include <string>
#include "stack.hpp"



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

		an::stack <custom> stack;

		for (int q{ 0 }; q != 5; ++q)
		{
			custom c;
			c.x = q;
			stack.push (std::move (c));
		}

		for (int q{ 0 }; q != 5; ++q)
		{
			auto el{ std::move (stack.pop ()) };
			std::cout << "el[" << q << "]: " << el.x << '\n';
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