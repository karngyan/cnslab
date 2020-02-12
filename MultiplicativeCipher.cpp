/*
Author: @karngyan
*/

#include<bits/stdc++.h>
#include "A3_MulModInverse.cpp"
using namespace std;
#define endl '\n'

class Encoder {
    int key;
    string message;
    string cipher;
public:
    Encoder() {
    }

    Encoder(string message, int key) {
        this->message = message;
        this->key = key;
    }

    string get_cipher() {
        return this->cipher;
    }

    string get_message() {
        return this->message;
    }

    int get_key() {
        return this->key;
    }

    void encode() {
        int n = this->message.size();
        int key = this->key;
        this->cipher.clear();
        for (int i = 0 ; i < n ; ++i) {
            char x = ((this->message[i] - 'a')%26 * key % 26) % 26;

            this->cipher += (x + 'a');
        }
    }
};

class Decoder {
    int key;
    string message;
    string cipher;
public:
    Decoder() {
    }

    Decoder(string cipher, int key) {
        this->cipher = cipher;
        if (__gcd(key, 26) != 1) {
            cout << "\n\nDecoder Error: Key must be co-prime with 26. Exiting...\n\n";
            exit(1);
        }
        this->key = key;
    }

    string get_cipher() {
        return this->cipher;
    }

    string get_message() {
        return this->message;
    }

    int get_key() {
        return this->key;
    }

    void decode() {
        int n = this->cipher.size();
        int key = this->key;

        this->message.clear();
        int key_inverse = multiplicative_inverse(key, 26);

        for (int i = 0 ; i < n ; ++i) {
            char x = ((this->cipher[i] - 'a')%26 * key_inverse%26) % 26;
            this->message += (x + 'a');
        }
    }
};

signed main() {

    // freopen("in", "r", stdin);
    // string message;
    // cin >> message;
    // int key;
    // cin >> key;

    string message = "abcd";
    int key = 7;

    Encoder * encoder = new Encoder(message, key);
    encoder->encode();
    cout << "Encoding Process: \n";
    cout << "M: " << encoder->get_message() << endl;
    cout << "K: " << encoder->get_key() << endl;
    cout << "C: " << encoder->get_cipher() << endl;

    Decoder * decoder = new Decoder(encoder->get_cipher(), key);
    decoder->decode();
    cout << "\nDecoding Process: \n";
    cout << "C: " << decoder->get_cipher() << endl;
    cout << "K: " << decoder->get_key() << endl;
    cout << "M: " << decoder->get_message() << endl;



    return 0;
}

