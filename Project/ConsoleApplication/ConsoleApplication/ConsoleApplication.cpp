#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace bg
{
    namespace burgas
    {
        struct targovska {};

        namespace mr
        {
            struct pgkpi {};
        }
    }
}

double* foo()
{
    double* arr = new double(10);

    // delete[] arr;

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
    vector<USER> users
    {
        {1, "user1", "user@gmail.com", 16},
        {1, "user1", "user@gmail.com", 17},
        {1, "user1", "user@gmail.com", 18},
        {1, "user1", "user@gmail.com", 19}
    };
}
