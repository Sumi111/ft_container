#ifndef MAP_ITERATOR_HPP
#define MAP_ITERATOR_HPP

#include <iterator>
#include <functional>

#include "node.hpp"
#include "iterator_traits.hpp"
#include "type_traits.hpp"



namespace ft 
{
    template <class T, class Node, class Compare, class tree>
    class map_iterator : public ft::iterator<std::bidirectional_iterator_tag, T>
    {
        public :
            typedef ft::iterator<std::bidirectional_iterator_tag, T>   traits_type;
            typedef typename traits_type::value_type                    value_type;
            typedef typename traits_type::pointer                       pointer;
            typedef typename traits_type::reference                     reference;
            typedef typename traits_type::difference_type               difference_type;
            typedef typename traits_type::iterator_category             iterator_category;

        private :
            Node*             _ptr;
            const tree       *_tree;
            Compare           _cmp;

        public :
            map_iterator() : _ptr(), _tree(), _cmp() {}
            map_iterator(Node* node, const tree *t) : _ptr(node), _tree(t) {}
            map_iterator(const map_iterator<T, Node, Compare, tree> &x)
            {
                *this = x;
            }
            
            virtual ~map_iterator() {}

            map_iterator &operator=(map_iterator const& x)
            {
                _ptr = x._ptr;
                _tree = x._tree;
                _cmp = x._cmp;
                return (*this);
            }

            Node* base() const
            {
                return (_ptr);
            }

            T* operator->() const   {   return (_ptr->_data);    }
            T& operator*() const    {   return (*_ptr->_data);   }

            operator map_iterator<const T, const Node, Compare, tree>() const
            {
                return map_iterator<const T, const Node, Compare, tree>(_ptr, _tree);
            }

            
            map_iterator& operator++()
            {
				// std::cout << "error may be here \n";
                Node* p;
                if (_ptr == 0)
                    return (*this = map_iterator(_tree->findmin(_tree->getRoot()), _tree));
                if (_ptr == _tree->findmax(_tree->getRoot()))
                    return (*this = map_iterator(0, _tree));
                if (_ptr->right != 0)
                {
                    _ptr = _ptr->right;
                    while (_ptr->left != 0)
                        _ptr= _ptr->left;
                }
                else
                {
                    p = _ptr->parent;
                    while (p != 0 && _ptr == p->right)
                    {
                        _ptr = p;
                        p = p->parent;
                    }
                    _ptr = p;
                }
                return (*this);
            }
            map_iterator operator++(int)
            {
                map_iterator tmp(*this);
                ++(*this);
                return (tmp);
            }
            map_iterator& operator--()
            {
                Node* p;
                if (_ptr == 0)
                    _ptr = _tree->findmax(_tree->getRoot());
                else
                {
                   if (_ptr->left != 0)
                    {
                        _ptr = _ptr->left;
                        while (_ptr->right != 0)
                            _ptr= _ptr->right;
                    }
                    else
                    {
                        p = _ptr->parent;
                        while (p != 0 && _ptr == p->left)
                        {
                            _ptr = p;
                            p = p->parent;
                        }
                        _ptr = p;
                    }
                }
                return (*this);
            }
            map_iterator operator--(int)
            {
                map_iterator tmp(*this);
                operator--();
                return (tmp);
            }
            friend bool	operator==(map_iterator const& lhs, map_iterator const& rhs) { return (lhs._ptr == rhs._ptr); }
            friend bool	operator!=(map_iterator const& lhs, map_iterator const& rhs) { return (lhs._ptr != rhs._ptr); }
    };
};

#endif
