// LR_OOP1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "PatternTemplates.h"

using namespace std;


class Smart_home {
private:
    bool russian_language;

protected:
    string Voice_assistant;
    string protocols;
    string OS;


public:
    Smart_home(); // Конструктор
    virtual ~Smart_home(); // Деструктор

    string get_voice_assistant() const { return Voice_assistant; }
    bool get_russian_language() const { return russian_language; }
    string getOS() const { return OS; }

    virtual void music() = 0;

};

Smart_home::Smart_home() : Voice_assistant("No"), russian_language(false), protocols("wi-fi"), OS("Windows, Android, iOS")
{
    //cout << "Creating Smart home..." << endl;
}

Smart_home::~Smart_home()
{
    //cout << "Deleting Smart home..." << endl;
}


class yandex_Alice : public Smart_home {
public:
    yandex_Alice();
    ~yandex_Alice();

    string get_voice_assistant() const;

    void music();
};

// Реализация конструктора
yandex_Alice::yandex_Alice() : Smart_home()
{
    Voice_assistant = "Alice";
    protocols = "Zigbee, Matter, Wi-Fi";

    //cout << "Creating yandex Alice..." << endl;
}

yandex_Alice::~yandex_Alice()
{
    //cout << "Deleting yandex_Alice..." << endl;
}

string yandex_Alice::get_voice_assistant() const {
    //cout << Smart_home::get_voice_assistant() << " - Виртуальный голосовой помощник, созданный компанией Яндекс." << endl;

    return Smart_home::get_voice_assistant();
}

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
    Voice_assistant = "Google Assistant";
    protocols = "Bluetooth, Matter, Wi-Fi";

    // << "Creating google_home..." << endl;
}

google_home::~google_home() {
    //cout << "Deleting google_home..." << endl;
}

void google_home::music() {
    cout << "Включаю Youtube music" << endl;
}


class homekit : public Smart_home {
public:
    homekit();
    ~homekit();

    void music();
    void TV();
};

homekit::homekit() : Smart_home() {
    OS = "IOS";
    Voice_assistant = "Siri";
    protocols = "Bluetooth, Matter, Wi-Fi";

    //cout << "Creating homekit..." << endl;
}

homekit::~homekit() {
   // cout << "Deleting homekit..." << endl;
}

void homekit::music() {
    cout << "Включаю Apple music" << endl;
}

void homekit::TV() {
    //cout << "Включаю AppleTV" << endl;
}

// Реализация паттерна "Фабричный метод"

enum class SmartHomeType : int
{
    Yandex = 1,
    Google = 2,
    HomeKit = 3,

    Undefined = 0
};

Smart_home* CreateSmart_home(SmartHomeType type)
{
    Smart_home* newSmartHome = nullptr;

    if (type == SmartHomeType::Yandex)
    {
        newSmartHome = new yandex_Alice;
    }
    else if (type == SmartHomeType::Google)
    {
        newSmartHome = new google_home;
    }
    else if (type == SmartHomeType::HomeKit)
    {
        newSmartHome = new homekit;
    }

    return newSmartHome;
}

void MusicAll(Iterator<Smart_home*>* it)
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
    SmartHomeType type = SmartHomeType::Undefined;
    int ii;
    cin >> ii;
    type = static_cast<SmartHomeType>(ii);

    Smart_home* newSmart_home = CreateSmart_home(type);
    newSmart_home->music();
    delete newSmart_home;

    cout << endl;

    // Стек


    size_t N = 0;
    wcout << L"Введите количество систем: ";
    cin >> N;

    StackClass<Smart_home*> Smart_homeStack;
    for (size_t i = 0; i < N; i++)
    {
        int fruit_num = rand() % 3 + 1; // Число от 1 до 3 (случайный фрукт)
        SmartHomeType fruit_type = static_cast<SmartHomeType>(fruit_num);
        Smart_home* newSmart_home = CreateSmart_home(fruit_type);
        Smart_homeStack.Push(newSmart_home);
    }

    wcout << L"Размер стека систем: " << Smart_homeStack.Size() << endl;

    Iterator<Smart_home*>* it2 = new StackIterator<Smart_home*>(&Smart_homeStack);
    MusicAll(it2);
    delete it2;

    cout << endl << endl;



    // 3. Массив

    ArrayClass<Smart_home*> fruitArray;
    for (size_t i = 0; i < 5; i++)
    {
        int fruit_num = rand() % 3 + 1; // Число от 1 до 3 (случайный фрукт)
        SmartHomeType fruit_type = static_cast<SmartHomeType>(fruit_num);
        Smart_home* newSmart_home = CreateSmart_home(fruit_type);
        fruitArray.Add(newSmart_home);
    }

    wcout << L"Размер массива фруктов: " << Smart_homeStack.Size() << endl;


    Iterator<Smart_home*>* it3 = new ArrayIterator<Smart_home*>(&fruitArray);
    MusicAll(it3);
    delete it3;





































    //yandex_Alice newYA;

    ////cout << "Голосовой помощник: " << newYA.get_voice_assistant() << endl;
    ////cout << "Поддерживаемые ОС: " << newYA.getOS() << endl;
    //newYA.music();

    //cout << endl;

    //google_home newGH;

    ////cout << "Голосовой помощник: " << newGH.get_voice_assistant() << endl;
    ////cout << "Поддерживаемые ОС: " << newGH.getOS() << endl;
    //newGH.music();

    //cout << endl;

    //homekit newHK;

    ////cout << "Голосовой помощник: " << newHK.get_voice_assistant() << endl;
    ////cout << "Поддерживаемые ОС: " << newHK.getOS() << endl;
    //newHK.music();
    //newHK.TV();


    //cout << endl;

    ////ПРИМЕР ПОЛИМОРФИЗМА

    //Smart_home* newSmart_home1 = new yandex_Alice; // Инициализация указателя экземпляром унаследованного класса
    //Smart_home* newSmart_home2 = new google_home;

    //// Создание экземпляра класса с созданием ссылки

    //homekit temp_homekit;
    //Smart_home& newSmart_home3 = temp_homekit;

    //cout << endl;

    ////cout << "Использование интерфейса родительского класса" << endl;

    ////cout << "OS Yandex Alice: " << newSmart_home1->getOS() << endl;
    ////cout << "OS Google Home: " << newSmart_home2->getOS() << endl;
    ////cout << "OS Apple Homehit : " << newSmart_home3.getOS() << endl;


    //cout << endl;

    ////cout << "Вызов функции, реализация которой была переопределена в унаследованном классе" << endl;

    //string appleWeight2 = newSmart_home1->get_voice_assistant();
    //string appleWeight3 = newSmart_home3.get_voice_assistant();
    ////cout << appleWeight2 << " " << appleWeight3 << endl;

    ////cout << endl;


    ////cout << "Вызов виртуальной функции" << endl;
    //newSmart_home1->music();
    //newSmart_home2->music();
    //newSmart_home3.music();

    //cout << endl;

    //delete newSmart_home1;
    //delete newSmart_home2;


}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
