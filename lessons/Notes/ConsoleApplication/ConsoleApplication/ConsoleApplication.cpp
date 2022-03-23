#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

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

    sort(users.begin(), users.end(),
        [](USER u1, USER u2) {return u1.age > u2.age; });

    for (auto user : users)
    {
        cout << user.id << " " << user.name << " " << user.age << endl;
    }

    vector <int> numbers = { 4, 6, 1, 8, 4 };

    auto it = find_if(numbers.begin(), numbers.end(),
        [](int num) {return num == 1; });

    if (it != numbers.end())
    {
        cout << "The element is: " << *it << endl;
    }

    else
    {
        cout << "The element was not found" << endl;
    }

    /*
    sort(numbers.begin(), numbers.end(),
        [](int a, int b) {return a > b; });

    for (auto num : numbers)
    {

    }
    */

    auto sum = [](int a, int b) { return a + b; };
    int c = sum(5, 6);
    cout << c;
}
