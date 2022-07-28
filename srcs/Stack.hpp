#ifndef STACK_HPP
# define STACK_HPP

# include "vector.hpp"

namespace ft
{
	template <class T, class Container = ft::vector<T> >
	class stack
	{
	public:
		typedef typename Container::value_type		value_type;
		typedef typename Container::size_type		size_type;
		typedef Container							container_type;

		explicit stack (const container_type& ctnr = container_type())
			: c(ctnr)
		{}

		bool empty() const
		{
			return (c.empty());
		}

		size_type size() const
		{
			return (c.size());
		}

		value_type& top()
		{
			return (c.back());
		}

		const value_type& top() const
		{
			return (c.back());
		}

		void push(const value_type& val)
		{
			c.push_back(val);
		}
		
		void pop()
		{
			c.pop_back();
		}

		template <typename U, typename Cont>
		friend bool operator==(const stack<U, Cont>& lhs, const stack<U, Cont>& rhs);

		template <typename U, typename Cont>
		friend bool operator<(const stack<U, Cont>& lhs, const stack<U, Cont>& rhs);

		template <typename U, typename Cont>
		friend bool operator>(const stack<U, Cont>& lhs, const stack<U, Cont>& rhs);
	
	protected:
		Container	c;
	};
	
	template<typename T, typename Container>
	bool operator==(const stack<T, Container>& x, const stack<T, Container>& y)
	{
		return (x.c == y.c);
	}

	template<typename T, typename Container>
	bool operator<(const stack<T, Container>& x, const stack<T, Container>& y)
	{
		return (x.c < y.c);
	}

	template<typename T, typename Container>
	bool operator!=(const stack<T, Container>& x, const stack<T, Container>& y)
	{
		return (!(x == y));
	}

	template<typename T, typename Container>
	bool operator>(const stack<T, Container>& x, const stack<T, Container>& y)
	{
		return (y < x);
	}

	template<typename T, typename Container>
	bool operator<=(const stack<T, Container>& x, const stack<T, Container>& y)
	{
		return (!(y < x));
	}

	template<typename T, typename Container>
	bool operator>=(const stack<T, Container>& x, const stack<T, Container>& y)
	{
		return (!(x < y));
	}
}

#endif