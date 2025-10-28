// 3_3. Реализовать очередь с помощью двух стеков.
// Требования: Очередь должна быть реализована в виде класса. Стек тоже должен быть реализован в виде класса (на основе динамического массива).

#include <iostream>
#include <exception>

class Stack {
    public:
        Stack() : stack(new int[16]), size(0), capacity(16) {}
        ~Stack() {
            delete[] stack;
        }

        void push(int value) {
            if (size == capacity) {
                capacity *= 2;
                int* new_stack = new int[capacity];
                for (int i = 0; i < size; ++i) {
                    new_stack[i] = stack[i];
                }
                delete[] stack;
                stack = new_stack;
            }
            stack[size++] = value;
        }
        int pop() {
            if (isEmpty())
                throw std::out_of_range("Stack is empty!");
            return stack[--size];
        }

        int peek() {
            if (isEmpty())
                throw std::out_of_range("Stack is empty!");
            return stack[size - 1];
        }

        bool isEmpty() {
            return size == 0;
        }

    private:
        int *stack;
        int size, capacity;
};

class Queue {
    public:
        Queue() : stack1(new Stack()), stack2(new Stack()) {}
        void enqueue(int value) {
            stack1->push(value);
        }
        int dequeue() {
            if (isEmpty())
                throw std::out_of_range("Queue is empty!");
            if (stack2->isEmpty())
                dumpStack1();
            return stack2->pop();
        }
        int peek() {
            if (isEmpty())
                throw std::out_of_range("Queue is empty!");
            if (stack2->isEmpty())
                dumpStack1();
            return stack2->peek();
        }

        int isEmpty() {
            return stack1->isEmpty() && stack2->isEmpty();
        }

    private:
        Stack *stack1, *stack2;

        void dumpStack1() {
            while (!stack1->isEmpty()) {
                stack2->push(stack1->pop());
            }
        }
};

int main() {
    int cmd_count;
    std::cin >> cmd_count;

    int status = 0;

    Queue q = Queue();

    for (int i = 0; i < cmd_count; ++i) {
        int cmd, arg; 
        std::cin >> cmd >> arg;
        if (cmd == 2) {
            if ((q.isEmpty() && arg != -1) || (!q.isEmpty() && arg != q.dequeue())) {
                status = 1;
                break;
            }
        }
        else {
            q.enqueue(arg);
        }
    }

    std::cout << ((!status) ? "YES" : "NO") << std::endl;

    return 0;
}