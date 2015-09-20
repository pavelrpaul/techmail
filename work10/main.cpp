#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <typeinfo>
#include <stdexcept>
#include <new>
#include <stdio.h>
#include <errno.h>

#define MIN 1

const char *filename = "testfile.txt";
FILE *fout;
void debug(char* str);

using namespace std;

template<class T> class Vector{
    int n;
    T* data;
    int head;

    void realloc_plus()
    {
        n += 1;
        T *temp = new T[n];
        int  i = 0;
        while (head != n) {
            temp[i] = data[head];
            i++;
            head++;
        }
        delete[] data;
        data = temp;
        //data[size] = NULL;
        head = 0;
    }
    void setZero(){
        for (int i(0); i < n; i++){
            data[i] = 0;
        }
    }
    void push_back(T elem) {
        realloc_plus();
        data[n - 1] = elem;
    }
public:
    Vector(){
        debug("-->Vectro()");
        cout << "set N : ";
        try{
            if (!(cin >> n)) throw n;
        }
        catch (int){
            debug("error: try to cin << char*");
            cout << "Mistake! it will be default(1)! \n";
            n = MIN;
            cin.clear();
            cin.ignore(1, '\n');
        }
        head = 0;
        if (n < MIN) throw n;
        try{
            data = new T[n];
            setZero();
        }
        catch (bad_alloc x){
            debug(" error : bad_alloc");
            cout << "Memory problem#1!\n";
            exit(1);
        }
        debug("Vectro()-->");
    }
    Vector(int temp){
        debug("-->Vector(int)");
        try{
            head = 0;
            n = temp;
            if (n < MIN) throw n;
            try{
                data = new T[n];
                setZero();
            }
            catch (bad_alloc x){
                debug("error: bad_alloc");
                cout << "Memory problem#2!\n";
                exit(2);
            }
        }
        catch (int){
            debug("mistake in N");
            cout << "mistake in N\n";
        }
        debug("Vector(int)-->");
    }
    ~Vector(){
        debug("-->~Vector()");
        delete data;
        n = 0;
        debug("~Vector()-->");
    }
    int getN(){
        return n;
    }

    void setData(int size){
        debug("-->setData()");
        for (int i(0); i < size; i++){
            cout << "Please enter a number : ";
            try{
                T temp;
                cin.clear();
                cin.ignore(1000, '\n');
                if (!(cin >> temp)) throw i;
                try{
                    if (i >= n) throw "size";
                    data[i] = temp;
                }
                catch (const char* text){
                    debug("error: IndexOutOfArray ");
                    cout << "container is full!\n";
                }
            }
            catch (int){
                debug("error: cin error");
                cout << "Mistake! it will be default(0)! \n";
                cin.clear();
                cin.ignore(1000, '\n');
            }
        }
        debug("setData()-->");
    }


    //====================================module=================//
    double module(){
        debug("-->module()");
        double module = 0;
        for (int i(0); i < n + 1; i++){ //================exception!!!!!!!!!!!!!!!!!====================//
            try{
                if (i >= n) throw "size";
                module += pow(data[i], 2);
            }
            catch (const char* text){
                debug("error: IndexOutOfArray");
            }
        }
        debug("module()-->");
        return sqrt(module);
    }
    //=================== * const===============//
    void multiplicatConstant(T elem){
        debug("-->multiplicatConstant()");
        for (int i(0); i < n + 2; i++){//=====================exception==================//
            try{
                if (i >= n) throw "size";
                data[i] = data[i] * elem;
            }
            catch (const char* text){
                debug("error: IndexOutOfArray");
            }
        }
        debug("multiplicatConstant()-->");
    }

    //=================scalar==================//
    double scalarMultiplicat(Vector<T>& obj){
        debug("-->scalarMultiplicat()");
        double result = 0;
        int index;
        if (n >= obj.getN()) index = n;
        else index = obj.getN();

        for (int i(0); i < index; i++){
            try{
                if (i >= n || i >= obj.getN()) throw index;
                try{
                    if (i >= n) throw "size";
                    result += data[i] * obj[i];
                }
                catch (const char* text){
                    debug("error: IndexOutOfArray");

                }
            }
            catch (...){
                debug("errorr: IndexOutOfArray");
            }
        }
        debug("scalarMultiplicat()-->");
        return result;
    }

    void show(){
        debug("-->show() ");
        int temp = head;
        cout << "( ";
        while (temp != n){
            cout << data[temp] << " ; ";
            temp++;
        }
        cout << ")\n";
        debug("show()-->");
    }
    T& operator[](int index){
        debug("-->operator[]");
        try{
            if (0 > index || index >= this->getN()) throw index;
            return data[index];
        }
        catch (int k){
            debug("errorr: IndexOutOfArray");
            if (k < 0){
                cout << "acsess denide(0)! you try to get vector[-x]! check you code\n";
                exit(4);
            }
            else{
                cout << "acsess denied(0)!\n";
                exit(4);
            }
        }
        debug("operator[]-->");
    }

    friend ostream& operator<<(ostream& io_Stream, Vector<T>& obj){
        debug("-->ostream<< ");
        try{
            if (obj.getN() < MIN) throw 0;
            obj.show();
        }
        catch (int){
            debug("errorr: Vector : Empty");
            cout << "Vector : Empty\n";
        }
        catch (...){
            debug("error: Unkown error");
            cout << "Unkown error\n";
        }
        debug("ostream<<-->");
        return io_Stream;
    }
    friend istream& operator>>(istream& io_Stream, Vector<T>& obj){
        debug("-->operator>> ");
        obj.setData(obj.getN());
        debug("operator>>-->");
        return io_Stream;
    }
    Vector<T>& operator=(Vector<T>& obj){
        debug("-->operator= ");
        this->~Vector();
        try{
            head = 0;
            n = obj.getN();
            if (n < MIN) throw n;
            try{
                data = new T[n];
                setZero();
            }
            catch (bad_alloc x){
                debug("error: bad_alloc");
                cout << "Memory problem#in =!\n";
                exit(3);
            }
        }
        catch (int){
            debug("errorr: mistake in N!");
            cout << "mistake in N\n";
        }
        for (int i(0); i < n; i++){
            data[i] = obj[i];
        }
        debug("operator= -->");
        return *this;
    }
    friend Vector<T>& operator*(Vector<T>& obj, T x){
        debug("-->operator* on constant ");
        cout << "multiplication on " << x << endl;
        Vector<T> *temp = new Vector<T>(obj.getN());
        *temp = obj;
        temp->multiplicatConstant(x);
        debug("operator* on constant--> ");
        return *temp;
    }
    //========================sum==========================//
    friend Vector<T>& operator+(Vector<T>& obj1, Vector<T>& obj2){
        debug("-->operator+ ");
        cout << "sum two vectors\n";
        int index;
        if (obj2.getN() >= obj1.getN()) index = obj2.getN();
        //else index = obj1.getN();
        Vector<T> *temp = new Vector<T>(index);
        for (int i(0); i < index; i++){
            try{
                if (i >= obj2.getN() || i >= obj1.getN()){
                    throw index;
                }
                (*temp)[i] = obj1[i] + obj2[i];
            }
            catch (...){
                debug("errorr: IndexOutOfArray");
                if (obj2.getN() >= obj1.getN()) {
                    (*temp)[i] = obj2[i];
                }
                else{ (*temp)[i] = obj1[i]; }
            }
        }
        debug("operator+ -->");
        return *temp;
    }
    //===========================sub===============================//
    friend Vector<T>& operator-(Vector<T>& obj1, Vector<T>& obj2){
        debug("-->operator- ");
        cout << "subtraction two vectors\n";
        int index;
        if (obj2.getN() >= obj1.getN()) index = obj2.getN();
        else index = obj1.getN();
        Vector<T> *temp = new Vector<T>(index);
        for (int i(0); i < index; i++){
            try{
                if (i == obj2.getN() || i == obj1.getN()) throw index;
                (*temp)[i] = obj1[i] - obj2[i];
            }
            catch (...){
                debug("error: IndexOutOfArray");
                if (obj2.getN() >= obj1.getN()) (*temp)[i] = -obj2[i];
                else (*temp)[i] = -obj1[i];
            }
        }
        debug("operator- -->");
        return *temp;
    }
    friend T operator*(Vector<T>& obj1, Vector<T>& obj2){
        debug("-->operator* vectors ");
        cout << "scalar Multiplication\n";
        debug("operator* vectors -->");
        return obj1.scalarMultiplicat(obj2);
    }
    Vector<T>& operator++(){
        debug("-->icremet ");
        for (int i(0); i < n; i++){
            try{
                if (i >= n) throw "size";
                data[i]++;
            }
            catch (const char* text){
                debug("errorr: IndexOutOfArray");
            }
        }
        debug("icremet-->");
        return *this;
    }
    Vector<T>& operator--(){
        debug("-->decremet ");
        for (int i(0); i < n + 2; i++){
            try{
                if (i >= n) throw "size";
                data[i]--;
            }
            catch (const char* text){
                debug("error: IndexOutOfArray");
            }
        }
        debug("decremet -->");
        return *this;
    }
    void funcForArray(Vector<T>& obj1){
        float result;
        float temp;
        try{
            double a = module();
            double b = obj1.module();
            float tempA = round(a * 10000) / 10000.;
            temp = a * b;
            if (temp == 0) throw "zero";
            double t = this->scalarMultiplicat(obj1);
            float tempT = round(t * 10000) / 10000.;
            result = (tempT) / temp;
            try{
                if (abs(result) != 1) throw - 1;
                else throw 1;
            }
            catch (int k){
                if (k < 0){
                    cout << "colliniarity : none!\n";
                }
                else{
                    cout << "colliniarity : yes!\n";
                }
            }
        }
        catch (const char*){
            debug("error2: div on ZERO!");
        }
        try{
            result = this->scalarMultiplicat(obj1);
            if (result != 0) throw - 1;
            else throw 1;
        }
        catch (int t){
            if (t < 0){
                cout << "orthogonality : none!\n";
            }
            else{
                cout << "orthogonality : yes!\n";
            }
        }
    }
};

void debug(char* str){
    int ecode;
    int encode = fprintf(fout, "%s  ", str);
    fprintf(fout, " in code %d\n", encode);
}

template <class T> void vectorFunc(Vector<T>* arr, int index1, int index2, int size){
    debug("-->vectorFunc()");
    try{
        if (index1 >= size || index2 >= size) throw size;
        arr[index1].funcForArray(arr[index2]);
    }
    catch (int){
        debug("error1: IndexOutOfArray");
    }
    debug("vectorFunc()-->");
}

int main(){
    const int N = 3;
    if ((fout = fopen(filename, "w")) == NULL) {
        fprintf(stderr, "Output file open error \"%s\", code %d\n", filename, errno);
        return 1;
    }
    Vector<int> array[N];
    for (int i(0); i < N; i++){
        cin >> array[i];
    }
    cout << " vectors\n";
    for (int i(0); i < N; i++){
        cout << array[i];
    }

    for (int i(0); i < N; i++){
        ++array[i];
    }
    cout << "increment vectors\n";
    for (int i(0); i < N; i++){
        cout << array[i];
    }
    array[0] = array[1] + array[2];
    cout << "plus\n";
    for (int i(0); i < N; i++){
        cout << array[i];
    }
    vectorFunc(array, 0, 1, N);


    fclose(fout);


    return 0;
}


