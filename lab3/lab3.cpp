// #include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

template <typename DataType>
class List {
    private:
    // Length of the list
    int length;

    // Cursor Position
    int cursorPosition;

    // num of elements
    int numberOfElements;

    // List in the form of a vector
    vector<DataType> array;

    // Prefix sum array
    vector<int> psa;

    public:

    List(int listSize);
    void insert(const DataType &newDataItem);
    void remove();
    void replace(const DataType &newDataItem);
    void clear();
    bool isEmpty();
    bool isFull();
    void gotoBeginning();
    void gotoEnd();
    bool gotoNext();
    bool gotoPrior();
    DataType getCursor();
    void showStructure();
    void uniqueify();
    void createPrefixSumArray();
    int subArraySum(int left, int right);
};

template <typename DataType>
List<DataType>::List(int listSize) {

    array.resize(listSize);

    length = listSize;

    cursorPosition = -1;

    numberOfElements = 0;
}

template <typename DataType>
void List<DataType>::insert(const DataType &newDataItem) {
    //* shifting all the necessary elements to the right
    for (int i = numberOfElements - 1; i > cursorPosition; i++) {
        array[i + 1] = array[i];
    }
    //* new item is inserted right next to the cursor
    array[cursorPosition + 1] = newDataItem;
    cursorPosition++;
    numberOfElements++;
}

template <typename DataType>
void List<DataType>::remove() {
    //* shifting the required elements to the left
    for (int i = cursorPosition; i < numberOfElements - 1; i++) {
        array[i] = array[i + 1];
    }

    if (cursorPosition == numberOfElements - 1) {
        cursorPosition--;
    } else {
        cursorPosition++;
    }
    numberOfElements--;
}

template <typename DataType>
void List<DataType>::replace(const DataType &newDataItem) {
    array[cursorPosition] = newDataItem;
}

template <typename DataType>
void List<DataType>::clear() {
    array.clear();//clears the array and sets length to 0
    array.resize(length);//sets the length to normal length
}

template <typename DataType>
bool List<DataType>::isEmpty() {
    return numberOfElements == 0;
}

template <typename DataType>
bool List<DataType>::isFull() {
    return numberOfElements == length;
}

template <typename DataType>
void List<DataType>::gotoBeginning() {
    cursorPosition = 0;
}

template <typename DataType>
void List<DataType>::gotoEnd() {
    cursorPosition = numberOfElements - 1;
}

template <typename DataType>
bool List<DataType>::gotoNext() {
    if (cursorPosition == numberOfElements - 1) {
        return false;
    } else {
        cursorPosition++;
        return true;
    }
}

template <typename DataType>
bool List<DataType>::gotoPrior() {
    if (cursorPosition == 0) {
        return false;
    } else {
        cursorPosition--;
        return true;
    }
}

template <typename DataType>
DataType List<DataType>::getCursor() {
    return array[cursorPosition];
}

template <typename DataType>
void List<DataType>::showStructure() {
    // if (numberOfElements == 0) {
    if (this->isEmpty()) {
        cout << "Empty List:(" << endl;
        return;
    } else {
        cout << "The number of elements in the list is " << numberOfElements << endl;
        for (int i = 0; i < numberOfElements; i++) {
            cout << array[i] << " ";
        }
        cout << endl;
    }
}

template <typename DataType>
void List<DataType>::uniqueify() {
    gotoBeginning();

    int size = numberOfElements;

    for (int i = 0; i < numberOfElements; i++) {
        int current = getCursor();
        if (gotoNext()) {
            int next = getCursor();
            if (current == next) {
                next++;
                replace(next);
            }
        }
    }
}

template <typename DataType>
void List<DataType>::createPrefixSumArray() {
    int sum = 0;
    for (int i = 0; i < numberOfElements; i++) {
        sum += array[i];
        psa.push_back(sum);
        // cout << "psa: " << psa.at(i) << endl;
    }
}

template <typename DataType>
int List<DataType>::subArraySum(int left, int right) {
    return psa[right - 1] - psa[left - 2];
}

template <typename DataType>
vector<DataType> merge(List<DataType> l1, List<DataType> l2) {
    vector<DataType> ans;

    l1.gotoBeginning();
    l2.gotoBeginning();


    while (!l1.isEmpty() && !l2.isEmpty()) {
        if (l1.getCursor() > l2.getCursor()) {
            ans.push_back(l2.getCursor());
            cout << "Adding this to vector: " << l2.getCursor() << endl;
            l2.remove();
        } else {
            ans.push_back(l1.getCursor());
            cout << "Adding this to vector: " << l1.getCursor() << endl;
            l1.remove();
        }
    }

    if (l1.isEmpty()) {
        while (!l2.isEmpty()) {
            ans.push_back(l2.getCursor());
            cout << "Adding this to vector: " << l2.getCursor() << endl;
            l2.remove();
        }
    } else if (l2.isEmpty()) {
        while (!l1.isEmpty()) {
            ans.push_back(l1.getCursor());
            cout << "Adding this to vector: " << l1.getCursor() << endl;
            l1.remove();
        }
    }

    return ans;
}

int main() {
    // // TODO Task 1: Done
    // List<string> l1(5);
    // List<string> l2(3);

    // l1.insert("aay");
    // l1.insert("aaz");
    // l1.insert("abx");
    // l1.insert("aby");
    // l1.insert("abz");

    // l2.insert("aax");
    // l2.insert("aazz");
    // l2.insert("az");

    // l1.showStructure();
    // l2.showStructure();

    // vector<string> ans = merge(l1, l2);

    // for (int i = 0; i < ans.size(); i++) cout << ans[i] << endl;

    // // TODO Task 2: Done
    // List<int> tempList(10);
    // for (int i = 0;i < 10;i++) tempList.insert(1);
    // tempList.showStructure();
    // tempList.uniqueify();
    // tempList.showStructure();

    // // TODO Task 3: Done
    // List<int> tempList(5);

    // tempList.insert(6);
    // tempList.insert(1);
    // tempList.insert(4);
    // tempList.insert(8);
    // tempList.insert(3);

    // tempList.createPrefixSumArray();

    // cout << tempList.subArraySum(1, 3) << endl;
    // cout << tempList.subArraySum(1, 5) << endl;
    // cout << tempList.subArraySum(4, 5) << endl;
    // cout << tempList.subArraySum(1, 1) << endl;
    // cout << tempList.subArraySum(2, 4) << endl;

    return 0;
}