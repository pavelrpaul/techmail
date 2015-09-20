#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define MIS "Error!"
#define PI  3.14//15926535
using namespace std;

class FlatFigure{
public:
    virtual void show() = 0;
    virtual double square() = 0;
    virtual double perimeter() = 0;
};
class Triangle : public FlatFigure{
    int a, b, c;
public:
    Triangle();
    Triangle(int a, int b,  int c){
        this->a = a;
        this->b = b;
        this->c = c;
    }
    void show(){
        cout << "  Triangle :\n";
        printf("Sides : %i, %i, %i\n", a,b,c);
        cout << "Square: " << square() << endl;
        cout << "Perimeter: " << perimeter() << endl;
    }
    double square(){
        if ((a + b) > c && (b + c) > a && (c + a) > a && check()){
            double p = perimeter() / 2;
            return sqrt(p * (p - a) * (p - b) * (p - c));
        }
        else{
            cout << MIS <<endl;
            return -98;
        }

    }
    bool check(){
        if(a > 0 && b > 0 && c > 0){
            return true;
        }
        else{
            return false;
        }
    }
    double perimeter(){
        if ((a + b) > c && (b + c) > a && (c + a) > a && check()){
            return (a + b + c);
        }
        else{
            cout << MIS <<endl;
            return -98;
        }

    }
    ~Triangle();
};
class Circle : public FlatFigure{
    int r;
public:
    Circle(int r){
        this->r = r;
    }
    void show(){
        cout << "  Circle :\n";
        printf("Radius %i\n", r);
        cout << "Square: " << square() << endl;
        cout << "Perimeter: " << perimeter() << endl;
    }
    double square(){
        if (r > 0){
            return (PI * pow(r, 2.0));
        }
        else{
            cout << MIS <<endl;
            return -99;
        }

    }
    double perimeter(){
        if (r > 0){
            return 2 * PI * r;
        }
        else{
            cout << MIS <<endl;
            return -99;
        }

    }
    ~Circle();
};

int main(){
    const int N = 10;
    FlatFigure *arr[N];
    for (int i = 0; i < N; i++){
        arr[i] = new Triangle(i - 1, i + 1, i + 1);
        i++;
        if (i < N) arr[i] = new Circle(i-1);
    }
    for (int i = 0; i < N; i++){
        arr[i]->show();
    }
    for(int i = 0; i < N; i++){
        delete arr[i];
    }
    return 0;
}
