/**
 * Author: Raymund Lew
 *
 * Fibonacci series with a command line input for Nth Fibonacci number.
 */
#include <iostream>
#include <string.h>
#include <stdlib.h>

using namespace std;

int fib_iter(int n, int& functionCalls, int& loops) {
    // count function calls
    functionCalls++;

    // fib(0) = 0, fib(1) = 1
    if (n <= 1) {
        return n;
    }
    // fib(2) = 1
    int fib = 1;
    int lastfib = 1;
    for (int i = 3; i <= n; ++i) {
        // count loops
        loops++;
        int temp = fib;
        fib = fib + lastfib;
        lastfib = temp;
    }
    return fib;
}

int fib_rec(int n, int& functionCalls, int& loops) {
    functionCalls++;
    loops++;
    if (n <= 1) {
        return n;
    }
    return fib_rec(n - 1, functionCalls, loops) + fib_rec(n - 2, functionCalls, loops);
}

int main(int argc, char* argv[]) {
    // assume argv[1] is the string
    if (argc < 2) {
        cerr << "number plz thx\n";
        return 1;
    }

    // check if it's a number
    int len = strlen(argv[1]);
    for (int i = 0; i < len; ++i) {
        if (!isdigit(argv[1][i])) {
            cerr << "number plz thx\n";
            return 1;
        }
    }

    int n = atoi(argv[1]);
    int loops = 0;
    int functionCalls = 0;

    // iterative
    cout << "Iterative Fibonacci: ";
    cout << fib_iter(n, functionCalls, loops) << "\n";
    cout << "\tLoops: " << loops << "\n";
    cout << "\tFunction calls: " << functionCalls << "\n";

    loops = 0;
    functionCalls = 0;
    // recursive
    cout << "Recursive Fibonacci: ";
    cout << fib_rec(n, functionCalls, loops) << "\n";
    cout << "\tLoops: " << loops << "\n";
    cout << "\tFunction calls: " << functionCalls << "\n";
    return 0;
}
