// shte preimenuvam file-a na namespaces

#include <iostream>

using namespace std;

// We use a namespace insetad of a structure because we can have a structure in a namespace

namespace first
{
    namespace second // we can nest namespaces (archiachal structure)
    {
        int val = 40;
    }

    int val = 10;
}

int val = 20; // global var

int main()
{
    // extern int val; to access external items
    int val = 30; // local var

    cout << val << endl; // prints 30 (looks at scope)

    // To print out 10
    cout << first::val << endl; // "::" - scope resolution operator

    // To print out 40
    cout << first::second::val << endl;
}


/*

Druga chast ot uroka koito posle da otdelq?

#include <iostream>
#include "Header1.h

int main ()
{
    std::cout << Countries::Bulgaria.Captial << " 
 << Countries::Bulgaria.Population << std::endl;
    std::cout << Countries::Areas::Burgas.Name;
 }

*/