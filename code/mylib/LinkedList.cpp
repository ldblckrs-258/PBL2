#pragma once
#include <iostream>
template <typename T>
class Node {
    public:
        T data;
        Node* next;
        Node(const T& newData) : data(newData), next(nullptr) {}
};

inline std::string clearStr(const std::string& str) {
    std::string result;
    for (char c : str) {
        if (std::isprint(static_cast<unsigned char>(c))) {
            result += c;
        }
    }
    return result;
}

template <typename T>
class LinkedList {
    private:
        Node<T>* head;
        int size;
    public:

        LinkedList() : head(nullptr), size(0) {}

        ~LinkedList() {
            clear();
        }

        void push_back(const T& value) {
            Node<T>* newNode = new Node<T>(value);
            if (!head) {
                head = newNode;
            } else {
                Node<T>* temp = head;
                while (temp->next) {
                    temp = temp->next;
                }
                temp->next = newNode;
            }
            ++size;
        }

        void print() const {
            Node<T>* temp = head;
            while (temp) {
                std::cout << temp->data << " ";
                temp = temp->next;
            }
            std::cout << std::endl;
        }

        void clear() {
            while (head) {
                Node<T>* temp = head;
                head = head->next;
                delete temp;
            }
            size = 0;
        }

        void removeFront() {
            if (head) {
                Node<T>* temp = head;
                head = head->next;
                delete temp;
                --size;
            }
        }

        void removeBack() {
            if (!head) {
                return;
            }

            if (!head->next) {
                delete head;
                head = nullptr;
            } else {
                Node<T>* temp = head;
                while (temp->next->next) {
                    temp = temp->next;
                }
                delete temp->next;
                temp->next = nullptr;
            }
            --size;
        }

        T& operator[](int index) {
            int currentIndex = 0;
            Node<T>* temp = head;
            while (temp) {
                if (currentIndex == index) {
                    return temp->data;
                }
                temp = temp->next;
                ++currentIndex;
            }

            throw std::out_of_range("Index out of range");
        }

        int getSize() const {
            return size;
        }

        Node<T>*begin() const {
            return head;
        }

        using FuncName = std::string (T::*)() const;
        int search(const std::string& str, FuncName funcName) const {
            Node<T>* temp = head;
            int index = 0;
            while (temp) {
                if (clearStr((temp->data.*funcName)()) == clearStr(str)) {
                    return index;
                }
                temp = temp->next;
                ++index;
            }
            return -1;
        }
};