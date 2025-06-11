
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

// Структура для даних туриста
struct Tourist {
    int passportCode;
    string surname;
    int days;

    void print() const {
        cout << left << setw(10) << passportCode << setw(15) << surname << setw(5) << days << endl;
    }
};

// Вузол для двонаправленого зв’язного списку (дек)
struct Node {
    Tourist data;
    Node* prev;
    Node* next;
    Node(const Tourist& t) : data(t), prev(nullptr), next(nullptr) {}
};

// Клас для дека
class Deque {
private:
    Node* front;
    Node* back;
    int size;

public:
    Deque() : front(nullptr), back(nullptr), size(0) {}

    ~Deque() {
        while (front) {
            Node* temp = front;
            front = front->next;
            delete temp;
        }
    }

    void push_front(const Tourist& t) {
        Node* newNode = new Node(t);
        if (size == 0) {
            front = back = newNode;
        } else {
            newNode->next = front;
            front->prev = newNode;
            front = newNode;
        }
        size++;
    }

    void push_back(const Tourist& t) {
        Node* newNode = new Node(t);
        if (size == 0) {
            front = back = newNode;
        } else {
            newNode->prev = back;
            back->next = newNode;
            back = newNode;
        }
        size++;
    }

    void pop_front() {
        if (size == 0) {
            cout << "Дек порожній!" << endl;
            return;
        }
        Node* temp = front;
        front = front->next;
        if (front) {
            front->prev = nullptr;
        } else {
            back = nullptr;
        }
        delete temp;
        size--;
    }

    void pop_back() {
        if (size == 0) {
            cout << "Дек порожній!" << endl;
            return;
        }
        Node* temp = back;
        back = back->prev;
        if (back) {
            back->next = nullptr;
        } else {
            front = nullptr;
        }
        delete temp;
        size--;
    }

    void print() const {
        cout << "Вміст дека:" << endl;
        cout << left << setw(10) << "Паспорт" << setw(15) << "Прізвище" << setw(5) << "Дні" << endl;
        cout << string(30, '-') << endl;
        Node* current = front;
        while (current) {
            current->data.print();
            current = current->next;
        }
        cout << endl;
    }
};

int main() {
    srand(time(NULL));
    Deque deque;
    const int T = 12; // Кількість туристів (варіант 8)
    const int N = 8;  // Номер варіанту
    const int MIN_VAL = -20 * N; // -160
    const int MAX_VAL = 20 * N;  // 160

    // Ініціалізація 12 туристів
    cout << "Ініціалізація 12 туристів із випадковими даними:" << endl;
    for (int i = 0; i < T; i++) {
        Tourist t;
        t.passportCode = MIN_VAL + rand() % (MAX_VAL - MIN_VAL + 1);
        t.surname = "Турист" + to_string(i + 1);
        t.days = MIN_VAL + rand() % (MAX_VAL - MIN_VAL + 1);
        deque.push_back(t);
    }

    // Виведення початкового дека
    deque.print();

    // Демонстрація операцій
    cout << "Додавання нового туриста на початок:" << endl;
    Tourist t1 = {1000, "НовийТурист1", 50};
    deque.push_front(t1);
    deque.print();

    cout << "Додавання нового туриста в кінець:" << endl;
    Tourist t2 = {2000, "НовийТурист2", 75};
    deque.push_back(t2);
    deque.print();

    cout << "Видалення туриста з початку:" << endl;
    deque.pop_front();
    deque.print();

    cout << "Видалення туриста з кінця:" << endl;
    deque.pop_back();
    deque.print();

    return 0;
}
