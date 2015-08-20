/**********************************************************
** Author: Jason Goldfine-Middleton
** Date: 08/20/15
** Description: Gaddis - Starting Out With C++: Early
**                       Objects (8e)
**
**              Programming Challenge 10-01
**              ===========================
**
**              Write a program that dynamically allocates
**              an array large enough to hold a user-
**              defined number of test scores. Once all the
**              scores are entered, the array should be
**              passed to a function that sorts them in
**              ascending order. Another function should be
**              called that calculates the average score.
**              The program should display the sorted list
**              of scores and average with appropriate
**              headings. Use pointer notation rather than
**              array notation whenever possible.
**
**              Input Validation: Do not accept negative
**                                numbers for test scores.
**********************************************************/

#include <iomanip>    // for fixed, setprecision, and showpoint
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::fixed;         // see below
using std::setprecision;  // with fixed, set number of decimal places
using std::showpoint;     // always display decimal point
using std::string;


// function prototypes
double average(const int *arr, const int size); 
int getValidInput(int minValue, string prompt, string errMsg);
void printArr(const int *arr, const int size); 
void sortAscending(int *arr, const int size); 


int main() {
  int numScores;    // number of test scores
  int *testScores;  // scores

  // prompt user for number of test scores
  numScores = getValidInput(1, "Enter the number of test scores: ",
                            "There must be at least 1 test.  Please "
                            "enter a valid number of test scores: ");

  // dynamically allocate heap space for array of scores
  testScores = new int[numScores];

  // prompt user for valid test scores to fill array
  for (int i = 0; i < numScores; i++) {
    *(testScores + i) = getValidInput(0, "Enter a test score: ",
                                      "Test score must be non-negative.  "
                                      "Please enter a valid score: ");
  }

  // sort the test scores from least to greatest
  sortAscending(testScores, numScores);

  // find the average of all scores
  double avg = average(testScores, numScores);

  // print the sorted test scores
  cout << endl << "Test scores in ascending order: " << endl;
  printArr(testScores, numScores);

  // print the average of all scores
  cout << showpoint << setprecision(2) << fixed;
  cout << endl << "Average score: " << avg << endl << endl;

  // free allocated heap memory from array to prevent memleak
  delete [] testScores;

  return 0;
}


/*********************************************************************
** Description: Returns the average of an array of ints as a double.
*********************************************************************/ 
double average(const int *arr, const int size) {
  int sum = 0;  // accumulator

  for (int i = 0; i < size; i++) {
    sum += *(arr + i);
  }

  // apply cast to sum to prevent int division
  return static_cast<double>(sum) / size;
}


/*********************************************************************
** Description: Prompts the user for an int value greater than or
**              equal to minValue.  Until the user inputs a valid int,
**              it displays a custom error message.
*********************************************************************/ 
int getValidInput(int minValue, string prompt, string errMsg) {
  int input;

  cout << prompt << endl;

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
** Description: Prints the contents of an int array to the display.
*********************************************************************/ 
void printArr(const int *arr, const int size) {
  for (int i = 0; i < size; i++) {
    // *(arr + i) == arr[i]
    cout << *(arr + i) << "  ";
  }

  cout << endl;
}


/*********************************************************************
** Description: Sorts an int array from least to greatest.  Note that
**              the array is modified.
*********************************************************************/ 
void sortAscending(int *arr, const int size) {
  int maxIndex, maxValue, temp;

  // start at end of array and work down
  //
  // this loop in charge of where the current search interval
  // ends as well as where to put the found max value
  // from the said search interval
  for (int i = size - 1; i >= 0; i--) {
    maxIndex = maxValue = 0;

    // search section of array from beginning to index i
    for (int j = 0; j <= i; j++) {
      int curValue = *(arr + j);

      // keep the maximum known value and where it's located
      // up to date
      if (curValue > maxValue) {
        maxIndex = j;
        maxValue = curValue;
      }
    }

    // swap the element with maxValue with the last
    // element of current search interval
    temp = *(arr + i);
    *(arr + i) = maxValue; // maxValue ==  *(arr + maxIndex)
    *(arr + maxIndex) = temp;
  }
}
