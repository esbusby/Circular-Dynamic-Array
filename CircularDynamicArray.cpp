#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

template<typename T>
class CircularDynamicArray {
    private:
    int size;   
    int cap;
    int front;
    int back;
    T error;
    T* array;
    int median(int val1, int val2, int val3){
        if(val1 <= val2 && val1 >= val3){
            return val1;
        }
        else if(val1 <= val3 && val1 >= val2){
            return val1;
        }
        else if(val2 <= val1 && val2 >= val3){
            return val2;
        }
        else if(val2 <= val3 && val2 >= val1){
            return val2;
        }
        else if(val3 <= val1 && val3 >= val2){
            return val3;
        }
        else{
            return val3;
        }
    }
    void Merge(T* array, int i, int j, int k){
        int mergedSize;                            
        int mergePos;                              
        int leftPos;                               
        int rightPos;                              
        T* mergedArray;

        mergePos = 0;
        mergedSize = k - i + 1;
        leftPos = i;                               
        rightPos = j + 1;                         
        mergedArray = new T[mergedSize];       
        
        while (leftPos <= j && rightPos <= k) {
            if (array[leftPos] < array[rightPos]) {
                mergedArray[mergePos] = array[leftPos];
                ++leftPos;
            }
            else {
                mergedArray[mergePos] = array[rightPos];
                ++rightPos;
                
            }
            ++mergePos;
        }
        
        while (leftPos <= j) {
            mergedArray[mergePos] = array[leftPos];
            ++leftPos;
            ++mergePos;
        }
        
        while (rightPos <= k) {
            mergedArray[mergePos] = array[rightPos];
            ++rightPos;
            ++mergePos;
        }
        
        for (mergePos = 0; mergePos < mergedSize; ++mergePos) {
            array[i + mergePos] = mergedArray[mergePos];
        }
        delete[] mergedArray;
    }
    void MergeSort(T* array, int i, int k){
        int j;
   
        if (i < k) {
            j = (i + k) / 2;
            
            MergeSort(array, i, j);
            MergeSort(array, j + 1, k);
            
            Merge(array, i, j, k);
        }
    }

    public:
    CircularDynamicArray(){
        array = new T[cap = 2];
        size = 0;
        front = 0;
        back = 0;
    }
    CircularDynamicArray(int s){
        cap = s;
        array = new T[cap];
        size = s;
        front = 0;
        back = 0;
    }
    ~CircularDynamicArray(){
        delete[] array;
    };
    T& operator[](int i){
        if (i < 0 || i >= size) {
        cout << "Error: Index is out of bounds." << endl;
        return error;
        }
        return array[(front + i) % cap];
    }
    void addEnd(T v){
        if(size == cap){
            int newCap = cap * 2;
            T* newArray = new T[newCap];
            for(int i =  0; i < size; i++){
                newArray[i] = array[(front + i) % cap];
            }

            front = 0;
            back = size - 1;

            delete[] array;

            array = newArray;
            cap = newCap;
        }
        array[(front + size) % cap] = v;
        size++;
        back = (size - 1) % cap;
    }
    void addFront(T v){
        if(size == cap){
        int newCap = cap * 2;
        T* newArray = new T[newCap];
        
        for(int i = 0; i < size; i++){
            newArray[i+1] = array[(front + i) % cap];
        }

        front = 1;
        back = size - 1;

        delete[] array;

        array = newArray;
        cap = newCap;
    }
        front = (front - 1 + cap) % cap;
        array[front] = v;
        size++;
    }
    void delEnd(){
        size--;
        back = (back - 1 + cap) % cap;

        if(size <= (cap / 4) && cap > 2){
            int newCap = cap / 2;
            T* newArray = new T[newCap];

            for(int i = 0; i < size; i++){
                newArray[i] = array[(front + i) % cap];
            }

            front = 0;
            back = size - 1;

            delete[] array;

            array = newArray;
            cap = newCap;
        }

}
    void delFront(){
        front = (front + 1) % cap;
        size--;

        if(size == (cap / 4) && cap > 2){
            int newCap = cap / 2;
            T* newArray = new T[newCap];

            for(int i = 0; i < size; i++){
                newArray[i] = array[(front + i) % cap];
            }

            front = 0;
            back = size - 1;

            delete[] array;

            array = newArray;
            cap = newCap;
         }        
    }
    int length(){
        return size;
    }
    int capacity(){
        return cap;
    }
    void clear(){
        delete[] array;
        array = new T[cap = 2];
        size = 0;
        front = 0;
        back = 0;
     }
    T QSelect(int k){
        T* newArray = new T[cap];
        for(int i = 0; i < size; i++){
            newArray[i] = array[(front + i) % cap];
        }
        front = 0;
        back = size - 1;
        delete[] array;
        array = newArray;

        int val1 = rand() % size;
        int val2 = rand() % size;
        int val3 = rand() % size;

        int pivotIndex = median(val1, val2, val3);
        T pivot = array[pivotIndex];
        
        CircularDynamicArray left;
        CircularDynamicArray equal;
        CircularDynamicArray right;

        for(int i = 0; i < size; i++){
            if(array[i] < pivot){
                left.addEnd(array[i]);
            }
            else if(array[i] == pivot){
                equal.addEnd(array[i]);
            }
            else{
                right.addEnd(array[i]);
            }
        }

        if(k <= left.length()){
            return left.QSelect(k);
        }
        else if(k <= left.length() + equal.length()){
            return equal[0];
        }
        else{
            return right.QSelect(k - equal.length() - left.length());
        }
    }
    void Sort(){
        T* newArray = new T[cap];
        for(int i = 0; i < size; i++){
            newArray[i] = array[(front + i) % cap];
        }
        front = 0;
        back = size - 1;
        delete[] array;
        array = newArray;

        MergeSort(array, front, (front + size - 1) % cap);
     }
    int linearSearch(T e){
        for(int i = 0; i < size; i++){
            if(array[(i + front) % cap] == e){
                return i;
            }
        }
        return -1;
     }
    int binSearch(T e){
        int low = 0;
        int high = size - 1;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (array[mid] == e) {
                return mid; 
            } else if (array[mid] < e) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        return -1;
    }
    CircularDynamicArray(const CircularDynamicArray &old){
        size = old.size;
        cap = old.cap;
        front = old.front;
        back = old.back;
        array = new T[cap];
        for(int i = 0; i < cap; i++){
            array[i] = old.array[i];
        }

    }
    CircularDynamicArray& operator=(const CircularDynamicArray& rhs){
        delete[] array;
        size = rhs.size;
        cap = rhs.cap;
        front = rhs.front;
        back = rhs.back;
        array = new T[cap];
        for(int i = 0; i < rhs.cap; i++){
            array[i] = rhs.array[i];
        } 

        return *this;
    }
};
