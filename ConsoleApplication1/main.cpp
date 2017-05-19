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

std::future<bool> submitForm (const std::string& form)
{
	point <ipoint> point (5ui16, 5ui16);
	
	point += 10;
	point = point + 5;


	auto handle = [](const std::string& form) -> bool
	{
		std::cout << "Handle the submitted form: " << form << "\n";
		return true;
	};

	std::packaged_task<bool (const std::string&)> task (handle);
	auto future = task.get_future ();
	std::thread thread (std::move (task), form);
	thread.detach ();
	return std::move (future);
}

void main () noexcept
{
	submitForm ("window");

	system ("pause");
}