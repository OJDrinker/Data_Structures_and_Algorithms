// File Name: assign4_aod9.cpp
//
// Author: Andrew Daly
// Date: 08/05/2020
// Assignment Number: 4
// Instructor: Dan Tamir
//
// This program generates a Binary Search Tree (BST)
// and scan it in a preorder and a Breadth First
// Search (BFS) way.

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#define SIZE 20

using namespace std;

// **************************************************
// Queue: using class to create a queue from scratch
// **************************************************

class Queue {
private:
    int items[SIZE], front, rear;

public:

    // **************************************************
    // Constructor
    // **************************************************

    Queue() {
        front = -1;
        rear = -1;
    }

    // **************************************************
    // isFull: check if queue is overflowing or not
    // **************************************************

    bool isFull() {
        if (front == 0 && rear == SIZE - 1) {
            return true;
        }
        return false;
    }

    // **************************************************
    // isEmpty: check if queue is empty or not
    // **************************************************

    bool isEmpty() {
        if (front == -1)
            return true;
        else
            return false;
    }

    // **************************************************
    // push: add an item to the queue
    //
    // element: the item to be added
    // **************************************************

    void push(int element) {
        if (isFull()) {
            cout << "Queue is full";
        }
        else {
            if (front == -1) front = 0;
            rear++;
            items[rear] = element;
        }
    }

    // **************************************************
    // pop: remove oldest element from the queue
    // **************************************************

    int pop() {
        int element;
        if (isEmpty()) {
            cout << "Queue is empty" << endl;
            return (-1);
        }
        else {
            element = items[front];
            if (front >= rear) {
                front = -1;
                rear = -1;
            }
            else {
                front++;
            }
        }
    }

    // **************************************************
    // display: output the result to a file
    // **************************************************

    void display() {
        int i;{
        while (!isEmpty()) {
            cout << items[front] << "  ";
            pop();
            cout << items[front] << "  ";
            pop();
            cout << items[front] << endl;
            pop();
            }
        }
    }
};

// Initalizing...

int edgeCounter = 0;
const int MAX = 10000;
int id[MAX], edges;
pair <long long, pair<int, int> > p[MAX];

// **************************************************
// initialize: setting up an array
// **************************************************

void initialize()
{
    for (int i = 0; i < MAX; ++i)
        id[i] = i;
}

// **************************************************
// root: setting up edges
//
// x: a verticle
// **************************************************
int root(int x)
{
    while (id[x] != x)
    {
        id[x] = id[id[x]];
        x = id[x];
    }
    return x;
}

// **************************************************
// unionSet: creates a union set of edges
//
// x: a verticle
// y: a verticles
// **************************************************

void unionSet(int x, int y)
{
    int p = root(x);
    int q = root(y);
    id[p] = id[q];
}

// **************************************************
// kruskal: minimum spanning tree algorithm
//
// input: edges with their verticles and weight
// **************************************************

void kruskal(pair<long long, pair<int, int> > p[])
{
    Queue q;

    int x, y;
    long long cost;

    for (int i = 0; i < edges; ++i)
    {
        // Selecting edges one by one in increasing order from the beginning

        x = p[i].second.first;
        y = p[i].second.second;
        cost = p[i].first;

        // Check if the selected edge forms a cycle or not

        if (root(x) != root(y))
        {
            unionSet(x, y);
            q.push(x);
            q.push(y);
            q.push(cost);
            ++edgeCounter;
        }
    }
    cout << edgeCounter << endl;
    q.display();
}

// **************************************************
// main: driver code
// **************************************************

int main()
{
    Queue q;

    int x, y;
    int i = 0;
    long long weight;
    initialize();

    ifstream file("input.txt");
    file >> edges;

    for (int i = 0; i < edges; ++i)
    {
        file >> x >> y >> weight;
        p[i] = make_pair(weight, make_pair(x, y));
    }

    // Edges sorted in the ascending order

    sort(p, p + edges);
    // Peforms the Kruskal algorithm and display the result

    kruskal(p);

    return 0;
}