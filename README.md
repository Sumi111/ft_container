# Ft_Containers

*Implementing the following containers and the necessary <container>.hpp files with a Makefile:*
* vector
* map
* stack (It will use your vector class as default underlying container. But it must still be compatible with other containers, the STL ones included.)

*Also have to implement:*
* std::iterator_traits
* std::reverse_iterator
* std::enable_if (Yes, it is C++11 but you will be able to implement it in a C++98 manner. This is asked so you can discover SFINAE.)
* std::is_integral
* std::equal and/or std::lexicographical_compare
* std::pair
* std::make_pair

## STACK
Refer stack's source code to know the member_types and member functions of this container.

**Follow this link :** https://cplusplus.com/reference/stack/stack/ to identify which member functions apply to specific versions of the C++ language standard(since we are sticking to C++98).

Our stack container will use our vector class as default underlying container(*initially I used the **std::vector**, so its easier to test this container alone*). But keep in mind it should also be compatible with the other STL containers as well. 

  
 ## VECTOR
 Similar to how we started with stack, refer vector's source code or https://cplusplus.com/reference/vector/vector/ to start.
 
 Some of the topics to read:
 *  iterators : https://www.geeksforgeeks.org/iterators-c-stl/
 *  allocators: https://www.geeksforgeeks.org/stdallocator-in-cpp-with-examples/
 *  enable_if : https://cplusplus.com/reference/type_traits/enable_if/
 *  SFINAE    : https://www.geeksforgeeks.org/substitution-failure-is-not-an-error-sfinae-in-cpp/
 
