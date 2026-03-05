#include "NonLinear.h"
#include <iostream>

int main()
{
    NonLinear nonLinear;

    nonLinear.loadCSV("players.csv");

    nonLinear.insert("Kim", 500);
    nonLinear.insert("Lee", 200);
    nonLinear.insert("Park", 350);

    std::cout << "Find Lee\n";
    nonLinear.find("Lee");

    std::cout << "\nTop 3\n";
    nonLinear.top(3);

    std::cout << "\nDelete Lee\n";
    nonLinear.deleteNode("Lee");

    nonLinear.find("Lee");

    return 0;
}