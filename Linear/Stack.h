#pragma once

// Undo 목록을 저장할 스택.
// Redo 목록을 저장할 스택.
class Stack
{
public :
	explicit Stack(int capacity = 128);
	~Stack();

	bool Push(char cmd);
	bool Pop(char& outCmd);
	bool Peek(char& outCmd) const;

	bool IsEmpty() const;
	void Clear();

	// top부터 아래로 출력하기 위해.
	int Size() const;
	char GetAt(int index) const; // 0이면 top, 1이면 그 아래.

private :
	char* data;
	int capacity; // 스택의 최대 크기.
	int top; // Push 위치. Pop할 때는 top - 1 위치에서 Pop.
};

