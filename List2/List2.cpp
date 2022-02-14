// List2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;

#define tab "\t"

class List
{
    class Element
    {
        int Data;
        Element* pNext;
        Element* pPrev;
    public:
        Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr)
            :Data(Data), pNext(pNext), pPrev(pPrev)
        {
            cout << "EConstructor:\t" << this << endl;
        }
        ~Element()
        {
            cout << "EDestructor:\t" << this << endl;
        }
        friend class List;
    }*Head, *Tail;
    size_t size;
public:
    List()
    {
        Head = Tail = nullptr;
        size = 0;
        cout << "LConstructor:\t" << this << endl;
    }
    ~List()
    {
        cout << "LDestructor:\t" << this << endl;
    }
    void push_front(int Data)
    {
        if (Head==nullptr && Tail==nullptr)
        {
            Head = Tail = new Element(Data);
            size++;
            return;
        }
        Element* New = new Element(Data);
        New->pNext = Head;
        Head->pPrev = New;
        Head = New;
        size++;

        /*Head = Head->pPrev = new Element(Data);*/
    }
    void push_back(int Data)
    {
        if (Head == nullptr && Tail == nullptr)
        {
            Head = Tail = new Element(Data);
            size++;
            return;
        }
        Element* New = new Element(Data);
        Element* Temp = Head;
        while (Temp->pNext)
        {
            Temp = Temp->pNext;
        }
        Temp->pNext = New;
        size++;
    }

    void pop_front()
    {
        Element* Del = Head;
        delete Del;
        size--;
    }

    void pop_back()
    {
        Element* Temp = Head;
        while (Temp->pNext->pNext != nullptr)
        {
            Temp = Temp->pNext;
        }
        delete Temp->pNext;
        Tail = Temp->pPrev;
        Temp->pNext = nullptr;
        size--;
    }

    void insert(int Data, int index)
    {
        Element* New = new Element(Data);
        Element* Temp = Head;
        for (size_t i = 0; i < index-1; i++)
        {
            Temp = Temp->pNext;
        }
        New->pNext = Temp->pNext;
        Temp->pNext = New;
        size++;
    }
    
    
    void print()const
    {
        for (Element* Temp = Head; Temp; Temp = Temp->pNext)
        {
            cout <<Temp<<tab<< Temp->Data << tab << Temp->pNext << Temp->pPrev << endl;
        }
        cout << "Колличество элементов списка: " << size << endl;
    }
    void reverse_print()const
    {
        for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
        {
            cout << Temp << tab << Temp->Data << tab << Temp->pNext << Temp->pPrev << endl;
        }
        cout << "Колличество элементов списка: " << size << endl;
    }
};

int main()
{
    setlocale(LC_ALL, "rus");
    int n;
    cin >> n;
    List list;
    for (size_t i = 0; i < n; i++)
    {
        //list.push_front(rand() % 100);
        list.push_front(rand() % 100);
    }
    list.print();
    list.insert(48, 1);
    list.print();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
