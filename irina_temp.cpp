//
// Created by micup on 12/13/2020.
//

#include <iostream>
#include <cstring>

template<typename T>
class stack {
private:
    T* s;
    int nr;
public:
    stack() {
        s = nullptr;
        nr = 0;
    }

    void push(T x) {
        nr++;
        T *temp = new T(nr);
        for(int i=0; i<nr-1; i++){
            temp[i] = s[i];
        }
        temp[nr-1] = x;
        s = new T(nr);
        std::memcpy(s, temp, nr);
        delete temp;
    }

    T pop(){
        nr--;
        T aux = s[nr];
        T* temp = new T(nr);
        std::memcpy(temp, s, nr);
        std::memcpy(s,temp,nr);
        delete temp;
        return aux;
    }
    void printStack() {
        for (int i = 0; i < nr; i++)
            std::cout << s[i] << " ";
        std::cout << std::endl;
    }
};

int main()
{
    stack<int> s;
    s.push(2);
    s.push(3);
    s.printStack();
    s.pop();
    s.printStack();
}