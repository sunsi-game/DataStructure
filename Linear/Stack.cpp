#include "Stack.h"

Stack::Stack(int capacity)
    : data(nullptr), capacity(capacity), top(-1)
{
    data = new char[capacity];
}

Stack::~Stack()
{
    delete[] data;
	data = nullptr;
}

bool Stack::IsEmpty() const
{
    return top < 0;
}

bool Stack::Push(char cmd)
{
    if (top >= capacity - 1)
    {
        return false;
    }
    data[++top] = cmd;
    return true;
}

bool Stack::Pop(char& outCmd)
{
    if (IsEmpty())
    {
        return false;
    }
    outCmd = data[top--];
    return true;
}

bool Stack::Peek(char& outCmd) const
{
    if (IsEmpty())
    {
        return false;
    }
    outCmd = data[top];
	return true;
}

void Stack::Clear()
{
	top = -1;
}

int Stack::Size() const
{
	return top + 1;
}

char Stack::GetAt(int index) const
{
    if (index < 0 || index > top)
    {
        return '\0';
    }
	return data[top - index];
}
