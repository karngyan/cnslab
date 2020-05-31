/*
Author: @karngyan
*/
#include<bits/stdc++.h>
#include "myutility.h"
// -std=c++14
// Columnar Transposition
using namespace std;

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
        string message = this->message;
        this->cipher.clear();

        // create column
        vector<vector<char>> columns;
        int key_size = key.size();
        vector<char> key_order(key_size);
        string _s = key;
        sort(_s.begin(), _s.end());
        vector<bool> done(key_size, false);
        for (int i = 0 ; i < key_size; ++i) {
            for (int j = 0 ; j < key_size; ++j) {
                if (_s[i] == key[j] and !done[j]) {
                    done[j] = true;
                    key_order[j] = i+1 + '0';
                    break;
                }
            }
        }
        
        columns.push_back(key_order);

        vector<char> tmp;
        srand(time(NULL));
        for (int i = 0 ; i < n ; ++i) {
            tmp.push_back(message[i]);
            if (tmp.size() == key_size) {
                columns.push_back(tmp);
                tmp.clear();
            }
        }
        
        if (tmp.size() > 0) {
            for (int i = tmp.size(); i < key_size ; ++i) {
                char random_char = rand()%26 + 'A';
                tmp.push_back(random_char);
            }
            columns.push_back(tmp);
        }

        //show_column
        cout << "\nColumn: \n";
        for(auto row: columns) {
            for (char c : row) {
                cout << c << " ";
            }
            cout << "\n";
        }

        //generate cipher
        this->cipher.clear();
        map<int, int> location;
        for (int i = 0 ; i < key_size ; ++i) {
            location[columns[0][i] - '0'] = i;
        }

        for (auto it : location) {
            int column = it.second;
            for (int i = 1; i < columns.size() ; ++i) {
                this->cipher += columns[i][column];
            }
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
        int n = this->message.size();
        string key = this->key;
        string cipher = this->cipher;
        int key_size = key.size();

        // create column
        vector<vector<char>> columns((cipher.size() / key_size) + 1, vector<char>(key_size));
        vector<char> key_order(key_size);
        string _s = key;
        sort(_s.begin(), _s.end());
        vector<bool> done(key_size, false);
        for (int i = 0 ; i < key_size; ++i) {
            for (int j = 0 ; j < key_size; ++j) {
                if (_s[i] == key[j] and !done[j]) {
                    done[j] = true;
                    key_order[j] = i+1 + '0';
                    break;
                }
            }
        }
        
        columns[0] = key_order;

        map<int, int> location;
        for (int i = 0 ; i < key_size ; ++i) {
            location[columns[0][i] - '0'] = i;
        }

        int _c_iter = 0;
        for (auto it : location) {
            int column = it.second;
            for (int i = 1; i < columns.size() ; ++i) {
                columns[i][column] = this->cipher[_c_iter++];
            }
        }

        //show_column
        cout << "\nColumn: \n";
        for(auto row: columns) {
            for (char c : row) {
                cout << c << " ";
            }
            cout << "\n";
        }
        
        //generate message
        this->message.clear();
        for (int i = 1 ; i < columns.size() ; ++i) {\
            for (auto it : columns[i]) {
                this->message += it;
            }
        }

    }
};

signed main() {

    string message = "WE ARE DISCOVERED. FLEE AT ONCE.";
    string key = "ZEBRAS";

    _capitalise(message);
    _capitalise(key);

    message = _remove_spaces(message);
    key = _remove_spaces(key);

    Encoder *  encoder = new  Encoder(message, key);
    cout << "Encoding Process: \n";
    encoder->encode();
    cout << "M: " <<  encoder->get_message() << endl;
    cout << "K: " <<  encoder->get_key() << endl;
    cout << "C: "; string cipher = encoder->get_cipher();
    for (int i = 0 ; i < cipher.size() ; ++i) {
        cout << cipher[i];
        if ((i+1)%(cipher.size() / key.size()) == 0) {
            cout << " ";
        }
    }
    cout << endl;

    Decoder *  decoder = new  Decoder(encoder->get_cipher(), key);
    cout << "\nDecoding Process: \n";
    decoder->decode();
    cout << "C: " <<  decoder->get_cipher() << endl;
    cout << "K: " <<  decoder->get_key() << endl;
    cout << "M: " <<  decoder->get_message() << endl;


    /**
    Output:
    Encoding Process: 

    Column: 
    6 3 2 4 1 5 
    W E A R E D 
    I S C O V E 
    R E D F L E 
    E A T O N C 
    E K I R V M 
    M: WEAREDISCOVEREDFLEEATONCE
    K: ZEBRAS
    C: EVLNV ACDTI ESEAK ROFOR DEECM WIREE 

    Decoding Process: 

    Column: 
    6 3 2 4 1 5 
    W E A R E D 
    I S C O V E 
    R E D F L E 
    E A T O N C 
    E K I R V M 
    C: EVLNVACDTIESEAKROFORDEECMWIREE
    K: ZEBRAS
    M: WEAREDISCOVEREDFLEEATONCEKIRVM
    **/


    return 0;
}