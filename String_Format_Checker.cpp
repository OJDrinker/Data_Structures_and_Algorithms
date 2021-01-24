// File Name: assign1_aod9.cpp
//
// Author: Andrew Daly
// Date: 07/15/2020
// Assignment Number: 1
// Instructor: Dan Tamir
//
// This program performs string format checker,
// ensuring that the string is in this format:
// A(n)B(n)A(n), consecutive As followed by n
// consecutive Bs followed by n consecutive As

#include <iostream>
#include <fstream>
#include <string>
#define MAX_SIZE 20

using namespace std;

// **************************************************
// Stack: class to be used as a stack
// **************************************************

class Stack {
private:
    char arr[MAX_SIZE];
    int top;
public:
    Stack();
    void push(char val);
    char pop();
    bool isEmpty();
    bool isFull();
};

Stack::Stack() {
    top = -1;
}

// **************************************************
// push: add an element to the top of the stack
//
// letter: the element to be pushed
// **************************************************

void Stack::push(char letter) {
    arr[top++] = letter;
}

// **************************************************
// pop: delete the top element of the stack
//
// **************************************************

char Stack::pop() {
    return arr[--top];
}

// **************************************************
// isEmpty: check if the stack is empty or not
//
// **************************************************

bool Stack::isEmpty() {
    return top == -1;
}

// **************************************************
// isFull: check if the stack is full or not
//
// **************************************************

bool Stack::isFull() {
    return top == MAX_SIZE - 1;
}

// **************************************************
// main: the driver code to read file and check
//       if the strings inside fit the criteia
//
// **************************************************

int main() {
    Stack s;

    // Please change the file name if needed

    ifstream file("exp.txt");
    string str;

    // Reading file line by line

    while (getline(file, str)) {
        for (int i = 0; i < str.size(); ++i) {
            s.push(str[i]);
        }

        // Check if Stack is not overflowing

        s.isFull();

        // Check if the string itself is a palindrome

        int index = 0;
        bool format_checker = true;
        bool isFormRight = true;
        while (!s.isEmpty()) {
            if (s.pop() != str[index++] )
                format_checker = false;
        }

        // Check if string is of the form A(n)B(n)A(n)

        int a;
        for (a = 0; a < str.size(); a++)
            if (str[a] != 'A')
                break;
        int b;
        for (b = a; b < str.size(); b++)
            if (str[b] != 'B')
                break;
        int c;
        for (c = b; c < str.size(); c++)
            if (str[c] != 'A')
                isFormRight = false;

        // Display the result

        if (format_checker && isFormRight) {
            cout << "'" << str <<"'" << " == Format is OK" << endl;
        }
        else {
            cout << "'" << str << "'" << " == Format not acceptable" << endl;
        }
    }
    return 0;
}