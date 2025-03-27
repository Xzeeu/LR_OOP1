// LR_OOP1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "Patterntemplates.h"

using namespace std;


class Smart_home {
private:
    bool russian_language;

protected:
    string voice_assistant;
    string protocols;
    string OS;


public:
    Smart_home(); // Конструктор
    virtual ~Smart_home(); // Деструктор

    string get_voice_assistant() const { return voice_assistant; }
    bool get_russian_language() const { return russian_language; }
    string getOS() const { return OS; }

    virtual void music() = 0;

};

Smart_home::Smart_home() : voice_assistant("No"), russian_language(false), protocols("wi-fi"), OS("Windows, Android, iOS"){}

Smart_home::~Smart_home(){}

class yandex_Alice : public Smart_home {
public:
    yandex_Alice();
    ~yandex_Alice();

    string get_voice_assistant() const;

    void music();
};

yandex_Alice::yandex_Alice() : Smart_home()
{
    voice_assistant = "Alice";
    protocols = "Zigbee, Matter, Wi-Fi";
}

yandex_Alice::~yandex_Alice(){}

string yandex_Alice::get_voice_assistant() const {return Smart_home::get_voice_assistant();}

void yandex_Alice::music() {
    cout << "Включаю Яндекс Музыку" << endl;
}

class google_home : public Smart_home {
public:
    google_home();
    ~google_home();

    void music();
};

google_home::google_home() : Smart_home() {
    voice_assistant = "Google Assistant";
    protocols = "Bluetooth, Matter, Wi-Fi";
}

google_home::~google_home() {}

void google_home::music() {
    cout << "Включаю Youtube music" << endl;
}

class homekit : public Smart_home {
public:
    homekit();
    ~homekit();

    void music();
    void tV();
};

homekit::homekit() : Smart_home() {
    OS = "IOS";
    voice_assistant = "Siri";
    protocols = "Bluetooth, Matter, Wi-Fi";
}

homekit::~homekit() {}

void homekit::music() {
    cout << "Включаю Apple music" << endl;
}

void homekit::tV() {
    //cout << "Включаю AppletV" << endl;
}

// Фабричный метод

enum class Smart_home_type : int
{
    Yandex = 1,
    Google = 2,
    HomeKit = 3,

    Undefined = 0
};

Smart_home* Create_smart_home(Smart_home_type type)
{
    Smart_home* new_smart_home = nullptr;

    if (type == Smart_home_type::Yandex)
    {
        new_smart_home = new yandex_Alice;
    }
    else if (type == Smart_home_type::Google)
    {
        new_smart_home = new google_home;
    }
    else if (type == Smart_home_type::HomeKit)
    {
        new_smart_home = new homekit;
    }

    return new_smart_home;
}

void Music_all(Iterator<Smart_home*>* it)
{
    for (it->First(); !it->IsDone(); it->Next())
    {
        Smart_home* currentSmart_home = it->GetCurrent();
        currentSmart_home->music();
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");

    wcout << L"На какой платформе включить музыку (1 - Yandex, 2 - Google, 3 - HomeKit)?" << endl;
    Smart_home_type type = Smart_home_type::Undefined;
    int ii;
    cin >> ii;
    type = static_cast<Smart_home_type>(ii);

    Smart_home* newSmart_home = Create_smart_home(type);
    newSmart_home->music();
    delete newSmart_home;

    cout << endl;


    size_t N = 0;
    wcout << L"Введите количество систем: ";
    cin >> N;

    // Стек

    Stack_class<Smart_home*> Smart_home_stack;
    for (size_t i = 0; i < N; i++)
    {
        int smart_home_num = rand() % 3 + 1;
        Smart_home_type smart_home_type = static_cast<Smart_home_type>(smart_home_num);
        Smart_home* newSmart_home = Create_smart_home(smart_home_type);
        Smart_home_stack.Push(newSmart_home);
    }

    wcout << L"Обход СТЕКА" << endl;

    Iterator<Smart_home*>* it2 = new StackIterator<Smart_home*>(&Smart_home_stack);
    Music_all(it2);
    delete it2;

    cout << endl << endl;



    // Массив

    Array_class<Smart_home*> smart_home_array;
    for (size_t i = 0; i < N; i++)
    {
        int smart_home_num = rand() % 3 + 1;
        Smart_home_type smart_home_type = static_cast<Smart_home_type>(smart_home_num);
        Smart_home* newSmart_home = Create_smart_home(smart_home_type);
        smart_home_array.Add(newSmart_home);
    }

    wcout << L"Обход МАССИВА" << endl;


    Iterator<Smart_home*>* it3 = new ArrayIterator<Smart_home*>(&smart_home_array);
    Music_all(it3);
    delete it3;

}

// Запуск программы: CtRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
