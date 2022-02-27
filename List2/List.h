#pragma once


#include <iostream>

using std::cin;
using std::cout;
using std::endl;

#define tab "\t"

template<typename T>
class List
{
    class Element
    {
        T Data;
        Element* pNext;
        Element* pPrev;
    public:
        Element(T Data, Element* pNext = nullptr, Element* pPrev = nullptr);
        ~Element();
        friend class List<T>;
    }*Head, * Tail;
    size_t size;

    class BaseIterator
    {
    protected:
        Element* Temp;
    public:
        BaseIterator(Element* Temp = nullptr);
        ~BaseIterator();

        virtual BaseIterator& operator++() = 0;
        virtual BaseIterator& operator--() = 0;

        bool operator ==(const BaseIterator& other)const;

        bool operator !=(const BaseIterator& other)const;

        const T& operator*()const;

        operator bool()const;
    };
public:
    class ConstIterator : public BaseIterator
    {
    public:
        ConstIterator(Element* Temp = nullptr);

        ~ConstIterator();

        ConstIterator& operator++();

        ConstIterator& operator++(int);

        ConstIterator& operator--();

        ConstIterator& operator--(int);
    };

    class ConstReverseIterator :public BaseIterator
    {
    public:
        ConstReverseIterator(Element* Temp = nullptr);

        ~ConstReverseIterator();

        ConstReverseIterator& operator++();

        ConstReverseIterator& operator++(int);

        ConstReverseIterator& operator--();

        ConstReverseIterator& operator--(int);
    };

    class Iterator : public ConstIterator
    {
    public:
        Iterator(Element* Temp = nullptr);
        ~Iterator();
        T& operator *();
    };
    class ReverseIterator : public ConstReverseIterator
    {
    public:
        ReverseIterator(Element* Temp = nullptr);
        ~ReverseIterator();
        T& operator*();

    };

    ConstIterator cbegin()const;
    ConstIterator cend()const;
    ConstReverseIterator crbegin()const;
    ConstReverseIterator crend()const;

    Iterator begin();
    Iterator end();
    ReverseIterator rbegin();
    ReverseIterator rend();
    List();

    List(unsigned int size);

    List(const std::initializer_list<T>& il);

    ~List();

    const T& operator[](int index)const;
    T& operator[](int index);

    void push_front(T Data);
    void push_back(T Data);

    void pop_front();
    void pop_back();

    void insert(int index, T Data);
    void Erase(int index);

    void print()const;
    void reverse_print()const;
};
