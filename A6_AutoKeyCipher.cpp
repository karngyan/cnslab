/*
Author: @karngyan
*/

#include<bits/stdc++.h>
#include "myutility.h"
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
            char x = ((this->message[i] - 'A') + key) % 26;
            key = this->message[i] - 'A';
            this->cipher += (x + 'A');
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

        for (int i = 0 ; i < n ; ++i) {
            char x = ((this->cipher[i] - 'A') - key + 26) % 26;
            key = x;
            this->message += (x + 'A');
        }
    }
};

signed main() {

    string message = "abcd";
    int key = 1;

    _capitalise(message);
    message = _remove_spaces(message);

    Encoder * encoder = new  Encoder(message, key);
    encoder->encode();
    cout << "Encoding Process: \n";
    cout << "M: " <<  encoder->get_message() << endl;
    cout << "K: " <<  encoder->get_key() << endl;
    cout << "C: " <<  encoder->get_cipher() << endl;

    Decoder *  decoder = new  Decoder(encoder->get_cipher(), key);
    decoder->decode();
    cout << "\nDecoding Process: \n";
    cout << "C: " <<  decoder->get_cipher() << endl;
    cout << "K: " <<  decoder->get_key() << endl;
    cout << "M: " <<  decoder->get_message() << endl;

    /**
    Output:
    Encoding Process: 
    M: ABCD
    K: 1
    C: BBDF

    Decoding Process: 
    C: BBDF
    K: 1
    M: ABCD
    **/

    return 0;
}

