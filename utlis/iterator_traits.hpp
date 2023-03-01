#ifndef ITERATOR_TRAITS_HPP
#define ITERATOR_TRAITS_HPP

#include <cstddef>	// For std::ptrdiff_t
#include <iterator> 

namespace ft
{
	// traits class for iterators
	// defines the properties of iterators
	// typedef->defines a new type (like a shorthand)
	// typename->lets the compiler know the name provided is a type.
	template<class Iterator>
	struct iterator_traits
	{
		typedef typename Iterator::difference_type 		difference_type;
		typedef typename Iterator::value_type 			value_type;
		typedef typename Iterator::pointer 				pointer;
		typedef typename Iterator::reference 			reference;
		typedef typename Iterator::iterator_category	iterator_category;
	};

	// Iterator traits specialized for pointers and const
	template<class T>
	struct iterator_traits<T*>
	{
		typedef std::ptrdiff_t						difference_type;
		typedef T 									value_type;
		typedef T* 									pointer;
		typedef T& 									reference;
		typedef std::random_access_iterator_tag		iterator_category;
	};
	template <class T>
	struct iterator_traits<const T*>
	{
		typedef std::ptrdiff_t							difference_type;
		typedef const T									value_type;
		typedef const T*								pointer;
		typedef const T&								reference;
		typedef std::random_access_iterator_tag			iterator_category;
	};

	// serves as a base type for all iterators
	// (Note: value type shld not be const even if obj is of type const)
	template<class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&>
	struct iterator
	{
		typedef Category  		iterator_category;
		typedef T         		value_type;
		typedef Distance  		difference_type;
		typedef Pointer  	 	pointer;
		typedef Reference 		reference;
	};

	/*******************	ITERATOR_TAGS	********************
	* method for accessing information that is associated with iterators or
	* empty types used to identify the category of an iterator.
	************************************************************/

	struct input_iterator_tag  {};
	struct output_iterator_tag {};
	struct forward_iterator_tag       : public input_iterator_tag         {};
	struct bidirectional_iterator_tag : public forward_iterator_tag       {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};

	 template <class T>
  struct bidirectional_iterator : iterator<std::bidirectional_iterator_tag, T>
  {
      typedef typename iterator<std::bidirectional_iterator_tag, T>::iterator_category     iterator_category;
      typedef typename iterator<std::bidirectional_iterator_tag, T>::value_type            value_type;
      typedef typename iterator<std::bidirectional_iterator_tag, T>::difference_type       difference_type;
      typedef typename iterator<std::bidirectional_iterator_tag, T>::pointer               pointer;
      typedef typename iterator<std::bidirectional_iterator_tag, T>::reference             reference;
      
      private:
        pointer m_ptr;
  };
};

#endif