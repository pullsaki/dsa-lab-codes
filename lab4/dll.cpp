#include<iostream>
#include<vector>
#include<string>
using namespace std;

template<typename DT>
class SinglyLinkedNode{
    public:
    DT dataitem;
    SinglyLinkedNode<DT> *next;
    SinglyLinkedNode(DT nodevalue, SinglyLinkedNode<DT> *nextpointer);
};

template<typename DT>
SinglyLinkedNode<DT>::SinglyLinkedNode(DT nodevalue, SinglyLinkedNode<DT> *nextpointer)
{
    dataitem = nodevalue;
    next = nextpointer;
}

template<typename DT>
class SinglyLinkedList{
    protected:
    SinglyLinkedNode<DT> *head;
    SinglyLinkedNode<DT> *cursor;
    int numberofitems;


    public:
    SinglyLinkedList();
    void insert(const DT &newdataitem);
    void remove();
    void replace(const DT &newdataitem);
    void clear();
    bool isempty();
    void gotobeginning();
    void gotoend();
    bool gotonext();
    bool gotoprior();
    DT getcursor();
    void showstructure();
};

template<typename DT>
SinglyLinkedList<DT>::SinglyLinkedList(){
    head = NULL;
    cursor = NULL;
    numberofitems = 0;
}
template<typename DT>
void SinglyLinkedList<DT>::insert(const DT &newdataitem){
    if(numberofitems == 0){
        head = new SinglyLinkedNode<DT>(newdataitem, NULL);
        cursor = head;
    }
else{
    SinglyLinkedNode<DT> *new_node = SinglyLinkedNode<DT>(newdataitem, cursor->next);
    cursor->next = new_node;
    cursor = cursor->next;
}
numberofitems++;
}

template<typename DT>
void SinglyLinkedList<DT>::remove(){
    if(cursor==head){
        head = head->next;
        delete cursor;
        cursor = head;
        numberofitems--;
        return;
    }
    SinglyLinkedNode<DT> *prev_node =head;
    while(prev_node->next != cursor){
        prev_node = prev_node->next;
    }
    if(cursor->next == NULL){
        prev_node->next = NULL;
        delete cursor;
        cursor = head;
    }
    else{
        prev_node->next = cursor->next;
        delete cursor;
        cursor = prev_node->next;
    }
numberofitems--;
}

template<typename DT>
void SinglyLinkedList<DT>::replace(const DT &newdataitem){
    cursor->dataitem = newdataitem;
}

template<typename DT>
void SinglyLinkedList<DT>::clear() {
    cursor = head;
while(cursor->next!=NULL) {
    SinglyLinkedNode<DT> *nextNode = cursor->next;
    delete cursor;
    cursor = nextNode;
}
numberofitems = 0;
head = NULL;
cursor = NULL;
}

template<typename DT>
bool SinglyLinkedList<DT>::isempty(){
    return numberofitems==0;
}

template<typename DT>
void SinglyLinkedList<DT>::gotobeginning(){
    cursor = head;
}

template<typename DT>
void SinglyLinkedList<DT>::gotoend(){
    while(cursor->next!=NULL){
        cursor = cursor->next;
    }
}

template<typename DT>
bool SinglyLinkedList<DT>::gotonext(){
    if(numberofitems==0){
        return false;
    }
    else{
        cursor = cursor->next;
        return true;
    }
}

template<typename DT>
bool SinglyLinkedList<DT>::gotoprior(){
    if(cursor == head){
        return false;
    }
    else{
        SinglyLinkedNode<DT> *prev_node = head;
        while(prev_node->next!=cursor){
            prev_node = prev_node->next;
            cursor = prev_node;
            return true;
        }
    }
}

template<typename DT>
DT SinglyLinkedList<DT>::getcursor(){
    return cursor->dataitem;
}

template<typename DT>
void SinglyLinkedList<DT>::showstructure(){
    if(numberofitems==0){
        cout << "List is empty" << endl;
        return;
    }
    else{
        SinglyLinkedNode<DT> *temp_node = head;
        while(temp_node!=NULL){
            cout << temp_node->dataitem << " ";
            temp_node = temp_node->next;
        }
}
}

template<typename DT>
class DoublyLinkedNode:public SinglyLinkedNode<DT>{
    public:
    DoublyLinkedNode<DT> *next;
    DoublyLinkedNode<DT> *prev;
    using SinglyLinkedNode<DT>::dataitem;

    DoublyLinkedNode(DT nodeValue, DoublyLinkedNode<DT> *nextPointer, DoublyLinkedNode<DT> *prevPointer);
};

template<typename DT>
DoublyLinkedNode<DT>::DoublyLinkedNode(DT nodeValue, DoublyLinkedNode<DT> *nextPointer, DoublyLinkedNode<DT> *prevPointer):SinglyLinkedNode<DT>(nodeValue, nextPointer){
    next = nextPointer;
    prev = prevPointer;
}

template<typename DT>
class DoublyLinkedList:public SinglyLinkedList<DT>{

    public:
    DoublyLinkedNode<DT> *head;
    DoublyLinkedNode<DT> *cursor;
    using SinglyLinkedList<DT>::numberofitems;

    public:
    DoublyLinkedList();
    void insert(const DT &newdataitem);
    DT getcursor();
    bool isempty();
    void clear();
    void remove();
    void replace(const DT &newdataitem);
    bool gotoprior();
    void showstructure();
    void gotobeginning();
    void gotoend();
    bool gotonext();

};

template<typename DT>
DoublyLinkedList<DT>::DoublyLinkedList():SinglyLinkedList<DT>(){
    head = NULL;
    cursor = NULL;
}

template<typename DT>
void DoublyLinkedList<DT>::insert(const DT &newdataitem){
    if(numberofitems==0){
        head = new DoublyLinkedNode<DT>(newdataitem, NULL, NULL);
        cursor = head;
    }
    else{
        DoublyLinkedNode<DT> *new_node = new DoublyLinkedNode<DT>(newdataitem, cursor->next, cursor->prev);
        if(cursor->prev!=NULL){
        cursor->prev->next = new_node;
        }
        if(cursor->next != NULL){
        cursor->next->prev = new_node;
        }
        cursor->next = new_node;
        cursor = cursor->next;
    }
numberofitems++;
}

template<typename DT>
void DoublyLinkedList<DT>::remove(){
    if(cursor==head){
        head = head->next;
        delete cursor;
        cursor = head;
        numberofitems--;
        return;
    }
    if(cursor->next == NULL){
        cursor->prev->next = NULL;
        delete cursor;
        cursor = head;
    }
    else{
        cursor->prev->next = cursor->next;
        cursor->next->prev = cursor->prev;
        delete cursor;
        cursor = cursor->prev->next;
    }
}

template<typename DT>
void DoublyLinkedList<DT>::replace(const DT &newdataitem){
    cursor->dataitem = newdataitem;
}

template<typename DT>
DT DoublyLinkedList<DT>::getcursor(){
    return cursor->dataitem;
}

template<typename DT>
bool DoublyLinkedList<DT>::isempty(){
    return numberofitems==0;
}

template<typename DT>
bool DoublyLinkedList<DT>::gotoprior(){
    if(cursor == head){
        return false;
    }
    else{
        cursor = cursor->prev;
        return true;
    }
}

template<typename DT>
bool DoublyLinkedList<DT>::gotonext(){
    if(numberofitems==0){
        return false;
    }
    else{
        cursor = cursor->next;
        return true;
    }
}

template<typename DT>
void DoublyLinkedList<DT>::gotobeginning(){
    cursor = head;
}

template<typename DT>
void DoublyLinkedList<DT>::gotoend(){
    while(cursor->next!=NULL){
        cursor = cursor->next;
    }
}

template<typename DT>
void DoublyLinkedList<DT>::showstructure(){
    if(numberofitems==0){
        cout << "List is empty" << endl;
        return;
    }
    else{
        DoublyLinkedNode<DT> *temp_node = head;
        while(temp_node!=NULL){
            cout << temp_node->dataitem << " ";
            temp_node = temp_node->next;
        }
        cout << endl;
}
}

int main(){
    DoublyLinkedList<int> list;
    list.insert(1);
    list.insert(2);
    list.insert(3);
    list.insert(4);
    list.insert(5);
    list.insert(6);
    list.remove();
    list.gotonext();
list.gotonext();
list.showstructure();
list.replace(10);
list.showstructure();
list.gotobeginning();
cout<<list.getcursor()<<endl;
list.gotoend();
cout<<list.getcursor()<<endl;
list.gotoprior();
list.gotoprior();
cout<<list.getcursor()<<endl;
list.gotonext();
list.gotonext();
cout<<list.getcursor()<<endl;

}