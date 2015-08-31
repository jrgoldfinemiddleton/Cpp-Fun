/**********************************************************
** Author: Jason Goldfine-Middleton
** Date: 08/29/15
** Description: Gaddis - Starting Out With C++: Early
**                       Objects (8e)
**
**              Programming Challenge 10-02
**              ===========================
**
**              Modify the program of Programming Challenge
**              10-01 to allow the user to enter name–score
**              pairs. For each student taking a test, the
**              user types a string representing the name
**              of the student, followed by an integer
**              representing the student’s score. Modify
**              both the sorting and average-calculating
**              functions so they take arrays of
**              structures, with each structure containing
**              the name and score of a single student. In
**              traversing the arrays, use pointers rather
**              than array indices.
**********************************************************/

#include <iomanip>    // for fixed, setprecision, and showpoint
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::fixed;         // see below
using std::left;          // left-align output
using std::setprecision;  // with fixed, set number of decimal places
using std::setw;          // set output string width
using std::showpoint;     // always display decimal point
using std::string;


struct Test {
  // public
  string student;   // test taker
  int score;        // score received
};


// function prototypes
double average(const Test *arr, const int size); 
int getValidInput(int minValue, string prompt, string errMsg);
void printArr(const Test *arr, const int size); 
void sortAscending(Test *arr, const int size); 


int main() {
  int numScores;    // number of test scores
  Test *tests;      // scores

  // prompt user for number of test scores
  numScores = getValidInput(1, "Enter the number of test scores: ",
                            "There must be at least 1 test.  Please "
                            "enter a valid number of test scores: ");

  // dynamically allocate heap space for array of scores
  tests = new Test[numScores];

  // prompt user for valid test scores to fill array
  for (int i = 0; i < numScores; i++) {
    Test *curExam = tests + i;
    
    cout << "Enter student name: ";

    cin.ignore();     // skip the newline in the buffer
    getline(cin, curExam->student);
    
    curExam->score = getValidInput(0, "Enter a test score: ",
                                      "Test score must be non-negative.  "
                                      "Please enter a valid score: ");
  }

  // sort the test scores from least to greatest
  sortAscending(tests, numScores);

  // find the average of all scores
  double avg = average(tests, numScores);

  // print the sorted test scores
  cout << endl << "Exam Summary:" << endl;
  printArr(tests, numScores);

  // print the average of all scores
  cout << showpoint << setprecision(2) << fixed;
  cout << "Average score: " << avg << endl << endl;

  // free allocated heap memory from array to prevent memleak
  delete [] tests;

  return 0;
}


/*********************************************************************
** Description: Returns the average score from an array of Tests as a
**              double.
*********************************************************************/ 
double average(const Test *arr, const int size) {
  int sum = 0;  // accumulator

  for (int i = 0; i < size; i++) {
    sum += (arr + i)->score;
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
** Description: Prints the contents of a Test array to the display.
*********************************************************************/ 
void printArr(const Test *arr, const int size) {
  for (int i = 0; i < size; i++) {
    // *(arr + i) == arr[i]
    cout << "Student #" << (i + 1) << ": "
         << setw(25) << left << (arr + i)->student
         << "  Score: "
         << setw(3) << (arr + i)->score << endl;
  }

  cout << endl;
}


/*********************************************************************
** Description: Sorts a Test array from least to greatest.  Note that
**              the array is modified.
*********************************************************************/ 
void sortAscending(Test *arr, const int size) {
  int maxIndex, maxValue;
  Test temp;

  // start at end of array and work down
  //
  // this loop in charge of where the current search interval
  // ends as well as where to put the found max value
  // from the said search interval
  for (int i = size - 1; i >= 0; i--) {
    maxIndex = maxValue = 0;

    // search section of array from beginning to index i
    for (int j = 0; j <= i; j++) {
      int curValue = (arr + j)->score;

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
    *(arr + i) = *(arr + maxIndex); // maxValue == (arr + maxIndex)->score
    *(arr + maxIndex) = temp;
  }
}
