
#include <stdlib.h>
#include <iostream>

using namespace std;

class List{
    int size;
    int step;
    int head;
    int *data;
    int counter;
    void addElem(int elem);
public:
    List();
    List(const List&a);
    List(int n);

    void setList(int *data, int sizeArr);
    int *getList();
    int getSize();
    int getHead();
    int getCounter();

    void realloc_plus();
    void show();
    int searchElem(int elem);
    void push_back(int elem);
    void push_begin(int elem);
    void insert(int pos, int elem);
    void remove(int pos);
    bool checkCount(int pos);

    ~List(){delete[] data;}
    //void sort();
};

void func(List **obj, int N);

int main()
{
    int N = 3;
    List **arr = new List*[N];
    arr[0] = new List(10);
    arr[1] = new List(11);
    arr[2] = new List(12);
    func(arr, N);

    List *l = new List(10);
    List *list = new List();

    *list = *l;
    list->show();
    list->insert(10, 91);
    l->show();
    list->show();
    l->remove(11);
    l->show();
    l->remove(10);
    l->show();
    l->remove(4);
    l->show();

    //cout << l->searchElem(29) << endl;
    system("pause");
    return 0;
}

/*
void List::sort(){
    int i, j;
    for (i = head; i < counter; ++i) {
        for (j = head; j < counter - i; j++){
            if (data[j] > data[j + 1])
                std::swap(data[j], data[j + 1]);
        }
    }
}
*/
int List::getHead(){
    return head;
}
int List::getCounter(){
    return counter;
}

List::List(int n){
    counter = 0;
    size = 2;
    step = 2;
    head = 0;
    data = new int[size];
    data[head] = NULL;
    for (int i = 0; i < n; i++) {
        this->push_back(i);
    }
}

List::List(const List &a){
    this->size = a.size;
    this->step = a.step;
    this->head = a.head;
    this->counter = a.counter;
    this->data = new int[size];
    //int index = a.head;
    for(int i = a.head; i < a.counter; i++){
        this->data[i] = a.data[i];
    }
}
void func(List **obj, int N){
    for(int i = 0; i < N; i++){
        int *temp = new int[obj[i]->getCounter()];
        temp = obj[i]->getList();
        int index = obj[i]->getCounter();
        for(int j = 0; j < index - 1; j++){
            for(int k = 0; k < index - j - 1; k++){
                if(temp[k] > temp[k + 1]) swap(temp[k], temp[k + 1]);
            }
        }
        for (int t = 0; t < index; t++){
            cout << temp[t] << " ";
        }
        cout << endl;
    obj[i]->setList(temp, index);
    }
}

int List::getSize(){
    return size;
}

//===================set array fo fucn===================//
void List::setList(int *data, int sizeArr){
    for(int i = 0; i < sizeArr; i++){
        this->push_back(data[i]);
    }
}

//===================get array fo fucn===================//
int *List::getList(){
    int *temp = new int[counter];
    for (int i = head; i < counter; i++){
        temp[i] = data[i];
    }
    return temp;
}

bool List::checkCount(int pos){
    if (pos >= 0 && pos < counter) return true;
    else return false;
}
//==============================remove method========================//
void List::remove(int pos){
    if (!checkCount(pos)){
        cout << "false in removing!" << endl;
        return;
    }
    if(pos == 0){
        head++;
        return;
    }
    if(pos == counter){
        data[counter] = NULL;
        return;
    }
    int *temp = new int[size];
    int  i = 0, index = head;
    while (index != pos) {
        temp[i] = data[index];
        i++;
        index++;
    }
    index++;
    while(index != counter){
        temp[i] = data[index];
        i++;
        index++;
    }
    delete[] data;
    data = temp;
    counter = i;
}
//=================================insetrt metod=======================//
void List::insert(int pos, int elem){
    if(pos == counter){
        push_back(elem);
        return;
    }
    if (!checkCount(pos)){
        cout << "false in insert!" << endl;
        return;
    }
    if(pos == head){
        push_begin(elem);
        return;
    }
    if (counter < (size - 1)){
        int *temp = new int[size];
        int  i = 0, index = head;
        while (index != pos) {
            temp[i] = data[index];
            i++;
            index++;
        }
        temp[i] = elem;
        i++;
        while(index != counter){
            temp[i] = data[index];
            i++;
            index++;
        }
        delete[] data;
        data = temp;
        counter = i;
        data[counter] = NULL;
    }
    else{
        realloc_plus();
        insert(pos, elem);
    }
}
//===========================push_begin===========================//
void List::push_begin(int elem){
    if (counter < (size - 1)){
        int *temp = new int[size];
        int  i = 0;
        temp[i] = elem;
        i++;
        int index = head;
        while (index != counter) {
            temp[i] = data[index];
            i++;
            index++;
        }
        delete[] data;
        data = temp;
        counter = i;
        data[counter] = NULL;
    }
    else{
        realloc_plus();
        push_begin(elem);
    }
}
//==============================serch metod========================//return position
int List::searchElem(int elem){
    int temp = head;
    while (temp != counter){
        if (elem == data[temp]) return temp;
        temp++;
    }
    return -1;
}
//======================================push_back=====================//
void List::push_back(int elem){
    addElem(elem);
}
void List::addElem(int elem) {
    if (counter < (size - 1)){
        data[counter] = elem;
        data[counter + 1] = NULL;
        counter++;
    }
    else{
        realloc_plus();
        addElem(elem);
    }

}

List::List(){
    counter = 0;
    size = 2;
    step = 2;
    head = 0;
    data = new int[size];
    data[head] = NULL;
}
//=========================dinamic array=====================//
void List::realloc_plus()
{
    size *= step;
    int *temp = new int[size];
    int  i = 0;
    while (head != counter) {
        temp[i] = data[head];
        i++;
        head++;
    }
    delete[] data;
    data = temp;
    counter = i;
    data[counter] = NULL;
    head = 0;
}

void List::show(){
    int temp = head;
    while (temp != counter) {
        cout << " -> " << data[temp];
        temp++;
    }
    cout << endl;
}



//#include <stdlib.h>
//#include <iostream>

//using namespace std;

//class List{
//    int size;
//    int step;
//    int head;
//    int *data;
//    int counter;
//    void addElem(int elem);
//public:
//    List();
//    List(const List&a);
//    List(int n);

//    void setList(int *data, int sizeArr);
//    int *getList();
//    int getSize();
//    int getHead();
//    int getCounter();

//    void realloc_plus();
//    void show();
//    int searchElem(int elem);
//    void push_back(int elem);
//    void push_begin(int elem);
//    void insert(int pos, int elem);
//    void remove(int pos);
//    bool checkCount(int pos);

//    ~List(){delete[] data;}
//    //void sort();
//};

//void func(List **obj, int N);

//int main()
//{
//    int N = 3;
//    List **arr = new List*[N];
//    arr[0] = new List(10);
//    arr[1] = new List(11);
//    arr[2] = new List(12);
//    func(arr, N);

//    List *l = new List(10);
//    List *list = new List();

//    *list = *l;
//    list->show();
//    list->insert(10, 91);
//    l->show();
//    list->show();
//    l->remove(11);
//    l->show();
//    l->remove(10);
//    l->show();
//    l->remove(0);
//    l->show();

//    //cout << l->searchElem(29) << endl;
//    return 0;
//}

///*
//void List::sort(){
//    int i, j;
//    for (i = head; i < counter; ++i) {
//        for (j = head; j < counter - i; j++){
//            if (data[j] > data[j + 1])
//                std::swap(data[j], data[j + 1]);
//        }
//    }
//}
//*/
//int List::getHead(){
//    return head;
//}
//int List::getCounter(){
//    return counter;
//}

//List::List(int n){
//    counter = 0;
//    size = 2;
//    step = 2;
//    head = 0;
//    data = new int[size];
//    data[head] = NULL;
//    for (int i = 0; i < n; i++) {
//        this->push_back(i);
//    }
//}

//List::List(const List &a){
//    this->size = a.size;
//    this->step = a.step;
//    this->head = a.head;
//    this->counter = a.counter;
//    this->data = new int[size];
//    //int index = a.head;
//    for(int i = a.head; i < a.counter; i++){
//        this->data[i] = a.data[i];
//    }
//}
//void func(List **obj, int N){
//    for(int i = 0; i < N; i++){
//        int *temp = new int[obj[i]->getSize()];
//        temp = obj[i]->getList();
//        int index = obj[i]->getCounter();
//        for(int j = obj[i]->getHead(); j < index - 1; j++){
//            for(int k = obj[i]->getHead(); k < index - j - 1; k++){
//                if(temp[k] > temp[k + 1]) swap(temp[k], temp[k + 1]);
//            }
//        }
//    obj[i]->setList(temp, index);
//    }
//}

//int List::getSize(){
//    return size;
//}

////===================set array fo fucn===================//
//void List::setList(int *data, int sizeArr){
//    for(int i = 0; i < sizeArr; i++){
//        this->push_back(data[i]);
//    }
//}

////===================get array fo fucn===================//
//int *List::getList(){
//    int *temp = new int[size];
//    for (int i = head; i < counter; i++){
//        temp[i] = data[i];
//    }
//    return temp;
//}

//bool List::checkCount(int pos){
//    if (pos >= 0 && pos < counter) return true;
//    else return false;
//}
////==============================remove method========================//
//void List::remove(int pos){
//    if (!checkCount(pos)){
//        cout << "false in removing!" << endl;
//        return;
//    }
//    if(pos == 0){
//        head++;
//        return;
//    }
//    if(pos == counter){
//        data[counter] = NULL;
//        return;
//    }
//    int *temp = new int[size];
//    int  i = 0, index = head;
//    while (index != pos) {
//        temp[i] = data[index];
//        i++;
//        index++;
//    }
//    index++;
//    while(index != counter){
//        temp[i] = data[index];
//        i++;
//        index++;
//    }
//    delete[] data;
//    data = temp;
//    counter = i;
//}
////=================================insetrt metod=======================//
//void List::insert(int pos, int elem){
//    if(pos == counter){
//        push_back(elem);
//        return;
//    }
//    if (!checkCount(pos)){
//        cout << "false in insert!" << endl;
//        return;
//    }
//    if(pos == head){
//        push_begin(elem);
//        return;
//    }
//    if (counter < (size - 1)){
//        int *temp = new int[size];
//        int  i = 0, index = head;
//        while (index != pos) {
//            temp[i] = data[index];
//            i++;
//            index++;
//        }
//        temp[i] = elem;
//        i++;
//        while(index != counter){
//            temp[i] = data[index];
//            i++;
//            index++;
//        }
//        delete[] data;
//        data = temp;
//        counter = i;
//        data[counter] = NULL;
//    }
//    else{
//        realloc_plus();
//        insert(pos, elem);
//    }
//}
////===========================push_begin===========================//
//void List::push_begin(int elem){
//    if (counter < (size - 1)){
//        int *temp = new int[size];
//        int  i = 0;
//        temp[i] = elem;
//        i++;
//        int index = head;
//        while (index != counter) {
//            temp[i] = data[index];
//            i++;
//            index++;
//        }
//        delete[] data;
//        data = temp;
//        counter = i;
//        data[counter] = NULL;
//    }
//    else{
//        realloc_plus();
//        push_begin(elem);
//    }
//}
////==============================serch metod========================//return position
//int List::searchElem(int elem){
//    int temp = head;
//    while (temp != counter){
//        if (elem == data[temp]) return temp;
//        temp++;
//    }
//    return -1;
//}
////======================================push_back=====================//
//void List::push_back(int elem){
//    addElem(elem);
//}
//void List::addElem(int elem) {
//    if (counter < (size - 1)){
//        data[counter] = elem;
//        data[counter + 1] = NULL;
//        counter++;
//    }
//    else{
//        realloc_plus();
//        addElem(elem);
//    }

//}

//List::List(){
//    counter = 0;
//    size = 2;
//    step = 2;
//    head = 0;
//    data = new int[size];
//    data[head] = NULL;
//}
////=========================dinamic array=====================//
//void List::realloc_plus()
//{
//    size *= step;
//    int *temp = new int[size];
//    int  i = 0;
//    while (head != counter) {
//        temp[i] = data[head];
//        i++;
//        head++;
//    }
//    delete[] data;
//    data = temp;
//    counter = i;
//    data[counter] = NULL;
//    head = 0;
//}

//void List::show(){
//    cout << counter << " " << size << endl;
//    int temp = head;
//    while (temp != counter) {
//        cout << " -> " << data[temp];
//        temp++;
//    }
//    cout << endl;
//}
