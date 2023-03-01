#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft
{

	template <class Iterator>
	class reverse_iterator : public ft::iterator<typename ft::iterator_traits<Iterator>::iterator_category,
													typename ft::iterator_traits<Iterator>::value_type,
													typename ft::iterator_traits<Iterator>::difference_type,
													typename ft::iterator_traits<Iterator>::pointer,
													typename ft::iterator_traits<Iterator>::reference>
	{
		public:
			typedef Iterator                                            	iterator_type;
			typedef ft::iterator_traits<iterator_type> 						traits_type;
			typedef typename ft::iterator_traits<Iterator>::difference_type difference_type;
			typedef typename ft::iterator_traits<Iterator>::reference       reference;
			typedef typename ft::iterator_traits<Iterator>::pointer         pointer;

		private: 
			iterator_type    _it;

		public:
			reverse_iterator()								: _it()		{}
			reverse_iterator(iterator_type x)				: _it(x)	{}
			template <class T>
			reverse_iterator(const reverse_iterator<T>& u)	:_it(u.base()) {}
			~reverse_iterator() {}

			reverse_iterator &operator=(const reverse_iterator& u) {
				if (this != &u)
					_it = u.base();
				return *this;
			}

			iterator_type base() const{
				return _it;
			}

			reference operator*() const			{
				iterator_type temp = _it;
				return *(--temp);
			}

			pointer operator->() const{
				return &(operator*());
			}

			reverse_iterator &operator++() {
				--_it;
				return *this;
			}

			reverse_iterator operator++(int) {
				reverse_iterator temp = *this;
				--_it;
				return temp;
			}

			reverse_iterator operator+(difference_type n) const {
				return reverse_iterator(_it - n);
			}

			reverse_iterator &operator+=(difference_type n) {
				_it -= n;
				return *this;
			}

			reverse_iterator &operator--() {
				++_it;
				return *this;
			}

			reverse_iterator operator--(int) {
				reverse_iterator temp = *this;
				--(*this);
				return temp;
			}

			reverse_iterator operator-(difference_type n) const {
				return reverse_iterator(_it + n);
			}

			reverse_iterator &operator-=(difference_type n) {
				_it += n;
				return *this;
			}

			reference operator[](difference_type n) const {
				return  base()[-n - 1];
			}
	};
	
	// Non member function
	template <class Iter1, class Iter2>
	bool operator==(const reverse_iterator<Iter1> &x, const reverse_iterator<Iter2> &y)		{	return x.base() == y.base();	}

	template <class Iter1, class Iter2>
	bool operator!=(const reverse_iterator<Iter1> &x, const reverse_iterator<Iter2> &y)		{	return x.base() != y.base();	}

	template <class Iter1, class Iter2>
	bool operator<(const reverse_iterator<Iter1> &x, const reverse_iterator<Iter2> &y)		{	return x.base() > y.base();		}

	template <class Iter1, class Iter2>
	bool operator<=(const reverse_iterator<Iter1> &x, const reverse_iterator<Iter2> &y)		{	return x.base() >= y.base();	}

	template <class Iter1, class Iter2>
	bool operator>(const reverse_iterator<Iter1> &x, const reverse_iterator<Iter2> &y)		{	return x.base() < y.base();		}

	template <class Iter1, class Iter2>
	bool operator>=(const reverse_iterator<Iter1> &x, const reverse_iterator<Iter2> &y)		{	return x.base() <= y.base();	}


	template <class Iterator>
	reverse_iterator<Iterator>
	operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator> &x) { return reverse_iterator<Iterator>(x.base() - n);	}

	template <class Iter1, class Iter2>
	typename reverse_iterator<Iter1>::difference_type
	operator-(const reverse_iterator<Iter1> &x, const reverse_iterator<Iter2> &y)			{	return y.base() - x.base();		}
};

#endif
