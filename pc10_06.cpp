/**********************************************************
** Author: Jason Goldfine-Middleton
** Date: 09/01/15
** Description: Gaddis - Starting Out With C++: Early
**                       Objects (8e)
**
**              Programming Challenge 10-06
**              ===========================
**
**              In statistics the median of a set of values
**              is the value that lies in the middle when
**              the values are arranged in sorted order. If
**              the set has an even number of values, then
**              the median is taken to be the average of
**              the two middle values. Write a function
**              that determines the median of a sorted
**              array. The function should take an array of
**              numbers and an integer indicating the size
**              of the array and return the median of the
**              values in the array. You may assume the
**              array is already sorted. Use pointer
**              notation whenever possible.
**********************************************************/

#include <iostream>

// function prototypes
double findMedian(const double nums[], int size);
bool isEven(int val);

int main() {

  double list1[5] = {4, 5, 7, 9, 11};
  double list2[1] = {5};
  double list3[6] = {10, 8, 6, 4, 2, 0};

  std::cout << "list1 median: " << findMedian(list1, 5) << std::endl;
  std::cout << "list2 median: " << findMedian(list2, 1) << std::endl;
  std::cout << "list3 median: " << findMedian(list3, 6) << std::endl;

  return 0;
}


/*********************************************************************
** Description: Returns true if the input is even, false otherwise.
*********************************************************************/
bool isEven(int val) {
  // using bitwise AND operation
  // if the last digit of the binary representation of val is 1
  // return false, otherwise return true
  return (val & 1) == 0;
}


/*********************************************************************
** Description: Returns the median of the values in an array that is
**              already sorted.  Whether the array is sorted in
**              ascending or descending order is inconsequential.
*********************************************************************/
double findMedian(const double nums[], int size) {
  double med;
  int mid = size / 2;

  isEven(size) ?
    med = 0.5 * ( *(nums + mid - 1) + *(nums + mid) ) :
    med = *(nums + mid);

  return med;
}
