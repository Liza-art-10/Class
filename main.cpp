#include <iostream>
#include <string>

using namespace std;

// Базовый класс Car
class Car {
private:
    string brand;         // Торговая марка
    int cylinder_count;   // Число цилиндров
    int power;            // Мощность (л.с.)
    static int count;     // Статический счетчик объектов

public:
    // Конструкторы
    Car() : brand("Unknown"), cylinder_count(0), power(0) {
        count++;  // Увеличиваем счетчик при создании объекта
        cout << "Car default constructor. Total objects: " << count << endl;
    }
    
    Car(string b, int c, int p) : brand(b), cylinder_count(c), power(p) {
        count++;
        cout << "Car parameterized constructor. Total objects: " << count << endl;
    }
    
    Car(const Car& other) : brand(other.brand), cylinder_count(other.cylinder_count), power(other.power) {
        count++;
        cout << "Car copy constructor. Total objects: " << count << endl;
    }

    // Деструктор
    ~Car() {
        count--;  // Уменьшаем счетчик при уничтожении объекта
        cout << "Car destructor. Total objects: " << count << endl;
    }

    // Геттеры
    string getBrand() const { return brand; }
    int getCylinderCount() const { return cylinder_count; }
    int getPower() const { return power; }

    // Сеттеры
    void setBrand(string b) { brand = b; }
    void setCylinderCount(int c) { cylinder_count = c; }
    void setPower(int p) { power = p; }

    // Оператор присваивания
    Car& operator=(const Car& other) {
        if (this != &other) {  // Защита от самоприсваивания
            brand = other.brand;
            cylinder_count = other.cylinder_count;
            power = other.power;
        }
        cout << "Car assignment operator called." << endl;
        return *this;
    }

    // Дружественные операторы ввода/вывода
    friend ostream& operator<<(ostream& os, const Car& car);
    friend istream& operator>>(istream& is, Car& car);
    
    // Дружественная функция для подсчёта объектов
    friend int count();
};

// Инициализация статической переменной
int Car::count = 0;

// Оператор вывода для Car
ostream& operator<<(ostream& os, const Car& car) {
    os << "Brand: " << car.brand 
       << ", Cylinders: " << car.cylinder_count 
       << ", Power: " << car.power << " hp";
    return os;
}

// Оператор ввода для Car
istream& operator>>(istream& is, Car& car) {
    cout << "Enter brand: ";
    is >> car.brand;
    cout << "Enter cylinder count: ";
    is >> car.cylinder_count;
    cout << "Enter power (hp): ";
    is >> car.power;
    return is;
}

// Функция подсчёта объектов
int count() {
    return Car::count;
}

// Производный класс Lorry (грузовик)
class Lorry : public Car {
private:
    int load_capacity;  // Грузоподъёмность (кг)

public:
    // Конструкторы
    Lorry() : Car(), load_capacity(0) {
        cout << "Lorry default constructor." << endl;
    }
    
    Lorry(string b, int c, int p, int l) : Car(b, c, p), load_capacity(l) {
        cout << "Lorry parameterized constructor." << endl;
    }
    
    Lorry(const Lorry& other) : Car(other), load_capacity(other.load_capacity) {
        cout << "Lorry copy constructor." << endl;
    }

    // Деструктор
    ~Lorry() {
        cout << "Lorry destructor." << endl;
    }

    // Геттер и сеттер для грузоподъёмности
    int getLoadCapacity() const { return load_capacity; }
    void setLoadCapacity(int l) { load_capacity = l; }

    // Оператор присваивания
    Lorry& operator=(const Lorry& other) {
        if (this != &other) {
            Car::operator=(other);  // Вызов оператора присваивания базового класса
            load_capacity = other.load_capacity;
        }
        cout << "Lorry assignment operator called." << endl;
        return *this;
    }

    // Дружественные операторы ввода/вывода
    friend ostream& operator<<(ostream& os, const Lorry& lorry);
    friend istream& operator>>(istream& is, Lorry& lorry);
};

// Оператор вывода для Lorry
ostream& operator<<(ostream& os, const Lorry& lorry) {
    // Вывод информации из базового класса
    os << static_cast<const Car&>(lorry) 
       << ", Load capacity: " << lorry.load_capacity << " kg";
    return os;
}

// Оператор ввода для Lorry
istream& operator>>(istream& is, Lorry& lorry) {
    // Ввод информации для базового класса
    is >> static_cast<Car&>(lorry);
    cout << "Enter load capacity (kg): ";
    is >> lorry.load_capacity;
    return is;
}

int main() {
    cout << "\n===== DEMONSTRATING CAR CLASS =====\n";
    
    // Создание объектов Car разными способами
    Car car1;
    cout << "Car1 (default): " << car1 << endl;
    
    Car car2("Toyota", 4, 150);
    cout << "Car2 (parameterized): " << car2 << endl;
    
    Car car3 = car2;  // Копирование
    cout << "Car3 (copy of car2): " << car3 << endl;
    
    // Использование сеттеров
    car1.setBrand("Honda");
    car1.setCylinderCount(6);
    car1.setPower(200);
    cout << "Car1 after setters: " << car1 << endl;
    
    // Присваивание
    car3 = car1;
    cout << "Car3 after assignment: " << car3 << endl;
    
    // Ввод с клавиатуры
    Car car4;
    cin >> car4;
    cout << "Car4 (user input): " << car4 << endl;

    cout << "\n===== DEMONSTRATING LORRY CLASS =====\n";
    
    // Создание объектов Lorry
    Lorry lorry1;
    cout << "Lorry1 (default): " << lorry1 << endl;
    
    Lorry lorry2("Volvo", 6, 350, 5000);
    cout << "Lorry2 (parameterized): " << lorry2 << endl;
    
    Lorry lorry3 = lorry2;  // Копирование
    cout << "Lorry3 (copy of lorry2): " << lorry3 << endl;
    
    // Использование сеттеров
    lorry1.setBrand("MAN");
    lorry1.setCylinderCount(8);
    lorry1.setPower(450);
    lorry1.setLoadCapacity(10000);
    cout << "Lorry1 after setters: " << lorry1 << endl;
    
    // Присваивание
    lorry3 = lorry1;
    cout << "Lorry3 after assignment: " << lorry3 << endl;
    
    // Ввод с клавиатуры
    Lorry lorry4;
    cin >> lorry4;
    cout << "Lorry4 (user input): " << lorry4 << endl;

    cout << "\n===== OBJECT COUNT DEMONSTRATION =====\n";
    cout << "Total objects before scope: " << count() << endl;
    
    {  // Вложенная область видимости
        Car tempCar("Ford", 4, 120);
        Lorry tempLorry("Scania", 6, 400, 8000);
        cout << "Total objects inside scope: " << count() << endl;
    }  // tempCar и tempLorry уничтожаются здесь
    
    cout << "Total objects after scope: " << count() << endl;
    
    cout << "\n===== FINAL OBJECT COUNT =====\n";
    cout << "Total objects at program end: " << count() << endl;
    
    return 0;
}
