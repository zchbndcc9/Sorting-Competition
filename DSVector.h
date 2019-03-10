#ifndef DSVECTOR_H
#define DSVECTOR_H

#include "DSString.h"

template <class T>
class DSVector {
public:
    //Default constructor
    DSVector<T>();
    //Initial capacity of vec determined by user
    DSVector<T>(const int);
    //Constructor of vec filled by value determined by user
    DSVector<T>(const int, const T&);
    //Copy constructor
    DSVector<T>(const DSVector&);
    //Use an array as constructor
    DSVector<T>(const T*, int);

    //Access certain index of vec
    T& operator[](const int);
    //Copy contents of vec to current vec object
    DSVector<T>& operator=(const DSVector&);

    //Returns size of vec
    int getSize();
    //Returns capacity of vec
    int getCapacity();
    //Access ref to first member
    T& front();
    //Access ref to last member
    T& back();
    //Add member to end of vec
    void push(const T&);
    //Delete member from end of vec
    void pop();
    //Insert member at certain index of vec
    void insert(int, const T&);
    //If size == 0, returns false
    bool isEmpty();
    //Returns index if it has member, else returns -1
    bool hasMember(int&, const T&);

    ~DSVector<T>();

private:
    bool recursiveBinarySearch(int&, int, int, const T&);
    void copyVec(T*, const T*);
    //Initializes vec to zero
    void fillVec(const T&, const int);
    //Adds one to size and doubles capacity
    void resizeVec();
    //Points to arr of members that are in the heap
    T* vecPtr;
    //Amount of members in vec
    int size;
    //Amount of total members that can be held in vec
    int capacity;
};

template <class T>
DSVector<T>::DSVector(){
    size = 0;
    capacity = 5;
    //Creates an empty array of 5 if user does not specify size
    vecPtr = new T[capacity];
}

template <class T>
DSVector<T>::DSVector(const int newCapacity){
    size = 0;
    capacity = newCapacity;
    vecPtr = new T[capacity];
}

template <class T>
DSVector<T>::DSVector(const int newSize, const T& fillType){
    size = newSize;
    //Pads with twice as many additional spaces for user to
    //fill before having to resize
    capacity = size*2;
    vecPtr = new T[capacity];
    fillVec(fillType, size);
}

template <class T>
DSVector<T>::DSVector(const DSVector& rhs){
    size = rhs.size;
    capacity = rhs.capacity;
    vecPtr = new T[capacity];
    copyVec(this->vecPtr, rhs.vecPtr);
}

template <class T>
DSVector<T>::DSVector(const T* arrPtr, int arrSize){
    size = arrSize;
    capacity = size*2;
    vecPtr = new T[capacity];
    copyVec(this->vecPtr, arrPtr);
}

template <class T>
int DSVector<T>::getSize(){
    return size;
}

template <class T>
int DSVector<T>::getCapacity(){
    return capacity;
}

template <class T>
T& DSVector<T>::operator[](const int index){
    //If user tries to access index of vec that is greater than the size,
    //will throw errror
    if(index >= size){


    }else{
        return *(vecPtr + index);
    }

}

template <class T>
DSVector<T>& DSVector<T>::operator=(const DSVector& rhs){
    if(&rhs != this){
        size = rhs.size;
        capacity = rhs.capacity;
        delete[] vecPtr;
        vecPtr = new T[capacity];
        copyVec(this->vecPtr, rhs.vecPtr);
        return *this;
    }
}

template <class T>
//Returns ptr to first member in the dyn. alloc. array
T& DSVector<T>::front(){
    return *vecPtr;

}

template <class T>
//Returns ptr to last member in the dyn. alloc. array
T& DSVector<T>::back(){
    return *(vecPtr + (size-1));
}

template <class T>
void DSVector<T>::push(const T& newMember){
    if(size != capacity){
        vecPtr[size] = newMember;
        size++;
    } else {
        resizeVec();
        vecPtr[size-1] = newMember;
    }
}

template <class T>
void DSVector<T>::pop(){
    if(size == 0){
        std::cout << "ERROR: CANNOT REMOVE AN ITEM FROM EMPTY VECTOR";
    } else {
        vecPtr[size-1] = 0;
        size--;
    }

}


template <class T>
void DSVector<T>::insert(int index, const T& newMember){
    if(index >= size){

    }
    //If vector needs to be resized
    if(size == capacity){
        resizeVec();
        T* temp = new T[capacity];
        for(int i = 0; i < index; i++){
            temp[i] = this->vecPtr[i];
        }
        //Size has already been changed so need to go to size
        //- 1 so that bounds of vecare not exceeded
        for(int i = index; i < (size-1); i++){
            temp[i+1] = this->vecPtr[i];
        }
        temp[index] = newMember;
        delete[] vecPtr;
        vecPtr = temp;
    } else if(index == 0){
        T* temp = new T[capacity];
        for(int i = 0; i < size; i++){
          temp[i+1] = this->vecPtr[i];
        }
        temp[0] = newMember;
        delete[] vecPtr;
        vecPtr = temp;
        size++;
    } else {
        T* temp = new T[capacity];
        for(int i = 0; i < index; i++){
            temp[i] = this->vecPtr[i];
        }
        for(int i = index; i < size; i++){
            temp[i+1] = this->vecPtr[i];
        }
        temp[index] = newMember;
        delete[] vecPtr;
        vecPtr = temp;
        size++;
    }
}

template <class T>
bool DSVector<T>::isEmpty(){
    return (size == 0 ? true : false);
}

template <class T>
bool DSVector<T>::hasMember(int& index, const T& newMember){
    for(int i = 0; i < size; i++){
        if(vecPtr[i] == newMember){
            index = i;
            return true;
        }
    }
    return false;
}

template <class T>
DSVector<T>::~DSVector(){
    delete[] vecPtr;
}

template <class T>
bool DSVector<T>::recursiveBinarySearch(int& memberIndex, int low, int high, const T& newMember){
   if(low > high){
       return false;
   } else {
       int mid = ((high+low)/2);

       if(this->vecPtr[mid] == newMember) {
            memberIndex = mid;
            return true;
       } else if (this->vecPtr[low] == newMember) {
            memberIndex = low;
            return true;
       } else if (this->vecPtr[high] == newMember) {
            memberIndex = high;
            return true;
       } else if (newMember > this->vecPtr[mid]) {
            return recursiveBinarySearch(memberIndex, mid, high, newMember);
       } else {
            return recursiveBinarySearch(memberIndex, low, mid, newMember);
       }
    }
}

//Does this look ok? Copying once I've already allocated the space
template <class T>
void DSVector<T>::copyVec(T* lhs, const T* rhs){
    for(int i = 0; i < capacity; i++){
        lhs[i] = rhs[i];
    }
}
template <class T>
void DSVector<T>::fillVec(const T& fillType, const int amountToFill){
    for(int i = 0; i < amountToFill; i++){
        vecPtr[i] = fillType;
    }
}

template <class T>
void DSVector<T>::resizeVec(){
  //Once newMember is added, the vec will have enough space
  //for twice the amount of new members
    T* temp = new T[(++size)*2];
    copyVec(temp, this->vecPtr);
    delete[] vecPtr;
    vecPtr = temp;
    capacity = size*2;
}

#endif // DSVECTOR_H
