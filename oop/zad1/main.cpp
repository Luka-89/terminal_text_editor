#include <iostream>
#include <string>

int main() {
    int n;
    std::cin >> n;
    int niz[n];

    for(int i = 0; i < n; i++) {
        std::cin >> niz[i];
    }



    for(int i = n - 1; i >= 0; i--) {
        std::cout << niz[i] << " ";
    }





    return 0;
}   