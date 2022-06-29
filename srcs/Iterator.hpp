#ifndef ITERATOR_HPP
# define ITERATOR_HPP

namespace ft
{
	class input_iterator_tag {};
	class output_iterator_tag {};
	class forward_iterator_tag : public input_iterator_tag {};
	class bidrectional_iterator_tag : public forward_iterator_tag {};
	class random_access_iterator_tag : public bidrectional_iterator_tag {};

	/* https://cplusplus.com/reference/iterator/iterator_traits/ */
	template <typename Iterator>
	struct iterator_traits
	{
		typedef typename Iterator::iterator_category					iterator_category;
		typedef typename Iterator::value_type							value_type;
		typedef typename Iterator::difference_type						difference_type;
		typedef typename Iterator::pointer								pointer;
		typedef typename Iterator::reference							reference;
	};

	template <typename T>
	struct iterator_traits<T*>
	{
		typedef random_access_iterator_tag								iterator_category;
		typedef T														value_type;
		typedef ptrdiff_t												difference_type;
		typedef T*														pointer;
		typedef T&														reference;
	};

	template <typename T>
	struct iterator_traits<const T*>
	{
		typedef random_access_iterator_tag								iterator_category;
		typedef T														value_type;
		typedef ptrdiff_t												difference_type;
		typedef const T*												pointer;
		typedef const T&												reference;
	};
	
	/* https://cplusplus.com/reference/iterator/reverse_iterator/ */
	template <typename Iterator>
	class reverse_iterator
	{
	public:
		typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
		typedef typename iterator_traits<Iterator>::value_type			value_type;
		typedef typename iterator_traits<Iterator>::difference_type		difference_type;
		typedef typename iterator_traits<Iterator>::pointer				pointer;
		typedef typename iterator_traits<Iterator>::reference			reference;

	protected:
		Iterator	mCurrent;

	public:
		reverse_iterator()
		{}

		explicit reverse_iterator(iterator_type Iter)
			: mCurrent(Iter)
		{}

		reverse_iterator(const reverse_iterator &Iter)
			: mCurrent(Iter.mCurrent)
		{}

		template <typename Iter>
		reverse_iterator(const reverse_iterator<Iter> &Iter)
			: mCurrent(Iter.base())
		{}

		iterator_type base() const
		{
			return (this->mCurrent);
		}

		reference operator*() const
		{
			Iterator tmp = this->mCurrent;
			return (*--tmp);
		}

		pointer operator->() const
		{
			return (&(operator*()));
		}

		reverse_iterator &operator++()
		{
			--this->mCurrent;
			return (*this);
		}

		reverse_iterator operator++(int)
		{
			reverse_iterator tmp = *this;
			--this->mCurrent;
			return (tmp);
		}

		reverse_iterator &operator--()
		{
			++this->mCurrent;
			return (*this);
		}

		reverse_iterator operator--(int)
		{
			reverse_iterator tmp = *this;
			++this->mCurrent;
			return (tmp);
		}

		reverse_iterator operator+(difference_type n) const
		{
			return (reverse_iterator(this->mCurrent - n));
		}

		reverse_iterator &operator+=(difference_type n)
		{
			this->mCurrent -= n;
			return (*this);
		}

		reverse_iterator operator-(difference_type n) const
		{
			return (reverse_iterator(this->mCurrent + n));
		}

		reverse_iterator &operator-=(difference_type n)
		{
			this->mCurrent += n;
			return (*this);
		}

		reference operator[](difference_type n) const
		{
			return (*(*this + n));
		}
	};
	template <typename _Iterator>
	bool operator==(const reverse_iterator<_Iterator> &__x,
					const reverse_iterator<_Iterator> &__y)
	{
		return (__x.base() == __y.base());
	}

	template <typename _Iterator>
	bool operator<(const reverse_iterator<_Iterator> &__x,
				   const reverse_iterator<_Iterator> &__y)
	{
		return (__y.base() < __x.base());
	}

	template <typename _Iterator>
	bool operator!=(const reverse_iterator<_Iterator> &__x,
					const reverse_iterator<_Iterator> &__y)
	{
		return !(__x == __y);
	}

	template <typename _Iterator>
	bool operator>(const reverse_iterator<_Iterator> &__x,
				   const reverse_iterator<_Iterator> &__y)
	{
		return (__y < __x);
	}

	template <typename _Iterator>
	bool operator<=(const reverse_iterator<_Iterator> &__x,
					const reverse_iterator<_Iterator> &__y)
	{
		return !(__y < __x);
	}

	template <typename _Iterator>
	bool operator>=(const reverse_iterator<_Iterator> &__x,
					const reverse_iterator<_Iterator> &__y)
	{
		return !(__x < __y);
	}

	template <typename _Iterator>
	typename reverse_iterator<_Iterator>::difference_type
	operator-(const reverse_iterator<_Iterator> &__x,
			  const reverse_iterator<_Iterator> &__y)
	{
		return (__y.base() - __x.base());
	}

	template <typename _Iterator>
	reverse_iterator<_Iterator>
	operator+(typename reverse_iterator<_Iterator>::difference_type __n,
				 const reverse_iterator<_Iterator> &__x)
	{
		return reverse_iterator<_Iterator>(__x.base() - __n);
	}
}

#endif