#ifndef PAIR_HPP
# define PAIR_HPP

namespace ft
{
	template <typename T1, typename T2>
	class pair
	{
	public:
		typedef T1		first_type;
		typedef T2		second_type;

		first_type		first;
		second_type		second;

		pair()
			: first(first_type()), second(second_type())
		{}

		template<class U, class V>
		pair(const pair<U, V>& pr)
			: first(pr.first), second(pr.second)
		{}

		pair(const first_type& a, const second_type& b)
			: first(a), second(b)
		{}

		pair& operator=(const pair& pr)
		{
			this->first = pr.first;
			this->second = pr.second;
			return (*this);
		}
	};

	template<typename T1, typename T2>
	pair<T1, T2> make_pair(T1 x, T2 y)
	{
		return (pair<T1, T2>(x, y));
	}

	template<typename T1, typename T2>
	bool operator==(const pair<T1, T2>& x, const pair<T1, T2>& y)
	{
		return (x.first == y.first && x.second == y.second);
	}

	template<typename T1, typename T2>
	bool operator<(const pair<T1, T2>& x, const pair<T1, T2>& y)
	{
		return (x.first < y.first || (!(y.first < x.first) && x.second < y.second));
	}

	template<typename T1, typename T2>
	bool operator!=(const pair<T1, T2>& x, const pair<T1, T2>& y)
	{
		return (!(x == y));
	}

	template<typename T1, typename T2>
	bool operator>(const pair<T1, T2>& x, const pair<T1, T2>& y)
	{
		return (y < x);
	}

	template<typename T1, typename T2>
	bool operator<=(const pair<T1, T2>& x, const pair<T1, T2>& y)
	{
		return (!(y < x));
	}

	template<typename T1, typename T2>
	bool operator>=(const pair<T1, T2>& x, const pair<T1, T2>& y)
	{
		return (!(x < y));
	}
}	

#endif