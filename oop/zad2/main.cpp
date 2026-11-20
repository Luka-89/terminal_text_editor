#include <iostream>
#include <string>

void swapRef(int& a, int& b) {
    a = a + b;
    b = a - b;
    a = a - b;
}

void swapPtr(int* a, int* b) {
    *a = *a + *b;
    *b = *a - *b;
    *a = *a - *b;
}
void fun(int n);

void sumaMatrice(int n, int m) {
    // int matrica [m][n]{};
    int** matrica = new int*[m]; 
    for(int i = 0; i < m; i++) {
        matrica[i] = new int[n];
    }


    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            std::cin >> matrica[i][j];
        }
    }

    int s = 0;

    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            s += matrica[i][j];
        }
    }

    std::cout << s;

    for(int i = 0; i < m; i++) {
        delete[] matrica[i];
    }
    delete[] matrica;

}

int main() {
    int m = 2;
    int n = 3;
    sumaMatrice(m, n);

    return 0;
}

void fun(int n) {
    int* niz = new int[n]{};

    int prvi;
    int drugi;
    for(int i = 0; i < n; i++) {
        std::cin >> niz[i];

        if(i == 0) prvi = niz[i];

        if(i == 1)  { 
            if(prvi < niz[i]) {
                drugi = prvi;
                prvi = niz[i];
            }
            else drugi = niz[i];
        }

        if(niz[i] > prvi) {
            drugi = prvi;
            prvi = niz[i];
        }
        else if(niz[i] > drugi) drugi = niz[i];
    }

    std::cout << prvi << " " << drugi;


    delete[] niz;
}
