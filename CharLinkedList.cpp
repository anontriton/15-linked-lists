/*
 *  CharLinkedList.cpp
 *  Iverson Lai
 *  10/2/23
 *
 *  CS 15 HW 2 Cheshire ConCATenation - Time to get linked up in Fur
 *
 *  This is an implementation file for a doubly linked list data structure
 *
 */

#include "CharLinkedList.h"
#include <sstream>
#include <stdexcept>

/*
 * name:      CharLinkedList default constructor
 * purpose:   initialize an empty CharLinkedList
 * arguments: none
 * returns:   none
 * effects:   initializes the front pointer to nullptr and sets numChars to
 *            0 since list is empty
 */
CharLinkedList::CharLinkedList() {
    front = nullptr;
    back = nullptr;
    numChars = 0;
}

/*
 * name:      CharLinkedList single argument constructor
 * purpose:   initializes a CharLinkedList with one element
 * arguments: char to instantiate into linked list
 * returns:   none
 * effects:   initializes a node with char c and points to nullptr both ways.
 *            Also initializes front pointer to point to the node.
 *            numChars sets to one element.
 */
CharLinkedList::CharLinkedList(char c) {
    Node *newNode = new Node;

    newNode->data = c;
    newNode->prev = nullptr;
    newNode->next = nullptr;

    front = newNode;
    back = newNode;
    numChars = 1;
}

/*
 * name:      CharLinkedList multi-argument constructor
 * purpose:   initializes a CharLinkedList with several elements, specified by
 *            the parameters
 * arguments: array of chars to instantiate into linked list and size of list
 * returns:   none
 * effects:   sets size to the number of elements in the list and initalizes
 *            a linked list with the elements in the passed array
 */
CharLinkedList::CharLinkedList(char arr[], int size) {
    front = nullptr;
    back = nullptr;
    numChars = size;
    Node *curr = nullptr; // keep track of index while iterating
    
    for (int i = 0; i < size; ++i) {
        Node *newNode = new Node(arr[i]);

        if (front == nullptr) {
            // while empty, front points to newNode and newNode points to null
            front = newNode;
            back = newNode;
            newNode->prev = nullptr;
            newNode->next = nullptr;
            curr = newNode;
        } else {
            // when not empty, add newNode to the end of the list
            curr->next = newNode;
            newNode->prev = curr;
            newNode->next = nullptr;
            curr = newNode;
            back = newNode;
        }
    }
}

/*
 * name:      CharLinkedList copy constructor
 * purpose:   deep copies a given instance
 * arguments: another CharLinkedList
 * returns:   none
 * effects:   creates new instance of a linked list with its own independent
              copy of the data in the linked list passed as the argument
 */
CharLinkedList::CharLinkedList(const CharLinkedList &other) {
    numChars = other.numChars;
    
    if (other.front == nullptr) { // check if other list is empty
        front = nullptr;
        back = nullptr;
    } else {
        // initialize new node for first elem in list to be deep copied
        front = new Node(other.front->data);
        back = front;

        Node *newNode = front;
        Node *otherNode = other.front->next;

        // iterate through other list and deep copy to new nodes
        while (otherNode != nullptr) {
            newNode->next = new Node(otherNode->data);

            newNode->next->prev = newNode; // access prev ptr of next node

            newNode = newNode->next;
            otherNode = otherNode->next;
            back = newNode;
        }
    }
}

/*
 * name:      destructorResursive()
 * purpose:   recursively iterates through linked list and deletes the nodes
 * arguments: node pointer to current node
 * returns:   none
 * effects:   none
 */
void CharLinkedList::destructorRecursive(Node *curr) {
    // check if current node is empty
    if (curr == nullptr) {
        return;
    }

    Node *next = curr->next;
    delete curr;
    // recursively call function to next node
    CharLinkedList::destructorRecursive(next);
}

/*
 * name:      CharLinkedList destructor
 * purpose:   clears memory on the heap
 * arguments: none
 * returns:   none
 * effects:   resets front and back pointers and updates numChars to 0
 */
CharLinkedList::~CharLinkedList() {
    CharLinkedList::destructorRecursive(front);
    
    /* not recursive
    Node *curr = front;
    while (curr != nullptr) {
        Node *next = curr->next;
        delete curr;
        curr = next;
    }
    */

    // ensure front and back are nullptr to avoid memory leaks
    front = nullptr;
    back = nullptr;
    numChars = 0; // update size
}

/*
 * name:      CharLinkedList assignment operator
 * purpose:   deep copies RHS into LHS and recycles the proper memory
 * arguments: other CharLinkedList
 * returns:   this object
 * effects:   recycles memory on the heap, updates numChars
 */
CharLinkedList &CharLinkedList::operator=(const CharLinkedList &other) {
    // return this if the object being assigned is the same
    if (this == &other) {
        return *this;
    }
    
    // delete current instance to have the memory be recycled
    Node *curr = front;
    while (curr != nullptr) {
        Node *next = curr->next;
        delete curr;
        curr = next;
    }

    // initialize new node for first elem in list to be deep copied
    front = new Node(other.front->data);
    back = front;

    Node *newNode = front;
    Node *otherNode = other.front->next;

    // iterate through other list and deep copy to new nodes
    while (otherNode != nullptr) {
        newNode->next = new Node(otherNode->data);

        newNode->next->prev = newNode; // access prev ptr of next node

        newNode = newNode->next;
        otherNode = otherNode->next;
        back = newNode;
    }

    this->numChars = other.numChars;

    return *this;
}


/*
 * name:      isEmpty()
 * purpose:   checks if the list is empty
 * arguments: none
 * returns:   boolean value
 * effects:   none
 */
bool CharLinkedList::isEmpty() const {
    if (numChars == 0) {
        return true;
    } else {
        return false;
    }
}

/*
 * name:      clear()
 * purpose:   clears the list of any elements
 * arguments: none
 * returns:   none
 * effects:   sets numChars to 0 and front and back to nullptr
 */
void CharLinkedList::clear() {
    Node *curr = front;
    if (front != nullptr) {
        while (curr != nullptr) {
            Node *next = curr->next;
            delete curr;
            curr = next;
        }
    }

    numChars = 0;
    front = nullptr;
    back = nullptr;
}

/*
 * name:      size()
 * purpose:   communicates the number of elements in the list and is zero if
 *            and only if isEmpty() is true
 * arguments: none
 * returns:   integer size
 * effects:   none
 */
int CharLinkedList::size() const {
    if (isEmpty()) {
        return 0;
    } else {
        return numChars;
    }
}

/*
 * name:      first()
 * purpose:   communicates the first element in the list, throws error if empty
 * arguments: none
 * returns:   char element
 * effects:   none
 */
char CharLinkedList::first() const {
    if (isEmpty()) {
        throw std::runtime_error("cannot get first of empty LinkedList");
    } else {
        return front->data;
    }
}

/*
 * name:      last()
 * purpose:   communicates the last element in the list, throws error if empty
 * arguments: none
 * returns:   char element
 * effects:   none
 */
char CharLinkedList::last() const {
    if (isEmpty()) {
        throw std::runtime_error("cannot get last of empty LinkedList");
    } else {
        return back->data;
    }
}

/*
 * name:      elementAtRecursive()
 * purpose:   private recursive helper function, returns the element at a given
 *            index in the list, throws error if out of range
 * arguments: node to iterate through list and integer index
 * returns:   char element
 * effects:   none
 */
char CharLinkedList::elementAtRecursive(Node *curr, int index) const {
    // check if given index is outside range of number of elems in list
    if (index < 0 || index >= numChars) {
        std::string sidx = std::to_string(index);
        std::string size = std::to_string(numChars);
        std::string err = "index (" + sidx + ") not in range [0.." + size + ")";
        throw std::range_error(err);
    }

    // returns element at 0 if index is 0
    if (index == 0) {
        return curr->data;
    }

    // recursively call function at next node, also decrementing index
    return CharLinkedList::elementAtRecursive(curr->next, index - 1);
}

/*
 * name:      elementAt()
 * purpose:   communicates an element at a specified index of the linked list,
 *            will throw error if index is out of range of the list
 * arguments: integer index
 * returns:   char element
 * effects:   none
 */
char CharLinkedList::elementAt(int index) const {
    // using private recursive helper function
    return CharLinkedList::elementAtRecursive(front, index);

    /* not recursive
    // iterate through linked list and return data stored at the current node
    Node *curr = front;
    for (int i = 0; i < index; ++i) {
        curr = curr->next;
    }
    return curr->data;
    */
}

/*
 * name :     toString
 * purpose:   returns a string that contains the size of the current linked list
 *            and all the char elements in the list as one concatenated word
 * arguments: none
 * returns:   string
 * effects:   none
 */
std::string CharLinkedList::toString() const {
    std::stringstream ss;

    ss << "[CharLinkedList of size " << numChars << " <<";

    Node *curr = front;

    // iterate through each elem in the linked list and puts into string stream
    while (curr != nullptr) {
        ss << curr->data;
        curr = curr->next;
    }
    ss << ">>]";

    return ss.str();
}

/*
 * name :     toReverseString
 * purpose:   returns a string that contains the size of the current linked list
 *            and all the char elements in the list as one concatenated word in
 *            reverse order
 * arguments: none
 * returns:   string
 * effects:   none
 */
std::string CharLinkedList::toReverseString() const {
    std::stringstream ss;

    ss << "[CharLinkedList of size " << numChars << " <<";

    Node *curr = back;

    // iterate through each elem in the linked list and puts into string stream
    while (curr != nullptr) {
        ss << curr->data;
        curr = curr->prev;
    }
    ss << ">>]";

    return ss.str();
}

/*
 * name :     pushAtBack()
 * purpose:   adds an element to the back of the linked list
 * arguments: char to push to back of list
 * returns:   none
 * effects:   increases numChars by one
 */
void CharLinkedList::pushAtBack(char c) {
    Node *newNode = new Node(c);

    // check if list is empty first
    if (front == nullptr && back == nullptr) {
        front = newNode;
        back = newNode;
    } else {
        newNode->next = nullptr;
        // connect previous back node to new back node
        newNode->prev = back;
        back->next = newNode;

        back = newNode;
    }

    numChars++;
}

/*
 * name :     pushAtFront()
 * purpose:   adds and element to the front of the linked list
 * arguments: char to push to front of list
 * returns:   none
 * effects:   increases numChars by one
 */
void CharLinkedList::pushAtFront(char c) {
    Node *newNode = new Node(c);

    // check if list is empty first
    if (front == nullptr && back == nullptr) {
        front = newNode;
        back = newNode;
    } else {
        newNode->prev = nullptr;
        // connect previous front node to new front node
        newNode->next = front; 
        front->prev = newNode;

        front = newNode;
    }

    numChars++;
}

/*
 * name :     insertAt()
 * purpose:   adds and element to the list at a given index
 * arguments: char to push to front of list and integer index
 * returns:   none
 * effects:   increases numChars by one and updates pointers correctly
 */
void CharLinkedList::insertAt(char c, int index) {
    // check if given index is outside range of number of elems in list
    if (index < 0 || index > numChars) {
        std::string sidx = std::to_string(index);
        std::string size = std::to_string(numChars);
        std::string err = "index (" + sidx + ") not in range [0.." + size + "]";
        throw std::range_error(err);
    }
    // special case for if list is empty
    else if (index == 0 && numChars == 0) {
        CharLinkedList::pushAtBack(c); // increments numChars
        numChars--; // decrement because it gets incremented later
    }

    Node *newNode = new Node(c);

    // special case for inserting at beginning of the list
    if (index == 0) {
        newNode->next = front;
        front->prev = newNode;
        front = newNode;
    } 
    // special case for inserting at the index after the last element
    else if (index == numChars && index != 0) {
        newNode->prev = back;
        back->next = newNode;
        back = newNode;
    } 
    else {
        // iterate through linked list so that curr will be at the index
        Node *curr = front;
        for (int i = 0; i < index; ++i) {
            curr = curr->next;
        }

        // link newNode to the node before index, so that newNode is at index
        newNode->prev = curr->prev;
        curr->prev->next = newNode;

        // link newNode to the front of the node that was previously at index
        newNode->next = curr;
        curr->prev = newNode;
    }
    
    numChars++;
}

/*
 * name :     insertInOrder()
 * purpose:   adds and element to the list in ASCII order
 * arguments: char to insert
 * returns:   none
 * effects:   increases numChars by one and updates pointers correctly
 */
void CharLinkedList::insertInOrder(char c) {
    // special case for if list is empty
    if (numChars == 0) {
        CharLinkedList::pushAtFront(c);
        return;
    }

    Node *newNode = new Node(c);

    // iterate through list from the front and insert if newNode comes earlier
    // in ASCII order than the current node at any point in the list
    Node *curr = front;
    int index = 0;

    while (curr != nullptr) {
        if (newNode->data <= curr->data) {
            CharLinkedList::insertAt(c, index);
            return;
        }
        curr = curr->next;
        index++;
    }

    // iterate through list from the other direction to ensure newNode gets
    // inserted if it was not already inserted
    curr = back;
    index = numChars;

    while (curr != nullptr) {
        if (newNode->data > curr->data) {
            CharLinkedList::insertAt(c, index);
            return;
        }
        curr = curr->prev;
        index--;
    }   
}

/*
 * name :     popFromFront()
 * purpose:   removes the first element in a linked list
 * arguments: none
 * returns:   none
 * effects:   decreases numChars by one and correctly updates front pointer
 */
void CharLinkedList::popFromFront() {
    if (isEmpty()) {
        throw std::runtime_error("cannot pop from empty LinkedList");
    }

    // initialize temp node ptr, update pointers, delete node at front
    Node *temp = front;
    front = temp->next;

    if (front == nullptr) { // special case for if the list becomes empty
        back = nullptr;
    } else {
        front->prev = nullptr;
    }

    delete temp;

    numChars--;
}

/*
 * name :     popFromBack()
 * purpose:   removes the last element in a linked list
 * arguments: none
 * returns:   none
 * effects:   decreases numChars by one and correctly updates back pointer
 */
void CharLinkedList::popFromBack() {
    if (isEmpty()) {
        throw std::runtime_error("cannot pop from empty LinkedList");
    }

    // initialize temp node ptr, update pointers, delete node at back
    Node *temp = back;
    back = temp->prev;

    if (back == nullptr) { // special case for if the list becomes empty
        front = nullptr;
    } else {
        back->next = nullptr;
    }

    delete temp;

    numChars--;
}

/*
 * name :     removeAt()
 * purpose:   removes the element at a specified index
 * arguments: integer index
 * returns:   none
 * effects:   decreases numChars by one and correctly updates pointers
 */
void CharLinkedList::removeAt(int index) {
    if (index < 0 || index >= numChars) {
        std::string sidx = std::to_string(index);
        std::string size = std::to_string(numChars);
        std::string err = "index (" + sidx + ") not in range [0.." + size + ")";
        throw std::range_error(err);
    }
    
    // special case for removing from front of the list
    if (index == 0) {
        CharLinkedList::popFromFront();
        numChars++; // undo increment from popFromFront function
    }
    // special case for removing from back of the list
    else if (index != 0 && index == (numChars - 1)) {
        CharLinkedList::popFromBack();
        numChars++; // undo increment from PopFromBack function
    }
    // initialize curr ptr and iterate so that curr will be at the index
    else {
        Node *curr = front;
        for (int i = 0; i < index; ++i) {
            curr = curr->next;
        }

        // link nodes before and after index to each other
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;

        /* use this block instead in case there are errors with front & back ptr
        if (curr->next == nullptr) { // check for end of list
            curr->prev->next = nullptr;
        } else {
            curr->prev->next = curr->next;
        }
        if (curr->prev == nullptr) { // check for beginning of list
            curr->next->prev = nullptr;
        } else {
            curr->next->prev = curr->prev;
        }
        */

        // delete node that was previously at the index
        delete curr;
    }

    numChars--;
}

/*
 * name :     replaceAtRecursive()
 * purpose:   recursively calls itself until index matches the desired node to
 *            replace and replaces it with specified char argument
 * arguments: node ptr to iterate through list, char c to replace, integer index
 * returns:   none
 * effects:   none
 */
void CharLinkedList::replaceAtRecursive(Node *curr, char c, int index) {
    if (index < 0 || index >= numChars) {
        std::string sidx = std::to_string(index);
        std::string size = std::to_string(numChars);
        std::string err = "index (" + sidx + ") not in range [0.." + size + ")";
        throw std::range_error(err);
    }

    // if index is 0, then changes data at current node to char c parameter
    if (curr != nullptr && index == 0) {
        curr->data = c;
    } else {
        // recursively call function, increment curr and decrement index
        CharLinkedList::replaceAtRecursive(curr->next, c, index - 1);
    }
}

/*
 * name :     replaceAt()
 * purpose:   replaces element at specified index with desired char, calls on
 *            private recursive helper function
 * arguments: char c to replace, integer index
 * returns:   none
 * effects:   none
 */
void CharLinkedList::replaceAt(char c, int index) {
    // call private recursive helper function
    CharLinkedList::replaceAtRecursive(front, c, index);
}

/*
 * name :     concatenate()
 * purpose:   concatenates two linked lists so that it is one super linked list
 * arguments: other CharLinkedList
 * returns:   none
 * effects:   adds numChars of both linked lists and updates pointers
 */
void CharLinkedList::concatenate(CharLinkedList *other) {
    // special case for self-concatenation
    if (this == other) {
        // instantiate new list to hold a copy of this list
        CharLinkedList copy_list;

        // copy all elements of this list into new copy_list
        Node *curr = front;
        for (int i = 0; i < numChars; ++i) {
            if (curr != nullptr) {
                copy_list.CharLinkedList::pushAtBack(curr->data);
                curr = curr->next;
            }
        }

        // add elements of copy_list to the end of this list
        curr = copy_list.front;
        for (int i = 0; i < copy_list.numChars; ++i) {
            if (curr != nullptr) {
                CharLinkedList::pushAtBack(curr->data);
                curr = curr->next;
            }
        }
    }
    // for all other cases where there is already another instance of a list
    else {
        // iterate through nodes of other list and add them to back of this list
        Node *curr = other->front;
        for (int i = 0; i < other->numChars; ++i) {
            if (curr != nullptr) {
                CharLinkedList::pushAtBack(curr->data);
                curr = curr->next;
            }
        }
    }
}