// ForwardList.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;

#define tab "\t"

template<typename T>class ForwardList;
template<typename T>class Iterator;

template <typename T>
class Element       
{
    T Data;
    Element<T>* pNext;
    static int count;
public:
    Element(T Data, Element<T>* pNext=nullptr) :Data(Data), pNext(pNext)
    {
        count++;
        cout << "EConstructor:\t" << this << endl;
    }
    ~Element()
    {
        count--;
        cout << "EDestructor:\t" << this << endl;
    }
    friend class ForwardList<T>;
    friend class Iterator<T>;
};

template<typename T>
int Element<T>::count = 0;

template<typename T>
class Iterator
{
    Element<T>* Temp;
public:

    Iterator(Element<T>*Temp=nullptr):Temp(Temp)
    {
        cout << "ItConstructor:\t" << this << endl;
    }

    ~Iterator()
    {
        cout << "ItDestructor:\t" << this << endl;
    }

    Iterator<T>& operator++()
    {
        Temp = Temp->pNext;
        return *this;
    }

    Iterator<T> operator++(int)
    {
        Iterator old = *this;
        Temp = Temp->pNext;
        return old;
    }

    bool operator ==(const Iterator<T>& other)const
    {
        return this->Temp == other.Temp;
    }

    bool operator !=(const Iterator<T>& other)const
    {
        return this->Temp != other.Temp;
    }

    const T& operator *()const
    {
        return Temp->Data;
    }
    T& operator *()
    {
        return Temp->Data;
    }

    operator bool()const
    {
        return Temp;
    }
};

template<typename T>
class ForwardList
{
    Element<T>* Head;
    unsigned int size;
public:
    Element<T>* getHead()
    {
        return Head;
    }
    Iterator<T> begin()
    {
        return Head;
    }
    Iterator<T> end()
    {
        return nullptr;
    }
    ForwardList()
    {
        Head = nullptr;
        size = 0;
        cout << "LConstructor:\t" << this << endl;
    }
    ForwardList(unsigned int size) : ForwardList()
    {
        this->Head = nullptr;
        this->size = 0;
        for (size_t i = 0; i < size; i++)
        {
            push_front(T());
        }
    }
    ForwardList(const std::initializer_list<T>& il):ForwardList()
    {
        /*for (int const* it=il.begin(); it!=il.end(); it++)
        {
            push_back(*it);
        }*/
        for (T const* it=il.end()-1; it!=il.begin()-1; it--)
        {
            push_front(*it);
        }
    }
    ForwardList(const ForwardList<T>& other):ForwardList()
    {
        /*for (Element<T>*Temp = other.Head;Temp;Temp=Temp->pNext)
        {
            push_back(Temp->Data);
        }*/
        for (Iterator<T> it = other.Head; it!=nullptr; ++it)
        {
            push_back(*it);
        }
    }
    ~ForwardList()
    {
        while (Head)pop_front();
        cout << "LDestructor:\t" << this << endl;
    };

    ForwardList<T>& operator=(const ForwardList<T> other)
    {
        if (this == &other)return *this;
        while (Head)
        {
            pop_front();
        }
        for (Iterator<T> it = other.Head; it; ++it)push_back(*it);
        cout << "CopyAssigment:\t" << this << endl;
        
    }

    const T& operator[](int index)const
    {
        Element<T>* Temp = Head;
        for (size_t i = 0; i < index; i++)Temp = Temp->pNext;
        return Temp->Data;
        
    }
    T& operator[](int index)
    {
        Element<T>* Temp = Head;
        for (size_t i = 0; i < index; i++)Temp = Temp->pNext;
        return Temp->Data;

    }

    void push_front(T Data)
    {
        /*Element* New = new Element(Data);
        New->pNext = Head;
        Head = New;*/
        Head = new Element<T>(Data, Head);
        size++;
    }

   /* void unique()
    {
        if (Head == nullptr)return;
        for (Element<T>* Temp = Head; Temp; Temp=Temp->pNext)
        {
            for (Element<T>* Temp = Head; Temp; Temp = Temp->pNext)
            {
                if (Temp->pNext==Temp->pNext->pNext)
                {
                    Element<T>* Del = Temp->pNext->pNext;
                    Temp->pNext = Del->pNext;
                    delete Del;
                }
            }
        }
    }*/


    void print()const
    {
        ///*Element* Temp = Head;
        //while (Temp)
        //{
        //    cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
        //    Temp = Temp->pNext;
        //}

        for (Element<T>*Temp=Head; Temp; Temp=Temp->pNext)
        {
            cout << Temp << tab << Temp->Data << tab << Temp->pNext<<endl;
        }

        cout << "Колличество элементов списка: " << size << endl;
        cout << "Общее Колличество элементов: " << Head->count << endl;

    }

    void push_back(T Data)
    {
        if (Head == nullptr)return push_front(Data);
        Element<T>* New = new Element<T>(Data);
        Element<T>* Temp = Head;
        while (Temp->pNext)
        {
            Temp = Temp->pNext;
        }
        Temp->pNext = New;
        size++;
        
    }

    void pop_front()
    {
        if (Head == nullptr)return;
        Element<T>* Del = Head;
        Head = Head->pNext;
        delete Del;
        size--;
    }

    void pop_back()
    {
        if (Head == nullptr)return;
        if (Head->pNext == nullptr)return pop_front();
        Element<T>* Temp = Head;
        while (Temp->pNext->pNext!=nullptr)
        {
            Temp = Temp->pNext;
        }
        delete Temp->pNext;
        Temp->pNext = nullptr;
        size--;
    }

    void reverse()
    {
        Element<T>* prev = nullptr;
        Element<T>* Temp = Head;
        Element<T>* next;
        while (Temp->pNext)
        {
            next = Temp->pNext;

            

            Temp = Temp->pNext;
        }
    }

    void insert(int index, T Data)
    {
        if (index==0||Head==nullptr)return push_front(Data);
        if (index>size)return;
        Element<T>* New = new Element<T>(Data);
        Element<T>* Temp = Head;
        for (size_t i = 0; i < index-1; i++)
        {
            Temp = Temp->pNext;
        }
        New->pNext = Temp->pNext;
        Temp->pNext = New;
        size++;
    }

    void Erase(int index)
    {
        if (index > size)return;
        if (index == 0 || Head == nullptr)return pop_front();
        Element<T>* Temp = Head;
        for (size_t i = 0; i < index-1; i++)
        {
            Temp = Temp->pNext;
        }
        Element<T>* Del = Temp->pNext;
        Temp->pNext = Temp->pNext->pNext;
        delete Del;
        size--;
    }
};

//#define base_check
//#define CONSTRUCTORS_CHECK

int main()
{
    setlocale(LC_ALL, "");
#ifdef base_check
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
#endif // base_check

   /* ForwardList list1;
    list1.push_back(3);
    list1.push_back(5);
    list1.push_back(8);
    list1.push_back(13);
    list1.push_back(21);
    list1.print();

    ForwardList list2;
    list2.push_back(34);
    list2.push_back(55);
    list2.push_back(89);
    list2.print();*/

#ifdef CONSTRUCTORS_CHECK
    int n;
    cout << "введите размер списка: "; cin >> n;
    ForwardList list;
    for (size_t i = 0; i < n; i++)
    {
        list.push_front(rand());
    }
    cout << "cписок заполнен" << endl;
#endif // CONSTRUCTORS_CHECK

   /* int n;
    cin >> n;
    ForwardList list(n);
    for (size_t i = 0; i < n; i++)
    {
        list[i] = rand() % 100;
    }
    for (size_t i = 0; i < n; i++)
    {
        cout << list[i] << endl;
    }*/

    /*ForwardList list = { 3,5,8,13,21 };
    list.print();
    for (Iterator it = list.getHead(); it != nullptr; it++)
    {
        cout << *it << tab;
    }
    cout << endl;*/
    ForwardList<int> list = { 3,5,8,8,13,21 };
    for (int i : list)
    {
        cout << i << tab;
    }
    cout << endl;

    list.reverse();

    for (int i : list)
    {
        cout << i << tab;
    }
    cout << endl;


    /*ForwardList<double> d_list = { 2.5, 3.14, 5.2, 8.3 };
    for (double i : d_list)
    {
        cout << i << tab;
    }
    cout << endl;

    ForwardList<std::string> s_list = { "have", "a", "nice", "day" };
    for (std::string i : s_list)
    {
        cout << i << tab;
            
    }
    cout << endl;

    ForwardList<std::string> s_list2;
    s_list2 = s_list;
    for (std::string i : s_list2) cout << i << tab; cout << endl;*/


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
