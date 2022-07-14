#ifndef STACK_HPP
# define STACK_HPP

#include "Vector.hpp"

namespace ft
{
	template <class T, class Container = ft::vector<T> >
	class stack
	{
	public:
		typedef typename Container::value_type	value_type;
		typedef typename Container::size_type	size_type;
		typedef Container						container_type;

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
	
	protected:
	
		Container c;

	private:

		template <typename U, class Cont>
		friend bool operator==(const stack<U, Cont> &lhs, const stack<U, Cont> &rhs);

		template <typename U, class Cont>
		friend bool operator<(const stack<U, Cont> &lhs, const stack<U, Cont> &rhs);

		template <typename U, class Cont>
		friend bool operator>(const stack<U, Cont> &lhs, const stack<U, Cont> &rhs);
	};

	template <typename T, typename Container>
	bool operator==(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
	  return (lhs.c == rhs.c);
	}

	template <typename T, typename Container>
	bool operator<(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
	  return (lhs.c < rhs.c);
	}

	template <typename T, typename Container>
	bool operator!=(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
	  return !(lhs == rhs);
	}

	template <typename T, typename Container>
	bool operator>(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
	  return (rhs < lhs);
	}

	template <typename T, typename Container>
	bool operator<=(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
	  return !(rhs < lhs);
	}

	template <typename T, typename Container>
	bool operator>=(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
	  return !(lhs < rhs);
	}
}

#endif