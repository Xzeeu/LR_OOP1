#ifndef PatternTemplatesH
#define PatternTemplatesH

// ��������� ����� "����"

const size_t MaxSize = 100;

template <typename T> // T - ������������� ��� ������
class StackClass
{
private:

    // ���������� ���������, ���������� ������ ���� T
    T Items[MaxSize];

    // ������ �������� �����, ���������� �� �������
    size_t Top;

public:

    // �������� ����, �������� �� ���� ������
    bool IsEmpty() const { return (Top == 0); }

    // ����������� ������� �����
    size_t Size() const { return Top; }

    // ��������� � ���� ����� �������
    void Push(T newObject) { Items[Top++] = newObject; }

    // ������� �� ������ ������� �������
    T Pop() { return Items[--Top]; }

    // ��������� �������� �� �������
    T GetElementByIndex(size_t index) const { return Items[index]; }

    // �����������
    StackClass() : Top(0) {}
};

// ��������� ����� "������"

template <typename T>
class ArrayClass
{
private:

    T Items[MaxSize];
    size_t ArraySize;

public:

    void Add(T newObject) { Items[ArraySize++] = newObject; }
    size_t Size() const { return ArraySize; }

    // ������ ������� ��������� �������� �� ������� (���������� ��������� [])
    T operator[](size_t index) const { return Items[index]; }

    // ������ ������� ��������� �������� �� �������
    T GetElement(size_t index) const { return Items[index]; }

    ArrayClass() : ArraySize(0) {}
};

// ��������� �����, ����������� ������� "��������"
// (����� �����������, ��� ��� �������� ������� ��� ����������)

template<typename T> // T - ������������� ��� ������ (������� ����������)
class Iterator
{
protected:
    Iterator() {}

public:
    virtual ~Iterator() {}
    virtual void First() = 0; // ������������������ �� ������ ����������
    virtual void Next() = 0;  // ������� � ���������� ��������
    virtual bool IsDone() const = 0;  // ���������, ��������� �� �����
    virtual T GetCurrent() const = 0; // �������� ������� �������
};

// ���������� �������� "��������",
// ��������������� ��� ������ �������

template<typename T>
class ArrayIterator : public Iterator<T>
{
private:
    const ArrayClass<T>* ArrayContainer; // ��������� �� ������
    size_t Pos; // ������� ��������� � �������

public:
    ArrayIterator(ArrayClass<T>* container)
        : ArrayContainer(container), Pos(0) {
    }

    void First() override { Pos = 0; }
    void Next() override { Pos++; }
    bool IsDone() const override { return (Pos >= ArrayContainer->Size()); }
    T GetCurrent() const override { return ArrayContainer->GetElement(Pos); }
};

// ���������� �������� "��������",
// ��������������� ��� ������ �����

template<typename T>
class StackIterator : public Iterator<T>
{
private:
    const StackClass<T>* StackContainer; // ��������� �� ������
    size_t Pos; // ������� ��������� � �������

public:
    StackIterator(StackClass<T>* container)
        : StackContainer(container), Pos(0) {
    }

    void First() override { Pos = 0; }
    void Next() override { Pos++; }
    bool IsDone() const override { return (Pos >= StackContainer->Size()); }
    T GetCurrent() const override { return StackContainer->GetElementByIndex(Pos); }
};

#endif // PatternTemplatesH
