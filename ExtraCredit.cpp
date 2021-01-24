// File Name: assignExtraCredit_aod9.cpp
//
// Author: Andrew Daly
// Date: 08/07/2020
// Assignment Number: Extra Credit
// Instructor: Dan Tamir
//

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// **************************************************
// Node: using struct to create nodes
// **************************************************

struct Node {
    int data;
    struct Node* next;
};
struct Node* head = NULL;

// **************************************************
// insert: push an node into the linked list
//
// new_data: valued to be pushed in
// **************************************************

void insert(int new_data) {
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
    new_node->data = new_data;
    new_node->next = head;
    head = new_node;
}

// **************************************************
// avgOfNodes: calculate the average of the set
//
// head: linked list's head
// **************************************************

float avgOfNodes(struct Node* head)
{
    if (!head)
        return -1;

    int count = 0;
    int sum = 0;
    float avg = 0.0;

    struct Node* current = head;
    while (current != NULL) {
        count++;
        sum += current->data;
        current = current->next;
    }
    avg = (double)sum / count;

    return avg;
}

// **************************************************
// findMedian: look for median of the set
//
// head: linked list's head
// **************************************************

void findMedian(Node* head)
{
    Node* slow_ptr = head;
    Node* fast_ptr = head;
    Node* pre_of_slow = head;

    if (head != NULL) {
        while (fast_ptr != NULL && fast_ptr->next != NULL) {

            fast_ptr = fast_ptr->next->next;

            pre_of_slow = slow_ptr;
            slow_ptr = slow_ptr->next;
        }

        if (fast_ptr != NULL)
            cout << slow_ptr->data;

        else
            cout << float(slow_ptr->data + pre_of_slow->data) / 2;
    }
}
// **************************************************
// findMod: find occuring value of the set
//
// head: linked list's head
// **************************************************
int findMod(struct Node* head)
{
    struct Node* p = head;

    int total_count = 0, max_count = 0, res = -1;
    while (p != NULL) {

        int count = 1;
        struct Node* q = p->next;
        while (q != NULL) {
            if (p->data == q->data)
                count++;
            q = q->next;
        }

        if (count > max_count)
        {
            max_count = count;
            res = p->data;
        }

        p = p->next;
        total_count++;
    }

    if (max_count >= 2)
        return res;

    return -1;
}

// **************************************************
// Driver Code
// **************************************************

int main() {
    string str;
    int numOfInputs, x, range;

    int smallest = 1000000; 
    int largest = 0;

    ifstream file;
    file.open("input.txt");
    file >> numOfInputs;

    for (int i = 0; i < numOfInputs; i++) {
        file >> x;
        if (smallest > x)
            smallest = x;
        if (largest < x)
            largest = x;
    }

    file.close();

    range = largest - smallest;

    file.open("input.txt");
    file >> numOfInputs;

    if (range <= 10) {
        for (int i = 0; i < numOfInputs; i++) {
            file >> x;
            insert(x);
        }
        cout << avgOfNodes(head) << endl;
        findMedian(head);
        cout << endl;
        int res = findMod(head);

        if (res != (-1))
            cout << res;
        else
            cout << "No mod";
    }

    file.close();

    return 0;
}