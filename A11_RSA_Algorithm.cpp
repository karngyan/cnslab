/*
Author: @karngyan
*/

#include<bits/stdc++.h>

using namespace std;

int gcd(int a, int b) {
    return __gcd(a, b);
}

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

class Rsa {
    int p = 13, q = 11; // 2 random prime numbers
    int e = 7;
    int d;
    int n;
    int phi;
    int message;
    int encrypted_message;
    int decrypted_message;
    
    void init() {
        int p = this->p;
        int q = this->q;
        int e = this->e;
        int n = p * q, phi = (p - 1) * (q - 1);

        this->n = n;
        this->phi = phi;
        
        // make sure e and phi are prime
        while (e < phi) {
            if (gcd(e, phi) == 1) {
                break;
            } else {
                e++;
            }
        }
    }

public:
    Rsa() {
        this->n = this->p * this->q;
        this->init();
    }

    Rsa(int p, int q, int e) {
        this->p = p;
        this->q = q;
        this->e = e;
        this->init();
    }

    int get_n() { return this->n; }
    int get_p() { return this->p; }
    int get_q() { return this->q; }
    int get_e() { return this->e; }
    int get_d() { return this->d; }
    int get_phi() { return this->phi; }
    int get_message() { return this->message; }
    int get_encrypted_message() { return this->encrypted_message; }
    int get_decrypted_message() { return this->decrypted_message; }

    int encrypt(int message) {
        this->message = message;
        this->encrypted_message = pow(message, this->e, this->n);
        return this->encrypted_message;
    }

    int decrypt() {
        int d;
        // can be done in log n time using fermats theorem of modulo mmi in A3
        // but for demonstartion purpose doing this 
        for (int i = 1 ; i <= phi ; ++i) {
            if ((i * this->e) % phi == 1) {
                this->d = i;
                d = i;
                break;
            }
        }

        this->decrypted_message = pow(this->encrypted_message, d, this->n);
        return this->decrypted_message;
    }
};

signed main() {

    Rsa * rsa = new Rsa();
    int message = 9;

    cout << "---- RSA ----"  << endl << endl;

    cout << "Original Message = "<< message;
    cout << "\n" << "p = " << rsa->get_p();
    cout << "\n" << "q = " << rsa->get_q();
    cout << "\n" << "n = pq = " << rsa->get_n();
    cout << "\n" << "phi = " << rsa->get_phi();
    cout << "\n" << "e = " << rsa->get_e();
    
    int cipher = rsa->encrypt(message);
    int decrypted_message = rsa->decrypt();

    cout << "\n" << "d = " << rsa->get_d();
    cout << "\n" << "Encrypted message = " << cipher;
    cout << "\n" << "Decrypted message = " << decrypted_message;


    /**
    Output:
    ---- RSA ----

    Original Message = 9
    p = 13
    q = 11
    n = pq = 143
    phi = 120
    e = 7
    d = 103
    Encrypted message = 48
    Decrypted message = 9
    **/
    
    return 0;
}