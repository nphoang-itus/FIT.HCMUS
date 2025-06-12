#ifndef STACK_BY_LINKED_LIST_H
#define STACK_BY_LINKED_LIST_H

#include "IStack.h"
#include <stdexcept>

class StackByLinkedList : public IStack {
private:
    struct _Node {
        int data;
        _Node* next;

        _Node(int x) : data(x), next(nullptr) {}
    };

    _Node* _top;

    _Node* _createNode(int x) {
        return new _Node(x);
    }

public:
    StackByLinkedList() : _top(nullptr) {}
    
    ~StackByLinkedList() override {
        if (_top) {
            clear();
        }
    }

    bool isEmpty() {
        return !_top;
    }

    void push(int x) override {
        _Node* newNode = _createNode(x);
        
        // stack is empty
        if (isEmpty()) {
            _top = newNode;
            return;
        }

        // stack is not empty --> add head into linkedlist
        newNode->next = _top;
        _top = newNode;
    }

    int pop() override {
        // stack is empty
        if (isEmpty()) {
            throw std::invalid_argument("Stack is empty so you can't pop element");
        }

        int result = _top->data;

        _Node* nodeToDel = _top;
        _top = _top->next;

        delete nodeToDel;

        return result;
    }

    int size() const override {
        _Node* curNode = _top;
        int result = 0;

        while (curNode) {
            result++;
            curNode = curNode->next;
        }


        return result;
    }

    void clear() override {
        while (_top) {
            _Node* delNode = _top;
            _top = _top->next;
            delete delNode;
        }
    }
};

#endif