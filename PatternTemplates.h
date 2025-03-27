#ifndef PatterntemplatesH
#define PatterntemplatesH

// Стек

const size_t MaxSize = 100;

template <typename Data_type>
class Stack_class
{
private:
    Data_type items[MaxSize];
    size_t top;

public:
    bool Is_empty() const { return (top == 0); }
    size_t Size() const { return top; }
    void Push(Data_type newObject) { items[top++] = newObject; }
    Data_type Pop() { return items[--top]; }
    Data_type Get_element_index(size_t index) const { return items[index]; }

    Stack_class() : top(0) {}
};

// Массив

template <typename Data_type>
class Array_class
{
private:

    Data_type items[MaxSize];
    size_t array_size;

public:

    void Add(Data_type newObject) { items[array_size++] = newObject; }
    size_t Size() const { return array_size; }
    Data_type GetElement(size_t index) const { return items[index]; }

    Array_class() : array_size(0) {}
};

// Итератор

template<typename Data_type>
class Iterator
{
protected:
    Iterator() {}

public:
    virtual ~Iterator() {}
    virtual void First() = 0;
    virtual void Next() = 0;
    virtual bool IsDone() const = 0;
    virtual Data_type GetCurrent() const = 0;
};

// Итератор для обхода массива

template<typename Data_type>
class ArrayIterator : public Iterator<Data_type>
{
private:
    const Array_class<Data_type>* ArrayContainer;
    size_t Pos;

public:
    ArrayIterator(Array_class<Data_type>* container)
        : ArrayContainer(container), Pos(0) {
    }

    void First() override { Pos = 0; }
    void Next() override { Pos++; }
    bool IsDone() const override { return (Pos >= ArrayContainer->Size()); }
    Data_type GetCurrent() const override { return ArrayContainer->GetElement(Pos); }
};

// Итератор для обхода стека

template<typename Data_type>
class StackIterator : public Iterator<Data_type>
{
private:
    const Stack_class<Data_type>* StackContainer;
    size_t Pos;

public:
    StackIterator(Stack_class<Data_type>* container)
        : StackContainer(container), Pos(0) {
    }

    void First() override { Pos = 0; }
    void Next() override { Pos++; }
    bool IsDone() const override { return (Pos >= StackContainer->Size()); }
    Data_type GetCurrent() const override { return StackContainer->Get_element_index(Pos); }
};

#endif // PatterntemplatesH
