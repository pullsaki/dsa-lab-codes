#include <iostream>

using namespace std;

template<typename DT>
class SinglyLinkedNode {
    public:
    // data items in the node
    DT dataItem;
    SinglyLinkedNode<DT> *next;
    // constructor
    SinglyLinkedNode(DT nodeValue, SinglyLinkedNode<DT> *nextPointer);
};

template<typename DT>
SinglyLinkedNode<DT>::SinglyLinkedNode(DT nodeValue, SinglyLinkedNode *nextPointer) {
    dataItem = nodeValue;
    next = nextPointer;
}

template<typename DT>
class SinglyLinkedList {
    // We declare these members protected because we will inherit this class later
    private:
    // Data Members
    SinglyLinkedNode<DT> *head;
    int numberOfItems;
    // These are utility functions that the main functions will call
    void insertEndRecursive(const DT &newDataItem, SinglyLinkedNode<DT> *current);
    void deleteEndRecursive(SinglyLinkedNode<DT> *current);
    void printForwardRecursive(SinglyLinkedNode<DT> *current);
    void printBackwardRecursive(SinglyLinkedNode<DT> *current);
    public:
    // Constructor
    SinglyLinkedList();
    void insertEnd(const DT &newDataItem);
    void insertBeginning(const DT &newDataItem);
    void deleteBeginning();
    void deleteEnd();
    void printForward();
    void printBackward();
    DT getHead();
};

template<typename DT>
SinglyLinkedList<DT>::SinglyLinkedList() {
    head = NULL;
    numberOfItems = 0;
}

template<typename DT>
void SinglyLinkedList<DT>::insertBeginning(const DT &newDataItem) {
    if (numberOfItems == 0) {
        head = new SinglyLinkedNode<DT>(newDataItem, NULL);
    } else {
        SinglyLinkedNode<DT> *temp = new SinglyLinkedNode<DT>(newDataItem, head);
        head = temp;
    }
    numberOfItems++;
}

template<typename DT>
void SinglyLinkedList<DT>::insertEnd(const DT &newDataItem) {
    insertEndRecursive(newDataItem, head);
}

template<typename DT>
void SinglyLinkedList<DT>::insertEndRecursive(const DT &newDataItem, SinglyLinkedNode<DT> *current) {
    if (numberOfItems == 0) {
        head = new SinglyLinkedNode<DT>(newDataItem, NULL);
        numberOfItems++;
    } else if (current->next == NULL) {
        current->next = new SinglyLinkedNode<DT>(newDataItem, NULL);
        numberOfItems++;
    } else {
        insertEndRecursive(newDataItem, current->next);
    }
}

template<typename DT>
void SinglyLinkedList<DT>::deleteBeginning() {
    SinglyLinkedNode<DT> *temp = head->next;
    delete head;
    head = temp;
    numberOfItems--;
}

template<typename DT>
void SinglyLinkedList<DT>::deleteEnd() {
    deleteEndRecursive(head);
}

template<typename DT>
void SinglyLinkedList<DT>::deleteEndRecursive(SinglyLinkedNode<DT> *current) {
    if (numberOfItems == 1) {
        delete head;
        head = NULL;
        numberOfItems--;
    } else if (current->next->next == NULL) {
        delete current->next;
        current->next = NULL;
        numberOfItems--;
    } else {
        deleteEndRecursive(current->next);
    }
}

template<typename DT>
void SinglyLinkedList<DT>::printForward() {
    printForwardRecursive(head);
}

template<typename DT>
void SinglyLinkedList<DT>::printForwardRecursive(SinglyLinkedNode<DT> *current) {
    if (current == NULL) return;
    std::cout << current->dataItem << " ";
    printForwardRecursive(current->next);
    if (current == head) std::cout << std::endl;
}

template<typename DT>
void SinglyLinkedList<DT>::printBackward() {
    printBackwardRecursive(head);
}

template<typename DT>
void SinglyLinkedList<DT>::printBackwardRecursive(SinglyLinkedNode<DT> *current) {
    if (current == NULL) return;
    printBackwardRecursive(current->next);
    std::cout << current->dataItem << " ";
    if (current == head) std::cout << std::endl;
}

template<typename DT>
DT SinglyLinkedList<DT>::getHead() {
    return head->dataItem;
}

template<typename DT>
class Stack {
    private:
    int numberOfItems;
    SinglyLinkedList<DT> stackList;

    public:
    Stack();

    void push(const DT &newDataItem);
    DT pop();
    bool isEmpty();
    DT getTop();//task 1 function
    void addFront(const DT &e);
    void addBack(const DT &e);
    void removeFront();
    void removeBack();
    DT front();
    DT back();
};

template<typename DT>
Stack<DT>::Stack() {
    numberOfItems = 0;
}

template<typename DT>
void Stack<DT>::push(const DT &newDataItem) {
    stackList.insertBeginning(newDataItem);
    numberOfItems++;
}

template<typename DT>
DT Stack<DT>::pop() {
    DT return_val = stackList.getHead();
    stackList.deleteBeginning();
    numberOfItems--;
    return return_val;
}

template<typename DT>
bool Stack<DT>::isEmpty() {
    return numberOfItems == 0;
}

template<typename DT>
DT Stack<DT>::getTop() {//returns the top of the stack
    return stackList.getHead();
}

template<typename DT>
void Stack<DT>::addFront(const DT &e) {
    push(e);
}

template<typename DT>
void Stack<DT>::addBack(const DT &e) {
    Stack<DT> temp;
    while(!this->isEmpty()) {
        temp.push(this->pop());
    }
    this->push(e);
    while(!temp.isEmpty()) {
        this->push(temp.pop());
    }
}

template<typename DT>
DT Stack<DT>::front() {
    return getTop();
}

template<typename DT>
DT Stack<DT>::back() {
    Stack<DT> temp;
    while (!this->isEmpty()) {
        temp.push(pop());
    }
    DT top = temp.getTop();
    while(!temp.isEmpty()) {
        push(temp.pop());
    }
    return top;
}

template<typename DT>
void Stack<DT>::removeFront() {
    pop();
}

template<typename DT>
void Stack<DT>::removeBack() {
    Stack<DT> temp;
    while (!this->isEmpty()) {
        temp.push(this->pop());
    }
    temp.pop();
    while(!temp.isEmpty()) {
        this->push(temp.pop());
    }
}

template<typename DT>
class StackDeque {
    public:
    StackDeque();//constructor
    int size();//returns size of the deque
    bool empty();//checks if the deque is empty
    DT front();//gets the first element
    DT back();//gets the last element
    void insertFront(const DT &e);//inserts the value to the front of the deque
    void insertBack(const DT &e);//inserts the value to the back of the deque
    void removeFront();//removes the front element
    void removeBack();//removes the back element

    private://member data
    Stack<DT> D;//doubly linked list with deque elements
    int n;//number of elements in the deque
};

template<typename DT>
StackDeque<DT>::StackDeque() : D(), n(0) {}//different way to initialize the values () contain the initial value of the member

template<typename DT>
void StackDeque<DT>::insertFront(const DT &e) {
    D.addFront(e);
    n++;
}

template<typename DT>
void StackDeque<DT>::insertBack(const DT &e) {
    D.addBack(e);
    n++;
}

template<typename DT>
void StackDeque<DT>::removeFront() {
    if (empty()) cout << "Remove Front of empty deque" << endl;
    else {
        D.removeFront();
        n--;
    }
}

template<typename DT>
void StackDeque<DT>::removeBack() {
    if (empty()) cout << "Remove Back of empty deque" << endl;
    else {
        D.removeBack();
        n--;
    }
}

template<typename DT>
int StackDeque<DT>::size() {
    return n;//returns the number of elements
}

template<typename DT>
bool StackDeque<DT>::empty() {
    return n == 0;//returns true if n is 0
}

template<typename DT>
DT StackDeque<DT>::front() {
    if (empty()) {
        cout << "Front of empty deque";
        return 0;
    }
    return D.front();//returns the front value
}

template<typename DT>
DT StackDeque<DT>::back() {
    if (empty()) {
        cout << "Back of empty deque";
        return 0;
    }
    return D.back();//returns the back value
}

int main() {
    StackDeque<int> l;
    l.insertFront(10);
    l.insertFront(11);
    l.insertBack(12);
    cout << l.front() << endl;
    cout << l.back() << endl;

    l.removeBack();
    cout << l.back() << endl;

    l.removeFront();
    cout << l.front() << endl;
    cout << l.back() << endl;
}
