#include "Queue.h"


Queue::Queue(int capacity)
	: data(nullptr), capacity(capacity + 1), front(0), rear(0)
{
    data = new char[capacity];
}

Queue::~Queue()
{
	delete[] data;
	data = nullptr;
}

bool Queue::Push(char cmd)
{
    if (IsFull())
    {
        return false;
    }
	rear = (rear + 1) % capacity;
    data[rear] = cmd;
	return true;
}

bool Queue::Pop(char& outCmd)
{
    if (IsEmpty())
    {
        return false;
    }
    front = (front + 1) % capacity;
    outCmd = data[front];
	return true;
}


bool Queue::IsEmpty() const
{
    return front == rear;
}

bool Queue::IsFull() const
{
    return ((rear + 1) % capacity) == front;
}
