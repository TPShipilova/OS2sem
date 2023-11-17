#include "sort.hpp"
#include "threads.hpp"
#include <iostream>
#include <chrono>

using namespace std::chrono;
using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        perror("Using: ./lab2_exe number_of_threads");
        exit(-1);
    }
    int n;
    cout << "Enter the quantity of elements: ";
    cin >> n;
    int mas[n];
    cout << "Fill array: ";
    for (int i = 0; i < n; ++i) {
        std::cin >> mas[i];
    }
    int threads(atoi(argv[1]));
    auto start = std::chrono::high_resolution_clock::now();
    sort(mas, n, threads);
    auto end = std::chrono::high_resolution_clock::now();

    duration<double> sec = end - start;
    cout << "Result: ";
    cout << sec.count() << " s" << std::endl;

    return 0;
}