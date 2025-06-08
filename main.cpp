#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

// Структура для зберігання даних про туриста
struct Tourist {
    string passport;    
    string surname;      
    int days;          
};

// Вузол однозв’язного списку
struct Node {
    Tourist data;
    Node* next;
    Node(Tourist t) : data(t), next(nullptr) {}
};

// Клас для роботи з однозв’язним списком
class SinglyLinkedList {
private:
    Node* head;
    int size;

public:
    SinglyLinkedList() : head(nullptr), size(0) {}

    // Очистити список
    void clear() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        size = 0;
        display();
    }

    // Додати елемент до списку (в кінець)
    void append(Tourist t) {
        Node* newNode = new Node(t);
        if (!head) {
            head = newNode;
        } else {
            Node* current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = newNode;
        }
        size++;
        display();
    }

    // Вилучити вказаний елемент зі списку (за індексом)
    void remove(int index) {
        if (index < 0 || index >= size) {
            cout << "Неправильний індекс!" << endl;
            return;
        }
        Node* current = head;
        Node* prev = nullptr;
        for (int i = 0; i < index; i++) {
            prev = current;
            current = current->next;
        }
        if (!prev) {
            head = current->next;
        } else {
            prev->next = current->next;
        }
        delete current;
        size--;
        display();
    }

    // Визначити кількість елементів у списку
    int getSize() {
        cout << "Кількість елементів у списку: " << size << endl;
        return size;
    }

    // Поміняти два сусідні елементи місцями після позиції p
    void swapAfter(int p) {
        if (p < 0 || p >= size - 1) {
            cout << "Неможливо виконати обмін для позиції " << p << endl;
            return;
        }
        Node* current = head;
        for (int i = 0; i < p; i++) {
            current = current->next;
        }
        Node* first = current->next;
        Node* second = first->next;
        first->next = second->next;
        second->next = first;
        if (current == head && p == 0) {
            head = second;
        } else {
            current->next = second;
        }
        display();
    }

    // Об’єднати два списки в один (дописування другого в кінець першого)
    void merge(SinglyLinkedList& other) {
        if (!other.head) return;
        if (!head) {
            head = other.head;
            size = other.size;
        } else {
            Node* current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = other.head;
            size += other.size;
        }
        other.head = nullptr;
        other.size = 0;
        display();
    }

    // Отримати доступ до k-го вузла списку
    Tourist* getNode(int k) {
        if (k < 0 || k >= size) {
            cout << "Неправильний індекс!" << endl;
            return nullptr;
        }
        Node* current = head;
        for (int i = 0; i < k; i++) {
            current = current->next;
        }
        cout << "Елемент за індексом " << k << ": " << current->data.passport << ", "
             << current->data.surname << ", " << current->data.days << " днів" << endl;
        return &current->data;
    }

    // Включити новий вузол перед k-им вузлом
    void insertBefore(int k, Tourist t) {
        if (k < 0 || k > size) {
            cout << "Неправильний індекс!" << endl;
            return;
        }
        Node* newNode = new Node(t);
        if (k == 0) {
            newNode->next = head;
            head = newNode;
        } else {
            Node* current = head;
            for (int i = 0; i < k - 1; i++) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
        size++;
        display();
    }

    // Розбити список на два за позицією k
    SinglyLinkedList split(int k) {
        SinglyLinkedList newList;
        if (k < 0 || k >= size) {
            cout << "Неправильний індекс для розбиття!" << endl;
            return newList;
        }
        Node* current = head;
        for (int i = 0; i < k - 1; i++) {
            if (!current) break;
            current = current->next;
        }
        if (current) {
            newList.head = current->next;
            current->next = nullptr;
            int newSize = 0;
            Node* temp = newList.head;
            while (temp) {
                newSize++;
                temp = temp->next;
            }
            newList.size = newSize;
            size -= newSize;
        }
        cout << "Перший список:" << endl;
        display();
        cout << "Другий список:" << endl;
        newList.display();
        return newList;
    }

    // Зробити копію списку
    SinglyLinkedList copy() {
        SinglyLinkedList newList;
        Node* current = head;
        while (current) {
            newList.append(current->data);
            current = current->next;
        }
        cout << "Копія списку:" << endl;
        newList.display();
        return newList;
    }

    // Знайти вузол із заданим значенням у полі (наприклад, прізвище)
    Node* findBySurname(string surname) {
        Node* current = head;
        int index = 0;
        while (current) {
            if (current->data.surname == surname) {
                cout << "Знайдено елемент за прізвищем " << surname << " на позиції " << index << endl;
                return current;
            }
            current = current->next;
            index++;
        }
        cout << "Елемент із прізвищем " << surname << " не знайдено" << endl;
        return nullptr;
    }

    // Виведення списку
    void display() {
        cout << "Поточний стан списку:" << endl;
        Node* current = head;
        int index = 0;
        while (current) {
            cout << index << ": " << current->data.passport << ", "
                 << current->data.surname << ", " << current->data.days << " днів" << endl;
            current = current->next;
            index++;
        }
        if (!head) cout << "Список порожній" << endl;
        cout << endl;
    }

    // Деструктор для звільнення пам’яті
    ~SinglyLinkedList() {
        clear();
    }
};

// Функція для генерації випадкових даних туристів
Tourist generateTourist(int variant) {
    Tourist t;
    t.passport = "XX" + to_string(rand() % 1000000); // Наприклад, XX123456
    string surnames[] = {"Smith", "Johnson", "Williams", "Brown", "Jones", "Garcia", "Miller", "Davis", "Rodriguez", "Martinez", "Hernandez", "Lopez"};
    t.surname = surnames[rand() % 12];
    t.days = rand() % (20 * variant) + 1; // Від 1 до 20*N
    return t;
}

int main() {
    srand(time(NULL));
    setlocale(LC_ALL, "uk_UA.UTF-8");

    const int T = 12; // Кількість елементів за варіантом
    const int variant = 8;

    SinglyLinkedList list1, list2;

    // Ініціалізація списку з T=12 елементів
    cout << "Ініціалізація першого списку:" << endl;
    for (int i = 0; i < T; i++) {
        list1.append(generateTourist(variant));
    }

    // Визначення кількості елементів
    list1.getSize();

    // Додавання нового елемента
    cout << "Додавання нового туриста:" << endl;
    Tourist newTourist = {"YY123456", "Taylor", 10};
    list1.append(newTourist);

    // Вилучення елемента (наприклад, за індексом 2)
    cout << "Вилучення елемента за індексом 2:" << endl;
    list1.remove(2);

    // Обмін двох сусідніх елементів після позиції 3
    cout << "Обмін елементів після позиції 3:" << endl;
    list1.swapAfter(3);

    // Доступ до k-го вузла (наприклад, k=5)
    cout << "Доступ до 5-го елемента:" << endl;
    list1.getNode(5);

    // Включення нового вузла перед k-им (k=4)
    cout << "Включення нового вузла перед 4-м:" << endl;
    Tourist beforeTourist = {"ZZ654321", "Wilson", 15};
    list1.insertBefore(4, beforeTourist);

    // Пошук за прізвищем
    cout << "Пошук туриста з прізвищем 'Smith':" << endl;
    list1.findBySurname("Smith");

    // Створення другого списку
    cout << "Ініціалізація другого списку:" << endl;
    for (int i = 0; i < 5; i++) {
        list2.append(generateTourist(variant));
    }

    // Об’єднання списків
    cout << "Об’єднання двох списків:" << endl;
    list1.merge(list2);

    // Розбиття списку на два за позицією 6
    cout << "Розбиття списку на два за позицією 6:" << endl;
    SinglyLinkedList newList = list1.split(6);

    // Копіювання списку
    cout << "Копіювання списку:" << endl;
    SinglyLinkedList copyList = list1.copy();

    // Очищення списку
    cout << "Очищення першого списку:" << endl;
    list1.clear();

    return 0;
}