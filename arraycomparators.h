#ifndef ARRAYCOMPARATORS_H
#define ARRAYCOMPARATORS_H

/** Brute force comparison.
 *  O(m*n), where m and n -- sizes of arrays.
 *
 *  @return number of common elements in arrays.
 **/
unsigned int compareslow(const int arr1[], unsigned int size1, const int arr2[], unsigned int size2);


/** Array comparison by array sorting and smart comparison of sorted arrays.
 *  O(n), where n -- maximum of array sizes.
 *
 *  Specified arrays will be sorted.
 *
 *  @return number of common elements in arrays.
 **/
unsigned int comparebysort(int arr1[], unsigned int size1, int arr2[], unsigned int size2);

/** Array comparison by array sorting and smart comparison of sorted arrays.
 *  O(n), where n -- maximum of array sizes.
 *
 *  Specified arrays will be sorted.
 *
 *  @return number of common elements in arrays.
 **/
unsigned int comparebysortu(unsigned int* arr1, unsigned int size1, unsigned int* arr2, unsigned int size2);


/** Array comparison by balanced search tree (AVL).
 *  O((n+m)log(n)), where m and n -- sizes of arrays.
 *
 *  @return number of common elements in arrays.
 **/
unsigned int comparebyavl(const int arr1[], unsigned int size1, const int arr2[], unsigned int size2);

#endif //ARRAYCOMPARATORS_H
