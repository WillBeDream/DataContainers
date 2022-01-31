// ForwardList.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>


using std::cin;
using std::cout;
using std::endl;

#define tab "\t"

class Element       
{
    int Data;
    Element* pNext;
public:
    Element(int Data, Element* pNext=nullptr) :Data(Data), pNext(pNext)
    {
        cout << "EConstructor:\t" << this << endl;
    }
    ~Element()
    {
        cout << "EDestructor:\t" << this << endl;
    }
    friend class ForwardList;
};

class ForwardList
{
    Element* Head;
public:
    ForwardList()
    {
        Head = nullptr;
        cout << "LConstructor:\t" << this << endl;
    }
    ~ForwardList()
    {
        cout << "LDestructor:\t" << this << endl;
    };

    void push_front(int Data)
    {
        Element* New = new Element(Data);
        New->pNext = Head;
        Head = New;
    }

    void print()const
    {
        Element* Temp = Head;
        while (Temp)
        {
            cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
            Temp = Temp->pNext;
        }
    }

    void push_back(int Data)
    {
        Element* New = new Element(Data);
        Element* Temp = Head;
        while (Temp->pNext!=nullptr)
        {
            Temp = Temp->pNext;
        }
        Temp->pNext = New;
        New->pNext = nullptr;
    }

    void pop_front()
    {
        Element* Del = Head;
        Head = Head->pNext;
        delete Del;
    }

    void pop_back()
    {
        Element* Temp = Head;
        while (Temp->pNext != nullptr)
        {
            Temp = Temp->pNext;
        }
        delete Temp;
        Temp->pNext = nullptr;
       
    }
};



int main()
{
    setlocale(LC_ALL, "");
    int n;
    cin >> n;
    ForwardList list;
    for (size_t i = 0; i < n; i++)
    {
        list.push_front(rand() % 100);
    }
    list.print();
    list.push_back(123);
    list.print();
    list.pop_back();
    list.print();


    return 0;

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
