#ifndef PAIR_HPP
# define PAIR_HPP

namespace ft
{
	template <typename T1, typename T2>
	class pair
	{
	public:
		typedef T1	first_type;
		typedef T2	second_type;

		first_type	first;
		second_type	second;

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

	template<typename _T1, typename _T2>
	pair<_T1, _T2> make_pair(_T1 __x, _T2 __y)
	{
		return (pair<_T1, _T2>(__x, __y);)
	}

	template<typename _T1, typename _T2>
	bool operator==(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y)
	{
		return (__x.first == __y.first && __x.second == __y.second;)
	}

	template<typename _T1, typename _T2>
	bool operator<(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y)
	{
		return (__x.first < __y.first || (!(__y.first < __x.first) && __x.second < __y.second);)
	}

	template<typename _T1, typename _T2>
	bool operator!=(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y)
	{
		return (!(__x == __y);)
	}

	template<typename _T1, typename _T2>
	bool operator>(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y)
	{
		return (__y < __x;)
	}

	template<typename _T1, typename _T2>
	bool operator<=(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y)
	{
		return (!(__y < __x);)
	}

	template<typename _T1, typename _T2>
	bool operator>=(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y)
	{
		return (!(__x < __y);)
	}
}	

#endif