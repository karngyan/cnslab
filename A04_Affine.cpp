
/*
Author: @karngyan
*/

#include<bits/stdc++.h>
#include "myutility.h"
using namespace std;
#define endl '\n'

class Encoder {
    int key1, key2;
    string message;
    string cipher;
public:
    Encoder() {
    }

    Encoder(string message, int key1, int key2) {
        this->message = message;
        this->key1 = key1;
        this->key2 = key2;
    }

    string get_cipher() {
        return this->cipher;
    }

    string get_message() {
        return this->message;
    }

    int get_key_one() {
        return this->key1;
    }

    int get_key_two() {
        return this->key2;
    }

    void encode() {
        int n = this->message.size();
        int key1 = this->key1;
        int key2 = this->key2;
        this->cipher.clear();
        for (int i = 0 ; i < n ; ++i) {
            char x = (((this->message[i] - 'A') * key1)%26 + key2) % 26;
            this->cipher += (x + 'A');
        }
    }
};

class Decoder {
    int key1, key2;
    string message;
    string cipher;
public:
    Decoder() {
    }

    Decoder(string cipher, int key1, int key2) {
        this->cipher = cipher;
        this->key1 = key1;
        if (__gcd(key1, 26) != 1) {
            cout << "\n\nDecoder Error: Key1 must be co-prime with 26. Exiting...\n\n";
            exit(1);
        }
        this->key2 = key2;
    }

    string get_cipher() {
        return this->cipher;
    }

    string get_message() {
        return this->message;
    }

    int get_key_one() {
        return this->key1;
    }

    int get_key_two() {
        return this->key2;
    }

    void decode() {
        int n = this->cipher.size();
        int key1 = this->key1;
        int key1_inverse;
        int key2 = this->key2;

        for (int i = 0 ; i < 26 ; ++i) {
            if ((key1 * i)%26 == 1) {
                key1_inverse = i;
                break;
            }
        }

        this->message.clear();

        for (int i = 0 ; i < n ; ++i) {
            char x = (((this->cipher[i] - 'A') - key2 + 26)%26*key1_inverse%26) % 26;
            this->message += (x + 'A');
        }
    }
};

signed main() {

    string message = "abcd";
    int key1 = 1, key2 = 3;
    _capitalise(message);

    message = _remove_spaces(message);
    _capitalise(message);


    Encoder *  encoder = new  Encoder(message, key1, key2);
    encoder->encode();
    cout << "Encoding Process: \n";
    cout << "M: " <<  encoder->get_message() << endl;
    cout << "K1: " <<  encoder->get_key_one() << " K2: " << encoder->get_key_two() << endl;
    cout << "C: " <<  encoder->get_cipher() << endl;

    Decoder *  decoder = new  Decoder(encoder->get_cipher(), key1, key2);
    decoder->decode();
    cout << "\nDecoding Process: \n";
    cout << "C: " <<  decoder->get_cipher() << endl;
    cout << "K1: " <<  decoder->get_key_one() << " K2: " << decoder->get_key_two() << endl;
    cout << "M: " <<  decoder->get_message() << endl;

    /**
    Output:
    Encoding Process: 
    M: ABCD
    K1: 1 K2: 3
    C: DEFG

    Decoding Process: 
    C: DEFG
    K1: 1 K2: 3
    M: ABCD
    **/
    
    return 0;
}

