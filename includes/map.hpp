#ifndef MAP_HPP
#define MAP_HPP

#include <functional>
#include <memory>
#include <vector>
#include <iostream> 
#include "../utlis/pair.hpp"
#include "../utlis/avl.hpp"
#include "../utlis/equal.hpp"
#include "../utlis/type_traits.hpp"


namespace ft
{

template <class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<pair<const Key, T> > >
class map
{
public:
    typedef Key                                      key_type;
    typedef T                                        mapped_type;
    typedef ft::pair<const key_type, mapped_type>    value_type;
    typedef Compare                                  key_compare;
    typedef Allocator                                allocator_type;
    typedef typename allocator_type::reference       reference;
    typedef typename allocator_type::const_reference const_reference;
    typedef typename allocator_type::pointer         pointer;
    typedef typename allocator_type::const_pointer   const_pointer;
    typedef std::ptrdiff_t                           difference_type;
    typedef size_t                                   size_type;
    typedef ft::AVL<value_type, Compare, Allocator>  tree;
    typedef typename tree::iterator             	 iterator;
    typedef typename tree::const_iterator       	 const_iterator;
    typedef typename tree::reverse_iterator       	 reverse_iterator;
    typedef typename tree::const_reverse_iterator	 const_reverse_iterator;

    class value_compare: public std::binary_function<value_type, value_type, bool>
    {
        friend class map;
        protected:
            Compare comp;
            value_compare(Compare c) : comp(c) {};
        public:
            typedef bool result_type;
            typedef value_type first_argument_type;
            typedef value_type second_argument_type;
            bool operator() (const value_type& x, const value_type& y) const
            {
            	return comp(x.first, y.first);
            }
    };

	private :
            tree            _avl;
            allocator_type	_alloc;
            key_compare     _comp;

	public :
	/*****************	CONSTRUCTORS	******************
	 * empty
	 * range
	 * copy
	 * destructor
	******************************************************/
	explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()): _alloc(alloc), _comp(comp)
	{}
    
	template <class InputIterator>
	map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()): _alloc(alloc), _comp(comp)
	{
		this->insert(first, last);
	}

	map(const map& x): _alloc(x._alloc), _comp(x._comp) {
		this->insert(x.begin(), x.end());
	}

	map& operator=(const map& x)
	{
		clear();
		if (this != &x)
		{
			_alloc	= x._alloc;
			_comp	= x._comp;
		}
		this->insert(x.begin(), x.end());
		return (*this);
	}

	~map() {
		_avl.clear();
	}

	/*****************	ITERATOR	*********************
	 * begin		Returns the iterator referring to 1st element
	 * end			returns iterator referring to past-the-end element
	 * rbegin		Returns a reverse iterator pointing to the last element
	 * rend			Returns a reverse iterator pointing to the element right before the first element
	******************************************************/

    iterator begin()				{	return (_avl.begin());	}
    const_iterator begin() const	{	return (_avl.begin());	}
	
	iterator end()					{	return (_avl.end());	}
    const_iterator end()   const 	{	return(_avl.end());		}

    reverse_iterator rbegin() 				{	return(_avl.rbegin());		}
    const_reverse_iterator rbegin() const	{	return (_avl.rbegin());		}
    
	reverse_iterator rend() 				{	return (_avl.rend());		}
    const_reverse_iterator rend() const		{	return (_avl.rend());		}

    /******************	CAPACITY	********************
	 * empty
	 * size
	 * max_size
	******************************************************/

    bool empty() const			{	return (_avl.empty());		}
    size_type size() const		{	return (_avl.size());		}
    size_type max_size() const	{	return (_avl.max_size());	}

    /******************	ELEMENT ACCESS	********************
	 * operator[]		If k matches the key of an element in the container,
	 					the function returns a reference to its mapped value.

						else  the function inserts a new element with that key
						and returns a reference to its mapped value
	******************************************************/
    mapped_type& operator[](const key_type& x)
	{
		if (_avl.find(x) == 0)
			return  ((insert(ft::make_pair(x,mapped_type())).first)->second);
		return (_avl.find(x)->_data->second);
	}

    /******************	MODIFIER	********************
	 * insert
	 * erase
	 * swap
	 * clear
	******************************************************/


    /******************	insert	********************
	 * single element		keys are unique so insertion checks if it is not there->insert else ->point to existing one
	 * with hint			position is provided for optimization->does not force to insert there
	 * range				insert range using iterartor
	******************************************************/

	ft::pair<iterator,bool> insert(const value_type& x)
	{
        bool sec = _avl.insert(x);
        iterator first = iterator(_avl.find(x.first), &_avl);
        ft::pair<iterator, bool> ret = ft::make_pair(first, sec);
        return (ret);
    }

	iterator insert(iterator position, const value_type& x)
	{
		(void)position;
		_avl.insert(x);
		return (iterator(_avl.find(x.first), &_avl));
	}

	template <class InputIterator>
	void insert (InputIterator first, InputIterator last)
	{
		for (; first != last; first++)
			_avl.insert(*first);
		return ;
	}

   	void erase(iterator position)
	{
		key_type k = position->first;
		_avl.remove(k);
		return ;
	}

	size_type erase(const key_type& k)
	{
		return (_avl.remove(k));
	}

	void erase(iterator first, iterator last)
	{
		std::vector<key_type> keys;
		while (first != last)
		{
			keys.push_back(first->first);
			first++;
		}
		for (size_t i = 0; i < keys.size(); i++)
				_avl.remove(keys[i]);
		for (size_t i = 0; i < keys.size(); i++)
				erase(keys[i]);
		keys.clear();
		return ;
	}

	void swap (map& x)
	{
		tree temp;

		temp = x._avl;
		x._avl = _avl;
		_avl = temp;
		return ;
	}

    void clear()
	{
		_avl.clear();
		return ;
	}

	/******************	OBSERVERS	********************
	 * key_comp			Returns a copy of the comparison object used by the container to compare keys
	 * value_comp		used to compare two elements to get whether the key of the first one goes before the second
	******************************************************/

    key_compare key_comp() const		{	return (_comp);					}

    value_compare value_comp() const	{	return (value_compare(_comp));	}

	/******************	ALLOCATOR	********************
	 * get_allocator
	******************************************************/
    allocator_type get_allocator() const
	{
		return (_avl.get_allocator());
	}

   	/******************	MAP OPERATIONS	********************
	 * find
	 * count
	 * lower_bound		Returns an iterator pointing to the first element in the container whose key is not considered to go before k
	 * upper_bound		Returns an iterator pointing to the first element in the container whose key is considered to go after k
	 * equal_range		Returns the bounds of a range that includes all the elements in the container which have a key equivalent to k
	******************************************************/
	
	iterator find(const key_type& x)
    {
        return (iterator(_avl.find(x), &_avl));
    }

    const_iterator find(const key_type& x) const
    {
        return (iterator(_avl.find(x), &_avl));
    }

    size_type count(const key_type& x) const
    {
        return (_avl.contains(x));
    }

    iterator lower_bound(const key_type& x)
    {
        return (_avl.bound(x, 2));
    }

    const_iterator lower_bound(const key_type& x) const
    {
        return (_avl.bound(x, 2));
    }

    iterator upper_bound(const key_type& x)
    {
        return (_avl.bound(x, 1));
    }
    const_iterator upper_bound(const key_type& x) const
    {
        return (_avl.bound(x, 1));
    }
    
    ft::pair<iterator,iterator> equal_range(const key_type& x)
    {
        ft::pair<iterator,iterator> ret =  ft::make_pair(lower_bound(x), upper_bound(x));
        return (ret);
    }
    ft::pair<const_iterator,const_iterator> equal_range(const key_type& x) const
    {
        ft::pair<const_iterator,const_iterator> ret =  ft::make_pair(lower_bound(x), upper_bound(x));
        return (ret);
    }       
};

	template <class Key, class T, class Compare, class Allocator>
    bool operator== ( const map<Key,T,Compare,Allocator>& lhs, const map<Key,T,Compare,Allocator>& rhs )
    {
        if (lhs.size() != rhs.size())
            return (lhs.size() == rhs.size());
        return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
    }

    template <class Key, class T, class Compare, class Allocator>
    bool operator!= ( const map<Key,T,Compare,Allocator>& lhs, const map<Key,T,Compare,Allocator>& rhs )
    {
        return (!(lhs == rhs));
    }

    template <class Key, class T, class Compare, class Allocator>
    bool operator<  ( const map<Key,T,Compare,Allocator>& lhs, const map<Key,T,Compare,Allocator>& rhs )
    {
        return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
    }
    template <class Key, class T, class Compare, class Allocator>
    bool operator> ( const map<Key,T,Compare,Allocator>& lhs, const map<Key,T,Compare,Allocator>& rhs )
    {
        return (ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()));
    }
    template <class Key, class T, class Compare, class Allocator>
    bool operator>=  ( const map<Key,T,Compare,Allocator>& lhs,  const map<Key,T,Compare,Allocator>& rhs )
    {
        if (lhs > rhs || lhs == rhs)
            return (true);
        return (false);
    }
    template <class Key, class T, class Compare, class Allocator>
    bool operator<= ( const map<Key,T,Compare,Allocator>& lhs,  const map<Key,T,Compare,Allocator>& rhs )
    {
        if (lhs  < rhs || lhs == rhs)
            return (true);
        return (false);
    }
    template <class Key, class T, class Compare, class Allocator>
    void swap (map<Key,T,Compare,Allocator>& x, map<Key,T,Compare,Allocator>& y)
    {
        x.swap(y);
    }
};

#endif