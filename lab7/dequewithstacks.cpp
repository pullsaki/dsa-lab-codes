#include <iostream>

using namespace std;

// class DLinkedList;//declaring before so that it can be used as a friend class

// typedef int DataType;//element type
// class DNode {//Doubly Linked Node
//     private:
//     DataType elem;//data value in the node
//     DNode *prev;//prev node
//     DNode *next;//next node
//     friend class DLinkedList;//DLinkedList can access these private values
// };

// class DLinkedList {
//     public:
//     DLinkedList();//constructor
//     ~DLinkedList();//destructor
//     bool empty() const;//checks if the list is empty
//     const DataType &front() const;//gets the front element
//     const DataType &back() const;//gets the back element
//     void addFront(const DataType &e);//add to the front
//     void addBack(const DataType &e);//add to the back of the list
//     void removeFront();//removes the front element
//     void removeBack();//removes the back element
//     void listReverse();//reverses the list

//     private://list sentinels??? head and tail of the list
//     DNode *header;//header's next points to the first(front) element
//     DNode *trailer;//trailer's prev points to the last(back) element

//     protected:
//     void add(DNode *v, const DataType &e);//insert new node after v
//     void remove(DNode *v);//remove node v
// };

// DLinkedList::DLinkedList() {
//     header = new DNode;
//     trailer = new DNode;
//     header->next = trailer;//headers next points to trailer
//     trailer->prev = header;//trailers prev points to head
// }

// DLinkedList::~DLinkedList() {
//     while (!empty()) removeFront();//remove all the elements but the sentinels
//     delete header;//remove the header sentinel
//     delete trailer;//remove the trailer sentinel
// }

// bool DLinkedList::empty() const {
//     return (header->next == trailer);//if the headers next is the trailer then that means the list is empty
// }

// const DataType &DLinkedList::front() const {
//     return header->next->elem;//gets the value of the front node
// }

// const DataType &DLinkedList::back() const {
//     return trailer->prev->elem;//gets the value of the back node
// }

// void DLinkedList::add(DNode *v, const DataType &e) {
//     DNode *u = new DNode;//new node
//     u->elem = e;//add the value to the node
//     u->next = v->next;//connects the next pointer of u to v's next
//     u->prev = v;//connects u's prev to v
//     v->next->prev = u;//connects v's next's prev to u
//     v->next = u;//connects v's next to u... finally u is placed after v successfully
// }

// void DLinkedList::addFront(const DataType &e) {
//     add(header, e);//adds e after header... that means e will become the new front value
// }

// void DLinkedList::addBack(const DataType &e) {
//     add(trailer->prev, e);//adds e after trailer's prev... that means e will become the new back value
// }

// void DLinkedList::remove(DNode *v) {
//     DNode *u = v->prev;//u is now the v's prev node
//     DNode *w = v->next;//w is now the v's next node
//     u->next = w;//u's next is now w
//     w->prev = u;//w's prev is now u
//     delete v;//v is abandoned and finally removed
// }

// void DLinkedList::removeFront() {
//     remove(header->next);//removes header's next so front node is removed
// }

// void DLinkedList::removeBack() {
//     remove(trailer->prev);//removes trailer's prev so back node is removed
// }

// void DLinkedList::listReverse() {
//     DLinkedList T;//temporary list
//     while (!this->empty()) {//store list into T temporarily
//         int s = this->front();
//         this->removeFront();
//         T.addFront(s);
//     }
//     while (!T.empty()) {//store the values from T into the main list but in reverse order
//         int s = T.front();
//         T.removeFront();
//         this->addBack(s);
//     }
// }

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
