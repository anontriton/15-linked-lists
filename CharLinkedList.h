/*
 *  CharLinkedList.h
 *  Iverson Lai
 *  Oct 2 2023
 *
 *  CS 15 HW 2 Cheshire ConCATenation - Time to get linked up in Fur
 *
 *  This is the header file for a doubly linked list, it defines the
 *  CharLinkedList class a well as the Node struct and all the methods and data
 *  members associated with the class.
 *
 */

#ifndef CHAR_LINKED_LIST_H
#define CHAR_LINKED_LIST_H

#include <string>

class CharLinkedList {

public:

    // constructors
    CharLinkedList();
    CharLinkedList(char c);
    CharLinkedList(char arr[], int size);
    CharLinkedList(const CharLinkedList &other);

    // destructor
    ~CharLinkedList();

    // assignment operator
    CharLinkedList &operator=(const CharLinkedList &other);

    // methods
    bool isEmpty() const;
    void clear();
    int size() const;
    char first() const;
    char last() const;
    char elementAt(int index) const;
    std::string toString() const;
    std::string toReverseString() const;

    void pushAtBack(char c);
    void pushAtFront(char c);
    void insertAt(char c, int index);
    void insertInOrder(char c);
    void popFromFront();
    void popFromBack();
    void removeAt(int index);
    void replaceAt(char c, int index);
    void concatenate(CharLinkedList *other);

private:

    struct Node {
        char data;
        Node *prev;
        Node *next;
        // constructors
        Node() : data('\0'), prev(nullptr), next(nullptr) {}
        Node(char c) : data(c), prev(nullptr), next(nullptr) {}
    };

    // data members
    Node *front;
    Node *back;
    int numChars;

    // helper functions
    void destructorRecursive(Node *curr);
    char elementAtRecursive(Node *curr, int index) const;
    void replaceAtRecursive(Node *curr, char c, int index);
};

#endif
