/*
 *  unit_tests.cpp
 *  Iverson Lai
 *  Oct 2 2023
 *
 *  CS 15 HW 2 Cheshire ConCATenation - Time to linked up in Fur
 *
 *  This is a test file for the doubly linked list data structur. It contains
 *  edge cases for the methods written out in the implementation file to ensure
 *  that everything is running as expected.
 *
 */

#include "CharLinkedList.h"
#include <cassert>
#include <iostream>

// instantiates an empty CharLinkedList
void constructor_test_default() {
    CharLinkedList list;

    assert(list.isEmpty() == 1);
    assert(list.toString() == "[CharLinkedList of size 0 <<>>]");
}

// instantiates a CharLinkedList with one char element as specified in argument
void constructor_test_single_param() {
    CharLinkedList list('a');

    assert(list.isEmpty() == 0);
    assert(list.toString() == "[CharLinkedList of size 1 <<a>>]");
}

// instantiates a CharLinekdList with several elements as specified in argument
void constructor_test_multi_param() {
    char testArr[] = "Nachos";
    CharLinkedList list(testArr, 6);

    assert(list.isEmpty() == 0);
    assert(list.toString() == "[CharLinkedList of size 6 <<Nachos>>]");
}

// instantiates two linked lists to test the copy constructor functionality
void constructor_test_copy() {
    char testArr[] = "Nachos";
    CharLinkedList origList(testArr, 6);
    CharLinkedList newList(origList);

    assert(origList.toString() == "[CharLinkedList of size 6 <<Nachos>>]");
    assert(newList.toString() == "[CharLinkedList of size 6 <<Nachos>>]");
}

// instantiates empty list and list with elems and copies elems to empty list
void assignment_operator_test_empty() {
    CharLinkedList emptyList;
    char testArr[] = "Nachos";
    CharLinkedList list(testArr, 6);

    assert(emptyList.toString() == "[CharLinkedList of size 0 <<>>]");
    assert(list.toString() == "[CharLinkedList of size 6 <<Nachos>>]");

    emptyList = list;

    assert(emptyList.toString() == "[CharLinkedList of size 6 <<Nachos>>]");
    assert(list.toString() == "[CharLinkedList of size 6 <<Nachos>>]");
}

// instantiates two lists of same number of elems and copies one to the other
void assignment_operator_test_same_size() {
    char testArr1[] = "Nachos";
    char testArr2[] = "Apples";
    CharLinkedList list1(testArr1, 6);
    CharLinkedList list2(testArr2, 6);

    assert(list1.toString() == "[CharLinkedList of size 6 <<Nachos>>]");
    assert(list2.toString() == "[CharLinkedList of size 6 <<Apples>>]");

    list1 = list2;

    assert(list1.toString() == "[CharLinkedList of size 6 <<Apples>>]");
    assert(list2.toString() == "[CharLinkedList of size 6 <<Apples>>]");
}

// instantiates two lists with elems but different sizes and copies one over
void assignment_operator_test_diff_size() {
    char testArr1[] = "Nachos";
    char testArr2[] = "Taiwanese";
    CharLinkedList list1(testArr1, 6);
    CharLinkedList list2(testArr2, 9);

    assert(list1.toString() == "[CharLinkedList of size 6 <<Nachos>>]");
    assert(list2.toString() == "[CharLinkedList of size 9 <<Taiwanese>>]");

    list1 = list2;

    assert(list1.toString() == "[CharLinkedList of size 9 <<Taiwanese>>]");
    assert(list2.toString() == "[CharLinkedList of size 9 <<Taiwanese>>]");
}

// instantiates empty list, checks if empty, adds elements, and checks if empty
void isEmpty_test() {
    CharLinkedList list;
    assert(list.isEmpty() == 1);

    list.pushAtBack('z');
    list.pushAtFront('a');

    assert(list.isEmpty() == 0);
}

// instantiates a list with elements and clears all of its elements
void clear_test_normal() {
    char testArr[] = "Nachos";
    CharLinkedList list(testArr, 6);
    assert(list.isEmpty() == 0);

    list.clear();
    assert(list.isEmpty() == 1);
}

// instantiates empty list, inserts many elements, and clears the list
void clear_test_many() {
    CharLinkedList list;

    for (int i = 0; i < 1000; i++) {
        list.pushAtBack('a');
    }
    assert(list.size() == 1000);

    list.clear();
    assert(list.isEmpty() == 1);
}

// instantiates empty list and clears it of any elements
void clear_test_empty() {
    CharLinkedList list;
    assert(list.isEmpty() == 1);

    list.clear();
    assert(list.isEmpty() == 1);
}

// instantiates a singleton list and returns the number of elements
void size_test_singleton() {
    CharLinkedList list('a');
    assert(list.size() == 1);
}

// instantiates a list with elements and returns the number of elements
void size_test_normal() {
    char testArr[] = "Nachos";
    CharLinkedList list(testArr, 6);
    assert(list.size() == 6);
}

// instantiates an empty list, inserts many elements, and returns size of list
void size_test_many() {
    CharLinkedList list;

    for (int i = 0; i < 1000; i++) {
        list.pushAtBack('a');
    }
    assert(list.size() == 1000);

    for (int i = 0; i < 1000; i++) {
        assert(list.elementAt(i) == 'a');
    }
}

// instantiates an empty list and returns the number of elements
void size_test_empty() {
    CharLinkedList list;
    assert(list.size() == 0);
}

// instantiates a singleton list and returns the first and only element
void first_test_singleton() {
    CharLinkedList list('a');

    assert(list.first() == 'a');
}

// instantiates a list with elements and returns the first element
void first_test_normal() {
    char testArr[] = "Nachos";
    CharLinkedList list(testArr, 6);
    assert(list.first() == 'N');
}

// instantiates an empty list, inserts elements, and returns the first element
void first_test_insert() {
    CharLinkedList list;

    list.pushAtBack('a');
    list.pushAtBack('b');
    list.pushAtBack('c');
    list.pushAtBack('d');
    list.pushAtFront('e');
    list.pushAtFront('f');
    list.pushAtFront('g');
    list.pushAtFront('h');

    assert(list.first() == 'h');
}

// instantiates an empty list and throws an error
void first_test_empty() {
    CharLinkedList list;

    // initialize variables to use for asserting the error message
    bool runtime_error_thrown = false;
    std::string error_message = "";

    try {
        list.first();
    }
    catch (const std::runtime_error &e) {
        runtime_error_thrown = true;
        error_message = e.what();
    }

    assert(runtime_error_thrown);
    assert(error_message == "cannot get first of empty LinkedList");
}

// instantiates a singleton list and returns the first and only element
void last_test_singleton() {
    CharLinkedList list('z');
    assert(list.last() == 'z');
}

// instantiates a list with elements and returns the first element
void last_test_normal() {
    char testArr[] = "Nachos";
    CharLinkedList list(testArr, 6);
    assert(list.last() == 's');
}

// instantiates an empty list, inserts many elements, and returns last element
void last_test_insert() {
    CharLinkedList list;

    list.pushAtBack('a');
    list.pushAtBack('b');
    list.pushAtBack('c');
    list.pushAtBack('d');
    list.pushAtFront('e');
    list.pushAtFront('f');
    list.pushAtFront('g');
    list.pushAtFront('h');

    assert(list.last() == 'd');
}

// instantiates an empty list and throws a range error
void last_test_empty() {
    CharLinkedList list;

    // initialize variables to use for asserting the error message
    bool runtime_error_thrown = false;
    std::string error_message = "";

    try {
        list.last();
    }
    catch (const std::runtime_error &e) {
        runtime_error_thrown = true;
        error_message = e.what();
    }

    assert(runtime_error_thrown);
    assert(error_message == "cannot get first of empty LinkedList");
}

// instantiates singleton list and finds char at given index
void elementAt_test_singleton() {
    CharLinkedList list('a');
    assert(list.elementAt(0) == 'a');
}

// instantiates list with elements and finds char at given index
void elementAt_test_normal() {
    char testArr[] = "Nachos";
    CharLinkedList list(testArr, 6);
    assert(list.elementAt(2) == 'c');
}

// instantiates an empty list, inserts many elements, finds char at given index
void elementAt_test_insert() {
    CharLinkedList list;

    list.pushAtBack('a');
    list.pushAtBack('b');
    list.pushAtBack('c');
    list.pushAtBack('d');
    list.pushAtFront('e');
    list.pushAtFront('f');
    list.pushAtFront('g');
    list.pushAtFront('h');

    assert(list.elementAt(4) == 'a');
}

// instantiates an empty list and throws a range error
void elementAt_test_empty() {
    CharLinkedList list;

    // initialize variables to use for asserting the error message
    bool range_error_thrown = false;
    std::string error_message = "";

    try {
        assert(list.elementAt(0));;
    }
    catch (const std::range_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }

    assert(range_error_thrown);
    assert(error_message == "index (0) not in range [0..0)");
}

// instantiates a list with many elements and finds char outside range
void elementAt_test_outside_range() {
    char testArr[] = "Nachos";
    CharLinkedList list(testArr, 6);

    // initialize variables to use for asserting the error message
    bool range_error_thrown = false;
    std::string error_message = "";

    try {
        assert(list.elementAt(45));
    }
    catch (const std::range_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }

    assert(range_error_thrown);
    assert(error_message == "index (45) not in range [0..6)");
}

// instantiates a singleton list and returns the list as a string
void toString_test_singleton() {
    CharLinkedList list('a');
    assert(list.toString() == "[CharLinkedList of size 1 <<a>>]");
}

// instantiates a list with elements and returns it as a string
void toString_test_normal() {
    char testArr[] = "Nachos";
    CharLinkedList list(testArr, 6);
    assert(list.toString() == "[CharLinkedList of size 6 <<Nachos>>]");
}

// instantiates an empty list, inserts elements, and returns list as string
void toString_test_insert() {
    CharLinkedList list;

    list.pushAtFront('i');
    list.pushAtBack('w');
    list.pushAtBack('a');
    list.pushAtFront('a');
    list.pushAtBack('n');
    list.pushAtBack('e');
    list.pushAtBack('s');
    list.pushAtFront('T');
    list.pushAtBack('e');

    assert(list.toString() == "[CharLinkedList of size 9 <<Taiwanese>>]");
}

// instantiates an empty list, returns list as an empty string
void toString_test_empty() {
    CharLinkedList list;
    assert(list.toString() == "[CharLinkedList of size 0 <<>>]");
}

// instantiates a singleton list, returns list as string in reverse order
void toReverseString_test_singleton() {
    CharLinkedList list('a');
    assert(list.toReverseString() == "[CharLinkedList of size 1 <<a>>]");
}

// instantiates a list with elements, returns elements in reverse as string
void toReverseString_test_normal() {
    char testArr[] = "Apple";
    CharLinkedList list(testArr, 5);
    assert(list.toReverseString() == "[CharLinkedList of size 5 <<elppA>>]");
}

// instantiates empty list, inserts elements, returns list in reverse order
void toReverseString_test_insert() {
    CharLinkedList list;

    list.pushAtFront('h');
    list.pushAtBack('o');
    list.pushAtBack('e');
    list.pushAtFront('S');


    assert(list.toReverseString() == "[CharLinkedList of size 4 <<eohS>>]");
}

// instantaites empty list and returns list in reverse order as a string
void toReverseString_test_empty() {
    CharLinkedList list;
    assert(list.toReverseString() == "[CharLinkedList of size 0 <<>>]");
}

// instantiates empty list and pushes chars into back of the list
void pushAtBack_test() {
    CharLinkedList list;

    list.pushAtBack('a');
    list.pushAtBack('b');
    list.pushAtBack('c');

    assert(list.toString() == "[CharLinkedList of size 3 <<abc>>]");
}

// instantiates empty list and pushes many chars into back of the list
void pushAtBack_test_many() {
    CharLinkedList list;

    for (int i = 0; i < 1000; i++) {
        list.pushAtBack('a');
    }
    assert(list.size() == 1000);

    for (int i = 0; i < 1000; i++) {
        assert(list.elementAt(i) == 'a');
    }
}

// instantiates empty list and pushes chars into front of the list
void pushAtFront_test() {
    CharLinkedList list;

    list.pushAtFront('t');
    list.pushAtFront('a');
    list.pushAtFront('c');

    assert(list.toString() == "[CharLinkedList of size 3 <<cat>>]");
}

// instantiates empty list and pushes many chars into front of the list
void pushAtFront_test_many() {
    CharLinkedList list;

    for (int i = 0; i < 1000; i++) {
        list.pushAtFront('a');
    }
    assert(list.size() == 1000);

    for (int i = 0; i < 1000; i++) {
        assert(list.elementAt(i) == 'a');
    }
}

// instantiates empty list and inserts a char
void insertAt_test_empty() {
    CharLinkedList list;

    list.insertAt('a', 0);

    assert(list.size() == 1);
    assert(list.elementAt(0) == 'a');
}

// instantiates empty list and inserts a char at an invalid index
void insertAt_test_empty_incorrect() {
    CharLinkedList list;

    bool range_error_thrown = false;
    std::string error_message = "";

    try {
        list.insertAt('a', 42);
    }
    catch (const std::range_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }

    assert(range_error_thrown);
    assert(error_message == "index (42) not in range [0..0]");
}

// instantiates empty list and inserts many elements at the back of the list
void insertAt_test_many() {
    CharLinkedList list;

    for (int i = 0; i < 1000; i++) {
        list.insertAt('a', i);
    }
    assert(list.size() == 1000);

    for (int i = 0; i < 1000; i++) {
        assert(list.elementAt(i) == 'a');
    }
}

// instantiates singleton list and inserts char to the front of the list
void insertAt_test_front_singleton() {
    CharLinkedList list('a');

    list.insertAt('z', 0);

    assert(list.size() == 2);
    assert(list.elementAt(0) == 'z');
    assert(list.elementAt(1) == 'a');
}

// instantiates list with elements and inserts char to the front of the list
void insertAt_test_front_normal() {
    char testArr[] = "Nachos";
    CharLinkedList list(testArr, 6);

    list.insertAt('s', 0);

    assert(list.toString() == "[CharLinkedList of size 7 <<sNachos>>]");
}

// instantiates list with elements and inserts char to the middle of the list
void insertAt_test_middle_normal() {
    char testArr[] = "Nachos";
    CharLinkedList list(testArr, 6);

    list.insertAt('r', 2);

    assert(list.toString() == "[CharLinkedList of size 7 <<Narchos>>]");
}

// instantiates singleton list and inserst char to the back of the list
void insertAt_test_back_singleton() {
    CharLinkedList list('a');

    list.insertAt('z', 1);

    assert(list.size() == 2);
    assert(list.elementAt(0) == 'a');
    assert(list.elementAt(1) == 'z');
}

// instantiates list with elements and isnerts char to the back of the list
void insertAt_test_back_normal() {
    char testArr[] = "Nachos";
    CharLinkedList list(testArr, 6);

    list.insertAt('e', 6);

    assert(list.toString() == "[CharLinkedList of size 7 <<Nachose>>]");
}

// instantiates list with elements and tries to insert char out of range
void insertAt_test_nonempty_incorrect() {
    char testArr[] = "Taiwanese";
    CharLinkedList list(testArr, 9);

    bool range_error_thrown = false;
    std::string error_message = "";

    try {
        list.insertAt('a', 42);
    }
    catch (const std::range_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }

    assert(range_error_thrown);
    assert(error_message == "index (42) not in range [0..9]");
}

// instantiates empty list and inserts char in ASCII order
void insertInOrder_test_empty() {
    CharLinkedList list;

    list.insertInOrder('g');

    assert(list.size() == 1);
    assert(list.elementAt(0) == 'g');
}

// instantiates singleton list and inserts char in ASCII order, front of list
void insertInOrder_test_singleton_front() {
    CharLinkedList list('g');

    list.insertInOrder('a');

    assert(list.size() == 2);
    assert(list.elementAt(0) == 'a');
    assert(list.elementAt(1) == 'g');
}

// instantiates singleton list and inserts char in ASCII order, back of list
void insertInOrder_test_singleton_back() {
    CharLinkedList list('g');

    list.insertInOrder('z');

    assert(list.size() == 2);
    assert(list.elementAt(0) == 'g');
    assert(list.elementAt(1) == 'z');
}

// instantiates list with elems and inserts char in ASCII order, front of list
void insertInOrder_test_normal_front() {
    char testArr[] = "bcdefgh";
    CharLinkedList list(testArr, 7);

    list.insertInOrder('a');

    assert(list.toString() == "[CharLinkedList of size 8 <<abcdefgh>>]");
}

// instantiates list with elems and inserts char in ASCII order, middle of list
void insertInOrder_test_normal_middle() {
    char testArr[] = "abcdfgh";
    CharLinkedList list(testArr, 7);

    list.insertInOrder('e');

    assert(list.toString() == "[CharLinkedList of size 8 <<abcdefgh>>]");
}

// instantiates list with elems and inserts char in ASCII order, back of list
void insertInOrder_test_normal_back() {
    char testArr[] = "abcdefg";
    CharLinkedList list(testArr, 7);

    list.insertInOrder('h');

    assert(list.toString() == "[CharLinkedList of size 8 <<abcdefgh>>]");
}

// instantiates singleton list and pops first and only element in list
void popFromFront_test_singleton() {
    CharLinkedList list('a');

    list.popFromFront();

    assert(list.isEmpty() == 1);
    assert(list.toString() == "[CharLinkedList of size 0 <<>>]");
}

// instantiates list with elements and pops first element in the list
void popFromFront_test_normal() {
    char testArr[] = "Spots";
    CharLinkedList list(testArr, 5);

    list.popFromFront();

    assert(list.toString() == "[CharLinkedList of size 4 <<pots>>]");
}

// instantiates a large list and confirms that the size gets decremented
void popFromFront_test_many() {
    CharLinkedList list;

    for (int i = 0; i < 1000; i++) {
        list.pushAtBack('a');
    }
    assert(list.size() == 1000);

    list.popFromFront();
    assert(list.size() == 999);
}

// instantiates empty list and tries to pop an element from empty list
void popFromFront_test_empty() {
    CharLinkedList list;

    bool runtime_error_thrown = false;
    std::string error_message = "";

    try {
        list.popFromFront();
    }
    catch (const std::runtime_error &e) {
        runtime_error_thrown = true;
        error_message = e.what();
    }

    assert(runtime_error_thrown);
    assert(error_message == "cannot pop from empty LinkedList");
}

// instantiates singleton list and pops the last and only element from the list
void popFromBack_test_singleton() {
    CharLinkedList list('a');

    list.popFromBack();

    assert(list.isEmpty() == 1);
    assert(list.toString() == "[CharLinkedList of size 0 <<>>]");
}

// instantiates list with elements and removes the last element
void popFromBack_test_normal() {
    char testArr[] = "Spots";
    CharLinkedList list(testArr, 5);

    list.popFromBack();

    assert(list.toString() == "[CharLinkedList of size 4 <<Spot>>]");
}

// instantiates large list and confirms that the size gets decremented
void popFromBack_test_many() {
    CharLinkedList list;

    for (int i = 0; i < 1000; i++) {
        list.pushAtBack('a');
    }
    assert(list.size() == 1000);

    list.popFromBack();
    assert(list.size() == 999);
}

// instantiates empty list and tires to pop an element from empty list
void popFromBack_test_empty() {
    CharLinkedList list;

    bool runtime_error_thrown = false;
    std::string error_message = "";

    try {
        list.popFromBack();
    }
    catch (const std::runtime_error &e) {
        runtime_error_thrown = true;
        error_message = e.what();
    }

    assert(runtime_error_thrown);
    assert(error_message == "cannot pop from empty LinkedList");
}

// instantates empty list and tries to remove char at index 0
void removeAt_test_empty() {
    CharLinkedList list;

    bool range_error_thrown = false;
    std::string error_message = "";

    try {
        list.removeAt(0);
    }
    catch (const std::range_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }

    assert(range_error_thrown);
    assert(error_message == "index (0) not in range [0..0)");
}

// instantiates empty list and tries to remove char from outside range
void removeAt_test_empty_outside_range() {
    CharLinkedList list;

    bool range_error_thrown = false;
    std::string error_message = "";

    try {
        list.removeAt(42);
    }
    catch (const std::range_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }

    assert(range_error_thrown);
    assert(error_message == "index (42) not in range [0..0)");
}

// instantiates singleton list and removes the only char in list
void removeAt_test_singleton() {
    CharLinkedList list('a');

    list.removeAt(0);

    assert(list.isEmpty() == 1);
    assert(list.toString() == "[CharLinkedList of size 0 <<>>]");
}

// instantiates singleton list and tries to remove char from outside range
void removeAt_test_singleton_outside_range() {
    CharLinkedList list('a');

    bool range_error_thrown = false;
    std::string error_message = "";

    try {
        list.removeAt(42);
    }
    catch (const std::range_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }

    assert(range_error_thrown);
    assert(error_message == "index (42) not in range [0..1)");
}

// instantiates list with elements and removes char at the front of list
void removeAt_test_front_normal() {
    char testArr[] = "pixel";
    CharLinkedList list(testArr, 5);

    list.removeAt(0);

    assert(list.toString() == "[CharLinkedList of size 4 <<ixel>>]");
}

// instantiates list with elements and removes char at index in the middle
void removeAt_test_middle_normal() {
    char testArr[] = "pixel";
    CharLinkedList list(testArr, 5);

    list.removeAt(3);
    assert(list.toString() == "[CharLinkedList of size 4 <<pixl>>]");

    list.removeAt(1);
    assert(list.toString() == "[CharLinkedList of size 3 <<pxl>>]");
}

// instantiates list with elements and removes char at back of the list
void removeAt_test_back_normal() {
    char testArr[] = "pixel";
    CharLinkedList list(testArr, 5);

    list.removeAt(4);

    assert(list.toString() == "[CharLinkedList of size 4 <<pixe>>]");
}

// instantiates a test with elements and tries to remove char outside range
void removeAt_test_normal_outside_range() {
    char testArr[] = "OneHundredFive";
    CharLinkedList list(testArr, 14);

    bool range_error_thrown = false;
    std::string error_message = "";

    try {
        list.removeAt(42);
    }
    catch (const std::range_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }

    assert(range_error_thrown);
    assert(error_message == "index (42) not in range [0..14)");
}

// instantiates empty list and tries to replace char at index 0
void replaceAt_test_empty() {
    CharLinkedList list;

    bool range_error_thrown = false;
    std::string error_message = "";

    try {
        list.replaceAt('a', 0);
    }
    catch (const std::range_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }

    assert(range_error_thrown);
    assert(error_message == "index (0) not in range [0..0)");
}

// instantiates singleton list and replaces the char at index 0
void replaceAt_test_singleton() {
    CharLinkedList list('a');

    list.replaceAt('b', 0);

    assert(list.isEmpty() == 0);
    assert(list.toString() == "[CharLinkedList of size 1 <<b>>]");
}

// instantiates singleton list and tries to replace at index outside range
void replaceAt_test_singleton_outside_range() {
    CharLinkedList list('a');

    bool range_error_thrown = false;
    std::string error_message = "";

    try {
        list.replaceAt('z', 26);
    }
    catch (const std::range_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }

    assert(range_error_thrown);
    assert(error_message == "index (26) not in range [0..1)");
}

// instantiates list with elements and replaces char at front of list
void replaceAt_test_normal_front() {
    char testArr[] = "racecar";
    CharLinkedList list(testArr, 7);

    list.replaceAt('f', 0);

    assert(list.toString() == "[CharLinkedList of size 7 <<facecar>>]");
}

// instantiates list with elements and replaces char in middle of list
void replaceAt_test_normal_middle() {
    char testArr[] = "racecar";
    CharLinkedList list(testArr, 7);

    list.replaceAt('t', 4);

    assert(list.toString() == "[CharLinkedList of size 7 <<racetar>>]");
}

// instantiates list with elements and replaces char at back of the list
void replaceAt_test_normal_back() {
    char testArr[] = "racecar";
    CharLinkedList list(testArr, 7);

    list.replaceAt('t', 6);

    assert(list.toString() == "[CharLinkedList of size 7 <<racecat>>]");
}

// instantiates list with elements and tries to replace at index outside range
void replaceAt_test_normal_outside_range() {
    char testArr[] = "racecar";
    CharLinkedList list(testArr, 7);

    bool range_error_thrown = false;
    std::string error_message = "";

    try {
        list.replaceAt('z', 7);
    }
    catch (const std::range_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }

    assert(range_error_thrown);
    assert(error_message == "index (7) not in range [0..7)");
}

// creates list with many elements and replaces front element
void replaceAt_test_many_front() {
    CharLinkedList list;

    for (int i = 0; i < 1000; i++) {
        list.pushAtBack('o');
    }
    
    list.replaceAt('x', 0);

    assert(list.size() == 1000);
    assert(list.elementAt(0) == 'x');

    // testing if 'x' was inserted only at the front and not anywhere else
    list.popFromFront();

    assert(list.size() == 999);
    assert(list.elementAt(0) == 'o');
}

// creates list with many elements and replaces middle element
void replaceAt_test_many_middle() {
    CharLinkedList list;

    for (int i = 0; i < 1000; i++) {
        list.pushAtBack('o');
    }
    
    list.replaceAt('x', 500);

    assert(list.size() == 1000);
    assert(list.elementAt(500) == 'x');
}

// creates list with many elements and replaces back element
void replaceAt_test_many_back() {
    CharLinkedList list;

    for (int i = 0; i < 1000; i++) {
        list.pushAtBack('o');
    }
    
    list.replaceAt('x', 999);

    assert(list.size() == 1000);
    assert(list.elementAt(999) == 'x');

    // testing if 'x' was inserted only at the back and not anywhere else
    list.popFromBack();

    assert(list.size() == 999);
    assert(list.elementAt(998) == 'o');

    bool range_error_thrown = false;
    std::string error_message = "";

    try {
        assert(list.elementAt(999));
    }
    catch (const std::range_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }

    assert(range_error_thrown);
    assert(error_message == "index (999) not in range [0..999)");
}

// creates list with many elements and tries to replace element outside index
void replaceAt_test_many_outside_range() {
    CharLinkedList list;

    for (int i = 0; i < 1000; i++) {
        list.pushAtBack('o');
    }
    
    bool range_error_thrown = false;
    std::string error_message = "";

    try {
        list.replaceAt('x', 1000);
    }
    catch (const std::range_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }

    assert(range_error_thrown);
    assert(error_message == "index (1000) not in range [0..1000)");
}

// instantiates two lists with elems and combines the second one with the first
void concatenate_test_normal() {
    char testArr1[] = "cat";
    char testArr2[] = "CHESHIRE";
    CharLinkedList list1(testArr1, 3);
    CharLinkedList list2(testArr2, 8);
    CharLinkedList *list2_ptr = &list2;

    list1.concatenate(list2_ptr);

    assert(list1.size() == 11);
    assert(list1.toString() == "[CharLinkedList of size 11 <<catCHESHIRE>>]");
}

// instantiate two lists, but the first one is empty, should return second list
void concatenate_test_first_empty() {
    char testArr2[] = "CHESHIRE";
    CharLinkedList list1;
    CharLinkedList list2(testArr2, 8);
    CharLinkedList *list2_ptr = &list2;

    list1.concatenate(list2_ptr);

    assert(list1.size() == 8);
    assert(list1.toString() == "[CharLinkedList of size 8 <<CHESHIRE>>]");
}

// instantiate two lists, but second is empty, should return list as normal
void concatenate_test_second_empty() {
    char testArr1[] = "cat";
    CharLinkedList list1(testArr1, 3);
    CharLinkedList list2;
    CharLinkedList *list2_ptr = &list2;

    list1.concatenate(list2_ptr);

    assert(list1.size() == 3);
    assert(list1.toString() == "[CharLinkedList of size 3 <<cat>>]");
}

// instantiates two empty lists, should return empty list
void concatenate_test_both_empty() {
    CharLinkedList list1;
    CharLinkedList list2;
    CharLinkedList *list2_ptr = &list2;

    list1.concatenate(list2_ptr);

    assert(list1.isEmpty() == 1);
    assert(list1.toString() == "[CharLinkedList of size 0 <<>>]");
}

// instantiates one list with elements and combines it with itself
void concatenate_test_itself() {
    char testArr1[] = "cat";
    CharLinkedList list1(testArr1, 3);
    CharLinkedList *list1_ptr = &list1;

    list1.concatenate(list1_ptr);

    assert(list1.size() == 6);
    assert(list1.toString() == "[CharLinkedList of size 6 <<catcat>>]");
}

int main() {

    // constructor and destructor tests
    constructor_test_default();
    constructor_test_single_param();
    constructor_test_multi_param();
    constructor_test_copy();

    // assignment operator tests
    assignment_operator_test_empty();
    assignment_operator_test_same_size();
    assignment_operator_test_diff_size();

    // method tests
    isEmpty_test();

    clear_test_normal();
    clear_test_many();
    clear_test_empty();

    size_test_singleton();
    size_test_normal();
    size_test_many();
    size_test_empty();

    first_test_singleton();
    first_test_normal();
    first_test_insert();
    first_test_empty();

    last_test_singleton();
    last_test_normal();
    last_test_insert();
    last_test_empty();

    elementAt_test_singleton();
    elementAt_test_normal();
    elementAt_test_insert();
    elementAt_test_empty();
    elementAt_test_outside_range();

    toString_test_singleton();
    toString_test_normal();
    toString_test_insert();
    toString_test_empty();

    toReverseString_test_singleton();
    toReverseString_test_normal();
    toReverseString_test_insert();
    toReverseString_test_empty();

    pushAtBack_test();
    pushAtBack_test_many();

    pushAtFront_test();
    pushAtFront_test_many();

    insertAt_test_empty();
    insertAt_test_empty_incorrect();
    insertAt_test_many();
    insertAt_test_front_singleton();
    insertAt_test_front_normal();
    insertAt_test_middle_normal();
    insertAt_test_back_singleton();
    insertAt_test_back_normal();
    insertAt_test_nonempty_incorrect();

    insertInOrder_test_empty();
    insertInOrder_test_singleton_front();
    insertInOrder_test_singleton_back();
    insertInOrder_test_normal_front();
    insertInOrder_test_normal_middle();
    insertInOrder_test_normal_back();

    popFromFront_test_singleton();
    popFromFront_test_normal();
    popFromFront_test_many();
    popFromFront_test_empty();

    popFromBack_test_singleton();
    popFromBack_test_normal();
    popFromBack_test_many();
    popFromFront_test_empty();

    removeAt_test_empty();
    removeAt_test_empty_outside_range();
    removeAt_test_singleton();
    removeAt_test_singleton_outside_range();
    removeAt_test_front_normal();
    removeAt_test_middle_normal();
    removeAt_test_back_normal();
    removeAt_test_normal_outside_range();

    replaceAt_test_empty();
    replaceAt_test_singleton();
    replaceAt_test_singleton_outside_range();
    replaceAt_test_normal_front();
    replaceAt_test_normal_middle();
    replaceAt_test_normal_back();
    replaceAt_test_normal_outside_range();
    replaceAt_test_many_front();
    replaceAt_test_many_middle();
    replaceAt_test_many_back();
    replaceAt_test_many_outside_range();

    concatenate_test_normal();
    concatenate_test_first_empty();
    concatenate_test_second_empty();
    concatenate_test_both_empty();
    concatenate_test_itself();

    return 0;
}