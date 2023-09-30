#pragma once
#include <string>
using namespace std;

template <typename T, typename P>
class LinkedList {
    private:
        struct Node {
            T data1;
            P data2;
            Node* next;
            Node(const T& data1, const P& data2) : data1(data1), data2(data2), next(nullptr) {}
        };
        Node* head;

    public:
        LinkedList() : head(nullptr) {}

        ~LinkedList() {
            while (head) {
                Node* temp = head;
                head = head->next;
                delete temp;
            }
        }

        void append(const T& data) {
            if (!head) {
                head = new Node(data);
            } else {
                Node* current = head;
                while (current->next) {
                    current = current->next;
                }
                current->next = new Node(data);
            }
        }

        void remove(const T& value) {
            Node* current = head;
            Node* prev = nullptr;
            
            while (current) {
                if (current->data == value) {
                    if (prev) {
                        prev->next = current->next;
                    } else {
                        head = current->next;
                    }
                    delete current;
                    return; 
                }
                
                prev = current;
                current = current->next;
            }
        }

        void removeLast() {
            if (!head) {
                return; 
            }
            if (!head->next) {
                delete head;
                head = nullptr;
                return; 
            }
            Node* current = head;
            Node* prev = nullptr;
            while (current->next) {
                prev = current;
                current = current->next;
            }
            delete current;
            prev->next = nullptr;
        }

        void clear() {
            while (head) {
                Node* temp = head;
                head = head->next;
                delete temp;
            }
        }

        void display() {
            Node* current = head;
            while (current) {
                cout << current->data << " ";
                current = current->next;
            }
            cout << endl;
        }
};
