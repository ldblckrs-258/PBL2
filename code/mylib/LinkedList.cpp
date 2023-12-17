#ifndef LINKEDLIST
#define LINKEDLIST

#include <iostream>
template <typename T>
class Node
{
public:
    T data;
    Node *next;
    Node(const T &newData) : data(newData), next(nullptr) {}
};

inline std::string clearStr(const std::string &str)
{
    std::string result;
    for (char c : str)
    {
        if (std::isprint(static_cast<unsigned char>(c)))
        {
            result += c;
        }
    }
    return result;
}

inline std::string toLowerCase(const std::string &str)
{
    std::string result = clearStr(str);
    for (char &c : result)
    {
        if ('A' <= c && c <= 'Z')
        {
            c += 32;
        }
    }
    return result;
}

template <typename T>
class LinkedList
{
private:
    Node<T> *head;
    int size;

public:
    LinkedList() : head(nullptr), size(0) {}

    ~LinkedList()
    {
        clear();
    }

    void push_back(const T &value)
    {
        Node<T> *newNode = new Node<T>(value);
        if (!head)
        {
            head = newNode;
        }
        else
        {
            Node<T> *temp = head;
            while (temp->next)
            {
                temp = temp->next;
            }
            temp->next = newNode;
        }
        ++size;
    }

    void print() const
    {
        Node<T> *temp = head;
        while (temp)
        {
            std::cout << temp->data << "\n";
            temp = temp->next;
        }
        std::cout << std::endl;
    }

    void clear()
    {
        while (head)
        {
            Node<T> *temp = head;
            head = head->next;
            delete temp;
        }
        size = 0;
    }

    T &operator[](int index)
    {
        int currentIndex = 0;
        Node<T> *temp = head;
        while (temp)
        {
            if (currentIndex == index)
            {
                return temp->data;
            }
            temp = temp->next;
            ++currentIndex;
        }

        throw std::out_of_range("Index out of range : " + std::to_string(index) + "/" + std::to_string(size - 1));
    }

    int getSize() const
    {
        return size;
    }

    Node<T> *begin() const
    {
        return head;
    }

    Node<T> *end() const
    {
        if (!head)
        {
            return nullptr;
        }
        Node<T> *current = head;
        while (current->next)
            current = current->next;
        return current;
    }

    void remove(int index)
    {
        if (index < 0 || !head || index >= size)
        {
            return;
        }
        if (index == 0)
        {
            Node<T> *temp = head;
            head = head->next;
            delete temp;
            --size;
            return;
        }
        Node<T> *current = head;
        Node<T> *previous = nullptr;
        for (int i = 0; i < index && current; ++i)
        {
            previous = current;
            current = current->next;
        }
        if (!current)
        {
            return;
        }
        previous->next = current->next;
        delete current;
        --size;
    }

    template <typename MemberFunction>
    int search(const std::string &str, MemberFunction func) const
    {
        std::string value = toLowerCase(str);
        Node<T> *temp = head;
        int index = 0;
        while (temp)
        {
            if (toLowerCase((temp->data.*func)()) == value)
            {
                return index;
            }
            temp = temp->next;
            ++index;
        }
        return -1;
    }
};

#endif