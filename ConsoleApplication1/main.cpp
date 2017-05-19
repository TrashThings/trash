#include <future>
#include <iostream>
#include <string>


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

std::future <bool> form_run (const std::string& form)
{
	std::packaged_task <bool (const std::string&)> task ([](const std::string& form) -> bool
	{
		point <ipoint> point (5ui16, 5ui16);

		point += 10;
		point = point + 5;

		std::cout << "Form element: " << form << "\n";
		return true;
	});

	auto future = task.get_future ();
	std::thread (std::move (task), form).detach ();

	return future;
}

void main () noexcept
{
	if (form_run ("window").get ())
	{
		std::cout << "good\n";
	}

	system ("pause");
}