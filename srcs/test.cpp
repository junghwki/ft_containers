#include "Iterator.hpp"
#include "Vector.hpp"
#include "VectorIterator.hpp"


int main(void)
{
	ft::vector<int> a;

	a.push_back(34);

	std::cout << a[0] << std::endl;
}