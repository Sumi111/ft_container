#ifndef EQUAL_HPP
#define EQUAL_HPP

namespace ft
{
	/**************************************		std::equal	*****************************************
	*  Compares the elements in the range [first1,last1) with those in the range beginning at first2,
	*  returns true if all of the elements in both ranges match.
	*  elements are compared using operator== or binary function pred
	**************************************************************************************************/
	template <class InputIterator1, class InputIterator2>
	bool equal (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2){
		while (first1 != last1)
		{
			if (!(*first1 == *first2))
				return false;
			++first1;
			++first2;
		}
		return true;
	}

	template <class InputIterator1, class InputIterator2, class BinaryPredicate>
	bool equal (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred){
		while (first1 != last1)
		{
			if (!(pred(*first1,*first2)))
				return false;
			first1++;
			first2++;
		}
		return true;
	}
	/******************************		std::lexicographical_compare	**********************************
	* Comparing sequentially the elements that have the same position in both ranges against each other,
	  until one element is not equivalent to the other.
	* The result of comparing these first non-matching elements is the result of the lexicographical comparison.
	* If both sequences compare equal until one of them ends.
	* The shorter sequence is lexicographically less than the longer one.
	*******************************************************************************************************/
	template <class InputIterator1, class InputIterator2> 
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2){
		while (first1!=last1)
		{
			if ((first2==last2) || (*first2 < *first1))
				return false;
			else if (*first1 < *first2)
				return true;
			++first1;
			++first2;
		}
		return (first2!=last2);
	};

	template <class InputIterator1, class InputIterator2, class Compare>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare comp){
		while (first1!=last1)
		{
			if ((first2==last2) || !comp(*first2,*first1))
				return false;
			else if (!comp(first1,*first2))
				return true;
			++first1;
			++first2;
		}
		return (first2!=last2);
	};
};

#endif