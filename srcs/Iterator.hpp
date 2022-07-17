#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <cstddef>

namespace ft
{
	class input_iterator_tag {};
	class output_iterator_tag {};
	class forward_iterator_tag : public input_iterator_tag {};
	class bidirectional_iterator_tag : public forward_iterator_tag {};
	class random_access_iterator_tag : public bidirectional_iterator_tag {};

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
		typedef Iterator												iterator_type;
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

		explicit reverse_iterator(iterator_type x)
			: mCurrent(x)
		{}

		reverse_iterator(const reverse_iterator &x)
			: mCurrent(x.mCurrent)
		{}

		template <typename _Iter>
		reverse_iterator(const reverse_iterator<_Iter> &x)
			: mCurrent(x.base())
		{}

		iterator_type base() const
		{
			return (mCurrent);
		}

		reference operator*() const
		{
			Iterator temp = mCurrent;
			return (*--temp);
		}

		pointer operator->() const
		{
			return (&(operator*()));
		}

		reverse_iterator &operator++()
		{
			--mCurrent;
			return (*this);
		}

		reverse_iterator operator++(int)
		{
			reverse_iterator temp = *this;
			--mCurrent;
			return (temp);
		}

		reverse_iterator &operator--()
		{
			++mCurrent;
			return (*this);
		}

		reverse_iterator operator--(int)
		{
			reverse_iterator temp = *this;
			++mCurrent;
			return (temp);
		}

		reverse_iterator operator+(difference_type n) const
		{
			return (reverse_iterator(mCurrent - n));
		}

		reverse_iterator &operator+=(difference_type n)
		{
			mCurrent -= n;
			return (*this);
		}

		reverse_iterator operator-(difference_type n) const
		{
			return (reverse_iterator(mCurrent + n));
		}

		reverse_iterator & operator-=(difference_type n)
		{
			mCurrent += n;
			return (*this);
		}

		reference operator[](difference_type n) const
		{
			return (*(*this + n));
		}
	}; 
 
	template <typename Iterator, typename Iterator2>
	bool operator==(const reverse_iterator<Iterator> &x, const reverse_iterator<Iterator2> &y)
	{
		return (x.base() == y.base());
	}

	template <typename Iterator, typename Iterator2>
	bool operator<(const reverse_iterator<Iterator> &x, const reverse_iterator<Iterator2> &y)
	{
		return (y.base() < x.base());
	}

	template <typename Iterator, typename Iterator2>
	bool operator!=(const reverse_iterator<Iterator> &x, const reverse_iterator<Iterator2> &y)
	{
		return (!(x == y));
	}

	template <typename Iterator, typename Iterator2>
	bool operator>(const reverse_iterator<Iterator> &x, const reverse_iterator<Iterator2> &y)
	{
		return (y < x);
	}

	template <typename Iterator, typename Iterator2>
	bool operator<=(const reverse_iterator<Iterator> &x, const reverse_iterator<Iterator2> &y)
	{
		return (!(y < x));
	}

	template <typename Iterator, typename Iterator2>
	bool operator>=(const reverse_iterator<Iterator> &x, const reverse_iterator<Iterator2> &y)
	{
		return (!(x < y));
	}

	template <typename Iterator, typename Iterator2>
	typename reverse_iterator<Iterator>::difference_type
	operator-(const reverse_iterator<Iterator> &x, const reverse_iterator<Iterator2> &y)
	{
		return (y.base() - x.base());
	}

	template <typename Iterator>
	reverse_iterator<Iterator>
	operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator> &x)
	{
		return (reverse_iterator<Iterator>(x.base() - n));
	}

}

#endif