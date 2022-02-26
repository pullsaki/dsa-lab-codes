#include <iostream>

using namespace std;

template <typename DT>
class SinglyLinkedNode {
    public:
    DT dataItem;
    SinglyLinkedNode<DT> *next;

    //constructor
    SinglyLinkedNode(DT nodeValue, SinglyLinkedNode<DT> *nextpointer);
};

template <typename DT>
SinglyLinkedNode<DT>::SinglyLinkedNode(DT nodeValue, SinglyLinkedNode<DT> *nextpointer) {
    dataItem = nodeValue;
    next = nextpointer;
}

template <typename DT>
class SinglyLinkedList {
    protected:
    SinglyLinkedNode<DT> *head;
    SinglyLinkedNode<DT> *cursor;
    int numberOfItems;

    public:
    SinglyLinkedList();

    void insert(const DT &newDataItem);
    void remove();
    void replace(const DT &newDataItem);
    void clear();
    bool isEmpty();
    void gotoBeginning();
    void gotoEnd();
    bool gotoNext();
    bool gotoPrior();
    DT getCursor();
    void showStructure();
};

template <typename DT>
SinglyLinkedList<DT>::SinglyLinkedList() {
    head = NULL;
    cursor = NULL;
    numberOfItems = 0;
}

template <typename DT>
void SinglyLinkedList<DT>::insert(const DT &newDataItem) {
    if (numberOfItems) {
        SinglyLinkedNode<DT> *new_node = new SinglyLinkedNode<DT>(newDataItem, cursor->next);
        cursor->next = new_node;
        cursor = cursor->next;
    } else {
        head = new SinglyLinkedNode<DT>(newDataItem, NULL);
        cursor = head;
    }
    numberOfItems++;
}

template <typename DT>
void SinglyLinkedList<DT>::remove() {
    if (cursor == head) {
        head = head->next;
        delete cursor;
        cursor = head;
        numberOfItems--;
        return;
    }

    SinglyLinkedNode<DT> *prev_node = head;
    while (prev_node->next != cursor) {
        prev_node = prev_node->next;
    }

    if (cursor->next == NULL) {
        prev_node->next = NULL;
        delete cursor;
        cursor = head;
    } else {
        prev_node->next = cursor->next;
        delete cursor;
        cursor = prev_node->next;
    }

    numberOfItems--;
}

template <typename DT>
void SinglyLinkedList<DT>::replace(const DT &newDataItem) {
    cursor->dataItem = newDataItem;
}

template <typename DT>
void SinglyLinkedList<DT>::clear() {
    cursor = head;
    while (cursor->next != NULL) {
        SinglyLinkedNode<DT> *nextNode = cursor->next;
        delete cursor;
        cursor = nextNode;
    }

    numberOfItems = 0;
    head = NULL;
    cursor = NULL;
}

template <typename DT>
bool SinglyLinkedList<DT>::isEmpty() {
    return numberOfItems == 0;
}

template <typename DT>
void SinglyLinkedList<DT>::gotoBeginning() {
    cursor = head;
}

template <typename DT>
void SinglyLinkedList<DT>::gotoEnd() {
    while (cursor->next != NULL) cursor = cursor->next;
}

template <typename DT>
bool SinglyLinkedList<DT>::gotoNext() {
    if (cursor->next == NULL) return false;
    else {
        cursor = cursor->next;
        return true;
    }
}

template <typename DT>
bool SinglyLinkedList<DT>::gotoPrior() {
    if (cursor == head) return false;
    else {
        SinglyLinkedNode<DT> *prev_node = head;
        while (prev_node->next != cursor) prev_node = prev_node->next;
        cursor = prev_node;
        return true;
    }
}

template <typename DT>
DT SinglyLinkedList<DT>::getCursor() {
    return cursor->dataItem;
}

template <typename DT>
void SinglyLinkedList<DT>::showStructure() {
    if (!numberOfItems) {
        cout << "Empty List" << endl;
        return;
    }

    SinglyLinkedNode<DT> *temp_node = head;
    while (temp_node != NULL) {
        cout << temp_node->dataItem << " ";
        temp_node = temp_node->next;
    }
    cout << endl;
}


template <typename DT>
class DoublyLinkedNode : public SinglyLinkedNode<DT> {
    public:
    DoublyLinkedNode<DT> *next;
    DoublyLinkedNode<DT> *prev;
    using SinglyLinkedNode<DT>::dataItem;

    //constructor
    DoublyLinkedNode(DT nodeValue, DoublyLinkedNode<DT> *nextPointer, DoublyLinkedNode<DT> *prevPointer);
};

template <typename DT>
DoublyLinkedNode<DT>::DoublyLinkedNode(DT nodeValue, DoublyLinkedNode<DT> *nextPointer, DoublyLinkedNode<DT> *prevPointer) : SinglyLinkedNode<DT>(nodeValue, nextPointer) {
    next = nextPointer;
    prev = prevPointer;
}

template <typename DT>
class DoublyLinkedList : public SinglyLinkedList<DT> {
    private:
    DoublyLinkedNode<DT> *head;
    DoublyLinkedNode<DT> *cursor;
    using SinglyLinkedList<DT>::numberOfItems;

    public:
    //constructor
    DoublyLinkedList();

    void insert(const DT &newDataItem);
    DT getCursor();
    bool isEmpty();
    void clear();
    void remove();
    void replace(const DT &newDataItem);
    void gotoBeginning();
    void gotoEnd();
    bool gotoNext();
    bool gotoPrior();
    void showStructure();
};

template <typename DT>
DoublyLinkedList<DT>::DoublyLinkedList() : SinglyLinkedList<DT>() {
    head = NULL;
    cursor = NULL;
}

template <typename DT>
void DoublyLinkedList<DT>::insert(const DT &newDataItem) {
    if (!numberOfItems) {
        head = new DoublyLinkedNode<DT>(newDataItem, NULL, NULL);
        cursor = head;
    } else {
        DoublyLinkedNode<DT> *new_node = new DoublyLinkedNode<DT>(newDataItem, cursor->next, cursor);
        cursor->next = new_node;
        cursor = cursor->next;
    }

    numberOfItems++;
}

template <typename DT>
DT DoublyLinkedList<DT>::getCursor() {
    return cursor->dataItem;
}

template <typename DT>
bool DoublyLinkedList<DT>::isEmpty() {
    return numberOfItems == 0;
}

template <typename DT>
void DoublyLinkedList<DT>::remove() {
    if (cursor == head) {
        head = head->next;
        delete cursor;
        cursor = head;
        numberOfItems--;
        return;
    }

    DoublyLinkedNode<DT> *prev_node = cursor->prev;

    if (cursor->next == NULL) {
        prev_node->next = NULL;
        delete cursor;
        cursor = head;
    } else {
        prev_node->next = cursor->next;
        delete cursor;
        cursor = prev_node->next;
    }

    numberOfItems--;
}

template <typename DT>
void DoublyLinkedList<DT>::clear() {
    cursor = head;
    while (cursor->next != NULL) {
        DoublyLinkedNode<DT> *nextNode = cursor->next;
        delete cursor;
        cursor = nextNode;
    }

    numberOfItems = 0;
    head = NULL;
    cursor = NULL;
}

template <typename DT>
void DoublyLinkedList<DT>::replace(const DT &newDataItem) {
    cursor->dataItem = newDataItem;
}

template <typename DT>
void DoublyLinkedList<DT>::gotoBeginning() {
    cursor = head;
}

template <typename DT>
void DoublyLinkedList<DT>::gotoEnd() {
    while (cursor->next != NULL) cursor = cursor->next;
}

template <typename DT>
bool DoublyLinkedList<DT>::gotoNext() {
    if (cursor->next == NULL) return false;
    else {
        cursor = cursor->next;
        return true;
    }
}

template <typename DT>
bool DoublyLinkedList<DT>::gotoPrior() {
    if (cursor == head) return false;
    else {
        cursor = cursor->prev;
        return true;
    }
}

template <typename DT>
void DoublyLinkedList<DT>::showStructure() {
    if (!numberOfItems) {
        cout << "Empty List" << endl;
        return;
    }

    DoublyLinkedNode<DT> *temp_node = head;
    while (temp_node != NULL) {
        cout << temp_node->dataItem << " ";
        temp_node = temp_node->next;
    }
    cout << endl;
}

int main() {
    DoublyLinkedList<int> list;
    list.insert(1);
    list.insert(2);
    list.insert(3);
    list.insert(4);
    list.insert(5);
    list.insert(6);
    list.showStructure();
    list.remove();
    list.gotoNext();
    list.gotoNext();
    list.showStructure();
    list.replace(10);
    list.showStructure();
    list.gotoBeginning();
    std::cout << list.getCursor() << std::endl;
    list.gotoEnd();
    std::cout << list.getCursor() << std::endl;
    list.gotoPrior();
    list.gotoPrior();
    std::cout << list.getCursor() << std::endl;
    list.gotoNext();
    std::cout << list.getCursor() << std::endl;
    list.clear();
    if (list.isEmpty()) std::cout << "List is empty\n";
}