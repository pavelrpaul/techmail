#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

using namespace std;

class Phone{
private:
    char *firstName;
    char *lastName;
    char *fatherName;
    char *adress;
    char *number;
    int inCalls;
    int outCalls;
public:

    Phone(char *firstN, char *lastN, char *fatherN, char *adr, char *num, int innerC, int outerC);
    Phone *copy(Phone *b);
    Phone(Phone *a);
    void set_firstName(char *temp);
    char *get_firstName();

    void set_lastName(char *temp);
    char *get_lastName();

    void set_fatherName(char *temp);
    char *get_fatherName();

    void set_adress(char *temp);
    char *get_adress();

    void set_number(char *temp);
    char *get_number();

    void set_inCalls(int temp);
    int get_inCalls();

    void set_outCalls(int temp);
    int get_outCalls();

    void method1(int limit); //get info about users which has innerCalls up the limit
    void method2(); //get info about users which has outCalls
    void show();
    ~Phone();
};


Phone::Phone(char *firstN, char *lastN, char *fatherN, char *adr, char *num, int innerC, int outerC){
    set_firstName(firstN);
    set_lastName(lastN);
    set_fatherName(fatherN);
    set_adress(adr);
    set_number(num);
    set_inCalls(innerC);
    set_outCalls(outerC);
}

Phone::~Phone(){
    free(firstName);
    free(lastName);
    free(fatherName);
    free(adress);
    free(number);
}
void Phone::set_firstName(char *temp){
    firstName = (char*)malloc(strlen(temp) * sizeof(char));
    strcpy(firstName, temp);
}
void Phone::set_lastName(char *temp){
    lastName = (char*)malloc(strlen(temp) * sizeof(char));
    strcpy(lastName, temp);
}
void Phone::set_fatherName(char *temp){
    fatherName = (char*)malloc(strlen(temp) * sizeof(char));
    strcpy(fatherName, temp);
}
void Phone::set_adress(char *temp){
    adress = (char*)malloc(strlen(temp) * sizeof(char));
    strcpy(adress, temp);
}
void Phone::set_number(char *temp){
    number = (char*)malloc(strlen(temp) * sizeof(char));
    strcpy(number, temp);
}
void Phone::set_inCalls(int temp){
    inCalls = temp;
}
void Phone::set_outCalls(int temp){
    outCalls = temp;
}

char *Phone::get_firstName(){
    return firstName;
}
char *Phone::get_lastName(){
    return lastName;
}
char *Phone::get_fatherName(){
    return fatherName;
}
char *Phone::get_adress(){
    return adress;
}
char *Phone::get_number(){
    return number;
}
int Phone::get_inCalls(){
    return inCalls;
}
int Phone::get_outCalls(){
    return outCalls;
}
Phone::Phone(Phone *a){
    this->set_firstName(a->get_firstName());
    this->set_lastName(a->get_lastName());
    this->set_fatherName(a->get_fatherName());
    this->set_adress(a->get_adress());
    this->set_number(a->get_number());
    this->inCalls = a->get_inCalls();
    this->outCalls = a->get_outCalls();
}

Phone *Phone::copy(Phone *a)
{
    set_firstName(a->get_firstName());
    set_lastName(a->get_lastName());
    set_fatherName(a->get_fatherName());
    set_adress(a->get_adress());
    set_number(a->get_number());

    this->inCalls = a->inCalls;
    this->outCalls = a->get_outCalls();

    return this;
}


void Phone::method1(int limit){
    if (get_inCalls() >= limit){
        printf("First/Last name: %s %s %s\nAdress: %s\nNumber: %s\n",
            get_firstName(), get_lastName(), get_fatherName(), get_adress(), get_number());
    }
}
void Phone::method2(){
    if (get_outCalls() > 0){
        printf("First/Last name: %s %s %s\nAdress: %s\nNumber: %s\n",
            get_firstName(), get_lastName(), get_fatherName(), get_adress(), get_number());
    }
}

void Phone::show(){
    printf("First/Last name: %s %s %s\nAdress: %s\nNumber: %s\nInCalls: %i OutCalls: %i\n",
        get_firstName(), get_lastName(), get_fatherName(), get_adress(), get_number(), get_inCalls(), get_outCalls());
}

int main(){
    int N = 4;
    Phone **obj;
    obj = new Phone*[N];
    obj[0] = new Phone("smith", "james", "pavlovich", "China", "999-432-112", 400, 30);
    obj[1] = new Phone("deen", "jake", "igorivich", "LA", "333-432-112", 100, 0);
    obj[2] = new Phone("pavlov", "petr", "sergeevish", "NY", "555-234-155", 300, 40);
    obj[3] = new Phone("smirnov", "bob", "alexandravich", "Iran", "888-342-543", 250, 60);

    for (int i = 0; i < N; i++){
        obj[i]->show();
    }
    cout << "===============first task===============\n" << endl;
    for (int i = 0; i < N; i++){
        obj[i]->method1(251);
    }
    cout << "===============second task===============\n" << endl;
    for (int i = 0; i < N; i++){
        obj[i]->method2();
    }
    cout << "===============third task===============\n" << endl;
    for (int i = 0; i < N -1; i++){
       for (int j = 0; j < N - 1 - i; j++){
            if (strcmp(obj[j]->get_firstName(), obj[j + 1]->get_firstName()) >= 0){
                Phone *abc = new Phone(obj[j]);
                obj[j]->copy(obj[j+1]);
                obj[j + 1]->copy(abc);
		delete abc;
            }
        }
    }
    for (int i = 0; i < N; i++){
        obj[i]->show();
    }
    for (size_t i = 0; i < N; ++i) {
            delete obj[i];
        }
    delete obj;
    return 0;
}
