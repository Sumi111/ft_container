#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp" 

namespace ft	//userdefined namespace
{

	template <class T, class Container = ft::vector<T> >
	class stack
	{
		public:
			typedef Container                                container_type;
			typedef typename container_type::value_type      value_type;
			typedef typename container_type::size_type       size_type;

		protected:
				container_type c;	//member objects->underlying container

		public:
			explicit stack (const container_type& c1 = container_type()) : c(c1) {};

			/********* MEMBER FUNCTIONS *********/
			// Element access
			const value_type& top() const	{	return c.back();	}
			value_type& top()				{	return c.back();	}

			// Capacity
			bool empty() const				{	return c.empty();	}
			size_type size() const			{	return c.size();	}

			// Modifiers
			void push(const value_type& x)	{	c.push_back(x);		}
			void pop()						{	c.pop_back();		}

			// Relational operators- Non member function
			friend bool operator==(const ft::stack<T, Container> &x, const ft::stack<T, Container> &y) 
			{
				return x.c == y.c;
			}
			friend bool operator<(const ft::stack<T, Container> &x, const ft::stack<T, Container> &y) 
			{
				return x.c < y.c;
			}
	};
	template <class T, class Container>
	bool operator!=(const ft::stack<T, Container> &x, const ft::stack<T, Container> &y)	{	return !(x == y);	}

	template <class T, class Container>
	bool operator>(const ft::stack<T, Container> &x, const ft::stack<T, Container> &y)	{	return (y < x);		}
	
	template <class T, class Container>
	bool operator>=(const ft::stack<T, Container>& x, const ft::stack<T, Container>& y)	{	return !(x < y);	}

	template <class T, class Container>
	bool operator<=(const ft::stack<T, Container>& x, const ft::stack<T, Container>& y)	{	return !(x > y);	}
};

#endif
