// LR_OOP1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <list>
#include "Patterntemplates.h"

using namespace std;

// Мощность колонки
enum class Source_power : int
{
    Low,
    Average,
    High,
    Unknown
};

// Способы включения музыки

enum class music_launch_method : int
{
    mobile_app,
    voice,
    website,

    None
};

class MusicStartStrategy {
public:
    virtual ~MusicStartStrategy() {}
    virtual void music() = 0;
};

class MobileAppMusicStartStrategy : public MusicStartStrategy
{
    void music() { cout << "Запускаю музыку с мобильного приложения"; }
};

class VoiceMusicStartStrategy : public MusicStartStrategy
{
    void music() { cout << "Запускаю музыку голосом"; }
};

class WebsiteMusicStartStrategy : public MusicStartStrategy
{
    void music() { cout << "Запускаю музыку с сайта"; }
};


MusicStartStrategy* CreateMusicStartStrategy(music_launch_method manner) {
    switch (manner) {
    case music_launch_method::mobile_app: return new MobileAppMusicStartStrategy;
    case music_launch_method::voice: return new VoiceMusicStartStrategy;
    case music_launch_method::website: return new WebsiteMusicStartStrategy;
    default:return nullptr;

    }
}


class Smart_home {
private:
    bool russian_language;
    Source_power Power;

    MusicStartStrategy* __MusicStartStrategy;

protected:
    string voice_assistant;
    string protocols;
    string OS;

    bool subscription;


public:
    Smart_home(Source_power power) : Power(power), subscription(false), __MusicStartStrategy(nullptr) {

        subscription = static_cast<bool>(rand() % 2);
    
    };

    virtual ~Smart_home() {
        if (__MusicStartStrategy != nullptr) delete __MusicStartStrategy;
    }


    string get_voice_assistant() const { return voice_assistant; }
    bool get_russian_language() const { return russian_language; }
    string getOS() const { return OS; }

    bool IsSubscription() const { return subscription; }
    // Функция с реализацией
    Source_power GetPower() const { return Power; }

    // Функция задания способа запуска музыки

    void SetMusicStartStrategy(MusicStartStrategy* musicStartStrategy)
    {
        __MusicStartStrategy = musicStartStrategy;
    }

    virtual void music() {
        if (IsSubscription())
        {
            cout << "Включаю музыку ";
        }
        else
        {
            cout << "Нет подписки! НЕ ";
        }

        if (__MusicStartStrategy != nullptr) {
            __MusicStartStrategy->music();
        }
        else
        {
            cout << "Ничего не делать! ";
        }
    }

};

//Smart_home::Smart_home() : voice_assistant("No"), russian_language(false), protocols("wi-fi"), OS("Windows, Android, iOS"){}

//Smart_home::~Smart_home(){}

class yandex_Alice : public Smart_home {
public:
    yandex_Alice();
    ~yandex_Alice();

    string get_voice_assistant() const;

    void music();
};

yandex_Alice::yandex_Alice() : Smart_home(Source_power::High)
{
    SetMusicStartStrategy(CreateMusicStartStrategy(music_launch_method::voice));
    voice_assistant = "Alice";
    protocols = "Zigbee, Matter, Wi-Fi";
}

yandex_Alice::~yandex_Alice(){}

string yandex_Alice::get_voice_assistant() const {return Smart_home::get_voice_assistant();}

void yandex_Alice::music() {
    cout << "Включаю Яндекс Музыку ";
    Smart_home::music();

    cout << endl;
}

class google_home : public Smart_home {
public:
    google_home();
    ~google_home();

    void music();
};

google_home::google_home() : Smart_home(Source_power::Low) {
    SetMusicStartStrategy(CreateMusicStartStrategy(music_launch_method::website));
    voice_assistant = "Google Assistant";
    protocols = "Bluetooth, Matter, Wi-Fi";
}

google_home::~google_home() {}

void google_home::music() {
    cout << "Включаю Youtube music ";
    Smart_home::music();

    cout << endl;
}

class homekit : public Smart_home {
public:
    homekit();
    ~homekit();

    void music();
    //void tV();
};

homekit::homekit() : Smart_home(Source_power::Average) {
    SetMusicStartStrategy(CreateMusicStartStrategy(music_launch_method::mobile_app));
    OS = "IOS";
    voice_assistant = "Siri";
    protocols = "Bluetooth, Matter, Wi-Fi";
}

homekit::~homekit() {}

void homekit::music() {
    cout << "Включаю Apple music ";
    Smart_home::music();

    cout << endl;
}

//void homekit::tV() {
//    //cout << "Включаю AppletV" << endl;
//}

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


// Декоратор итератора для выделения устройств по мощности

class PowerDecorator : public IteratorDecorator<class Smart_home*>
{
private:
    Source_power TargetPower;

public:
    PowerDecorator(Iterator<Smart_home*>* it, Source_power power)
        : IteratorDecorator<Smart_home*>(it), TargetPower(power) {}

    void First()
    {
        It->First();
        while (!It->IsDone() && It->GetCurrent()->GetPower() != TargetPower)
        {
            It->Next();
        }
    }

    void Next()
    {
        do
        {
            It->Next();

        } while (!It->IsDone() && It->GetCurrent()->GetPower() != TargetPower);
    }
};

// Декоратор итератора для выделения устройств по наличию подписки

class SubscriptionDecorator : public IteratorDecorator<class Smart_home*>
{
private:
    bool TargetSubscription;

public:
    SubscriptionDecorator(Iterator<Smart_home*>* it, bool isSubscription)
        : IteratorDecorator<Smart_home*>(it), TargetSubscription(isSubscription) {}

    void First()
    {
        It->First();
        while (!It->IsDone() && It->GetCurrent()->IsSubscription() != TargetSubscription)
        {
            It->Next();
        }
    }

    void Next()
    {
        do
        {
            It->Next();

        } while (!It->IsDone() && It->GetCurrent()->IsSubscription() != TargetSubscription);
    }
};


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

    size_t N = 30;

    // Массив устройств

    ArrayClass<Smart_home*> smarthomeArray;
    for (size_t i = 0; i < N; i++)
    {
        int smarthome_num = rand() % 3 + 1; // Число от 1 до 3
        Smart_home_type smart_home_type = static_cast<Smart_home_type>(smarthome_num);
        Smart_home* newSmartHome = Create_smart_home(smart_home_type);
        smarthomeArray.Add(newSmartHome);
    }

    wcout << L"Размер массива устройств: " << smarthomeArray.Size() << endl;

    list<Smart_home*> smarthomeVector;
    for (size_t i = 0; i < N; i++)
    {
        int smarthome_num = rand() % 3 + 1; // Число от 1 до 3
        Smart_home_type smart_home_type = static_cast<Smart_home_type>(smarthome_num);
        Smart_home* newSmartHome = Create_smart_home(smart_home_type);
        smarthomeVector.push_back(newSmartHome);
    }

    wcout << L"Размер списка устройств: " << smarthomeVector.size() << endl;



    // Обход всех элементов при помощи итератора
    cout << endl << "Попробовать запустить всё: " << endl;
    Iterator<Smart_home*>* allIt = smarthomeArray.GetIterator();
    Music_all(allIt);
    delete allIt;

    // Обход всех устройств с подпиской
    cout << endl << "Запустить только если есть подписка:" << endl;
    Iterator<Smart_home*>* goodIt = new SubscriptionDecorator(smarthomeArray.GetIterator(), true);
    Music_all(goodIt);
    delete goodIt;

    // Обход всех мощных устройств
    cout << endl << "Все мощные колонки:" << endl;
    Iterator<Smart_home*>* orangeIt = new PowerDecorator(smarthomeArray.GetIterator(), Source_power::High);
    Music_all(orangeIt);
    delete orangeIt;

    // Обход всех мощных устройств с подпиской
    cout << endl << "Все мощные колонки с подпиской:" << endl;
    Iterator<Smart_home*>* goodOrangeIt =
        new SubscriptionDecorator(new PowerDecorator(smarthomeArray.GetIterator(), Source_power::High), true);
    Music_all(goodOrangeIt);
    delete goodOrangeIt;

    // Демонстрация работы адаптера
    cout << endl << "Все мощные колонки с подпиской (другой контейнер):" << endl;
    Iterator<Smart_home*>* adaptedIt = new ConstIteratorAdapter <std::list<Smart_home*>, Smart_home*>(&smarthomeVector);
    Iterator<Smart_home*>* adaptedOrangeIt = new SubscriptionDecorator(new PowerDecorator(adaptedIt, Source_power::High), true);
    Music_all(adaptedOrangeIt);
    delete adaptedOrangeIt;

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
