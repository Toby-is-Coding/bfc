#pragma once
#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* fd; //forward
    Node* bk; //backward
};

class Tur {
public:
    Tur() : current(NULL), reg(0)
    {
        current = new Node;
        current->fd = NULL;
        current->bk = NULL;
        current->data = 0;
    }
    ~Tur() {
        Node* tmp;
        while (current->bk != NULL) {
            current = current->bk;
        }
        while (current != NULL) {
            tmp = current;
            current = current->fd;
            delete tmp;
        }
    }

    void right() { //move right
        if (current->fd != NULL) {
            current = current->fd;
        }
        else {
            current->fd = new Node;
            Node* tmp = current;
            current = current->fd;
            current->data = 0;
            current->bk = tmp;
            current->fd = NULL;
        }
    }
    void left() { //move left
        if (current->bk != NULL) {
            current = current->bk;
        }
        else {
            current->bk = new Node;
            Node* tmp = current;
            current = current->bk;
            current->data = 0;
            current->fd = tmp;
            current->bk = NULL;
        }
    }
    const int get() const { //get data
        return current->data;
    }
    void put(int data) { //set data to input
        current->data = data;
    }
    void upload() { //upload data to register
        reg = current->data;
    }
    void download() { //download register data to current block
        current->data = reg;
    }
    void add() { //increment
        current->data++;
    }
    void sub() { //decrement
        current->data--;
    }
    void zeroify() { //set data to 0
        current->data = 0;
    }

    friend ostream& operator<<(ostream& os, Tur& tur) {
        Node* tmp = tur.current;
        while (tmp->bk != NULL) {
            tmp = tmp->bk;
        }
        while (tmp != NULL) {
            os << '[' << tmp->data << ']';
            tmp = tmp->fd;
        }
        return os;
    }

private:
    Node* current;
    int reg; //register
};