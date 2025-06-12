#ifndef INTERFACE_STACK_H
#define INTERFACE_STACK_H

class IStack {
public:
    virtual ~IStack() = default;

    virtual void push(int x) = 0;
    virtual int pop() = 0;
    virtual int size() const = 0;
    virtual void clear() = 0;
};

#endif