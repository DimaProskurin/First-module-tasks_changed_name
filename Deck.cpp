#include <cstdio>

using namespace std;

const int Number = -123456;

void init(int* buffer, int n) {
	for (int i = 0; i < n; i++) {
		buffer[i] = Number;
	}
}

class Deck {
private:
	int head;
	int tail;
	int* buffer;
	int bufferSize;
	int realSize;

	void grow();

public:
	Deck() {
		head = 0;
		tail = 0;
		bufferSize = 2;
		realSize = 0;
		buffer = new int[bufferSize];
		init(buffer, bufferSize);
	}

	~Deck() {
		delete[] buffer;
	}

	void pushBack(int element);
	void pushFront(int element);
	int popBack();
	int popFront();
};

void Deck::grow() {
	int newBufferSize = bufferSize * 2;
	int* newBuffer = new int[newBufferSize];
	init(newBuffer, newBufferSize);

	int j = 0;
	for (int i = head + 1; j < bufferSize; i = (i + 1) % bufferSize, j++) {
		newBuffer[j] = buffer[i % bufferSize];
	}

	delete[] buffer;
	buffer = newBuffer;
	bufferSize = newBufferSize;

	head = bufferSize - 1;
	tail = realSize - 1;
}

void Deck::pushBack(int element) {
	if (realSize == bufferSize) {
		grow();
	}

	tail = (tail + 1) % bufferSize;
	buffer[tail] = element;
	realSize++;
}

void Deck::pushFront(int element) {
	if (bufferSize == realSize) {
		grow();
	}

	buffer[head] = element;
	head = (head - 1 + bufferSize) % bufferSize;
	realSize++;
}

int Deck::popBack() {
	int result = buffer[tail];
	buffer[tail] = Number;
	tail = (tail - 1 + bufferSize) % bufferSize;
	if (result == Number) {
		return -1;
	}
	else {
		realSize--;
		return result;
	}
}

int Deck::popFront() {
	int result = buffer[(head + 1) % bufferSize];
	buffer[(head + 1) % bufferSize] = Number;
	head = (head + 1) % bufferSize;
	if (result == Number) {
		return -1;
	}
	else {
		realSize--;
		return result;
	}
}

int main() {
	Deck MyDeck;
	bool result = true;
	int n;
	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		int a, b;
		scanf("%d %d", &a, &b);

		switch (a) {
			case 1:
				MyDeck.pushFront(b);
				break;
			case 2:
				if (MyDeck.popFront() != b) {
					result = false;
				}
				break;
			case 3:
				MyDeck.pushBack(b);
				break;
			case 4:
				if (MyDeck.popBack() != b) {
					result = false;
				}
				break;
		}
	}

	if (result) {
		printf("YES");
	}
	else {
		printf("NO");
	}

	return 0;
}
