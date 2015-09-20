#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <typeinfo>

#define PATH "============================================\n"

using namespace std;

class IObject{
public:
    virtual bool less(IObject*) = 0;//if less then TRUE;
    virtual IObject* clone() = 0;
    virtual void show(void) = 0;
};
class IntObject : public IObject{
    int data;
public:
    void setData(int data){ this->data = data; }
    int getData(){ return data; }

    bool less(IObject *obj){
        if (IntObject *bt = dynamic_cast<IntObject*>(obj)){
            if (data < bt->getData()){
                cout << "first < second" << endl;
                return true;
            }
            else {
                cout << "first > second" << endl;
                return false;
            }
        }
        else {
            cout << "error in dynamic_cast#1" << endl;
            exit(1);
        }
    }
    IObject* clone(){
        return this;
    }
    void show(void){
        cout << data << endl;
    }
};
class StringObject : public IObject{
    string data;
public:
    void setData(string data){ this->data = data; }
    string getData(){ return data; }

    bool less(IObject *obj){
        if (StringObject *bt = dynamic_cast<StringObject*>(obj)){
            if (data < bt->getData()){
                cout << "first < second" << endl;
                return true;
            }
            else {
                cout << "first > second" << endl;
                return false;
            }
        }
        else {
            cout << "error in dynamic_cast#1" << endl;
            exit(1);
        }
    }
    IObject* clone(){
        return this;
    }
    void show(void){
        cout << data << endl;
    }
};
class CharObject : public IObject{
    char data;
public:
    void setData(char data){ strcpy(&(this->data), &data); }
    char getData(){ return data; }

    bool less(IObject *obj){
        if (CharObject *bt = dynamic_cast<CharObject*>(obj)){
            char temp = bt->getData();
            if (strcmp(&(this->data), &temp) < 0){
                cout << "first < second" << endl;
                return true;
            }
            else {
                cout << "first > second" << endl;
                return false;
            }
        }
        else {
            cout << "error in dynamic_cast#3" << endl;
            exit(1);
        }
    }
    IObject* clone(){
        return this;
    }
    void show(void){
        cout << data << endl;
    }
};

template<class Key, class Data> struct Pair{
    Key key;
    Data data;
};

template<class Key, class Data>
class MultiMap{
    Key key;
    Data data;
    int counter;
    int size;
    int step;
    Pair<Key, Data> *arr;
public:
    MultiMap();
    void realloc_plus();
    void insert(Key f_key, Data f_data);
    void serch(Key f_key);
    void del(Key f_key);
    void add();
    MultiMap& operator [](IObject* newKey);
    MultiMap& operator = (IObject* newData);
    void show();
    ~MultiMap(){ delete[] arr; }
};

template<class Key, class Data>
MultiMap<Key, Data>::MultiMap(){
    counter = 0;
    size = 2;
    step = 2;
    arr = new Pair<Key, Data>[size];
};

template<class Key, class Data>
void MultiMap<Key, Data>::del(Key f_key){
    Pair<Key, Data> *temp = new Pair<Key, Data>[size];
    int index = 0;
    int lastCounter = counter;
    for (int i = 0; i < lastCounter; i++){
        if (arr[i].key.getData() != f_key.getData()){
            temp[index] = arr[i];
            index++;
        }
        else{
            counter--;
        }
    }
    Pair<Key, Data> *newTemp = new Pair<Key, Data>[counter];
    for (int i = 0; i < counter; i++){
        newTemp[i] = temp[i];
    }
    delete[] temp;
    delete[] arr;
    arr = newTemp;
    size = counter;
}

template<class Key, class Data>
void MultiMap<Key, Data>::realloc_plus(){
    size *= step;
    Pair<Key, Data> *temp = new Pair<Key, Data>[size];
    int  i = 0;
    while (i != counter) {
        temp[i] = arr[i];
        i++;
    }
    delete[] arr;
    arr = temp;
}
template<class Key, class Data>
void MultiMap<Key, Data>::serch(Key f_key){
    cout << "Try to found " <<f_key.getData() << endl;
    int found = 0;
    for (int i = 0; i < counter; i++){
        if (f_key.getData() == arr[i].key.getData()){
            found++;
            cout << "Found:" << endl;
            cout << "   Key: " << arr[i].key.getData();
            cout << "   Value: " << arr[i].data.getData() << endl;
        }
    }
    if (found == 0) cout << "Nothing found!\n";
}

template<class Key, class Data>
void MultiMap<Key, Data>::show(){
    for (int i = 0; i < counter; i++){
        cout << "Key: " << arr[i].key.getData() << "    Value: " << arr[i].data.getData() << endl;
    }
}

template <class Key, class Data>
void MultiMap<Key, Data>::insert(Key f_key, Data f_data){
    if (counter < (size - 1)){
        arr[counter].key.setData(f_key.getData());
        arr[counter].data.setData(f_data.getData());
        counter++;
    }
    else{
        realloc_plus();
        insert(f_key, f_data);
    }
}
template<class Key, class Data>
MultiMap<Key, Data>& MultiMap<Key, Data>::operator [](IObject* newKey){

    if (Key *bt = dynamic_cast<Key*>(newKey)){
        key.setData(bt->getData());
    }
    else {
        cout << "Error#1_4: dynamic_cast" << endl;
        exit(1);
    }
    return *this;
}

template<typename Key, typename Data>
MultiMap<Key, Data>& MultiMap<Key, Data>::operator = (IObject* newData){

    if (Data *bt = dynamic_cast<Data*>(newData)){
        data.setData(bt->getData());
    }
    else {
        cout << "Error#1_5: dynamic_cast" << endl;
        exit(1);
    }
    return *this;
}

template <class Key, class Data>
void MultiMap<Key, Data>::add(){
    insert(key, data);
}

int main(){
    MultiMap<IntObject, IntObject> m;
    IntObject intA;
    IntObject intB;
    IObject * p1 = &intA;
    IObject * p2 = &intB;
    intA.setData(8);
    intB.setData(14);
    m[p1] = p2;
    m.add();

    intA.setData(9);
    intB.setData(12);
    m[p1] = p2;
    m.add();

    intA.setData(26);
    intB.setData(17);
    m[p1] = p2;
    m.add();

    intA.setData(9);
    intB.setData(18);
    m[p1] = p2;
    m.add();

    m.show();

    IntObject f_key;
    f_key.setData(9);
    m.serch(f_key);
    m.show();

    m.del(f_key);
    m.show();

    intA.setData(8);
    intB.setData(14);
    m[p1] = p2;
    m.add();
    intA.setData(9);
    intB.setData(12);
    m[p1] = p2;
    m.add();
    intA.setData(26);
    intB.setData(17);
    m[p1] = p2;
    m.add();
    intA.setData(9);
    intB.setData(18);
    m[p1] = p2;
    m.add();
    intA.setData(8);
    intB.setData(14);
    m[p1] = p2;
    m.add();
    intA.setData(9);
    intB.setData(12);
    m[p1] = p2;
    m.add();
    intA.setData(26);
    intB.setData(17);
    m[p1] = p2;
    m.add();
    intA.setData(9);
    intB.setData(18);
    m[p1] = p2;
    m.add();
    intA.setData(8);
    intB.setData(14);
    m[p1] = p2;
    m.add();
    intA.setData(9);
    intB.setData(12);
    m[p1] = p2;
    m.add();
    intA.setData(26);
    intB.setData(17);
    m[p1] = p2;
    m.add();
    intA.setData(9);
    intB.setData(18);
    m[p1] = p2;
    m.add();
    intA.setData(8);
    intB.setData(14);
    m[p1] = p2;
    m.add();
    intA.setData(9);
    intB.setData(12);
    m[p1] = p2;
    m.add();
    intA.setData(26);
    intB.setData(17);
    m[p1] = p2;
    m.add();
    intA.setData(9);
    intB.setData(18);
    m[p1] = p2;
    m.add();
    intA.setData(8);
    intB.setData(14);
    m[p1] = p2;
    m.add();
    intA.setData(9);
    intB.setData(12);
    m[p1] = p2;
    m.add();
    intA.setData(26);
    intB.setData(17);
    m[p1] = p2;
    m.add();
    intA.setData(9);
    intB.setData(18);
    m[p1] = p2;
    m.add();
    intA.setData(8);
    intB.setData(14);
    m[p1] = p2;
    m.add();
    intA.setData(9);
    intB.setData(12);
    m[p1] = p2;
    m.add();
    intA.setData(26);
    intB.setData(17);
    m[p1] = p2;
    m.add();
    intA.setData(9);
    intB.setData(18);
    m[p1] = p2;
    m.add();
    m.show();

    cout << PATH;

    MultiMap<IntObject, CharObject> m1;
    IntObject intD;
    CharObject intC;
    intD.setData(8);
    intC.setData('a');
    m1.insert(intD, intC);
    intD.setData(9);
    intC.setData('b');
    m1.insert(intD, intC);
    intD.setData(26);
    intC.setData('c');
    m1.insert(intD, intC);
    intD.setData(9);
    intC.setData('d');
    m1.insert(intD, intC);
    m1.show();

    IntObject c_key;
    c_key.setData(9);
    m1.serch(c_key);
    m1.del(c_key);
    m1.show();

    cout << PATH;

    MultiMap<IntObject, StringObject> m2;
    IntObject intE;
    StringObject stringF;
    intE.setData(1);
    stringF.setData("map");
    m2.insert(intE, stringF);
    intE.setData(2);
    stringF.setData("mult");
    m2.insert(intE, stringF);
    intE.setData(3);
    stringF.setData("lol");
    m2.insert(intE, stringF);
    intE.setData(4);
    stringF.setData("c++");
    m2.insert(intE, stringF);
    intE.setData(2);
    stringF.setData("qwert");
    m2.insert(intE, stringF);
    m2.show();

    IntObject s_key;
    s_key.setData(9);
    m2.serch(s_key);
    m2.del(s_key);
    m2.show();

    cout << PATH;
    cout << "string less\n";

    StringObject strA;
    StringObject strB;

    IObject *ps1 = &strA;
    IObject *ps2 = &strB;

    strA.setData("aba");
    strB.setData("abc");

    ps1->less(ps2);


//    cout << "\nchar less\n";

//    CharObject charA;
//    CharObject charB;

//    IObject *pc1 = &charA;
//    IObject *pc2 = &charB;

//    charA.setData('c');
//    charB.setData('b');

//    pc1->less(pc2);

    //clone int

//    IObject * pi1 = &intA;
//    IObject * pi2 = &intB;
//    intA.setData(8);
//    intB.setData(9);
//    pi1->show();
//    pi2->show();
//    pi2 = pi1->clone();
//    pi1->show();
//    pi2->show();

    //clone char

//    CharObject charA;
//    CharObject charB;
//    IObject * ch1 = &charA;
//    IObject * ch2 = &charB;
//    charA.setData('c');
//    ch1->show();
//    ch2->show();
//    ch2 = ch1->clone();
//    ch1->show();
//    ch2->show();

//    //clone string
//    IObject * p1 = &strA;
//    IObject * p2 = &strB;
//    strA.setData("aba");
//    strB.setData("ccc");
//    p1->show();
//    p2->show();
//    p2 = p1->clone();
//    p1->show();
//    p2->show();


    return 0;
}













//#include <iostream>
//#include <string>

//using namespace std;

//template <Class KEY, Class DATA> struct pair{
//    KEY key;
//    DATA value;
//};

//class IObject{
//public:
//    virtual bool equal(IObject*) = 0;
//    virtual IObject* clone() = 0;
//};

//class IntObject: public IObject{

//};

//class CharObject: public IObject{

//};

//class StringObject: public IObject{

//};


//int main()
//{

//    return 0;
//}

