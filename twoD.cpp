/**********************************************************
** Author: Jason Goldfine-Middleton
** Date: 08/18/15
** Description: Constructs a dynamic 2-D array of ints on
**              the heap, sets the elements, prints them,
**              and frees the memory.
**********************************************************/

#include <iostream>

using namespace std;

int main() {

  int rows = 3, cols = 4; // just an example, you should get
                          // these from the user

  int **dynArr; // declare the pointer to the start of the
                // 2-D array

  dynArr = new int*[rows];  // new operator returns a pointer
                            // to an array of int* on the heap.
                            // dynArr itself lives on the stack
                            // and points to the first column which
                            // lives on the heap.

  // think of the array created above as being one column
  // now we're going to make rows pop out of it
  for (int curRow = 0; curRow < rows; ++curRow) {
    // for each index going up the column, make that index
    // point to its own row.
    // each element of these rows will be an int, not an int*
    dynArr[curRow] = new int[cols];
  }

  // put the sum of each element's row and column index
  // into the array
  for (int curRow = 0; curRow < rows; ++curRow) {
    for (int curCol = 0; curCol < cols; ++curCol) {
      dynArr[curRow][curCol] = curRow + curCol;
    }
  }

  // print out all the elements of the array
  for (int curRow = 0; curRow < rows; ++curRow) {
    for (int curCol = 0; curCol < cols; ++curCol) {
      cout << "element[" << curRow << "][" << curCol << "] = "
           << dynArr[curRow][curCol] << endl; 
    }
  }

  // deallocate that heap memory we used
  for (int curRow = 0; curRow < rows; ++curRow) {
    // delete the rows first because we won't be able
    // to access them after deleting the main column
    delete [] dynArr[curRow];
  }
  // now pointer no longer pointing to the main column
  delete [] dynArr;
  dynArr = NULL;

  // status: all heap memory freed

  return 0;
}
