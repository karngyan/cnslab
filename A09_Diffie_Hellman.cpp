/*
Author: @karngyan
*/
#include<bits/stdc++.h>
#include "myutility.h"
// -std=c++14
using namespace std;

/**
Mod = P = 23
base = g = 5
base needs to be a primitive root of Mod
**/
const int P = 23;
const int g = 5;

int pow(int x, int n, int mod) {
    // x^n % mod
    if (n == 0) 
        return 1;
    int half = pow(x, n/2, mod);
    if (n&1) {
        return ((half%mod * half%mod)%mod * x%mod) %mod;
    }
    return (half%mod * half%mod)%mod;
}

signed main() {

    // public
    cout << "P: " << P << endl;
    cout << "g: " << g << endl << endl;

    int a = 4;
    cout << "The private key a for Alice: " << a << endl;

    int A = pow(g, a, P);
    cout << "She sends Bob A (= g^a mod P): " << A << endl << endl;
    
    int b = 3;
    cout << "The private key b for Bob: " << b << endl;

    int B = pow(g, b, P);
    cout << "He sends Alice B (= g^b mod P): " << B << endl << endl;

    cout << "--------------" << endl;
    cout << "Alice Computes" << endl;
    cout << "--------------" << endl;
    
    int s_alice = pow(B, a, P);
    cout << "s_alice = B^a mod P = " << s_alice << endl << endl;

    cout << "--------------" << endl;
    cout << " Bob Computes " << endl;
    cout << "--------------" << endl;
    
    int s_bob = pow(A, b, P);
    cout << "s_bob = A^b mod P = " << s_bob << endl << endl;

    assert(s_alice == s_bob);
    int s = s_alice;
    cout << "Alice and Bob now share a secret, the number: " << s << endl << endl;



    /**
    Output:
    P: 23
    g: 5

    The private key a for Alice: 4
    She sends Bob A (= g^a mod P): 4

    The private key b for Bob: 3
    He sends Alice B (= g^b mod P): 10

    --------------
    Alice Computes
    --------------
    s_alice = B^a mod P = 18

    --------------
    Bob Computes 
    --------------
    s_bob = A^b mod P = 18

    Alice and Bob now share a secret, the number: 18
    **/
    
    return 0;
}