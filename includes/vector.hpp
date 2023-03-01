#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <algorithm>
#include <memory>
#include <stdexcept>
#include "../utlis/iterator.hpp"
#include "../utlis/equal.hpp"
#include "../utlis/type_traits.hpp"
#include "../utlis/reverse_iterator.hpp"
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
		size_type		_size;		// No. of elenents 
		size_type		_capacity;	// size of allocated storage
		allocator_type	_alloc;

	public:
		/*****************	CONSTRUCTORS	******************
		 * default
		 * fill
		 * range
		 * copy
		 * destructor
		******************************************************/
		explicit vector(const allocator_type& alloc = allocator_type())	{
			_size = 0;
			_capacity = 0;
			_alloc = alloc;
			_arr = 0;
		}

		explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()){
			_size = n;
			_capacity = n;
			_alloc = alloc;
			_arr = _alloc.allocate(n);
			for (unsigned long i = 0; i < _size; i++)
				_arr[i] = val;

		}
		
		template <class InputIterator>
		vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0 ){
			_size = 0;
			_capacity = 0;
			_alloc = alloc;
			_arr = NULL;
			insert(begin(), first, last);
		}

		vector (const vector& x){
			_alloc = x._alloc;
			_capacity = x._capacity;
			_arr = _alloc.allocate(x._capacity);
			_size = x._size;
			for (size_type i = 0; i < _size; i++ )
				_arr[i] = x._arr[i];
		};
		
		vector&	operator=(const vector& x) {
			if (this != &x)
				assign(x.begin(), x.end());
				return *this;
		};

		~vector(){
			_alloc.deallocate(_arr, _capacity);
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
		* Resize		changes size
		* Capacity		returns size of allocated storage capacity
		* empty			tests whether vector is empty
		* reserve		requests a change in capacity
		************************************************************/
		size_type size() const{
			return _size;
		}

		size_type max_size() const{
			return (_alloc.max_size());
		}
		
		void resize(size_type n, value_type val = value_type())
		{
			if (n < _size)
				_size = n;
			else if (n > _size)
			{
				pointer temp = _alloc.allocate(n);
				for (size_type i = 0; i < _size; i++)
					temp[i] = _arr[i];
				for (size_type i = _size; i < n; i++)
					temp[i] = val;
				_alloc.deallocate(_arr,n);
				_arr = temp;
				_size = n;
				_capacity *= 2;
			}
		}

		size_type capacity() const{
			return _capacity;
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
				pointer temp = _alloc.allocate(n);
				for (size_type i = 0; i < _size; i++)
				{
					temp[i] = _arr[i];
					_alloc.destroy(&_arr[i]);
				}
				_alloc.deallocate(_arr, _size);
				_arr = temp;
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

		/******************		MODIFIERS	******************
		* assign		Assigns new contents
		* push_back		adds element at the end
		* pop_back		deletes the last element
		* insert		insert elements	
		* erase			erase elements
		* swap			swaps content	
		* clear			clears content
		******************************************************/
		void push_back(T data){
			if (_size == _capacity)
			{
				pointer temp = _alloc.allocate(2 * _capacity + 1);
				_capacity = (_capacity * 2) + 1;
				for (size_type i = 0; i < _size; i++)
					temp[i] = _arr[i];
				_alloc.deallocate(_arr, _size);
				_arr = temp;
			}
			_arr[_size] = data;
			_size++;
		}

		void pop_back()	{	_size--;	}

		iterator erase (iterator position){
			size_type x = position - begin();
			_size--;
			pointer temp = _alloc.allocate(_capacity);
			for(size_type i = 0; i < x; i++)
				temp[i] = _arr[i];
			for(size_type i = x; i < _size; i++)
				temp[i] = _arr[i + 1];
			_alloc.deallocate(_arr, _size + 1);
			_arr = temp;
			return (&_arr[x]);
		}

		iterator erase(iterator first, iterator last)
		{
			size_type diff1 = first - begin();
			size_type diff2 = last - begin();

			for (size_type i = diff1, j = 0; i < _size; i++, j++)
				_arr[i] = _arr[diff2 + j];
			for (size_type i = diff2; i < _size; i++)
				_alloc.destroy(_arr+i);
			_size = _size - (last - first);
			return first;
		}

		void clear(){
			erase(begin(), end());
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

		iterator insert (iterator position, const value_type& val){
			size_type i = position - begin();
			insert(position, 1, val);
			return (begin() + i);
		}

		void insert(iterator position, size_type n, const value_type& val)
		{
			size_type i = position - begin();
			if ((_size + n) > _capacity)
				reserve(std::max(_capacity * 2, _size + n));
			for (size_type j = n + _size - 1; j > i + n - 1; j--)
			{
				_alloc.construct(&_arr[j], _arr[j - n]);
				_alloc.destroy(&_arr[j - n]);
			}
			for (size_type k = i; k < i + n; k++)
			{
				_alloc.construct(&_arr[k], val);
				_size++;
			}
		}

		template <class InputIterator>
		void insert( iterator position, InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0)
		{
			size_type			i = position - begin();
			size_type			j = std::distance(first, last);

			if ((_size + j) > _capacity)
				reserve(std::max(_capacity * 2, _size + j));
			for (size_type k = j + _size - 1; k > i + j - 1; k -= 1)
			{
				_alloc.construct(&_arr[k], _arr[k - j]);
				_alloc.destroy(&_arr[k - j]);
			}
			for (size_type l = i; l < i + j; l++)
			{
				_alloc.construct(&_arr[l], *first);
				first++;
				_size++;
			}
		}
		
		void swap(vector& x) {
			allocator_type temp = x._alloc;
			size_type t_c = x._capacity;
			size_type t_s = x._size;
			value_type*t = x._arr;

			x._alloc = _alloc;
			x._capacity = _capacity;
			x._size = _size;
			x._arr = _arr;

			_alloc = temp;
			_capacity = t_c;
			_size = t_s;
			_arr = t;
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
