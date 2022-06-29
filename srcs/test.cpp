#include "Iterator.hpp"
#include "Vector.hpp"
#include "VectorIterator.hpp"


int main(void)
{
	ft::Vector<int> a;

	a.push_back(3);

	std::cout << a[0] << std::endl;
}