#include <iostream>
#include <string>
#include <vector>

using namespace std;

double* foo()
{
    double* arr = new double(10);

    delete[] arr;

    return arr;
}

struct USER
{
    size_t id;
    string name;
    string email;
    uint8_t age;
};

int main()
{
    //
}