#include <iostream>
#include <chrono>

using namespace std;

template <typename DT>
class SinglyLinkedNode {
    public:
    //attributes
    DT dataItem;
    SinglyLinkedNode<DT> *next;

    //constructor
    SinglyLinkedNode(DT nodeValue, SinglyLinkedNode<DT> *nextPointer);
};

template <typename DT>
SinglyLinkedNode<DT>::SinglyLinkedNode(DT nodeValue, SinglyLinkedNode<DT> *nextPointer) {
    dataItem = nodeValue;
    next = nextPointer;
}

template <typename DT>
class SinglyLinkedList {
    private:
    //attributes
    SinglyLinkedNode<DT> *head;
    int numberOfItems;

    //Utility Functions required for main operations
    void insertEndRecursive(const DT &newDataItem, SinglyLinkedNode<DT> *current);
    void deleteEndRecursive(SinglyLinkedNode<DT> *current);
    void printForwardRecursive(SinglyLinkedNode<DT> *current);
    void printBackwardRecursive(SinglyLinkedNode<DT> *current);
    void moveNodeRecursive(int oldPosition, int newPosition, int count, SinglyLinkedNode<DT> *current);

    public:
    SinglyLinkedList();//constructor

    void insertEnd(const DT &newDataItem);
    void deleteEnd();
    void printForward();
    void printBackward();
};

template <typename DT>
SinglyLinkedList<DT>::SinglyLinkedList() {
    head = NULL;
    numberOfItems = 0;
}

template <typename DT>
void SinglyLinkedList<DT>::insertEnd(const DT &newDataItem) {
    insertEndRecursive(newDataItem, head);
}

template <typename DT>
void SinglyLinkedList<DT>::insertEndRecursive(const DT &newDataItem, SinglyLinkedNode<DT> *current) {
    if (!numberOfItems) {//if the list is empty, no need of recursion
        head = new SinglyLinkedNode<DT>(newDataItem, NULL);
    } else if (current->next == NULL) {//base case reached: no need of further recursions
        current->next = new SinglyLinkedNode<DT>(newDataItem, NULL);
    } else {//in all other cases recursion happens, move the pointer forward
        insertEndRecursive(newDataItem, current->next);//take recursive leap of faith
    }

    numberOfItems++;
}

template <typename DT>
void SinglyLinkedList<DT>::deleteEnd() {
    deleteEndRecursive(head);
}

template <typename DT>
void SinglyLinkedList<DT>::deleteEndRecursive(SinglyLinkedNode<DT> *current) {
    if (numberOfItems == 1) {//if the number of items is 1, no need of recursions
        delete head;
        head = NULL;
    } else if (current->next->next == NULL) {//base case reached: if recursion reaches last node but one, then remove the last node and stop
        delete current->next;
        current->next = NULL;
    } else {//in all other cases recursively move forward with current as current->next pointer until base case
        deleteEndRecursive(current->next);
    }

    numberOfItems--;
}

template <typename DT>
void SinglyLinkedList<DT>::printForward() {
    printForwardRecursive(head);
}

template <typename DT>
void SinglyLinkedList<DT>::printForwardRecursive(SinglyLinkedNode<DT> *current) {
    if (current == NULL) return;//base case reached: when current = NULL that means last element is printed and so the further recursion is stopped by returning

    cout << current->dataItem << " ";
    printForwardRecursive(current->next);//recursively move forward and print the dataItem
    //this executes after all the executions so when the recursion has the current = head when this line executes, that means all the printing is done and endl is printed :)
    if (current == head) cout << endl;
}

template <typename DT>
void SinglyLinkedList<DT>::printBackward() {
    printBackwardRecursive(head);
}

template <typename DT>
void SinglyLinkedList<DT>::printBackwardRecursive(SinglyLinkedNode<DT> *current) {
    if (current == NULL) return;//base case reached: return to previous call

    printBackwardRecursive(current->next);//first the recursion is called before printing
    cout << current->dataItem << " ";//this is printed only after the previous recursions are completed so the order of printing is reverse
    if (current == head) cout << endl;//this executes after all the recursions are done and first function call is reached so endl is printed as it is the last recursion
}

class Timer {
    private:
    chrono::time_point<chrono::high_resolution_clock> m_StartTimepoint;
    public:
    Timer();
    ~Timer();
    void Stop();
};
Timer::Timer() {
    // Initialize start time with the constructor
    m_StartTimepoint = chrono::high_resolution_clock::now();
}
Timer::~Timer() {
    Stop();
}
void Timer::Stop() {
    // Get time of object destruction
    auto endTimepoint = chrono::high_resolution_clock::now();
    // Get start and end time in microseconds
    auto start = chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
    auto end = chrono::time_point_cast<chrono::microseconds>(endTimepoint).time_since_epoch().count();
    // calculate time elapsed
    auto duration = end - start;
    double ms = duration * 0.001;
    cout << duration << " microseconds ( " << ms << " milliseconds)" << endl;
}

int main() {
    SinglyLinkedList<int> list;
    {
        Timer timer;
        for (int i = 0;i < 10000;i++) list.insertEnd(i + 1);
    }
    {
        Timer timer;
        for (int i = 0;i < 10000;i++) list.deleteEnd();
    }
}