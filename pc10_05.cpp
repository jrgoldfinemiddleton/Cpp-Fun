/**********************************************************
** Author: Jason Goldfine-Middleton
** Date: 09/01/15
** Description: Gaddis - Starting Out With C++: Early
**                       Objects (8e)
**
**              Programming Challenge 10-05
**              ===========================
**
**              In statistics the mode of a set of values
**              is the value that occurs most often. Write
**              a program that determines how many pieces
**              of pie most people eat in a year. Set up an
**              integer array that can hold responses from
**              30 people. For each person, enter the
**              number of pieces they say they eat in a
**              year. Then write a function that finds the
**              mode of these 30 values. This will be the
**              number of pie slices eaten by the most
**              people. The function that finds and returns
**              the mode should accept two arguments, an
**              array of integers, and a value indicating
**              how many elements are in the array.
**********************************************************/

#include <algorithm>    // needed for the std::sort() function
#include <iostream>
#include <string>
#include <vector>       // needed to use the std::vector type

using std::cin;
using std::cout;
using std::endl;
using std::sort;
using std::string;
using std::vector;

// function prototypes
int getValidInput(int minValue, string prompt, string errMsg);
vector<int> findMode(const int nums[], int size);

int main() {
  const int NUM_RESPONSES = 30;
  int responses[30];
  
  // prompt user for valid responses to fill array
  for (int i = 0; i < NUM_RESPONSES; i++) {
    responses[i] = getValidInput(0, 
                   "Enter the number of pie slices eaten in one year: ",
                   "Amount must be non-negative.  "
                   "Please enter a valid amount: ");
  }

  vector<int> modes = findMode(responses, NUM_RESPONSES);

  cout << "The modes:" << endl;
  for (int i = 0; i < modes.size(); i++) {
    cout << modes[i] << "  ";
  }

  cout << endl;

  return 0;
}


/*********************************************************************
** Description: Prompts the user for an int value greater than or
**              equal to minValue.  Until the user inputs a valid int,
**              it displays a custom error message.
*********************************************************************/ 
int getValidInput(int minValue, string prompt, string errMsg) {
  int input;

  cout << prompt;

  // prompt user for input at least as big as minValue
  while (true) {
    cin >> input;

    if (input < minValue) {
      // user gave invalid input
      cout << errMsg << endl;
    } else {
      // user gave valid input
      return input;
    }
  }
}


/*********************************************************************
** Description: Determines which values from an unsorted list of
**              integers are its modes and returns them in a vector.
**              They are sorted in ascending order.  Complexity is
**              roughly O(nlogn) time, where n is the number of items
**              contained in the list.
*********************************************************************/
vector<int> findMode(const int nums[], int size) {
  int maxFreq = 1;    // store highest found frequency
  vector<int> modes;  // store all modes

  // loop through all the integers
  for (int i = 0; i < size; i++) {

    int curFreq = 1;  // accumulator for occurrences of value
                      // at index i, starting from index i + 1

    // starting at the index after i, loop through the integers
    // in the list, seeking any matches with the value at index i

    // note: starting after index i will prevent duplicate values
    // from being pushed to modes
    for (int j = i + 1; j < size; j++) {

      // if a match is found, increment the accumulator
      if (nums[i] == nums[j]) {
        curFreq++;
      }
    }

    // if the accumulator for index i matches the maximum frequency
    // seen thus far, push the value stored at index i to modes
    if (curFreq == maxFreq) {
      modes.push_back(nums[i]);
    }

    // if the accumulator for index i is greater than the maximum
    // frequency seen, update maxFreq, clear all values stored in
    // modes (since there are other values that occur more
    // frequently), and push the value stored at index i to modes
    if (curFreq > maxFreq) {
      maxFreq = curFreq;
      modes.clear();
      modes.push_back(nums[i]);
    }
  }

  // sort all the modes
  sort(modes.begin(), modes.end());

  return modes;
}
