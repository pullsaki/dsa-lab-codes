#include <iostream>

using namespace std;

class DLinkedList;//declaring before so that it can be used as a friend class

typedef int DataType;//element type
class DNode {//Doubly Linked Node
    private:
    DataType elem;//data value in the node
    DNode *prev;//prev node
    DNode *next;//next node
    friend class DLinkedList;//DLinkedList can access these private values
};

class DLinkedList {
    public:
    DLinkedList();//constructor
    ~DLinkedList();//destructor
    bool empty() const;//checks if the list is empty
    const DataType &front() const;//gets the front element
    const DataType &back() const;//gets the back element
    void addFront(const DataType &e);//add to the front
    void addBack(const DataType &e);//add to the back of the list
    void removeFront();//removes the front element
    void removeBack();//removes the back element
    void listReverse();//reverses the list

    private://list sentinels??? head and tail of the list
    DNode *header;//header's next points to the first(front) element
    DNode *trailer;//trailer's prev points to the last(back) element

    protected:
    void add(DNode *v, const DataType &e);//insert new node after v
    void remove(DNode *v);//remove node v
};

DLinkedList::DLinkedList() {
    header = new DNode;
    trailer = new DNode;
    header->next = trailer;//headers next points to trailer
    trailer->prev = header;//trailers prev points to head
}

DLinkedList::~DLinkedList() {
    while (!empty()) removeFront();//remove all the elements but the sentinels
    delete header;//remove the header sentinel
    delete trailer;//remove the trailer sentinel
}

bool DLinkedList::empty() const {
    return (header->next == trailer);//if the headers next is the trailer then that means the list is empty
}

const DataType &DLinkedList::front() const {
    return header->next->elem;//gets the value of the front node
}

const DataType &DLinkedList::back() const {
    return trailer->prev->elem;//gets the value of the back node
}

void DLinkedList::add(DNode *v, const DataType &e) {
    DNode *u = new DNode;//new node
    u->elem = e;//add the value to the node
    u->next = v->next;//connects the next pointer of u to v's next
    u->prev = v;//connects u's prev to v
    v->next->prev = u;//connects v's next's prev to u
    v->next = u;//connects v's next to u... finally u is placed after v successfully
}

void DLinkedList::addFront(const DataType &e) {
    add(header, e);//adds e after header... that means e will become the new front value
}

void DLinkedList::addBack(const DataType &e) {
    add(trailer->prev, e);//adds e after trailer's prev... that means e will become the new back value
}

void DLinkedList::remove(DNode *v) {
    DNode *u = v->prev;//u is now the v's prev node
    DNode *w = v->next;//w is now the v's next node
    u->next = w;//u's next is now w
    w->prev = u;//w's prev is now u
    delete v;//v is abandoned and finally removed
}

void DLinkedList::removeFront() {
    remove(header->next);//removes header's next so front node is removed
}

void DLinkedList::removeBack() {
    remove(trailer->prev);//removes trailer's prev so back node is removed
}

void DLinkedList::listReverse() {
    DLinkedList T;//temporary list
    while (!this->empty()) {//store list into T temporarily
        int s = this->front();
        this->removeFront();
        T.addFront(s);
    }
    while (!T.empty()) {//store the values from T into the main list but in reverse order
        int s = T.front();
        T.removeFront();
        this->addBack(s);
    }
}

typedef int DataType;
class LinkedDeque {
    public:
    LinkedDeque();//constructor
    int size() const;//returns size of the deque
    bool empty() const;//checks if the deque is empty
    const DataType &front();//gets the first element
    const DataType &back();//gets the last element
    void insertFront(const DataType &e);//inserts the value to the front of the deque
    void insertBack(const DataType &e);//inserts the value to the back of the deque
    void removeFront();//removes the front element
    void removeBack();//removes the back element

    private://member data
    DLinkedList D;//doubly linked list with deque elements
    int n;//number of elements in the deque
};

LinkedDeque::LinkedDeque() : D(), n(0) {}//different way to initialize the values () contain the initial value of the member

void LinkedDeque::insertFront(const DataType &e) {
    D.addFront(e);
    n++;
}

void LinkedDeque::insertBack(const DataType &e) {
    D.addBack(e);
    n++;
}

void LinkedDeque::removeFront() {
    if (empty()) cout << "Remove Front of empty deque" << endl;
    else {
        D.removeFront();
        n--;
    }
}

void LinkedDeque::removeBack() {
    if (empty()) cout << "Remove Back of empty deque" << endl;
    else {
        D.removeBack();
        n--;
    }
}

int LinkedDeque::size() const {
    return n;//returns the number of elements
}

bool LinkedDeque::empty() const {
    return n == 0;//returns true if n is 0
}

const DataType &LinkedDeque::front() {
    if (empty()) cout << "Front of empty deque" << endl;
    return D.front();//returns the front value
}

const DataType &LinkedDeque::back() {
    if (empty()) cout << "Back of empty deque" << endl;
    return D.back();//returns the back value
}

int main() {
    LinkedDeque d;
    d.insertFront(1);
    d.insertBack(10);
    d.insertFront(2);
    cout << "front: " << d.front() << endl;
    cout << "back: " << d.back() << endl;
    d.removeBack();
    cout << "back: " << d.back() << endl;
    d.removeFront();
    cout << "front: " << d.front() << endl;
    cout << "back: " << d.back() << endl;
}