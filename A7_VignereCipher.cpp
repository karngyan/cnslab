/*
Author: @karngyan
*/

#include<bits/stdc++.h>
#include "myutility.h"

using namespace std;
#define endl '\n'

class Encoder {
    string key;
    string message;
    string cipher;
public:
    Encoder() {
    }

    Encoder(string message, string key) {
        this->message = message;
        this->key = key;
    }

    string get_cipher() {
        return this->cipher;
    }

    string get_message() {
        return this->message;
    }

    string get_key() {
        return this->key;
    }

    void encode() {
        int n = this->message.size();
        string key = this->key;
        this->cipher.clear();
        int j = 0;
        int key_size = key.size();

        for (int i = 0 ; i < n ; ++i) {
            char x = ((this->message[i] - 'A') + (key[j] - 'A')) % 26;
            this->cipher += (x + 'A');
            j++;
            j%=key_size;
        }
    }
};

class Decoder {
    string key;
    string message;
    string cipher;
public:
    Decoder() {
    }

    Decoder(string cipher, string key) {
        this->cipher = cipher;
        this->key = key;
    }

    string get_cipher() {
        return this->cipher;
    }

    string get_message() {
        return this->message;
    }

    string get_key() {
        return this->key;
    }

    void decode() {
        int n = this->cipher.size();
        string key = this->key;

        this->message.clear();
        int j = 0;
        int key_size = key.size();

        for (int i = 0 ; i < n ; ++i) {
            char x = ((this->cipher[i] - 'A') - (key[j] - 'A') + 26) % 26;
            this->message += (x + 'A');
            j++;
            j%=key_size;
        }
    }
};

signed main() {

    string message = "bitmesra";
    string key = "ab";

    _capitalise(message);
    _capitalise(key);

    message = _remove_spaces(message);
    key = _remove_spaces(key);

    Encoder *  encoder = new  Encoder(message, key);
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
    M: BITMESRA
    K: AB
    C: BJTNETRB

    Decoding Process: 
    C: BJTNETRB
    K: AB
    M: BITMESRA
    **/



    return 0;
}

