#ifndef AVL_HPP
#define AVL_HPP

#include <functional>
#include <memory>
#include "map_iterator.hpp"
#include "reverse_iterator.hpp"
#include "iterator_traits.hpp"
#include "pair.hpp"
#include "node.hpp"

namespace ft
{
    template <class T, class Compare = std::less<typename T::first_type>, class Allocator = std::allocator<T> > 
    class AVL
    {
        public:
            typedef T                                                               value_type;
            typedef typename value_type::first_type                                 key;
            typedef typename value_type::second_type                                value;
            typedef ft::AVLNODE<const T>                                            const_node;
			
            typedef Allocator                                                       base_alloc;
            typedef typename Allocator::template rebind<ft::AVLNODE<T> >::other     node_alloc;
           
            typedef ft::map_iterator<T, ft::AVLNODE<T>, Compare, AVL>               iterator;
            typedef ft::map_iterator<const T, const ft::AVLNODE<T>, Compare, AVL>   const_iterator;
            typedef ft::reverse_iterator<iterator>                                  reverse_iterator;
            typedef ft::reverse_iterator<const_iterator>                            const_reverse_iterator;
       
        private:
            ft::AVLNODE<T>* _node;
            node_alloc      n_alloc;
            base_alloc      b_alloc;
            int             _size;
            Compare         _comp;

        public : 
            AVL() : _node(0), _size(0) {}

            AVL(const AVL &x) : _node(0)
            {
                *this = assign(x);
            }

            ~AVL() {}

            AVL& assign(AVL const &x)
            {
                delete_all();
                n_alloc = x.n_alloc;
                b_alloc = x.b_alloc;
                _comp	= x._comp;
                for (const_iterator it = x.begin(); it != x.end(); it++)
                    insert(*it);
                _size	= x._size;
                return (*this);
            }

			void delete_node(ft::AVLNODE<T> *node)
            {
                b_alloc.destroy(node->_data);
                b_alloc.deallocate(node->_data, 1 * sizeof(T*));
                node->_data = NULL;
				// n_alloc.destroy(node);
                n_alloc.deallocate(node, 1 * sizeof(ft::AVLNODE<T> *));
                node = NULL;
            }

			ft::AVLNODE<T>* delete_tree(ft::AVLNODE<T>* x)
            {
                if (x->_data != 0)
                {
					if (x->left != 0)
						delete_tree(x->left);
					if (x->right != 0)
						delete_tree(x->right);
                    delete_node(x);
                }
                return 0;
            }

            void delete_all()
            {
				if (_node)
					_node = delete_tree(getRoot());
                _size = 0;
            }

            void clear()
            {
                delete_all();
                _size = 0;
            }

            int size() const        {   return (_size);                 }

            size_t max_size() const {   return (n_alloc.max_size());    }

            bool empty() const       
			{
                if (_size == 0)
                    return true;
                return false;
            }

            // end and begin
            iterator begin() 
            {
                ft::AVLNODE<T> *first = find(findMin(_node).first);
                return (iterator(first, this));
            }
            iterator end() 
            {
                return (iterator(NULL, this)); 
            }
            const_iterator begin() const 
            { 
                ft::AVLNODE<T> *first = find(findMin(_node).first);
                return (iterator(first, this));
            }
            const_iterator end() const 
            { 
                return (iterator(NULL, this)); 
            }

            // rend and rbegin
            reverse_iterator rbegin()   {   return reverse_iterator(end()); }
            reverse_iterator rend()     {   return (reverse_iterator(begin())); }
            const_reverse_iterator rbegin() const   {   return const_reverse_iterator(end());       }
            const_reverse_iterator rend() const     {   return (const_reverse_iterator(begin()));   }

            //find min and max
             ft::AVLNODE<T>* findmin(ft::AVLNODE<T>* x) 
            {
                while (x->left != 0)
                    x = x->left;
                return (x);
            }
            ft::AVLNODE<T>* findmin(ft::AVLNODE<T>* x) const
            {
                while (x->left != 0)
                    x = x->left;
                return (x);
            }

            ft::AVLNODE<T>* findmax(ft::AVLNODE<T>* x) 
            {
                while (x->right != 0)
                    x = x->right;
                return (x);
            }
            ft::AVLNODE<T>* findmax(ft::AVLNODE<T>* x) const
            {
                while (x->right != 0)
                    x = x->right;
                return (x);
            }

            ft::AVLNODE<T>* newNode(T x)
            {
                ft::AVLNODE<T>* node = n_alloc.allocate(1 * sizeof(ft::AVLNODE<T>*));
                node->_data = b_alloc.allocate(1 *  sizeof(T*));
                b_alloc.construct(node->_data, x);
				node->left = 0;
				node->right = 0;
                return (node);
            }

            int height()
            {
                int ht = 0;

                if (_node != 0)
                    ht = height(_node) - 1;
                return (ht);
            }

			bool contains(key k) const
			{
				return (contains(_node, k));
			}

			bool insert(T x)
			{
				if (!contains(_node, x.first))
				{
					_node = insert(_node, x);
					_node->parent = 0;
					_size++;
					return true;
				}
				return false;
			}

            bool remove(key x)
            {
                if (contains(_node, x))
                {
                    _node = remove(_node, x);
                    _size--;
                    return true;
                }
                return false;
            }

            ft::AVLNODE<T>* find(key x)
            {
                if (contains(_node, x))
                    return (find(_node, x));
                return 0;
            }

            ft::AVLNODE<T>* find(key x) const
            {
                if (contains(_node, x))
                    return (find(_node, x));
                return 0;
            }

            iterator bound(key k, int i)
            {
                ft::AVLNODE<T>* con = 0;
                if (i == 1)
                {
                    upper_bound(_node, k, &con);
                    if (!con)
                        return(iterator(0, this));
                    else
                        return iterator(con, this);
                }
                else
                {
                    lower_bound(_node, k, &con);
                    if (!con)
                        return (iterator(0, this));
                    else
                        return iterator(con, this);
                }
                return iterator(0, this);
            }
			 
            const_iterator bound(key k, int i) const
            {

                ft::AVLNODE<T>* con = 0;

                if (i == 1)
                {
                    upper_bound(_node, k, &con);
                    if (!con)
                        return(const_iterator(0, this));
                    else
                        return const_iterator(con, this);
                }
                else
                {
                    lower_bound(_node, k, &con);
                    if (!con)
                        return(const_iterator(0, this));
					else
                        return const_iterator(con, this);
                }
                return const_iterator(0, this);
            }
          
            node_alloc get_allocator() const    {   return (n_alloc);   }

            ft::AVLNODE<T>* getRoot(void) const {   return (_node);     }
       

        private:
            //  overwriting
            //  recursively call sub trees 
            bool contains(ft::AVLNODE<T>* node, key k) const
                {
                if (node == 0)
                    return false;
                bool c1 = _comp(node->_data->first, k);
                bool c2 = _comp(k, node->_data->first);
                if (!c1 && !c2)
                    return true;
                if (!c1)
                    return (contains(node->left, k));
                if (c1)
                    return (contains(node->right, k));
                return true;
            }

        void update(ft::AVLNODE<T>* node)
        {
            int l_ht = (node->left == NULL) ? -1 : height(node->left);
            int r_ht = (node->right == NULL) ? -1 : height(node->right);
            node->ht = 1 + std::max(l_ht, r_ht);
            node->bf = l_ht - r_ht;
        }

        ft::AVLNODE<T>* insert(ft::AVLNODE<T>* node, T x){
            if (!node)
                return (newNode(x));
            bool cmp = _comp(x.first, node->_data->first);
            if (cmp)
            {
                node->left = insert(node->left, x);
                node->left->parent = node;
            }
            else if (!cmp)
            {
                node->right = insert(node->right,x);
                node->right->parent = node;
            }
            update(node);
            return (balance(node));
        }

        ft::AVLNODE<T>* find(ft::AVLNODE<T>* x, key val)
        {
            if (x == 0)
                return 0;
            bool cmp1 = _comp(x->_data->first, val);
            bool cmp2 = _comp(val, x->_data->first);
            if (!cmp1 && !cmp2)
                return x;
            if (cmp2)
                return (find(x->left, val));
            else if (cmp1)
                return (find(x->right, val));
            return x;
        }
            
        ft::AVLNODE<T>* find(ft::AVLNODE<T>* node, key val) const
        {
            if (node == 0)
                return 0;
            bool cmp1 = _comp(node->_data->first, val);
            bool cmp2 = _comp(val, node->_data->first);
            if (!cmp1 && !cmp2)
                return node;
            if (!cmp1)
                return (find(node->left, val));
            else if (cmp1)
                return (find(node->right, val));
            return node;
        }

        int height(ft::AVLNODE<T>* node)
        {
            if (node == 0)
                return -1;
            int leftHeight = height(node->left) + 1;
            int rightHeight = height(node->right) + 1;
            if (leftHeight > rightHeight)
                return leftHeight;
            return rightHeight;
        }

		/*********************************************
        * bf == 2 -> left heavy 
        * if left_sub_tree bf >= 0 ->right rotation
        * else do left-right rotation

        * bf  == -2 -> right heavy
        * if right_sub_tree bf <= 0 -> left rotation
        * else do right-left rotation
		*********************************************/
        ft::AVLNODE<T>* balance(ft::AVLNODE<T>* node)
        {
            if (node->bf > 1)
            {
                if (node->left->bf >= 0)
                    return rightRotation(node);
                else
                    return leftrightCase(node);
            }
            else if (node->bf < -1)
            {
                if (node->right->bf <= 0)
                    return leftRotation(node);
                else
                    return rightleftCase(node);
            }
            return node;
        }

        ft::AVLNODE<T>* leftrightCase(ft::AVLNODE<T>* node)
        {
            node->left = leftRotation(node->left);
            return rightRotation(node);
        }

        ft::AVLNODE<T>* rightleftCase(ft::AVLNODE<T>* node)
        {
            node->right = rightRotation(node->right);
            return leftRotation(node);
        }

        // left and right rotations
        ft::AVLNODE<T>* leftRotation(ft::AVLNODE<T>* node)
        {
            ft::AVLNODE<T>* tmp = node->right;
            node->right = tmp->left;
            tmp->left = node;
            _resetParent(node, tmp);
            update(node);
            update(tmp);
            return tmp;
        }

        ft::AVLNODE<T>* rightRotation(ft::AVLNODE<T>* node)
        {
            ft::AVLNODE<T>* tmp = node->left;
            node->left = tmp->right;
            tmp->right = node;
            _resetParent(node, tmp);
            update(node);
            update(tmp);
            return tmp;
        }

        void _resetParent(ft::AVLNODE<T>* oldRoot, ft::AVLNODE<T>* newRoot) const
        {
            if (!oldRoot->parent)
            {
                newRoot->parent = NULL;
                if (oldRoot->left)
                    oldRoot->left->parent = oldRoot;
                if (oldRoot->right)
                    oldRoot->right->parent = oldRoot;
                oldRoot->parent = newRoot;
                return;
            }
            newRoot->parent = oldRoot->parent;
            oldRoot->parent = newRoot;
            if (oldRoot->left)
                oldRoot->left->parent = oldRoot;
            if (oldRoot->right)
                oldRoot->right->parent = oldRoot;
        }

		ft::AVLNODE<T>* freeNode(ft::AVLNODE<T>* node)
		{
			b_alloc.destroy(node->_data);
			b_alloc.deallocate(node->_data, 1);
            node->_data = NULL;
			n_alloc.destroy(node);
			n_alloc.deallocate(node, 1 * sizeof(ft::AVLNODE<T>*));
			return node = NULL;
		}

        ft::AVLNODE<T>* remove(ft::AVLNODE<T>* node, key value)
        {
			if (!node) 
				return node;
			else if (_comp(value, node->_data->first))
				node->left = remove(node->left, value);
			else if (_comp(node->_data->first, value))
				node->right = remove(node->right, value);
			else 
			{
				if (!node->left && !node->right)
					return node = freeNode(node);
				else if (!node->left && node->right)
				{
					ft::AVLNODE<T>* new_node = node->right;
					node = freeNode(node);
					return new_node;
				}
				else if (node->left && !node->right)
				{
					T Svalue = findMax(node->left);
                    b_alloc.destroy(node->_data);
                    b_alloc.construct(node->_data, Svalue);
                    node->left = remove(node->left, Svalue.first);
				} 
				else
				{
					T temp = findMin(node->right);
					b_alloc.destroy(node->_data);
					b_alloc.construct(node->_data, temp);
					node->right = remove(node->right, temp.first);
				}
			}
            update(node);
            return (balance(node));
        }

        void lower_bound(ft::AVLNODE<T>* node, key val, ft::AVLNODE<T>** con) const
        {
            if (node == 0)
                return ;
            bool cmp = _comp(node->_data->first, val);
            bool cmp1 = _comp(val, node->_data->first);
            if (!cmp && !cmp1)
            {
                *con = node;
                return ;
            }
            if (!cmp)
                lower_bound(node->left, val, con);
            if (*con == 0 && !cmp)
            {
                *con = node;
                return ;
            }
            if (cmp)
                lower_bound(node->right, val, con);
        }

        T findMin(ft::AVLNODE<T>* node) 
        {
            if (node == 0)
                return (ft::make_pair(key(), value()));
            while (node->left != 0)
                node = node->left;
            return (*(node->_data));
        }
        T findMax(ft::AVLNODE<T>* node) 
        {
            if (node == 0)
                return (ft::make_pair(key(), value()));
            while (node->right != 0)
                node = node->right;
            return (*(node->_data));
        }
        T findMin(ft::AVLNODE<T>* node) const
        {
            if (node == 0)
                return (ft::make_pair(key(), value()));
            while (node->left != 0)
                node = node->left;
            return (*(node->_data));
        }
        T findMax(ft::AVLNODE<T>* node) const
        {
            if (node == 0)
                return (ft::make_pair(key(), value()));
            while (node->right != 0)
                node = node->right;
            return (*(node->_data));
        }

        void upper_bound(ft::AVLNODE<T>* node, key val, ft::AVLNODE<T>** con) const
        {
            if (node == 0)
                return ;
            bool cmp =_comp(node->_data->first, val);
            bool cmp1 = _comp(val, node->_data->first);
            if (!cmp && !cmp1)
            {
                *con = node->right;
                return ;
            }
            if (!cmp)
                upper_bound(node->left, val, con);
            if (*con == 0 && !cmp)
            {
                *con = node;
                return ;
            }
            if (cmp)
                upper_bound(node->right, val, con);
        }

    };
};

#endif