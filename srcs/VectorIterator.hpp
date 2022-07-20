#ifndef VECTORITERATOR_HPP
# define VECTORITERATOR_HPP

# include "Iterator.hpp"
# include "Utils.hpp"

namespace ft
{
	template <typename T, bool is_const>
	class VectorIterator
	{
		public:
		typedef T																			value_type;
		typedef std::ptrdiff_t																difference_type;
		typedef std::size_t																	size_type;
		typedef typename ft::typeSelector<value_type*, const value_type*, is_const>::type	pointer;
		typedef typename ft::typeSelector<value_type&, const value_type&, is_const>::type	reference;
		typedef typename ft::random_access_iterator_tag										iterator_category;

	private:
		pointer																				mPtr;
	
	public:
		VectorIterator()
			: mPtr(NULL)
		{}

		VectorIterator(pointer ptr)
			: mPtr(ptr)
		{}

		VectorIterator(const VectorIterator<value_type, false>& it)
			: mPtr(it.getPtr())
		{}

		virtual ~VectorIterator()
		{}

		pointer getPtr(void) const
		{
			return (this->mPtr);
		}

		VectorIterator& operator=(const VectorIterator& it)
		{
			this->mPtr = it.mPtr;
			return (*this);
		}

		bool operator==(const VectorIterator<value_type, false>& it) const
		{
			return (this->mPtr == it.getPtr());
		}

		bool operator==(const VectorIterator<value_type, true>& it) const
		{
			return (this->mPtr == it.getPtr());
		}

		bool operator!=(const VectorIterator<value_type, false>& it) const
		{
			return (this->mPtr != it.getPtr());
		}

		bool operator!=(const VectorIterator<value_type, true>& it) const
		{
			return (this->mPtr != it.getPtr());
		}

		reference operator*() const
		{
			return (*(this->mPtr));
		}

		pointer operator->() const
		{
			return (this->mPtr);
		}

		VectorIterator& operator++()
		{
			++this->mPtr;
			return (*this);
		}

		VectorIterator operator++(int)
		{
			VectorIterator	temp(*this);

			operator++();
			return (temp);
		}

		VectorIterator& operator--()
		{
			--this->mPtr;
			return (*this);
		}

		VectorIterator operator--(int)
		{
			VectorIterator	temp(*this);

			operator--();
			return (temp);
		}

		VectorIterator operator+(const int& n) const
		{
			return (VectorIterator(this->mPtr + n));
		}

		VectorIterator operator-(const int& n) const
		{
			return (VectorIterator(this->mPtr - n));
		}

		difference_type operator-(const VectorIterator<value_type, false>& it) const
		{
			return (this->mPtr - it.getPtr());
		}

		difference_type operator-(const VectorIterator<value_type, true>& it) const
		{
			return (this->mPtr - it.getPtr());
		}

		VectorIterator& operator+=(const difference_type n)
		{
			this->mPtr += n;
			return (*this);
		}

		VectorIterator& operator-=(const difference_type n)
		{
			this->mPtr -= n;
			return (*this);
		}

		bool operator<(const VectorIterator<value_type, false>& it) const
		{
			return (this->mPtr < it.getPtr());
		}

		bool operator<(const VectorIterator<value_type, true>& it) const
		{
			return (this->mPtr < it.getPtr());
		}

		bool operator<=(const VectorIterator<value_type, false>& it) const
		{
			return (this->mPtr <= it.getPtr());
		}

		bool operator<=(const VectorIterator<value_type, true>& it) const
		{
			return (this->mPtr <= it.getPtr());
		}

		bool operator>(const VectorIterator<value_type, false>& it) const
		{
			return (this->mPtr > it.getPtr());
		}

		bool operator>(const VectorIterator<value_type, true>& it) const
		{
			return (this->mPtr > it.getPtr());
		}

		bool operator>=(const VectorIterator<value_type, false>& it) const
		{
			return (this->mPtr >= it.getPtr());
		}

		bool operator>=(const VectorIterator<value_type, true>& it) const
		{
			return (this->mPtr >= it.getPtr());
		}

		reference operator[](difference_type n) const
		{
			return (*(this->mPtr + n));
		}
	};

	template <typename T, bool is_const>
	VectorIterator<T, is_const>	operator+(const typename VectorIterator<T, is_const>::difference_type n, const VectorIterator<T, is_const>& it)
	{
		return (VectorIterator<T, is_const>(it.getPtr() + n));
	}
}

#endif