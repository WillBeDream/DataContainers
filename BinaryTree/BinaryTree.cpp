// BinaryTree.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;

#define tab "\t"

class Tree 
{
protected:
    class Element
    {
        int Data;
        Element* pLeft;
        Element* pRight;
    public:
        Element(int Data, Element* pLeft=nullptr, Element* pRight=nullptr) : Data(Data), pLeft(pLeft), pRight(pRight)
        {
            cout << "Econstructor:\t" << this << endl;
        }
        ~Element()
        {
            cout << "EDestructor:\t" << this << endl;
        }

        bool is_leaf()const
        {
            return pLeft == pRight;
        }

        friend class Tree;
        friend class UniqueTree;
    }*Root;
public:
    Element* getRoot()const
    {
        return Root;
    }

    Tree()
    {
        this->Root = nullptr;
        cout << "TConstructor:\t" << this << endl;
    }

    Tree(const std::initializer_list<int>& il) :Tree()
    {
        for (int const* it = il.begin(); it != il.end(); it++)
        {
            insert(*it, Root);
        }
    }

    Tree(const Tree& other):Tree()
    {
        copy(other.Root);
        cout << "CopyConstructor:\t" << this << endl;
    }


    ~Tree()

    {
        clear();
        cout << "TDestructor:\t" << this << endl;
    }

    void insert(int Data)
    {
        insert(Data, Root);
    }

    void clear()
    {
        clear(Root);
        Root = nullptr;
    }
    int minValue()const
    {
        return minValue(Root);
    }

    int maxValue()const
    {
        return maxValue(Root);
    }

    void print()
    {
        print(Root);
        cout << endl;
    }

    int size()const
    {
        return size(Root);
    }

    int summ()const
    {
        return summ(Root);
    }

    double avg()const
    {
        return avg(Root);
    }

    void erase(int Data)
    {
        return erase(Data, Root);
    }
private:
    void insert(int Data, Element*Root)
    {
        if (this->Root == nullptr)
        {
            this->Root = new Element(Data);
            return;
        }
        if (Root == nullptr)return;
        if (Data < Root->Data)
        {
            if (Root->pLeft == nullptr)
            {
                Root->pLeft = new Element(Data);
            }
            else insert(Data, Root->pLeft);
        }
        else
        {
            if (Root->pRight == nullptr)Root->pRight = new Element(Data);
            else insert(Data, Root->pRight);
        }
    }

    void erase(int Data, Element*& Root)
    {
        if(Root == nullptr)return;
        erase(Data, Root->pLeft);
        erase(Data, Root->pRight);
        if (Data==Root->Data)
        {
            if (Root->is_leaf())
            {
                delete Root;
                Root = nullptr;
            }
            else
            {
                if (size(Root->pLeft) > size(Root->pRight))
                {
                    Root->Data = maxValue(Root->pLeft);
                    erase(maxValue(Root->pLeft), Root->pLeft);
                }
                else
                {
                    Root->Data = minValue(Root->pRight);
                    erase(minValue(Root->pRight), Root->pRight);
                }
            }
        }
    }

    void clear(Element* Root)
    {
        if (Root == nullptr)return;
        clear(Root->pLeft);
        clear(Root->pRight);
        delete Root;
    }

    void copy(Element* Root)
    {
        if (Root == nullptr)return;
        insert(Root->Data, this->Root);
        copy(Root->pLeft);
        copy(Root->pRight);
    }

    int minValue(Element* Root)const
    {
        if (Root == nullptr)return 0;
       /* if (Root->pLeft == nullptr)return Root->Data;
        else return minValue(Root->pLeft);*/
        /*return Root->pLeft == nullptr ? Root->Data : minValue(Root->pLeft);*/
        return !Root->pLeft ? Root->Data : minValue(Root->pLeft);
    }

    int maxValue(Element* Root)const
    {
        if (Root == nullptr)return 0;
        /*if (Root->pRight == nullptr)return Root->Data;
        else return maxValue(Root->pRight);*/
        return Root->pRight == nullptr ? Root->Data : maxValue(Root->pRight);
    }

    int size(Element*Root)const
    {
       if (Root == nullptr)return 0;
       else return size(Root->pRight)+size(Root->pLeft)+1;
    }
    
    int summ(Element* Root)const
    {
        if (Root == nullptr)return 0;
        else return summ(Root->pLeft) + summ(Root->pRight) + Root->Data;
    }

    double avg(Element* Root)const
    {
        if (Root == nullptr)return 0;
        else return double(summ(Root->pLeft) + summ(Root->pRight) + Root->Data) / double(size(Root->pRight) + size(Root->pLeft) + 1);
    }

    void print(Element* Root)const
    {
        if (Root == nullptr)return;
        print(Root->pLeft);
        cout << Root->Data << "\t";
        print(Root->pRight);
    }
};

class UniqueTree : public Tree
{
    void insert(int Data, Element* Root)
    {
        if (this->Root == nullptr)
        {
            this->Root = new Element(Data);
            return;
        }
        if (Root == nullptr)return;
        if (Data < Root->Data)
        {
            if (Root->pLeft == nullptr)
            {
                Root->pLeft = new Element(Data);
            }
            else insert(Data, Root->pLeft);
        }
        else if(Data>Root->Data)
        {
            if (Root->pRight == nullptr)Root->pRight = new Element(Data);
            else insert(Data, Root->pRight);
        }
    }

    
public:
    void insert(int Data)
    {
        insert(Data, this->Root);
    }
};



int factorial(int n)
{
    if (n == 0)
    {
        return 1;
    }
    else return n * factorial(n - 1);
}

double power(double a, int n)
{
    if (n == 0)
    {
        return 1;
    }
    else return a * power(a, n - 1);
}


//#define BASE_CHECK

int main()
{
    setlocale(LC_ALL, "");
#ifdef BASE_CHECK 
    int n;
    cin >> n;
    UniqueTree tree;
    for (size_t i = 0; i < n; i++)
    {
        tree.insert(rand() % 100 + 2);
    }
    tree.print();
    cout << endl;
    cout << tree.avg() << endl;
#endif // BASE_CHECK 

    Tree tree = { 50,25,75,16,32,64,80,27,35 }; 
    tree.print();
    /*Tree tree2 = tree;
    tree2.print();*/
    int value;
    cin >> value;
    tree.erase(value);
    tree.print();
   
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
