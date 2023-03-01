#ifndef VEC_ITERATOR_HPP
#define VEC_ITERATOR_HPP

#include <cstddef>	// For std::ptrdiff_t
#include <iterator> // For std::random_access_iterator_tag
#include "iterator_traits.hpp"

namespace ft
{
	template <class U>
	class vec_iterator : public ft::iterator<std::random_access_iterator_tag, U>
	{
		public:
			// properties expected by iterator
			typedef ft::iterator<std::random_access_iterator_tag, U>   traits_type;
			typedef typename traits_type::difference_type               difference_type;
			typedef typename traits_type::value_type                    value_type;
			typedef typename traits_type::pointer                       pointer;
			typedef typename traits_type::reference                     reference;
			typedef typename traits_type::iterator_category             iterator_category;
		private:
			pointer _it;
		public:
			// constructors and destructor
			vec_iterator(void) 					: _it()		{};
			vec_iterator(pointer it) 			: _it(it)	{};
			template <class T>
			vec_iterator(const vec_iterator<T>& it):_it(it.base()){};
			~vec_iterator(void) {};


			vec_iterator &operator=(const vec_iterator& u){
				if (this != &u)
					_it = u._it;
				return (*this);
			}

			pointer	base() const{
				return  _it;
			};

			reference operator*() const{
				return (*_it);
			}
			pointer   operator->() const{
				return (_it);
			}
			vec_iterator& operator++(){
				_it++;
				return (*this);
			}
			vec_iterator  operator++(int){
				vec_iterator(tmp) = *this; _it += 1; return  tmp;
			}
			vec_iterator& operator--(){
				_it--;
				return (*this);
			}
			vec_iterator  operator--(int){
				vec_iterator(tmp) = *this; _it--; return  tmp;
			}
			vec_iterator  operator+ (difference_type n) const{
				return vec_iterator(_it + n);
			}
			vec_iterator& operator+=(difference_type n){
				_it += n;
				return (*this);
			}
			vec_iterator  operator-(difference_type n) const{
				return vec_iterator(base() - n);
			}
			vec_iterator& operator-=(difference_type n){
				_it -= n;
				return (*this);
			}
			reference	operator[](difference_type n) const{
				return (_it[n]);
			}
	};
	// NON MEMBER FUNCTIONS

	template <class Iter1, class Iter2>
	bool operator==(const vec_iterator<Iter1> &l, const vec_iterator<Iter2> &r) 	{	return l.base() == r.base();	};

	template <class Iter1, class Iter2>
	bool operator!=(const vec_iterator<Iter1> &l, const vec_iterator<Iter2> &r)		{	return  l.base() != r.base();	};

	template <class Iter1, class Iter2>
	bool operator>(const vec_iterator<Iter1> &l, const vec_iterator<Iter2> &r)		{	return  l.base() > r.base();	};
	
	template <class Iter1, class Iter2>
	bool operator<=(const vec_iterator<Iter1> &l, const vec_iterator<Iter2> &r) 	{	return  l.base() <= r.base();	};
		
	template <class Iter1, class Iter2>
	bool operator<(const vec_iterator<Iter1> &l, const vec_iterator<Iter2> &r) 		{	return  l.base() < r.base();	};
		
	template <class Iter1, class Iter2>
	bool operator>=(const vec_iterator<Iter1> &l, const vec_iterator<Iter2> &r)		{	return  l.base() >= r.base();	};
	
	template <class I>
	vec_iterator<I>
	operator+(typename vec_iterator<I>::difference_type n, const vec_iterator<I>& it ){	return  it + n;					};
	
	template <class I1, class I2>
	typename vec_iterator<I1>::difference_type
	operator-(const vec_iterator<I1>& l, const vec_iterator<I2>& r)					{	 return  l.base() - r.base();	};


};

#endif