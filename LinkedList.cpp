#include "LinkedList.h"
#include <iostream>

using namespace std;

//ADDS A VALUE TO THE FRONT OF THE LINKED-LIST
void LinkedList::push_front(int val) {
    Node* newNode = new Node; //INITIALIZE A NEW LINK* POINTER
    
    newNode->data = val; //SET THE DATA OF THE NEW POINTER TO THE VALUE YOU WISH TO PUSH TO THE FRONT OF THE LIST
    newNode->next = head; //STORE THE DATA OF THE NEXT POINTER TO THE CURRENT FIRST INDEX OF THE LIST
    head = newNode; //REPLACE THE CURRENT FIRST INDEX OF THE LIST TO THE LIST TO 'val'
}

//ADDS A VALUE TO THE BACK OF THE LINKED-LIST
void LinkedList::push_back(int val) {
    Node* newNode = new Node;
    newNode->data = val; 
    newNode->next = nullptr;

    if (!head) { //IF THERE IS NO HEAD,
        head = newNode; //THE NEW HEAD IS THE INDEX JUST CREATED
    } else { //IF THERE ALREADY IS A HEAD,
        Node* currentPointer = head; //INITIALIZE A NEW POINTER EQUAL TO THE FIRST INDEX OF THE LIST
        
        //FIND YOUR WAY TO THE END OF THE LIST,
        while (currentPointer->next) {
            currentPointer = currentPointer->next;
        }
        
        //SET THE LAST INDEX EQUAL TO THE INDEX JUST CREATED
        currentPointer->next = newNode;
    }
}

//REMOVES A VALUE FROM THE FRONT OF THE LINKED-LIST
void LinkedList::pop_front() {
    if (head) { //IF THE POINTER IS NOT NULL
        Node* temp = head; //INITIALIZE A NEW POINTER THAT TEMPORARILY STORES THE VALUE OF THE FIRST INDEX
        
        head = head->next; //SET THE FIRST INDEX EQUAL TO THE NEXT POINTER
        delete temp; //DELETE THE TEMPORARY POINTER
    }
    
    //return head->data; //RETURN THE VALUE OF THE FIRST INDEX
}

//REMOVES A VALUE FROM THE BACK OF THE LINKED-LIST
void LinkedList::pop_back() {
    //int lastValue = 0;
    if (head) { //IF THE POINTER IS NOT NULL
        if (!head->next) { //AND IF THE POINTERS NEXT LINK IS NULL
            delete head;
            head = nullptr; //SET THE NEW VALUE OF 'head' EQUAL TO A nullptr
        }
        else
        { //IF THE POINTER IS NULL 
            Node* currentPointer = head; //THE CURRENT POINTER WILL NOW EQUAL 'head'
            while (currentPointer->next && currentPointer->next->next) { //WHILE THESE POINTERS ARE NOT NULL
                currentPointer = currentPointer->next; //SET THE VALUE OF THE CURRENT POINTER EQUAL TO THE NEXT POINTER, SO WE CAN PUSH VALUES
                //lastValue = currentPointer->data; //STORE THE DATA OF THE LAST VALUE BEING REMOVED FROM THE LIST
            }
            delete currentPointer->next; //THEN WHEN THE NEXT LINK POINTER OF THE CURRENT POINTER BECOMES NULL, DELETE THE NEXT LINK POINTER
            currentPointer->next = nullptr; //THEN SET THE NEXT LINK POINTER OF THE CURRENT POINTER TO NULL
        }
    }
    
    //return lastValue; //RETURN THE VALUE OF THE LAST INDEX THAT WAS JUST REMOVED FROM THE LIST
}

//PRINTS THE LINKED-LIST
void LinkedList::printList() {
    if(size() == 0) return; //IF THERE'S NOTHING TO PRINT, RETURN
    Node* currentPtr = head;
    int indx = 0;
    
    while (currentPtr) { //WHILE THIS POINTER IS NOT NULL
        cout << currentPtr->data << "\n"; //OUTPUT THE DATA THIS POINTER HOLDS
        currentPtr = currentPtr->next; //THEN SET THE CURRENT POINTER EQUAL TO THE NEXT POINTER IN THE LIST
        indx++;
    }
    cout << "\n";
}

void LinkedList::printCollisions(int indexes){
    if(size() == 0) return;
    Node* currentPtr = head; //CREATE A CURRENT POINTER
    int indx{};
    
    bool streak = true;
    while (indx != indexes) { //WHILE THIS POINTER IS NOT NULL
        cout << "Linked List size " << indx << ": " << currentPtr->data << "\n"; //OUTPUT
        
        //COUNT MAX # COLLISIONS
        if(currentPtr->data != 0 && streak)
            streak = true;
        else
            streak = false;
        
        if(streak)
            m_maxCollisions++;
        
        currentPtr = currentPtr->next; //KEEP ITERATING
        indx++;
    }
    
    cout << "Maximum number of collisions: " << m_maxCollisions;
    cout << "\n";
}

//DESTROYS THE LINKED-LIST
void LinkedList::destroyList() {
    while (head) { //WHILE THE FIRST INDEX OF THE POINTER IS NOT NULL
        pop_front(); //CONTINUE TO DELETE INDEXES FROM THE ARRAY
    }
}

int LinkedList::size(){
    Node* currentPtr = head;
    int sum = 1;
        
    while(currentPtr->next) { 
        ++sum;
        
        currentPtr = currentPtr->next;
    }
    return sum;
}
