

using namespace std;

template <typename DT>
class SinglyLinkedNode {
    public://every node will have a data value and next pointer
    DT dataItem;//data value of the node
    SinglyLinkedNode<DT> *next;//points to the next node in the list

    //constructor
    SinglyLinkedNode(DT nodeValue, SinglyLinkedNode<DT> *nextpointer);
};

//constructor initializes the data value and next pointer
template <typename DT>
SinglyLinkedNode<DT>::SinglyLinkedNode(DT nodeValue, SinglyLinkedNode *nextpointer) {
    dataItem = nodeValue;
    next = nextpointer;
}

template <typename DT>
class SinglyLinkedList {
    //using protected because we want to inherit later
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

//initializes the attributes to NULL values
template <typename DT>
SinglyLinkedList<DT>::SinglyLinkedList() {
    head = NULL;
    cursor = NULL;
    numberOfItems = 0;
}

//inserts a node to the list
template <typename DT>
void SinglyLinkedList<DT>:: insert(const DT &newDataItem) {
    if (numberOfItems == 0) {//if the number of items are 0 then this node will be attached to the head pointer
        head = new SinglyLinkedNode<DT>(newDataItem, NULL) {
            cursor = head;
        }
    } else {//if not, the new node will be added next to the cursor
        SinglyLinkedNode<DT> *new_node = new SinglyLinkedNode<DT>(newDataItem, cursor->next);//next pointer of the node will point to cursors next to prevent loss of data
        cursor->next = new_node;//now, the cursor's next pointer will point to our new node
        cursor = cursor->next;//finally, the cursor moves to the newly added node
    }
    numberOfItems++;
}

//removes the node pointed by the cursor
template <typename DT>
void SinglyLinkedList<DT>::remove() {
    if (cursor == head) {//if cursor is head then this safely deletes the cursor item by shifting the head before
        head = head->next;//new head
        delete cursor;//cursor is deleted
        cursor = head;//cursor points to the new head
        numberOfItems--;//number of items reduced
        return;
    }
    
    SinglyLinkedNode<DT> *prev_node = head;//points to the node previous to the cursor
    while (prev_node->next != cursor) {
        prev_node = prev_node->next;
    }

    if (cursor->next == NULL) {//if the cursor is the last element
        prev_node->next = NULL;//prev node will have next pointer as null
        delete cursor;//delete the node at cursor
        cursor = head;//cursor will loop forward back to the head
    }

    else {//if the cursor is not the last element
        prev_node->next = cursor->next;//prev node will now have the next pointer as the cursor's next pointer
        delete cursor;
        cursor = prev_node->next;//cursor will now point to the next node
    }

    numberOfItems--;
}

template <typename DT>
void SinglyLinkedList<DT>::replace(const DT &newDataItem) {
    cursor->dataItem = newDataItem;//replace the cursor data item with new entered value
}

template <typename DT>
void SinglyLinkedList<DT>::clear() {
    cursor = head;//initializing at the first position
    while(cursor->next != NULL) {//iterates over the list
        SinglyLinkedNode<DT> *nextNode = cursor->next;//saving the next node before deleting
        delete cursor;//deleting the cursor node
        cursor = nextNode;//moving to the next node
    }

    //setting the attributes to default values;
    numberOfItems = 0;
    head = NULL;
    cursor = NULL;
}

int main() {

}