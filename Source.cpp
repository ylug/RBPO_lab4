#include <iostream>
using namespace std;


class Array
{
protected:
    int* arr;
public:
    Array() :arr(nullptr) {};//����������� �� ���������
    explicit Array(unsigned size);//����������� ��������������
    Array(const Array& other);//����������� �����������
    Array(Array&& other);//����������� �����������
    Array(std::initializer_list<int> list);//�����������, ����������� �� ���� std::initializer_list
    ~Array();//����������

    unsigned GetSize() const;

    const int& operator[](int index) const;
    int& operator[](int index);

    Array& operator=(const Array& other);
    Array& operator=(Array&& other);
    Array& operator=(std::initializer_list<int> ilist);

};

//����������� ������������� � ������������

explicit Array::Array(unsigned size)//����������� ��������������
{
    arr = new int[size];
    cout << "������� ������ :   ";
    for (int i = 0; i < size; i++)
    {
        cin >> arr[i];
    }
}
Array::Array(const Array& other)//����������� �����������
{
    unsigned n = sizeof(other.arr) / sizeof(int);
    arr = new int[n];
    for (int i = 0; i < n; i++)
    {
        arr[i] = other.arr[i];
    }
}
Array::Array(Array&& other)//����������� �����������
{
    arr = other.arr;
    other.arr = nullptr;
}
Array::Array(std::initializer_list<int> list)//�����������, ����������� �� ���� std::initializer_list
{
    arr = new int[list.size()];
    const int* initptr = list.begin();
    const int* endptr = list.end();
    unsigned i = 0;
    while (initptr != endptr)
    {
        arr[i] = *initptr;
        i++;
        initptr++;
    }
}
Array::~Array()
{
    delete[] arr;
}

//�������-�����
unsigned Array::GetSize() const
{
    unsigned n = sizeof(arr) / sizeof(int);
    return n;
}

const int& Array::operator[](int index) const
{
    return *(this->arr + index);
}
int& Array::operator[](int index)
{
    return *(this->arr + index);
}

Array& Array::operator=(const Array& other)//�������� ������������
{
    if (this == &other)
    {
        return *this;
    }
    unsigned n = sizeof(other.arr) / sizeof(int);
    arr = new int[n];
    for (int i = 0; i < n; i++)
    {
        arr[i] = other.arr[i];
    }
    return *this;
}
Array& Array::operator=(Array&& other)//�������� ������������ � ������������
{
    if (this == &other)
    {
        return *this;
    }
    arr = other.arr;
    other.arr = nullptr;
    return *this;
}

Array& Array::operator=(std::initializer_list<int> ilist)// �������� ������������ ����� �������������
{
    delete[] arr;
    arr = new int[ilist.size()];
    const int* initptr = ilist.begin();
    const int* endptr = ilist.end();
    unsigned i = 0;
    while (initptr != endptr)
    {
        arr[i] = *initptr;
        i++;
        initptr++;
    }
}



class QueueBasedOnArray : public Array
{
public:
    using Array::Array;
    using Array::GetSize;
    typedef int T;
    bool Push(const T& element);
    bool Pop(T& element);
    bool Peek(T& element);
};

bool QueueBasedOnArray::Push(const T& element)
{
    if (arr == nullptr)
    {
        arr = new int[1];
        *arr = element;
        return 1;
    }
    int n = GetSize() + 1;
    if (n > 100)
        return 0;
    int* arr1 = new int[n];
    for (int i = 0; i < n; i++)
    {
        arr1[i] = arr[i];
    }
    arr1[n] = element;
    delete[] arr;
    arr = arr1;
    return 1;
}
bool QueueBasedOnArray::Pop(T& element)
{
    if (arr == nullptr || GetSize() <= 0)
        return 0;
    int n = GetSize() - 1;
    element = arr[0];
    if (n == 0)
    {
        delete[] arr;
        arr = nullptr;
        return 0;
    }
    int* arr1 = new int[n];
    for (int i = 0; i < n; i++)
    {
        arr1[i] = arr[i+1];
    }
    delete[] arr;
    arr = arr1;
    return 1;
}
bool QueueBasedOnArray::Peek(T& element)
{
    if (arr == nullptr || GetSize() <= 0)
        return 0;
    element = arr[0];
    return 1;
}
