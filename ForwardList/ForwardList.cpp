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
    static int count;
public:
    Element(int Data, Element* pNext=nullptr) :Data(Data), pNext(pNext)
    {
        count++;
        cout << "EConstructor:\t" << this << endl;
    }
    ~Element()
    {
        count--;
        cout << "EDestructor:\t" << this << endl;
    }
    friend class ForwardList;
};

int Element::count = 0;

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
        cout << "Колличество элементов списка: " << Head->count << endl;
    }

    void push_back(int Data)
    {
        if (Head == nullptr)return push_front(Data);
        Element* New = new Element(Data);
        Element* Temp = Head;
        while (Temp->pNext)
        {
            Temp = Temp->pNext;
        }
        Temp->pNext = New;
        
    }

    void pop_front()
    {
        if (Head == nullptr)return;
        Element* Del = Head;
        Head = Head->pNext;
        delete Del;
    }

    void pop_back()
    {
        if (Head == nullptr)return;
        if (Head->pNext == nullptr)return pop_front();
        Element* Temp = Head;
        while (Temp->pNext->pNext!=nullptr)
        {
            Temp = Temp->pNext;
        }
        delete Temp->pNext;
        Temp->pNext = nullptr;
       
    }

    void insert(int index, int Data)
    {
        if (index==0||Head==nullptr)return push_front(Data);
        if (index>Head->count)return;
        Element* New = new Element(Data);
        Element* Temp = Head;
        for (size_t i = 0; i < index-1; i++)
        {
            Temp = Temp->pNext;
        }
        New->pNext = Temp->pNext;
        Temp->pNext = New;
    }

    void Erase(int index)
    {
        if (index == 0 || Head == nullptr)return pop_front();
        Element* Temp = Head;
        for (size_t i = 0; i < index-1; i++)
        {
            Temp = Temp->pNext;
        }
        Element* Del = Temp->pNext;
        Temp->pNext = Temp->pNext->pNext;
        delete Del;
        
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
        //list.push_front(rand() % 100);
        list.push_back(rand() % 100);
    }
    list.print();
    //list.push_back(123);
    //list.pop_front();
   // list.pop_back();
    list.print();
    
    int index;
    int value;
    cin >> index;
   /* cin >> value;
    list.insert(index, value);*/
    list.Erase(index);
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
