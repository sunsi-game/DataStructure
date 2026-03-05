#pragma once
// 키보드 이벤트를 저장할 수 있는 입력 큐
class Queue
{
public :
	explicit Queue(int capacity = 64);
	~Queue();

	bool Push(char cmd);
	bool Pop(char& outCmd);

	bool IsEmpty() const;
	bool IsFull() const;

private :
	char* data;
	int capacity; // 큐의 최대 크기.
	int front; // Pop 위치.
	int rear;  // Push 위치.
};

