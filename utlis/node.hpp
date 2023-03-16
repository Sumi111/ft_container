#ifndef NODE_HPP
#define NODE_HPP

#include <functional>

namespace ft
{
    template <class T>
    class AVLNODE
    {
        public :
            int			bf;
            int         ht;
            T*          _data;
            AVLNODE<T>* parent;
            AVLNODE<T>*	left;
            AVLNODE<T>*	right;

            AVLNODE() : ht(0),_data(0), parent(0), left(0),  right(0) {}
            AVLNODE(T data) : ht(0), _data(data), parent(0), left(0), right(0) {}
            AVLNODE(const AVLNODE& x) : ht(x.ht), bf(x.bf), _data(x._data), parent(x.parent), left(x.left), right(x.right) {}
            ~AVLNODE() {}
            AVLNODE& operator=(const AVLNODE& x)
            {
                bf = x.bf;
                _data = x._data;
                parent = x.parent;
                left = x.left;
                right = x.right;
                ht = x.ht;
                return (*this);
            }
    };
    template<class T>
    bool  operator== (const AVLNODE<T>&lhs, const AVLNODE<T>&rhs)
    {
        if (lhs->_data == 0 && rhs->_data == 0)
            return true;
        return (lhs->_data == rhs._data);
    };
    template<class T>
    bool operator!=(const AVLNODE<T>&lhs, const AVLNODE<T>&rhs)
    {
        return (!(lhs == rhs));
    };
};

#endif