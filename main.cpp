/*
Author: Lena Palmieri
KUID: 3115099
Date: 10/30/24
Lab: lab07
Last Modified: 11/2/24
Purpose: 
*/

#include <iostream>
#include <string>
#include <fstream>
using namespace std;
const int SIZE = 4; // Adjust if necessary
static int lineNum = 0;

class Matrix {
private:
int data[SIZE][SIZE]; // 2D array for matrix data (using int for simplicity)
public:
// 1. Read values from stdin into a matrix
void readFromStdin() {
    string name;
    //Gets filename from user and opens it
    cout << "Enter the filename: ";
    cin >> name;
    ifstream f(name);
    
    string line;
    //Continues from where the previous file reading left off
    f.seekg(lineNum);
    //Loops through each line and number in the line, converts them to an int and adds them to the array
    for (int i = 0; i < SIZE; i++) {
        getline(f, line);
        lineNum += line.length()+2;
        int nextNum, j = 0, endIndex = 0;
        while (endIndex > -1) {
            endIndex = line.find(" ");
            string nextString = line.substr(0, endIndex);
            //Checks the file input values to make sure they are numbers
            //If the input file contains a string or another non numerical value, than an error is thrown and the program proceeds to the catch block
            try {
                nextNum = stoi(nextString);
            }
            //Tells the user there is an invalid matrix input and terminates the program sucessfully
            catch(...) {
                cout << "Invalid value input!!!";
                exit(0);
            }
            nextNum = stoi(nextString);
            data[i][j] = nextNum;
            line = line.substr(endIndex+1, line.length()-endIndex);
            j++;
        }
    }
    
}
// 2. Display a matrix
void display() const {
    //Iterates through each index, printing the elements out
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            cout << data[i][j] << " ";
        }
        cout << endl;
    }
}
// 3. Add two matrices (operator overloading for +)
Matrix operator+(const Matrix& other) const {
    Matrix sum;
    //Iterates through each index, adding the corresponding ones together and assigning them to that index in the sum matrix
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            sum.data[i][j] = data[i][j] + other.data[i][j];
        }
    }
    return sum;
}
// 4. Multiply two matrices (operator overloading for *)
Matrix operator*(const Matrix& other) const {
    Matrix product;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            int sum = 0;
            //Iterates over the entire row in the first matrix and column in the second matrix, multiplying the values together and then adding them to the total
            //This value is then assigned to the corresponding element in the matrix
            for (int x = 0; x < SIZE; x++) {
                sum += (data[i][x] * other.data[x][j]);
            }
            product.data[i][j] = sum;
        }
    }
    return product;
}
// 5. Compute the sum of matrix diagonal elements
int sumOfDiagonals() const {
    int sum = 0;
    //Iterates through each diagonal entry, adding them together
    for (int x = 0; x < SIZE; x++) {
        sum += data[x][x];
    }
    return sum;
}
// 6. Swap matrix rows
void swapRows(int row1, int row2) {
    if (row1 >= 0 && row1 < SIZE && row2 >= 0 && row2 < SIZE) {
        int swapNum;
        //Swaps each index for the rows 1 by 1
        for (int i = 0; i < SIZE; i++) {
            swapNum = data[row1][i];
            data[row1][i] = data[row2][i];
            data[row2][i] = swapNum;
        }
    }
}
};
int main() {
// Example usage:
Matrix mat1;
cout << "Enter values for Matrix 1:" << endl;
mat1.readFromStdin();

cout << "Matrix 1:" << endl;
mat1.display();

Matrix mat2;
cout << "Enter values for Matrix 2:" << endl;
mat2.readFromStdin();
cout << "Matrix 2:" << endl;
mat2.display();
Matrix sum = mat1 + mat2;
cout << "Sum of matrices:" << endl;
sum.display();
Matrix product = mat1 * mat2;
cout << "Product of matrices:" << endl;
product.display();
cout << "Sum of diagonals of Matrix 1: " << mat1.sumOfDiagonals() << endl;
mat1.swapRows(0, 2);
cout << "Matrix 1 after swapping rows:" << endl;
mat1.display();

return 0;
}
