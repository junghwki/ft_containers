#ifndef VECTORITERATOR_HPP
# define VECTORITERATOR_HPP

#include <iostream>
#include "Iterator.hpp"
#include "Utils.hpp"

namespace ft
{
template <typename T, bool isConst>
class VectorIterator
{
public:
	typedef T																			value_type;
	typedef std::ptrdiff_t																difference_type;
	typedef std::size_t																	size_type;
	typedef typename ft::typeSelector<value_type*, const value_type*, isConst>::type	pointer;
	typedef typename ft::typeSelector<value_type&, const value_type&, isConst>::type	reference;
	typedef typename ft::random_access_iterator_tag										iterator_category;
	// typedef T										value_type;
	// typedef typename ft::random_access_iterator_tag	iterator_category;
	// typedef size_t									size_type;
	// typedef std::ptrdiff_t							difference_type;
	// typedef difference_type							distance_type;
	// typedef T*										pointer;
	// typedef T&										reference;
	// typedef VectorIterator<T>						iterator;

private:
	pointer mArr;

public:
	VectorIterator()
		: mArr(NULL)
	{
	}

	VectorIterator(const pointer Array)
		: mArr(Array)
	{
	}

	VectorIterator(const iterator Iter)
	{
		this->mArr = Iter.getPtr();
	}

	pointer getPtr() const
	{
		return (this->mArr);
	}

	~VectorIterator();

	VectorIterator<typename value_type> &operator=(const VectorIterator arg)
	{
		this->mArr(arg.getPtr());
	}

	VectorIterator<typename T> &operator++(void)
	{
		this->mArr++;
		return (*this);
	}

	VectorIterator<typename T> &operator--(void)
	{
		this->mArr--;
		return (*this);
	}

	VectorIterator<typename T> operator++(int)
	{
		VectorIterator<typename T> ret(*this);

		this->mArr++;
		return (ret);
	}

	VectorIterator<typename T> operator--(int)
	{
		VectorIterator<typename T> ret(*this);

		this->mArr--;
		return (ret);
	}

	VectorIterator<typename T> operator[](const int index)
	{
		return (this->mArr[index])
	}

	const VectorIterator<typename T> operator[](const int index) const
	{
		return (this->mArr[index])
	}

	const VectorIterator<typename T> operator*() const
	{
		return (*this->mArr);
	}

	const VectorIterator<typename T> operator->() const
	{
		return (*this->mArr);
	}

	const VectorIterator<typename T> operator+(size_t size) const
	{
		VectorIterator<typename T> temp;

		temp = *this;
		temp.mArr += size;
		return (temp);
	}

	const VectorIterator<typename T> operator-(size_t size) const
	{
		VectorIterator<typename T> temp;

		temp = *this;
		temp.mArr -= size;
		return (temp);
	}

	ptrdiff_t operator-(VectorIterator arg) const
	{
		return (this->mArr -= arg.getPtr());
	}

	VectorIterator<typename T> operator+=(size_t size) const
	{
		return (this->mArr += arg.getPtr());
	}

	VectorIterator<typename T> operator-=(size_t size) const
	{
		return (this->mArr -= arg.getPtr());
	}

	template <typename T1>
	bool operator==(VectorIterator<T1> &temp)
	{
		return (this->mArr == temp.getPtr());
	}

	template <typename T1>
	bool operator!=(VectorIterator<T1> &temp)
	{
		return (this->mArr != temp.getPtr());
	}

	template <typename T1>
	bool operator>(VectorIterator<T1> &temp)
	{
		return (this->mArr > temp.getPtr());
	}

	template <typename T1>
	bool operator<(VectorIterator<T1> &temp)
	{
		return (this->mArr < temp.getPtr());
	}

	template <typename T1>
	bool operator>=(VectorIterator<T1> &temp)
	{
		return (this->mArr >= temp.getPtr());
	}

	template <typename T1>
	bool operator<=(VectorIterator<T1> &temp)
	{
		return (this->mArr <= temp.getPtr());
	}
};
} // namespace ft

#endif