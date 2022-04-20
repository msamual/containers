#ifndef CONT_UTILS_HPP
# define CONT_UTILS_HPP

# include "reverse_iterator.hpp"

namespace ft
{
	template <bool B, class T = void>
	struct enable_if {};

	template <class T>
	struct enable_if<true, T>
	{
		typedef T type;
	};

	template <class T, T v>
	struct integral_constant
	{
		static const T		value = v;
		typedef T			value_type;
		typedef integral_constant type;
    	operator value_type() const {return value;}
	};

	typedef		integral_constant<bool, true>	true_type;
	typedef		integral_constant<bool, false>	false_type;

	template <class T>	struct is_integral                     : public false_type {};
	template <>			struct is_integral<bool>               : public true_type {};
	template <>			struct is_integral<char>               : public true_type {};
	template <>			struct is_integral<signed char>        : public true_type {};
	template <>			struct is_integral<unsigned char>      : public true_type {};
	template <>			struct is_integral<wchar_t>            : public true_type {};
	template <>			struct is_integral<char16_t>           : public true_type {};
	template <>			struct is_integral<char32_t>           : public true_type {};
	template <>			struct is_integral<short>              : public true_type {};
	template <>			struct is_integral<unsigned short>     : public true_type {};
	template <>			struct is_integral<int>                : public true_type {};
	template <>			struct is_integral<unsigned int>       : public true_type {};
	template <>			struct is_integral<long>               : public true_type {};
	template <>			struct is_integral<unsigned long>      : public true_type {};
	template <>			struct is_integral<long long>          : public true_type {};
	template <>			struct is_integral<unsigned long long> : public true_type {};
	template <>			struct is_integral<__int128_t>         : public true_type {};
	template <>			struct is_integral<__uint128_t>        : public true_type {};

	template <class	Iterator>
	typename ft::iterator_traits<Iterator>::difference_type		distance(Iterator first, Iterator last)
	{
		typename ft::iterator_traits<Iterator>::difference_type	n = 0;
		while (first++ != last)
			n++;
		return n;
	}

	template <class InputIterator1, class InputIterator2>
	bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
	{
		while (first1 != last1)
		{
			if (*first1++ != *first2++)
				return false;
		}
		return true;
	}

	template <class InputIterator1, class InputIterator2>
	bool	lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || *first2 < *first1)
				return false;
			else if (*first1 < *first2)
				return true;
			++first1;
			++first2;
		}
		return (first1 == last1) && (first2 != last2);
	}

	template <class T>
	void	swap(T *a, T *b)
	{
		T	tmp;

		tmp = *a;
		*a = *b;
		*b = tmp;
	}

};

#endif
