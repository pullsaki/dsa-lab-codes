#include <iostream>
#include <limits>

using namespace std;

class ArrayVector {
    public:
    ArrayVector(); //constructor
    int size() const; //number of elements in the vector
    bool empty() const; //checking if vector is empty
    int &operator[](int i); //element at index - implementation 1
    int at(int i); //element at index implementation 2
    void erase(int i); //remove element at index
    void insert(int i, const int &e); //insert element at index
    void reserve(int N);

    private:
    int capacity; //current array size
    int n; //number of elements existing in the array
    int *A; //array storing the elements of the vector
};

ArrayVector::ArrayVector() : capacity(0), n(0), A(NULL) {} //constructor sets the values of capacity and number of elements to 0 and sets array to NULL

int ArrayVector::size() const {
    return n; //returns the number of elements currently in the vector
}

bool ArrayVector::empty() const {
    return n == 0; //returns true if number of elements is 0
}

int &ArrayVector::operator[](int i) {
    return A[i]; //returns the element in the array at index i
}

int ArrayVector::at(int i) {
    if (i < 0 || i >= n) { //if the given index is out of range
        cout << "Error: Terminating"; //prints error statement
        return INT_MIN; //returns minimum number
    }
    return A[i]; //if index is in the range, then returns the element in the array at index i
}

void ArrayVector::reserve(int N) {
    if (capacity >= N) return; //if the capacity is already >= N then do nothing and return
    int *B = new int[N]; //creates a temporary array of the new size N to store the values in A
    for (int j = 0; j < n; j++) { //loops over the elements in A
        B[j] = A[j]; //copies elements in A to B
    }
    if (A != NULL) delete [] A; //if the array is not NULL then deleting the array A, if its already NULL then do nothing
    A = B; //make A refer to the new array B
    capacity = N; //set the new capacity to N
}

void ArrayVector::insert(int i, const int &e) {
    if (n >= capacity) { //if the number of elements already reached the capacity level then we need to increase the capacity of the array
        reserve(max(1, 2 * capacity)); //if the array size is 0 then set the new size to 1, if it is not 0 then sets the new size to double the initial size
    }
    for (int j = n - 1; j >= i; j--) { //looping over the elements in the array from the end to the index i
        A[j + 1] = A[j]; //shifts the elements to the right to make space of the new element at i
    }
    A[i] = e; //placing the new element in the newly created empty slot
    n++; //as we have added a new element... increasing the number of elements
}

void ArrayVector::erase(int i) {
    for (int j = i + 1; j < n; j++) { //looping over the elements of the array after index i so as to shift the elements to the left.. essentially removing element at index i
        A[j - 1] = A[j]; //shifting the elements to the left
    }
    n--; //we have removed an element so we are decreasing the no of elements variable
}

int main() {
    ArrayVector v;
    if (v.empty()) cout << "Empty vector" << endl;
    v.insert(0, 1);
    cout << "Elements: " << v[0] << endl;
    cout << "No. of elements: " << v.size() << endl;
    v.reserve(4);
    cout << "Reserved 4" << endl;
    cout << "Size: " << v.size() << endl;
    cout << "Elements: ";
    for (int i = 0; i < v.size(); i++) cout << v[i] << " ";
    cout << endl;

    for (int i = 1; i <= 10; i++) v.insert(i, i + 1);
    cout << "Elements: ";
    for (int i = 0; i < v.size(); i++) cout << v.at(i) << " ";
    cout << endl;

    v.erase(5);
    cout << "Elements: ";
    for (int i = 0; i < v.size(); i++) cout << v.at(i) << " ";
    cout << endl;
}