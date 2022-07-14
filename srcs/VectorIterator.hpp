#ifndef VECTORITERATOR_HPP
# define VECTORITERATOR_HPP

# include "Iterator.hpp"
# include "Utils.hpp"

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

		private:
			pointer mPtr;
		
		public:
			VectorIterator()
				: mPtr(NULL)
			{}

			VectorIterator(pointer Array)
				: mPtr(Array)
			{}

			VectorIterator(const VectorIterator<value_type, false>& iter)
				: mPtr(iter.getPtr())
			{}

			virtual ~VectorIterator()
			{}

			pointer getPtr(void) const
			{
				return (this->mPtr);
			}

			VectorIterator& operator=(const VectorIterator& iter)
			{
				this->mPtr = iter.mPtr;
				return (*this);
			}

			bool operator==(const VectorIterator<value_type, false>& iter) const
			{
				return (this->mPtr == iter.getPtr());
			}

			bool operator==(const VectorIterator<value_type, true>& iter) const
			{
				return (this->mPtr == iter.getPtr());
			}

			bool operator!=(const VectorIterator<value_type, false>& iter) const
			{
				return (this->mPtr != iter.getPtr());
			}

			bool operator!=(const VectorIterator<value_type, true>& iter) const
			{
				return (this->mPtr != iter.getPtr());
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
				VectorIterator temp(*this);

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
				VectorIterator temp(*this);

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

			difference_type operator-(const VectorIterator<value_type, false>& iter) const
			{
				return (this->mPtr - iter.getPtr());
			}

			difference_type operator-(const VectorIterator<value_type, true>& iter) const
			{
				return (this->mPtr - iter.getPtr());
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

			bool operator<(const VectorIterator<value_type, false>& iter) const
			{
				return (this->mPtr < iter.getPtr());
			}

			bool operator<(const VectorIterator<value_type, true>& iter) const
			{
				return (this->mPtr < iter.getPtr());
			}

			bool operator<=(const VectorIterator<value_type, false>& iter) const
			{
				return (this->mPtr <= iter.getPtr());
			}

			bool operator<=(const VectorIterator<value_type, true>& iter) const
			{
				return (this->mPtr <= iter.getPtr());
			}

			bool operator>(const VectorIterator<value_type, false>& iter) const
			{
				return (this->mPtr > iter.getPtr());
			}

			bool operator>(const VectorIterator<value_type, true>& iter) const
			{
				return (this->mPtr > iter.getPtr());
			}

			bool operator>=(const VectorIterator<value_type, false>& iter) const
			{
				return (this->mPtr >= iter.getPtr());
			}

			bool operator>=(const VectorIterator<value_type, true>& iter) const
			{
				return (this->mPtr >= iter.getPtr());
			}

			reference operator[](difference_type n) const
			{
				return (*(this->mPtr + n));
			}
	};

	template <typename T, bool isConst>
	VectorIterator<T, isConst>	operator+(const typename VectorIterator<T, isConst>::difference_type n, const VectorIterator<T, isConst>& iter)
	{
		return (VectorIterator<T, isConst>(iter.getPtr() + n));
	}
}

#endif