#ifndef SMARTPOINTER_SMARTPOINTER_H
#define SMARTPOINTER_SMARTPOINTER_H

#include <iostream>
using namespace std;

struct ReferenceCounter
{
private:
    int References;

public:
    ReferenceCounter()
    {
        References = 0;
    }

    int Increment()
    {
        References++;
        return References;
    }

    int Decrement()
    {
        References--;
        return References;
    }

    int GetReferences() const
    {
        return References;
    }
};


template<class Type>
class SmartPointer
{
    /** Pointer to element(s) */
    Type* Ptr;

    ReferenceCounter* RefCount;

public:
    //SmartPointer();
    SmartPointer(Type* NewPtr);
    SmartPointer(SmartPointer<Type>& CopyPtr);
    ~SmartPointer();


    Type& operator*();
    Type* operator->();
    SmartPointer<Type>& operator=(Type* NewPtr);
    SmartPointer<Type>& operator=(SmartPointer<Type>& NewPtr);

    Type& operator[](const int Index);
    //const Type& operator[](const int Index);



    int GetReferenceCount() const;

private:
    void DecrementAndCheckReference();
};

/*
template<class Type>
SmartPointer<Type>::SmartPointer()
{
    RefCount = new ReferenceCounter();
    Ptr = nullptr;

    cout << "default" << endl;
}
 */


template<class Type>
SmartPointer<Type>::SmartPointer(Type* NewPtr)
{
    RefCount = new ReferenceCounter();
    RefCount->Increment();

    Ptr = NewPtr;
}

template<class Type>
SmartPointer<Type>::SmartPointer(SmartPointer<Type>& CopyPtr)
{
    this->RefCount = CopyPtr.RefCount;
    this->RefCount->Increment();

    this->Ptr = CopyPtr.Ptr;
}

template<class Type>
SmartPointer<Type>::~SmartPointer()
{
    DecrementAndCheckReference();
}

template<class Type>
Type& SmartPointer<Type>::operator*()
{
    return *Ptr;
}

template<class Type>
Type* SmartPointer<Type>::operator->()
{
    return Ptr;
}

template<class Type>
SmartPointer<Type>& SmartPointer<Type>::operator=(Type* NewPtr)
{
    DecrementAndCheckReference();

    RefCount = new ReferenceCounter();
    RefCount->Increment();

    Ptr = NewPtr;

    return *this;
}

template<class Type>
SmartPointer<Type>& SmartPointer<Type>::operator=(SmartPointer<Type>& NewPtr)
{
    DecrementAndCheckReference();

    RefCount = NewPtr.RefCount;
    RefCount->Increment();

    Ptr = NewPtr.Ptr;

    return *this;
}

template<class Type>
Type& SmartPointer<Type>::operator[](const int Index)
{
    return Ptr[Index];
}

/*
template<class Type>
const Type& SmartPointer<Type>::operator[](const int Index)
{
    return Ptr[Index];
}
 */

template<class Type>
int SmartPointer<Type>::GetReferenceCount() const
{
    return RefCount->GetReferences();
}

template<class Type>
void SmartPointer<Type>::DecrementAndCheckReference()
{
    int Ref = RefCount->Decrement();
    if (Ref <= 0)
    {
        delete RefCount;
        delete Ptr;
        Ptr = nullptr;
        RefCount = nullptr;
    }
}

#endif //SMARTPOINTER_SMARTPOINTER_H