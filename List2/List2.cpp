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
    }*Head, * Tail;
    size_t size;

    class BaseIterator
    {
    protected:
        Element* Temp;
    public:
        BaseIterator(Element* Temp=nullptr) : Temp(Temp)
        {
            cout << "BITConstructor:\t" << this << endl;
        }
        ~BaseIterator()
        {
            cout << "BITDestructor:\t" << this << endl;
        }

        virtual BaseIterator& operator++() = 0;
        virtual BaseIterator& operator--() = 0;

        bool operator ==(const BaseIterator& other)const
        {
            return this->Temp == other.Temp;
        }

        bool operator !=(const BaseIterator& other)const
        {
            return this->Temp != other.Temp;
        }

        const int& operator*()const
        {
            return Temp->Data;
        }

        operator bool()const
        {
            return Temp;
        }
    };
public:
    class ConstIterator: public BaseIterator
    {
    public:
        ConstIterator(Element* Temp = nullptr) : BaseIterator(Temp)
        {
            cout << "ITConstructor:\t" << this << endl;
        }

        ~ConstIterator()
        {
            cout << "ItDestructor:\t" << this << endl;
        }

        ConstIterator& operator++()
        {
            Temp = Temp->pNext;
            return *this;
        }

        ConstIterator& operator++(int)
        {
            ConstIterator old = *this;
            Temp = Temp->pNext;
            return old;
        }

        ConstIterator& operator--()
        {
            Temp = Temp->pPrev;
            return *this;
        }

        ConstIterator& operator--(int)
        {
            ConstIterator old = *this;
            Temp = Temp->pPrev;
            return old;
        }
    };

    class ConstReverseIterator:public BaseIterator
    {
    public:
        ConstReverseIterator(Element* Temp = nullptr) :BaseIterator(Temp)
        {
            cout << "RITConstructor:\t" << this << endl;
        }

        ~ConstReverseIterator()
        {
            cout << "RITDestructor" << this << endl;
        }

        ConstReverseIterator& operator++()
        {
            Temp = Temp->pPrev;
            return *this;
        }

        ConstReverseIterator& operator++(int)
        {
            ConstReverseIterator old = *this;
            Temp = Temp->pPrev;
            return old;
        }

        ConstReverseIterator& operator--()
        {
            Temp = Temp->pNext;
            return *this;
        }

        ConstReverseIterator& operator--(int)
        {
            ConstReverseIterator old = *this;
            Temp = Temp->pNext;
            return old;
        }
    };

    class Iterator: public ConstIterator
    {
    public:
        
        Iterator(Element*Temp=nullptr): ConstIterator(Temp)
        {
            cout << "ItConsctructor:\t" << this << endl;
        }
        ~Iterator()
        {
            cout << "ItDesctructor:\t" << this << endl;
        }
        int& operator *()
        {
            return Temp->Data;
        }
    };
    class ReverseIterator:public ConstReverseIterator
    {
    public:
        ReverseIterator(Element* Temp = nullptr) : ConstReverseIterator(Temp)
        {
            cout << "RItConstructor:\t" << this << endl;
        }
        ~ReverseIterator()
        {
            cout << "RItDenstructor:\t" << this << endl;
        }
        int& operator*()
        {
            return Temp->Data;
        }

    };

    ConstIterator cbegin()const
    {
        return Head;
    }
    ConstIterator cend()const
    {
        return nullptr;
    }
    ConstReverseIterator crbegin()const
    {
        return Tail;
    }
    ConstReverseIterator crend()const
    {
        return nullptr;
    }

    Iterator begin()
    {
        return Head;
    }
    Iterator end()
    {
        return nullptr;
    }
    ReverseIterator rbegin()
    {
        return Tail;
    }
    ReverseIterator rend()
    {
        return nullptr;
    }
    List()
    {
        Head = Tail = nullptr;
        size = 0;
        cout << "LConstructor:\t" << this << endl;
    }
    List(unsigned int size):List()
    {
        for (size_t i = 0; i < size; i++)
        {
            push_front(int());
        }
    }
    List(const std::initializer_list<int>& il) :List()
    {
        for (int const* it = il.begin(); it != il.end() - 1; it++)
        {
            push_back(*it);
        }
    }

    ~List()
    {
        while (Tail)
        {
            pop_back();
        }
        cout << "LDestructor:\t" << this << endl;
    }

    const int& operator[](int index)const
    {
        Element* Temp = Head;
        for (size_t i = 0; i < index; i++)
        {
            Temp = Temp->pNext;
        }
        return Temp->Data;
    }

    int& operator[](int index)
    {
        Element* Temp = Head;
        for (size_t i = 0; i < index; i++)
        {
            Temp = Temp->pNext;
        }
        return Temp->Data;
    }

    void push_front(int Data)
    {
        if (Head==nullptr && Tail==nullptr)
        {
            Head = Tail = new Element(Data);
            size++;
            return;
        }
       /* Element* New = new Element(Data);
       New->pNext = Head;
       Head->pPrev = New;
       Head = New;*/
        Head = Head->pPrev = new Element(Data, Head);
        size++;

    }
    void push_back(int Data)
    {
        if (Head == nullptr && Tail == nullptr)
        {
            Head = Tail = new Element(Data);
            size++;
            return;
        }
        /*Element* New = new Element(Data);
        New->pPrev = Tail;
        Tail->pNext = New;
        Tail = New;*/
        Tail = Tail->pNext = new Element(Data, nullptr, Tail);
        size++;
    }

    void pop_front()
    {
        if (Head == nullptr && Tail == nullptr)return;
        if (Head == Tail)
        {
            delete Head;
            Head = Tail = nullptr;
            size--;
            return;
        }
        Head = Head->pNext;
        delete Head->pPrev;
        Head->pPrev = nullptr;
        size--;
        
    }

    void pop_back()
    {
        if (Head == Tail)return pop_front();
        Tail = Tail->pPrev;
        delete Tail->pNext;
        Tail->pNext = nullptr;
        size--;

    }

    void insert(int index, int Data)
    {
        if (index > size)return;
        if (index == 0)return push_front(Data);
        if (index == size)return push_back(Data);
        Element* Temp;
        if (index < size / 2)
        {
            Temp = Head;
            for (size_t i = 0; i < index; i++)Temp = Temp->pNext;
        }
        else
        {
            Temp = Tail;
            for (size_t i = 0; i < size-index-1; i++)
            {
                Temp = Temp->pPrev;
            }
        }
       /* Element* New = new Element(Data);
        New->pNext = Temp;
        New->pPrev = Temp->pPrev;
        Temp->pPrev->pNext = New;
        Temp->pPrev = New;*/
        Temp->pPrev = Temp->pPrev->pNext = new Element(Data, Temp, Temp->pPrev);
        size++;
    }

    void Erase(int index)
    {
        if (index > size)return;
        if (index == 0)return pop_front();
        if (index == size)return pop_back();
        Element* Temp;
        if (index < size / 2)
        {
            Temp = Head;
            for (size_t i = 0; i < index; i++)Temp = Temp->pNext;
        }
        else
        {
            Temp = Tail;
            for (size_t i = 0; i < size - index - 1; i++)
            {
                Temp = Temp->pPrev;
            }
        }
        Temp->pPrev->pNext = Temp->pNext;
        Temp->pNext->pPrev = Temp->pPrev;
        delete Temp;
        size--;
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

//#define BASE_CHECK
//#define CONSTR_CHECK

int main()
{
    setlocale(LC_ALL, "rus");

#ifdef BASE_CHECK
    
    int n;
    cin >> n;
    List list;
    for (size_t i = 0; i < n; i++)
    {
        //list.push_front(rand() % 100);
        list.push_back(rand() % 100);
    }
    list.print();
    list.Erase(1);
    list.print();
#endif // BASE_CHECK
    

#ifdef CONSTR_CHECK
    List list = { 3, 5, 8, 13, 21 };
    for (int i : list)cout << i << tab; cout << endl;
#endif // CONSTR_CHECK

    List list = { 3,5,8,13,21 };
    list.print();

    for (int i : list)
    {
        cout << i << tab;
    }
    cout << endl;

    list.insert(3, 25);
    
    for (List::ConstReverseIterator it = list.crbegin(); it; ++it)
    {
        cout << *it << tab;
    }
    cout << endl;


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
