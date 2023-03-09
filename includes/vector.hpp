#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <algorithm>
#include <memory>
#include <stdexcept>
#include <iterator> //std::distance
#include "../utlis/vec_iterator.hpp"
#include "../utlis/equal.hpp"
#include "../utlis/type_traits.hpp"
#include "../utlis/reverse_iterator.hpp"
#include "../utlis/iterator_validity.hpp"
#include <vector>

namespace ft
{

	template <class T, class Allocator = std::allocator<T> >
	class vector
	{
	public:
		typedef T                                        value_type;
		typedef Allocator                                allocator_type;
		typedef typename allocator_type::reference       reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::size_type       size_type;
		typedef typename allocator_type::difference_type difference_type;
		typedef typename allocator_type::pointer         pointer;
		typedef typename allocator_type::const_pointer   const_pointer;
		typedef ft::vec_iterator<T>						 iterator;
		typedef ft::vec_iterator<const T>				 const_iterator;
		typedef ft::reverse_iterator<iterator>			 reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>     const_reverse_iterator;

	protected:	
		value_type*		_arr;
		allocator_type	_alloc;
		size_type		_size;		// No. of elenents 
		size_type		_capacity;	// size of allocated storage

	public:
		/*****************	CONSTRUCTORS	******************
		 * default
		 * fill
		 * range
		 * copy
		 * destructor
		******************************************************/
		explicit vector(const allocator_type& alloc = allocator_type())	{
			_arr = 0;
			_alloc = alloc;
			_size = 0;
			_capacity = 0;
		}

		explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()): _arr(0), _alloc(alloc), _size(n), _capacity(n)
		{
			_arr = _alloc.allocate(_capacity);
			for (size_type i = 0; i < _size; i++)
				_alloc.construct(_arr + i, val);
		}
		
		template <class InputIterator>
		vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0 ) : _arr(0),
			_alloc(alloc),
			_size(0),
			_capacity(0) 
		{
			ft::check_range(first, last);
			size_type range = 0;
			for (InputIterator temp = first; temp != last; temp++) 
				range++;
			_arr = _alloc.allocate(range + 1);
			for (size_type i = 0; i < range; i++)
			{
				_size++;
				_alloc.construct(_arr + i, *first);
				first++;
			}
			_capacity = range;
		}

		vector (const vector& x): _arr(0), _alloc(x._alloc), _size(0), _capacity(0)
		{
			*this = x;
		};
		
		vector&	operator=(const vector& x) 
		{
			if (!this->empty())
				this->~vector();
			if (this != &x)
			{
				_arr = _alloc.allocate(x._capacity);
				_size = x._size;
				_capacity = x._capacity;
				for (size_type i = 0; i < _size; i++) {
					_alloc.construct(_arr + i, *(x._arr + i));
				}
			}
			return *this;
		};

		~vector()
		{
			clear();
			_alloc.deallocate(_arr, _capacity);
			_capacity = 0;
			_size = 0;
		}

		/************************		ITERATORS	**************************
		* begin		Returns an iterator pointing to the first element
		* end		Returns an iterator referring to the end element
		* rbegin	Return reverse iterator to reverse beginning(last element)
		* rend		Return reverse iterator to reverse end(first element)
		***********************************************************************/
		iterator begin()				{	return iterator(_arr);				}
		const_iterator begin() const	{	return const_iterator(_arr);		}

		iterator end()					{	return iterator(_arr + _size);		}
		const_iterator end() const		{	return const_iterator(_arr + _size);}

		reverse_iterator rbegin()				{	return reverse_iterator(_arr + _size);			}
		const_reverse_iterator rbegin() const	{	return const_reverse_iterator(_arr + _size);	}

		reverse_iterator rend()					{	return reverse_iterator(_arr); 					}
		const_reverse_iterator rend() const		{	return const_reverse_iterator(_arr);			}

		/********************		CAPACITY	********************
		* Size			returns size
		* Max_size		returns maximun size vector can hold
		* Capacity		returns size of allocated storage capacity
		* Resize		changes size
		* empty			tests whether vector is empty
		* reserve		requests a change in capacity
		************************************************************/
		size_type size() const		{	return _size;					}

		size_type max_size() const	{	return (_alloc.max_size());		}
		
		size_type capacity() const	{	return _capacity;				}

		void resize(size_type n, value_type val = value_type())
		{
			if (n > this->max_size()) 
				throw std::length_error("ft::vector::resize");
			else if (n > _capacity)
				this->reserve(std::max(_capacity * 2, n));
			for (size_type i = _size; i < n; i++)
				_alloc.construct(_arr + i, val);
			for (size_type i = _size; i > n; i--)
				_alloc.destroy(_arr + i - 1);
			_size = n;
		}


		bool empty() const{
			if (_size == 0)
				return (true);
			return (false);
		}

		void reserve(size_type n){
			if (n > max_size())
					throw std::length_error("exceeds maximum supported size");
			if (n > _capacity)
			{
				allocator_type	t_alloc;
				pointer 		temp 	= t_alloc.allocate(n);
				size_type		t_size	= _size;

				for (size_type i = 0; i < _size; i++)
					t_alloc.construct(temp + i, *(_arr + i));
				this->~vector();
				
				_arr	  = temp;
				_alloc	  = t_alloc;
				_size	  = t_size;
				_capacity = n;
			}
		}
		

		/******************		ELEMENT ACCESS	******************
		* operator[]		access element	
		* at				access element within bounds
		* front				access the first element
		* back				access the last element
		**********************************************************/
		reference operator[](size_type n)				{	return (_arr[n]);	}
		const_reference operator[] (size_type n) const	{	return (_arr[n]);	}

		reference at(size_type n){
			if (_size <= n)
					throw std::out_of_range("vector");
			return(_arr[n]);
		}

		const_reference at(size_type n) const{
			if (_size <= n)
					throw std::out_of_range("vector");
			return(_arr[n]);
		}

		reference front()				{	return (_arr[0]);	}
		const_reference front() const	{	return (_arr[0]);	}

		reference back()				{	return (_arr[_size - 1]);	}
		const_reference back() const	{	return (_arr[_size - 1]);	}

		T* data() 				{	return _arr;	}
		const T* data() const 	{	return _arr;	}

		/******************		MODIFIERS	******************
		* assign		Assigns new contents
		* push_back		adds element at the end
		* pop_back		deletes the last element
		* insert		insert elements	
		* erase			erase elements
		* swap			swaps content	
		* clear			clears content
		******************************************************/
		void push_back(const value_type &value) 
		{
			if (!_capacity)
				this->reserve(1);
			else if (_size == _capacity)
				this->reserve(_capacity * 2);
		
			_alloc.construct(_arr + _size, value);
			_size++;
		}

		void pop_back()	
		{	
			_alloc.destroy(&_arr[_size - 1]);
			_size--;
		}

		iterator erase (iterator position)
		{
			for (iterator i = position; i != this->end() - 1; i++)
				*i = *(i + 1);
			_alloc.destroy(_arr + _size - 1);
			_size--;
			return position;
		}

		iterator erase(iterator first, iterator last)
		{
			size_type diff1 = first - this->begin();
			size_type diff2 = last - this->begin();
			size_type d = last - first;
			size_type j = 0;

			for (size_type i = diff1; diff2 + j < _size; i++)
					_arr[i] = _arr[diff2 + j++];

			for (size_type i = 0; i < d; i++)
				_alloc.destroy(_arr + --_size);
			return first;
		}

		void clear()
		{
			for (size_type i = 0; i < _size; i++)
				_alloc.destroy(_arr + i);
			_size = 0;
		}

		template <class InputIterator>
		void assign(InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0)
		{
			size_type n = std::distance(first, last);
			if (n > _capacity)
				reserve(n);
			for (size_type i = 0; i < n; i++)
				_alloc.construct(_arr + i, *first++);
			_size = n;
		}

		void assign (size_type n, const value_type& val)
		{
			if (n > _capacity)
				reserve (n);
			for (size_type i = 0; i < n; i++)	
				_alloc.construct(_arr + i, val);
			_size = n;
		}

		iterator insert(iterator position, const value_type &val) 
		{
			difference_type d = position - this->begin();
			if (d >= 0) 
			{
				if (!_capacity)
					reserve(1);
				else if (_size == _capacity)
					reserve(_capacity * 2);

				if (static_cast<size_type>(d) > _size)
					_alloc.construct(_arr + _size, *(_arr + _size - 1));
				else 
				{
					for (size_type i = _size; i > static_cast<size_type>(d); i--) 
					{
						_alloc.construct(_arr + i, *(_arr + i - 1));
						_alloc.destroy(_arr + i - 1);
					}
					_alloc.construct(_arr + size_type(d), val);
				}
			}
			_size++;
			return position;
		}

		void insert(iterator position, size_type n, const value_type &val) 
		{
			difference_type d	= position - this->begin();
			size_type new_size 	= _size + n;

			if (_size + n >= _capacity)
				this->reserve(std::max(_capacity * 2, _size + n));

			allocator_type t_alloc;
			pointer		   temp = t_alloc.allocate(_size);
			for (size_type i = 0; i < _size; i++) 
				t_alloc.construct(temp + i, *(_arr + i));

			for (size_type i = static_cast<size_type>(d) + n; i < new_size; i++)
			{
				if (i < _size)
					_alloc.destroy(_arr + i);
				_alloc.construct(_arr + i, *(temp + i - n));
			}
			for (size_type i = d; i < static_cast<size_type>(d) + n; i++)
			{
				if (i < _size)
					_alloc.destroy(_arr + i);
				_alloc.construct(_arr + i, val);
			}
			for (size_type i = 0; i < _size; i++)
				t_alloc.destroy(temp + i);
			t_alloc.deallocate(temp, _size);
			_size += n;
		}

		template <class InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0)
		{
			difference_type d 	  = position - this->begin();
			difference_type range = d;
			size_type 		n	  = 0;

			for (InputIterator temp = first; temp != last; temp++) 
			{
				range++;
				n++;
			}
			if (_size + n >= _capacity)
				this->reserve(std::max(_capacity * 2, _size + n));

			allocator_type t_alloc;
			pointer 	   temp = t_alloc.allocate(_size);

			for (size_type i = 0; i < _size; i++)
				t_alloc.construct(temp + i, *(_arr + i));

			for (size_type i = static_cast<size_type>(range); i < _size + n; i++)
			{
				if (i < _size)
					_alloc.destroy(_arr + i);
				_alloc.construct(_arr + i, *(temp + i + static_cast<size_type>(d - range)));
			}

			for (size_type i = static_cast<size_type>(d); i < static_cast<size_type>(range); i++)
			{
				if (i < _size)
					_alloc.destroy(_arr + i);
				_alloc.construct(_arr + i, *first++);
			}

			for (size_type i = 0; i < _size; i++)
				t_alloc.destroy(temp + i);
			t_alloc.deallocate(temp, _size);
			_size += n;
		}
		
		void swap(vector& x) {
			value_type*t = x._arr;
			allocator_type temp = x._alloc;
			size_type t_s = x._size;
			size_type t_c = x._capacity;

			x._arr = _arr;
			x._alloc = _alloc;
			x._size = _size;
			x._capacity = _capacity;

			_arr = t;
			_alloc = temp;
			_size = t_s;
			_capacity = t_c;
		} 

		allocator_type get_allocator() const {
			return _alloc;
		}
	};

	/**************		NON MEMBER FUNC.	***************
	* swap	
	* relational operators
	*******************************************************/
	template <class T, class Alloc>
	void swap (vector<T,Alloc>& x, vector<T,Alloc>& y){
		x.swap(y);
	};

	template <class T, class Alloc>
	bool operator==(const vector<T,Alloc>& l, const vector<T,Alloc>& r){
		if (l.size() != r.size())
			return false;
		return ft::equal(l.begin(), l.end(), r.begin());
	};

	template <class T, class Alloc>
	bool operator!=(const vector<T,Alloc>& l, const vector<T,Alloc>& r){
		return !(l == r);
	};

	template <class T, class Alloc>
	bool operator<(const vector<T,Alloc>& l, const vector<T,Alloc>& r){
		return ft::lexicographical_compare(l.begin(), l.end(), r.begin(), r.end());
	};

	template <class T, class Alloc>
	bool operator>(const vector<T,Alloc>& l, const vector<T,Alloc>& r){
		return (r < l);
	};

	template <class T, class Alloc>
	bool operator<=(const vector<T,Alloc>& l, const vector<T,Alloc>& r){
		return !(l > r);
	};

	template <class T, class Alloc>
	bool operator>=(const vector<T,Alloc>& l, const vector<T,Alloc>& r){
		return !(l < r);
	};
};

#endif
