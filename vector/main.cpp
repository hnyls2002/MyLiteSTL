#include <iostream>
#include "vector.hpp"

using namespace std;

int main() {
    sjtu::vector<int> a, b;
    for (int i = 0; i < 1e5; ++i)a.push_back(i);
    for (int i = 1; i < 1e5; ++i)a.pop_back();
    cout << a.size() << endl;
    for (int i = 1; i <= 1e6; ++i)
        b = a;
    return 0;
}