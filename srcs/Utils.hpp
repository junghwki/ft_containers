#ifndef UTILS_HPP
# define UTILS_HPP

namespace ft
{
	template <bool Cond, typename T = void>
	class enable_if
	{
	};

	template <typename T>
	class enable_if <true, T>
	{
	public:
		typedef T type;
	};

	template <typename T>
	class is_integral
	{
	public:
		static const bool value = false;
	};

	template <>
	class is_integral <bool>
	{
	public:
		static const bool value = true;
	};

	template <>
	class is_integral <char>
	{
	public:
		static const bool value = true;
	};

	template <>
	class is_integral <wchar_t>
	{
	public:
		static const bool value = true;
	};

	template <>
	class is_integral <int>
	{
	public:
		static const bool value = true;
	};

	template <>
	class is_integral <short>
	{
	public:
		static const bool value = true;
	};

	template <>
	class is_integral <long>
	{
	public:
		static const bool value = true;
	};

	template <>
	class is_integral <long long>
	{
	public:
		static const bool value = true;
	};

	template <>
	class is_integral <unsigned char>
	{
	public:
		static const bool value = true;
	};

	template <>
	class is_integral <unsigned short>
	{
	public:
		static const bool value = true;
	};

	template <>
	class is_integral <unsigned int>
	{
	public:
		static const bool value = true;
	};

	template <>
	class is_integral <unsigned long>
	{
	public:
		static const bool value = true;
	};

	template <>
	class is_integral <unsigned long long>
	{
	public:
		static const bool value = true;
	};

	template <typename Type, typename constType, bool isConst = false>
	class typeSelector
	{
	public:
		typedef Type type;
	};

	template <typename Type, typename constType>
	class typeSelector<Type, constType, true>
	{
	public :
		typedef constType type;
	};

	template <typename T>
	class less
	{
	public:
		bool operator() (const T& x, const T& y) const
		{
			return (x < y);
		}
	};

	template <typename InputIterator1, typename InputIterator2>
	bool equal (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
	{
		while (first1 != last1)
		{
			if (*first1 != *first2)
			{
				return (false);
			}
			++first1;
			++first2;
		}
		return (true);
	}

	template <typename InputIterator1, typename InputIterator2>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || *first2 < *first1)
			{
				return (false);
			}
			else if (*first1 < *first2)
			{
				return (true);
			}
			++first1;
			++first2;
		}
		return (first2 != last2);
	}
}

#endif