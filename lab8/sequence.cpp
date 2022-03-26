#include <iostream>
#include <limits>

using namespace std;

typedef int Elem; //list base element type

class NodeList { //Doubly linked list
    private:
    struct Node { //nested struct for handling a Doubly Linked Node
        int elem; //element at the node
        Node *prev; //previous node
        Node *next; //next node
    };

    public:
    class Iterator { //nested class for handling iterator for the sequence
        Node *v; //pointer to node
        Iterator(Node *x); //creating iterator from node

        public:
        int &operator *(); //dereference operator to access data stored at that iterator
        bool operator == (const Iterator &p) const; //comparison operator to check if the iterators are pointing to the same object
        bool operator != (const Iterator &x) const; //not pointing to the same object
        Iterator &operator++(); //move to next position and return the reference to it
        // Iterator &operator++(int);
        Iterator &operator--(); //move to previous position and return the reference to it

        friend class NodeList; //node list can access the private members and create new operator
    };

    private:
    Node *header; //head of the list
    Node *trailer; //tail of the list
    int n; //number of nodes/items in the list

    public:
    NodeList(); //constructor
    // NodeList(NodeList &L);
    ~NodeList(); //destructor
    int size() const; //returns size of the list
    bool empty() const; //checks if the list is empty or not
    Iterator begin() const; //returns the beginning position
    Iterator end() const; //returns the position after last node
    // void operator=(NodeList &L);
    void insertFront(int value); //invoke insert(begin(), value)
    void insertBack(int value); //invoke insert(end(), value)
    void insert(const Iterator &p, int value); //insert element before position p
    void eraseFront(); //invoke erase(begin())
    void eraseBack(); //invoke erase(--end()) because end() points after the last node so we have to decrement it by 1 node
    void erase(const Iterator &p); //remove element at position p
    int getFront(); //returns the front element
    int getBack(); //returns the last element
};

int NodeList::getFront() {
    if (empty()) return INT_MIN;
    return header->next->elem; //returns the element at the next node of header (first node)
}

int NodeList::getBack() {
    if (empty()) return INT_MIN;
    return trailer->prev->elem; //returns the element at the prev node of trailer (last node)
}

NodeList::NodeList() { //constructor
    n = 0; //initializes number of nodes to 0
    header = new Node; //creates the header sentinel
    trailer = new Node; //creates the trailer sentinel
    header->next = trailer; //header points to trailer
    trailer->prev =  header; //trailer points to header essentially making the list empty
}

NodeList::~NodeList() {
    while(!empty()) { //loops until the list becomes empty
        eraseFront(); //erases the front element
    }
    delete header; //deletes the sentinels before ending
    delete trailer;
}

int NodeList::size() const {
    return n; //returns the number of nodes
}

bool NodeList::empty() const {
    return n == 0;
}

NodeList::Iterator NodeList::begin() const {
    return Iterator(header->next); //returns iterator to the first node
}

NodeList::Iterator NodeList::end() const {
    return Iterator(trailer); //returns iterator to the next of last node
}

NodeList::Iterator::Iterator(Node *u) { //constructor for the nested class of iterator
    v = u; //sets the node v(which the iterator points) to u
}

Elem &NodeList::Iterator::operator*() { //dereference operator
    return v->elem; //returns the element of the node pointed by the iterator
}

bool NodeList::Iterator::operator==(const Iterator &p) const {
    return v == p.v; //returns true if the node v is same as the node pointed by p
}

bool NodeList::Iterator::operator!=(const Iterator &p) const {
    return v != p.v; //returns true if the node v is not same as node pointed by p
}

NodeList::Iterator &NodeList::Iterator::operator++() {
    v = v->next; //iterator now points to the next node
    return *this; //returns the iterator
}

NodeList::Iterator &NodeList::Iterator::operator--() {
    v = v->prev; //now, the iterator points to the previous node
    return *this; //returns the iterator
}

void NodeList::insert(const Iterator &p, int value) { //insert a value before the position p
    Node *position = p.v; //pointer to node pointed by p
    Node *predecessor = position->prev; //points to p's previous node
    Node *newNode = new Node; //creating a new node for the new value
    newNode->elem = value; //storing the new value
    newNode->next = position; //new node's next points to position
    position->prev = newNode; //position's prev node now points to new node
    newNode->prev = predecessor; //new node's previous node is the position's old prev
    predecessor->next = newNode; //position's old previous node's next points to the new node
    n++; //increase the number of nodes by 1
}

void NodeList::insertFront(int value) {
    return insert(begin(), value); //inserts the value before begin() iterator
}

void NodeList::insertBack(int value) {
    return insert(end(), value); //inserts the value after the end() iterator
}

void NodeList::erase(const Iterator &p) { //erase the node at position p
    Node *oldNode = p.v; //storing the node at p
    Node *predecessor = oldNode->prev; //storing the prev node of p
    Node *sucessor = oldNode->next; //p's next node
    predecessor->next = sucessor; //p's prev node's next is now p's next
    sucessor->prev = predecessor; //p's next node's prev is now p's prev
    delete oldNode; //delete the node at p
    n--; //decrease the number of nodes by 1
}

void NodeList::eraseFront() {
    return erase(begin()); //erases the value at begin()
}

void NodeList::eraseBack() {
    return erase(--end()); //erases the value at node before end()
}