#include<iostream>
#include <string>

using namespace std;

class Node {
    public:
        int value;
        Node *next, *prev;

        Node (int value): value(value), next(nullptr), prev(nullptr) {}
};

class IntDLList {
    private:
        Node *head;
        Node *tail;
    public:
        IntDLList(): head(nullptr), tail(nullptr){}

        void addToHead(int value) {
            Node *newNode = new Node(value);
            newNode->next = head;
            newNode->prev = nullptr;

            //If the list is not empty
            if (head != nullptr){
                head->prev = newNode;
            }
            head = newNode;
        }

        void addToTail(int value) {
            Node *newNode = new Node(value);

            newNode->next = nullptr;

            if (head == nullptr){//If list is empty, newNode becomes the head 
                head = newNode;
                newNode->prev = nullptr;
                return; 
            }

            Node* current;
            for(current = head; current->next != nullptr; current = current->next);

            current->next = newNode;
            newNode->prev = current; 
        }

        void insertInOrder(int value) {
            Node *curr = head;

            if (!curr) {
                addToHead(value);
                return;
            }

            if (value < curr->value) {
                addToHead(value);
                return;
            }

            while (curr->next && value > curr->next->value) {
                curr = curr->next;
            }

            Node *newNode = new Node(value);
            newNode->next = curr->next;
            if (curr->next) {
                curr->next->prev = newNode;
            }
            newNode->prev = curr;
            curr->next = newNode;

            // Update tail if the new node is inserted at the end
            if (!newNode->next) {
                tail = newNode;
            }
        }

        int deleteFromHead(){// delete the head and return its info;
            if (head == nullptr){
                cerr << "List is empty. Cannot delete from an empty list." << endl;
                return -1;
            }
            int value = head->value;

            if(head -> next == nullptr){//Only one node in the list
                head = nullptr;
                tail = nullptr;
            }

            Node* temp = head;
            head = head->next;
            head->prev = nullptr; 

            delete temp;
            return value;
        } 

        int deleteFromTail(){// delete the tail and return its info;
            if (head == nullptr){
                cerr << "List is empty. Cannot delete from an empty list." << endl;
                return -1;
            }

            Node* curr;
            for (curr = head; curr->next != nullptr; curr = curr->next);

            if (head -> next == nullptr){//Only one node in the list 
                head = nullptr;
                tail = nullptr;
            }

            int value = curr->value;
            Node *temp = curr; 
            curr->prev->next = nullptr;

            delete temp;
            return value;
        } 

        void deleteNode(int value) {
            Node *curr;
            for(curr = head; curr->value; curr = curr->next){
                if(curr->value == value) {
                    // If the current node is in between two other nodes.
                    if(curr->prev && curr->next) {
                        curr->prev->next = curr->next;
                        curr->next->prev = curr->prev;
                    } else if(!curr->prev) { // The current node is the head of the linked list.
                        head = curr->next;
                        if(head) head->prev = nullptr;
                    } else { // The current node is the tail of the linked list.
                        tail = tail->prev;
                        if(tail) tail->next = nullptr;
                    }
                    delete curr;
                    return;
                }
            }
        }
        string addToString() const{
            string ordered_string;
            Node* curr = head;
            for( ;curr; curr = curr->next){
                ordered_string += to_string(curr->value);
            }
            return ordered_string;
        }

        void printList() {

            Node *curr;
            for (curr = head; curr; curr = curr->next){
                cout << curr->value;
            }
            cout << endl;
        }

        ~IntDLList(){
            Node *curr;
            for(curr = head; curr != nullptr;){
                Node *next = curr->next;
                delete curr;
                curr = next;
            }
            head = nullptr;
            tail = nullptr;
        }
};

int main() {
    IntDLList myList;
    myList.addToHead(8);
    myList.insertInOrder(3); // List: 3 8
    myList.addToTail(9); // List: 3 8 9
    myList.deleteNode(8); // List: 3 9
    myList.addToString(); //returns a string “3 9”
    myList.deleteFromTail();//List: 3 (returns 9)
    myList.insertInOrder(5); //List: 3 5
    myList.deleteFromHead();//List 5 (returns 3)

    myList.printList();
}
