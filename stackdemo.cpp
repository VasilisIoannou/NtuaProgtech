#include<iostream>


using namespace std;

template <typename T>
class stack{
public:
    stack<T>(int size);
    stack<T> (const stack &s);
    ~stack();
    const stack& operator= (const stack &s){
        delete[] List;
        ListSize = s. ListSize;
        DataPos = s.DataPos;
        List = new T[ListSize];
        for(int i=0;i<s.DataPos;i++)
            List[i]=s.List[i];

        return *this;
    }

    bool empty();
    void push (const T &x);
    T pop();
    int size();

    friend ostream& operator<< (std::ostream &out, const stack &s) {
        out<<'[';
        if(s.DataPos==0) out<<']';
        else{
            out<<s.List[0];
            for(int i=1;i<s.DataPos;i++)
                out<<", "<<s.List[i];
            out<<']';
        }
    }

private:
    int ListSize;
    int DataPos;
    T *List;
};

template <typename T> stack<T>::stack(int size){
    DataPos=0;
    ListSize=size;
    List = new T[ListSize];
}
template <typename T> stack<T>::stack(const stack &s){
    DataPos = s.DataPos;
    ListSize = s.ListSize;
    List = new T[ListSize];
    for(int i=0;i<ListSize;i++)
        List[i] = s.List[i];
}
template <typename T> stack<T>::~stack(){
    delete[] List;
}
template <typename T> bool stack<T>::empty(){
    if(DataPos==0) return true;
    return false;
}
template<typename T> void  stack<T>::push(const T &x){
    if(DataPos<ListSize)
        List[DataPos++] = x;
}
template<typename T> T stack<T>:: pop(){
    if(DataPos>0)
        return List[--DataPos];
}
template<typename T> int stack<T>::size(){
    return DataPos;
}

