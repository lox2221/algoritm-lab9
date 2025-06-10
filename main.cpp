#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

#define SIZE 29 // Кількість елементів: (10 * 8) % 51 = 29

// Структура для зберігання даних про туриста
struct Tourist {
    string passport; // Код паспорта (2 літери + 6 цифр)
    int days;       // Кількість днів
};

// Функція для генерації коду паспорта
string generatePassport() {
    string passport = "";
    passport += char('A' + rand() % 26); // Перша літера
    passport += char('A' + rand() % 26); // Друга літера
    for (int i = 0; i < 6; i++) {
        passport += to_string(rand() % 10); // 6 цифр
    }
    return passport;
}

// Клас для реалізації стека
class Stack {
private:
    Tourist arr[SIZE];
    int top;
public:
    Stack() { top = -1; }
    
    bool isEmpty() { return top == -1; }
    bool isFull() { return top == SIZE - 1; }
    
    void push(Tourist tourist) {
        if (!isFull()) {
            arr[++top] = tourist;
            cout << "Pushed to stack: Passport = " << tourist.passport 
                 << ", Days = " << tourist.days << endl;
        } else {
            cout << "Stack is full!" << endl;
        }
    }
    
    Tourist pop() {
        if (!isEmpty()) {
            Tourist tourist = arr[top--];
            cout << "Popped from stack: Passport = " << tourist.passport 
                 << ", Days = " << tourist.days << endl;
            return tourist;
        } else {
            cout << "Stack is empty!" << endl;
            return {"", 0};
        }
    }
    
    void display() {
        if (isEmpty()) {
            cout << "Stack is empty" << endl;
            return;
        }
        cout << "Stack contents:" << endl;
        for (int i = 0; i <= top; i++) {
            cout << "Tourist " << i + 1 << ": Passport = " << arr[i].passport 
                 << ", Days = " << arr[i].days << endl;
        }
    }
};

// Клас для реалізації черги
class Queue {
private:
    Tourist arr[SIZE];
    int front, rear;
public:
    Queue() { front = 0; rear = -1; }
    
    bool isEmpty() { return rear < front; }
    bool isFull() { return rear == SIZE - 1; }
    
    void enqueue(Tourist tourist) {
        if (!isFull()) {
            arr[++rear] = tourist;
            cout << "Enqueued to queue: Passport = " << tourist.passport 
                 << ", Days = " << tourist.days << endl;
        } else {
            cout << "Queue is full!" << endl;
        }
    }
    
    Tourist dequeue() {
        if (!isEmpty()) {
            Tourist tourist = arr[front++];
            cout << "Dequeued from queue: Passport = " << tourist.passport 
                 << ", Days = " << tourist.days << endl;
            return tourist;
        } else {
            cout << "Queue is empty!" << endl;
            return {"", 0};
        }
    }
    
    void display() {
        if (isEmpty()) {
            cout << "Queue is empty" << endl;
            return;
        }
        cout << "Queue contents:" << endl;
        for (int i = front; i <= rear; i++) {
            cout << "Tourist " << i - front + 1 << ": Passport = " << arr[i].passport 
                 << ", Days = " << arr[i].days << endl;
        }
    }
};

int main() {
    srand(time(NULL)); // Ініціалізація генератора випадкових чисел
    
    Stack stack;
    Queue queue;
    Tourist tourists[SIZE];
    
    // Генерація даних про туристів
    cout << "Generated tourist data:" << endl;
    for (int i = 0; i < SIZE; i++) {
        tourists[i].passport = generatePassport();
        tourists[i].days = (rand() % 321) - 160; // Від -160 до 160
        cout << "Tourist " << i + 1 << ": Passport = " << tourists[i].passport 
             << ", Days = " << tourists[i].days << endl;
    }
    cout << endl;
    
    // Демонстрація роботи стека
    cout << "=== Stack Operations ===" << endl;
    for (int i = 0; i < SIZE; i++) {
        stack.push(tourists[i]);
    }
    stack.display();
    
    cout << "\nPopping 5 elements from stack:" << endl;
    for (int i = 0; i < 5; i++) {
        stack.pop();
    }
    stack.display();
    
    // Демонстрація роботи черги
    cout << "\n=== Queue Operations ===" << endl;
    for (int i = 0; i < SIZE; i++) {
        queue.enqueue(tourists[i]);
    }
    queue.display();
    
    cout << "\nDequeuing 5 elements from queue:" << endl;
    for (int i = 0; i < 5; i++) {
        queue.dequeue();
    }
    queue.display();
    
    return 0;
}