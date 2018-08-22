#include <iostream>
#include <cassert>
#include <cstdlib>
#include <cstdio>
#include <string>

using namespace std;

class MyStack {
private:
	string* buffer;
	int size;
	int top;

	void grow();

public:
	MyStack() {
		size = 1;
		buffer = new string[size];
		top = -1;
	}
	~MyStack() {
		delete[] buffer;
	}

	bool isEmpty() {
		return top == -1;
	}

	void push(string element) {
		if (top == (size - 1)) {
			grow();
		}
		buffer[++top] = element;
	}

	string pop() {
		if (!isEmpty()) {
			return buffer[top--];
		}
		else {
			assert(0);
		}
	}
};

void MyStack::grow() {
	int newsize = size * 2;
	string* newbuffer = new string[newsize];
	for (int i = 0; i < size; i++) {
		newbuffer[i] = buffer[i];
	}
	delete[] buffer;
	buffer = newbuffer;
	size = newsize;
}

int createArr(string* arr, string str) {
	int count = 0;

	int i = 0;
	while (i < str.size()) {
		string number = "";
		while (i < str.size() && str.at(i) >= '0' && str.at(i) <= '9') {
			number += str.at(i);
			i++;
		}
		if (number == "") {
			arr[count] = str.at(i);
			i++;
		}
		else {
			arr[count] = number;
		}
		count++;
	}

	return count;
}

void toPostFix(string* arr, int count, MyStack* postFix, MyStack* tmpStack) {
	for (int i = 0; i < count; i++) {
		string current = arr[i];

		if (current.at(0) >= '0' && current.at(0) <= '9') {
			postFix->push(current);
		}
		else {
			if (current.at(0) == '(') {
				tmpStack->push(current);
			}
			else {
				if (current.at(0) == ')') {
					string tmp = tmpStack->pop();
					while (tmp.at(0) != '(') {
						postFix->push(tmp);
						tmp = tmpStack->pop();
					}
				}
				else {
					if (tmpStack->isEmpty()) {
						tmpStack->push(current);
					}
					else {
						string prev = tmpStack->pop();
						if (current.at(0) == '-' || current.at(0) == '+') {
							if (prev.at(0) != '(') {
								postFix->push(prev);
								tmpStack->push(current);
							}
							else {
								tmpStack->push(prev);
								tmpStack->push(current);
							}
						}
						if (current.at(0) == '/') {
							if (prev.at(0) == '*') {
								postFix->push(prev);
								tmpStack->push(current);
							}
							else {
								tmpStack->push(prev);
								tmpStack->push(current);
							}
						}
						if (current.at(0) == '*') {
							if (prev.at(0) == '/') {
								postFix->push(prev);
								tmpStack->push(current);
							}
							else {
								tmpStack->push(prev);
								tmpStack->push(current);
							}
						}
					}
				}
			}
		}
	}
	while (!tmpStack->isEmpty()) {
		string tmp = tmpStack->pop();
		postFix->push(tmp);
	}

	while (!postFix->isEmpty()) {
		tmpStack->push(postFix->pop());
	}
}

void toResultStack(MyStack* resultStack, MyStack* tmpStack) {
	while (!tmpStack->isEmpty()) {
		string current = tmpStack->pop();
		if (current.at(0) >= '0' && current.at(0) <= '9') {
			resultStack->push(current);
		}
		else {
			int first = stoi(resultStack->pop());
			int second = stoi(resultStack->pop());
			switch (current.at(0)) {
			case '+':
				resultStack->push(to_string(first + second));
				break;
			case '*':
				resultStack->push(to_string(first * second));
				break;
			case '-':
				resultStack->push(to_string(second - first));
				break;
			case '/':
				resultStack->push(to_string(second / first));
				break;
			}
		}
	}
}

int main() {
	string str;
	cin >> str;
	string* arr = new string[str.size()];
	int count = createArr(arr, str);

	MyStack postFix;
	MyStack tmpStack;
	toPostFix(arr, count, &postFix, &tmpStack);

	MyStack resultStack;
	toResultStack(&resultStack, &tmpStack);

	cout << resultStack.pop();
	delete[] arr;
	return 0;
}
