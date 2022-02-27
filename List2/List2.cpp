// List2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "List.h"

template<typename T>
List<T>::Element::Element(T Data, Element* pNext, Element* pPrev)
    :Data(Data), pNext(pNext), pPrev(pPrev)
{
    cout << "EConstructor:\t" << this << endl;
}
template<typename T>
List<T>::Element::~Element()
{
    cout << "EDestructor:\t" << this << endl;
}

template<typename T>
List<T>::BaseIterator::BaseIterator(Element* Temp) : Temp(Temp)
{
#ifdef DEBUG
    cout << "BITConstructor:\t" << this << endl;
#endif // DEBUG
}

template<typename T>
List<T>::BaseIterator::~BaseIterator()
{
#ifdef DEBUG
    cout << "BITDestructor:\t" << this << endl;
#endif // DEBUG
}

template<typename T>
bool List<T>::BaseIterator::operator ==(const List<T>::BaseIterator& other)const
{
    return this->Temp == other.Temp;
}
template<typename T>
bool List<T>::BaseIterator::operator !=(const List<T>::BaseIterator& other)const
{
    return this->Temp != other.Temp;
}

template<typename T>
const T& List<T>::BaseIterator::operator*()const
{
    return Temp->Data;
}

template<typename T>
List<T>::BaseIterator::operator bool()const
{
    return Temp;
}

template<typename T>
List<T>::ConstIterator::ConstIterator(Element* Temp) : BaseIterator(Temp)
{
#ifdef DEBUG
    cout << "ITConstructor:\t" << this << endl;
#endif // DEBUG
}

template<typename T>
List<T>::ConstIterator::~ConstIterator()
{
#ifdef DEBUG
    cout << "ItDestructor:\t" << this << endl;
#endif // DEBUG
}

template<typename T>
typename List<T>::ConstIterator& List<T>::ConstIterator::operator++()
{
    BaseIterator::Temp = BaseIterator::Temp->pNext;
    return *this;
}

template<typename T>
typename List<T>::ConstIterator& List<T>::ConstIterator::operator++(int)
{
    ConstIterator old = *this;
    BaseIterator::Temp = BaseIterator::Temp->pNext;
    return old;
}

template<typename T>
typename List<T>::ConstIterator& List<T>::ConstIterator::operator--()
{
    BaseIterator::Temp = BaseIterator::Temp->pPrev;
    return *this;
}

template<typename T>
typename List<T>::ConstIterator& List<T>::ConstIterator::operator--(int)
{
    ConstIterator old = *this;
    BaseIterator::Temp = BaseIterator::Temp->pPrev;
    return old;
}

template<typename T>
List<T>::ConstReverseIterator::ConstReverseIterator(Element* Temp) :BaseIterator(Temp)
{
#ifdef DEBUG
    cout << "RITConstructor:\t" << this << endl;
#endif // DEBUG
}

template<typename T>
List<T>::ConstReverseIterator::~ConstReverseIterator()
{
#ifdef DEBUG
    cout << "RITDestructor" << this << endl;
#endif // DEBUG
}

template<typename T>
typename List<T>::ConstReverseIterator& List<T>::ConstReverseIterator::operator++()
{
    BaseIterator::Temp = BaseIterator::Temp->pPrev;
    return *this;
}

template<typename T>
typename List<T>::ConstReverseIterator& List<T>::ConstReverseIterator::operator++(int)
{
    ConstReverseIterator old = *this;
    BaseIterator::Temp = BaseIterator::Temp->pPrev;
    return old;
}

template<typename T>
typename List<T>::ConstReverseIterator& List<T>::ConstReverseIterator::operator--()
{
    BaseIterator::Temp = BaseIterator::Temp->pNext;
    return *this;
}

template<typename T>
typename List<T>::ConstReverseIterator& List<T>::ConstReverseIterator::operator--(int)
{
    ConstReverseIterator old = *this;
    BaseIterator::Temp = BaseIterator::Temp->pNext;
    return old;
}

template<typename T>List<T>::Iterator::Iterator(Element* Temp) : ConstIterator(Temp)
{
#ifdef DEBUG
    cout << "ItConsctructor:\t" << this << endl;
#endif // DEBUG
}
template<typename T>List<T>::Iterator::~Iterator()
{
#ifdef DEBUG
    cout << "ItDesctructor:\t" << this << endl;
#endif // DEBUG
}
template<typename T>T& List<T>::Iterator::operator *()
{
    return BaseIterator::Temp->Data;
}

template<typename T>
List<T>::ReverseIterator::ReverseIterator(Element* Temp) : ConstReverseIterator(Temp)
{
#ifdef DEBUG
    cout << "RItConstructor:\t" << this << endl;
#endif // DEBUG
}
template<typename T>
List<T>::ReverseIterator::~ReverseIterator()
{
#ifdef DEBUG
    cout << "RItDenstructor:\t" << this << endl;
#endif // DEBUG

}
template<typename T>
T& List<T>::ReverseIterator::operator*()
{
    return BaseIterator::Temp->Data;
}

template<typename T>
typename List<T>::ConstIterator List<T>::cbegin()const
{
    return Head;
}

template<typename T>
typename List<T>::ConstIterator List<T>::cend()const
{
    return nullptr;
}
template<typename T>
typename List<T>::ConstReverseIterator List<T>::crbegin()const
{
    return Tail;
}
template<typename T>
typename List<T>::ConstReverseIterator List<T>::crend()const
{
    return nullptr;
}

template<typename T>
typename List<T>::Iterator List<T>::begin()
{
    return Head;
}
template<typename T>
typename List<T>::Iterator List<T>::end()
{
    return nullptr;
}
template<typename T>
typename List<T>::ReverseIterator List<T>::rbegin()
{
    return Tail;
}
template<typename T>
typename List<T>::ReverseIterator List<T>::rend()
{
    return nullptr;
}


template<typename T>List<T>::List()
{
    Head = Tail = nullptr;
    size = 0;
    cout << "LConstructor:\t" << this << endl;
}

template<typename T>List<T>::List(unsigned int size) :List()
{
    for (size_t i = 0; i < size; i++)
    {
        push_front(int());
    }
}

template<typename T>List<T>::List(const std::initializer_list<T>& il) :List()
{
    for (T const* it = il.begin(); it != il.end(); it++)
    {
        push_back(*it);
    }
}

template<typename T>List<T>::~List()
{
    while (Tail)
    {
        pop_back();
    }
    cout << "LDestructor:\t" << this << endl;
}

template<typename T>
const T& List<T>::operator[](int index)const
{
    Element* Temp = Head;
    for (size_t i = 0; i < index; i++)
    {
        Temp = Temp->pNext;
    }
    return Temp->Data;
}
template<typename T>
T& List<T>::operator[](int index)
{
    Element* Temp = Head;
    for (size_t i = 0; i < index; i++)
    {
        Temp = Temp->pNext;
    }
    return Temp->Data;
}

template<typename T>
void List<T>::push_front(T Data)
{
    if (Head == nullptr && Tail == nullptr)
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
template<typename T>
void List<T>::push_back(T Data)
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
template<typename T>
void List<T>::pop_front()
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
template<typename T>
void List<T>::pop_back()
{
    if (Head == Tail)return pop_front();
    Tail = Tail->pPrev;
    delete Tail->pNext;
    Tail->pNext = nullptr;
    size--;

}
template<typename T>
void List<T>::insert(int index, T Data)
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
        for (size_t i = 0; i < size - index - 1; i++)
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
template<typename T>
void List<T>::Erase(int index)
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
template<typename T>
void List<T>::print()const
{
    for (Element* Temp = Head; Temp; Temp = Temp->pNext)
    {
        cout << Temp << tab << Temp->Data << tab << Temp->pNext << Temp->pPrev << endl;
    }
    cout << "Колличество элементов списка: " << size << endl;
}
template<typename T>
void List<T>::reverse_print()const
{
    for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
    {
        cout << Temp << tab << Temp->Data << tab << Temp->pNext << Temp->pPrev << endl;
    }
    cout << "Колличество элементов списка: " << size << endl;
}


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

    /*List<int> list = { 3,5,8,13,21 };
    list.print();

    for (int i : list)
    {
        cout << i << tab;
    }
    cout << endl;

    list.insert(3, 25);
    
    for (List<int>::ConstReverseIterator it = list.crbegin(); it; ++it)
    {
        cout << *it << tab;
    }
    cout << endl;*/

    List<double> d_list = { 2.5, 3.14, 5.3, 8.3 };
    for (double i: d_list)
    {
        cout << i << tab;
        
    }
    cout << endl;
    for (List<double>::ReverseIterator it = d_list.rbegin(); it; ++it)
    {
        cout << *it << tab;
    }
    cout << endl;

    List<std::string> s_list = { "Have", "a", "nice", "day" };
    for (std::string i : s_list)cout << i << tab; cout << endl;
    for (List<std::string>::ReverseIterator it = s_list.rbegin(); it != s_list.rend(); ++it)
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



