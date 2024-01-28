#include<iostream>

using namespace std;

class Node {
    public:
        int value;
        Node *next, *prev;

        Node (int value) {
            this->value = value;
            next = nullptr;
            prev = nullptr;
        }
};

class IntDLList {
    private:
        Node *head;
        Node *tail;
    public:
        IntDLList() {
            head = nullptr;
            tail = nullptr;
        }

        void addToHead(int value) {
            Node *newNode = new Node(value);
            head = newNode;
            tail = newNode;
        }

        void printList() {
            Node *curr = head;

            while(curr) {
                cout << curr->value << " ";
                curr = curr->next;
            }
        }

        void insertInOrder(int value) {
            Node *curr = head;
            tail = curr;

            if(!curr) {
                cout << "Please use insertToHead() to insert a head node first" << endl;
                return;
            }

            if(curr->value > value) {
                Node *newNode = new Node(value);
                newNode->next = head;
                head->prev = newNode;
                head = newNode;
                return;
            }

            while(curr) {
                if(curr->next) {
                    if(value > curr->value && value < curr->next->value) {
                        Node *newNode = new Node(value);
                        newNode->next = curr->next;
                        curr->next->prev = newNode;
                        curr->next = newNode;
                        newNode->prev = curr;
                        curr = curr->next;
                    }
                }

            tail = curr;
            curr = curr->next;

            }
            if(value > tail->value) {
                Node *newNode = new Node(value);
                tail->next = newNode;
                newNode->prev = tail;
                tail = newNode;
            }
        }

        void addToTail(int value) {
            Node *newNode = new Node(value);
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }

        int deleteFromHead() {
            // If the linked list is empty
            if(!head) throw runtime_error("Cannot delete from an empty list");

            int value = head->value;
            Node *temp = head;
            head = head->next;
            if(head) head->prev = nullptr;

            delete temp;

            return value;
        }

        int deleteFromTail() {
            // If the linked list is empty
            if(!head) throw runtime_error("Cannot delete from an empty list");

            int value = tail->value;
            Node *temp = tail;
            tail = tail->prev;
            if(tail) tail->next = nullptr;

            delete temp;

            return value;
        }

        void deleteNode(int value) {
            Node *curr = head;
            // Traverses the entire linked list.
            while(curr) {
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
                curr = curr->next;
            }
        }

};

int main() {
    IntDLList myList;
    myList.addToHead(8);
    myList.insertInOrder(3);
    myList.addToTail(9);
    myList.deleteNode(8);
    int value = myList.deleteFromTail();
    cout << "Value: " <<value << endl;
    myList.insertInOrder(5);
    myList.deleteFromHead();

    myList.printList();
}