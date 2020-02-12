#include<bits/stdc++.h>
#include "myutility.h"
using namespace std;

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
            char x = ((this->message[i] - 'a') + key) % 26;
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
            char x = ((this->cipher[i] - 'a') - key + 26) % 26;
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
    return 0;
}