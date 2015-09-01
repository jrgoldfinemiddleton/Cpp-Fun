/**********************************************************
** Author: Jason Goldfine-Middleton
** Date: 08/18/15
** Description: This program asks the user for the size of
**              each dimension of a 3-D dynamic array.  It
**              then fills the array with integers, prints
**              the array, and then frees the memory that
**              was allocated.
**********************************************************/

#include <iostream>

using std::cin;
using std::cout;
using std::endl;


void fill3D(int ***a, int rows, int cols, int depth);
void getDimensions(int &x, int &y, int &z);
void print3D(int ***a, int rows, int cols, int depth);


int main() {
  // declare variables for array dimension size
  int xDim, yDim, zDim;

  // give sane default values
  xDim = yDim = zDim = 1;

  // prompt user for dimension sizes
  getDimensions(xDim, yDim, zDim);

  // allocate space for 3-D array of ints
  int ***dynArr = new int**[xDim];
  
  for (int i = 0; i < xDim; i++) {
    dynArr[i] = new int*[yDim];

    for (int j = 0; j < yDim; j++) {
      dynArr[i][j] = new int[zDim];
    }
  }

  // fill the array with ints
  fill3D(dynArr, xDim, yDim, zDim);

  // print out the array
  print3D(dynArr, xDim, yDim, zDim);

  // free space from array
  for (int i = 0; i < xDim; i++) {
    for (int j = 0; j < yDim; j++) {
      delete [] dynArr[i][j];
    }
    delete [] dynArr[i];
  }
  delete [] dynArr;
  dynArr = NULL;

  return 0;
}


/*********************************************************************
** Description: Prints all the elements of a three-dimensional dynamic
**              array.  A pointer to the array must be passed in.
*********************************************************************/ 
void print3D(int ***a, int rows, int cols, int depth) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      for (int k = 0; k < depth; k++) {
        cout << "Element at index [" << i << "]["
             << j << "][" << k << "] = "
             << a[i][j][k] << endl;
      }
    }
  }
  cout << endl;
}


/*********************************************************************
** Description: For each element of a three-dimensional dynamic array,
**              sets the value equal to the sum of the three indices
**              at that position.  A pointer to the array must be
**              passed in.
*********************************************************************/ 
void fill3D(int ***a, int rows, int cols, int depth) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      for (int k = 0; k < depth; k++) {
        a[i][j][k] = i + j + k;
      }
    }
  }
}


/*********************************************************************
** Description: Prompts the user for three integers between 1 and 5 to
**              establish the size of a three-dimensional dynamic
**              array.  The functions validates user input and updates
**              the variables referenced by the parameters.
*********************************************************************/ 
void getDimensions(int &x, int &y, int &z) {
  int a, b, c;
  a = b = c = 0;

  // ask user for each dimension with validation
  while (a < 1 || a > 5 || b < 1 || b > 5 || c < 1 || c > 5) {
    cout << endl;
    cout << "Please enter the x, y, and z dimensional sizes.  Separate\n"
         << "them with spaces.  Please choose a size between 1 and 5 for\n"
         << "each dimension: ";
    cin >> a >> b >> c;
  }

  x = a; y = b; z = c;

  cout << endl << "Thanks.  One epic array coming right up." << endl;
  cout << endl;
}
