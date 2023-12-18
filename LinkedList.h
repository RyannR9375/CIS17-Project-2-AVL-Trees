#include <cstdlib>
#include <iostream>

using namespace std;

class LinkedList{
public:
    LinkedList() : head(nullptr) {}
    LinkedList(int size) : head(nullptr) {
        for(int i = 0; i < size; ++i)
            push_back(0);
    }

    //ADDS A VALUE TO THE FRONT OF THE LINKED-LIST
    void push_front(int value);

    //ADDS A VALUE TO THE BACK OF THE LINKED-LIST
    void push_back(int value);

    //REMOVES A VALUE FROM THE FRONT OF THE LINKED-LIST
    void pop_front();

    //REMOVES A VALUE FROM THE BACK OF THE LINKED-LIST
    void pop_back();

    //PRINTS THE LINKED-LIST
    void printList();
    
    //PRINTS COLLISIONS (FOR FINAL QUESTION 1)
    void printCollisions(int indexes);

    //DESTROYS THE LINKED-LIST
    void destroyList();
    
    //FIND THE SIZE OF THE LINKED-LIST
    int size();
    
    //FIND MAX AMT OF COLLISIONS
    int maxCollisons() { return m_maxCollisions; }

    //DESTRUCTOR
    ~LinkedList() {
        destroyList();
    }
    
    //OVERRIDES
    int &operator[](int indx) {
        if(indx > size()){
            cout << "Error. Index specificed is greater than linked list size.\n";
            return m_errorNum;
        }
        Node* current = head;
        for(int i = 0; i < indx; i++)
            current = current->next;
        
        return current->data;
    }
    
private:
    struct Node {
        int data;
        Node* next;
        Node* prev;
    };

    Node* head; // POINTER TO THE FIRST 'VALUE'/POINTER IN THE LINKED LIST
    
    int m_errorNum = -1;
    int m_maxCollisions{};
};