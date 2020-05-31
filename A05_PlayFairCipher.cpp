/*
Author: @karngyan
-std=c++14
*/

#include<bits/stdc++.h>
#include "myutility.h"
using namespace std;
#define endl '\n'


class Encoder {
    string key;
    string message;
    string cipher;
    char mat[5][5];

    vector< pair<char, char> > pairs;
    map<char, pair<int, int> > position;

    void make_matrix() {
        set<char> alpha;
        for(int i = 0 ; i < 26 ; ++i) {
            char c = i + 'A';
            if (c == 'J') continue;
            alpha.insert(c);
        }

        string new_key = "";

        int key_size = this->key.size();
        map<char, bool> key_char;
        for (int i = 0 ; i < key_size ; ++i) {
            if (key_char.find(this->key[i]) == key_char.end()) {
                new_key += this->key[i];
                key_char[this->key[i]] = true;
            }
        }

        int k = 0;
        for (int i = 0 ; i < 5 ; ++i) {
            for (int j = 0 ; j < 5 ; ++j) {
                mat[i][j] = '$';
                if (k < new_key.size()) {
                    mat[i][j] = new_key[k];
                    k++;
                    alpha.erase(alpha.find(mat[i][j]));
                }
            }
        }
        for (int i = 0 ; i < 5 ; ++i) {
            for (int j = 0 ; j < 5 ; ++j) {
                if (mat[i][j] == '$') {
                    char c = *alpha.begin();
                    alpha.erase(alpha.begin());
                    mat[i][j] = c;
                }

                position[mat[i][j]] = make_pair(i, j);

            }
        }
    }
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
        string p = this->message;
        this->make_matrix();
        int n = p.size();
        map<char, pair<int, int> > position = this->position;
        vector< pair<char, char> > pairs;
        int i = 0;

        string new_p = "";
        for (int i = 0 ; i < n ; ++i) {
            if (p.size() == 0) {
                new_p += p[i];
            } else {
                char c = new_p[new_p.size() - 1];
                if (p[i] == c) {
                    new_p += 'X';
                }

                new_p += p[i];
            }
        }

        if (new_p.size()&1) new_p += 'Z';
        p = new_p;
        n = p.size();
        while(i+1 < n) {
            char a = p[i];
            char b = p[i+1];
            i+=2;
            pairs.push_back(make_pair(a, b));
        }

        this->pairs = pairs;
        this->cipher.clear();

        for (int i = 0 ; i < pairs.size() ; ++i) {
            char a = pairs[i].first;
            char b = pairs[i].second;

            pair<int, int> aa = position[a];
            pair<int, int> bb = position[b];

            // cout << a << b << " " << aa.first<<"," << aa.second << " " << bb.first << "," << bb.second << endl;
            if (aa.first == bb.first) {
                this->cipher += mat[aa.first][(aa.second+1)%5];
                this->cipher +=  mat[bb.first][(bb.second+1)%5];
            } else if (aa.second == bb.second) {
                this->cipher += mat[(aa.first+1)%5][aa.second];
                this->cipher +=  mat[(bb.first+1)%5][bb.second];
            } else {
                this->cipher += mat[aa.first][bb.second];
                this->cipher += mat[bb.first][aa.second];
            }
            // cout << this->cipher << endl;
            // this->cipher += ' ' ;
        }

    }

    void show_matrix() {
        this->make_matrix();
        cout << "\n\n";
        for (int i = 0 ; i < 5 ; ++i) {
            for (int j = 0 ; j < 5 ; ++j) {
                cout << this->mat[i][j] << " \n"[j == 4];
            }
        }
        cout << "\n";
    }

    void show_pairs() {
        cout << "\n";
        for (int i = 0 ; i < pairs.size() ; ++i) {
            char a = (this->pairs)[i].first;
            char b = (this->pairs)[i].second;
            cout << a << b << " ";
        }
        cout << endl;
    }
};

class Decoder {
    string message;
    string cipher;
    string key;
    char mat[5][5];

    vector< pair<char, char> > pairs;
    map<char, pair<int, int> > position;

    void remove_char(string &s, char c) {
        string ans = "";
        for(auto it : s) {
            if (it == c) {
                continue;
            }
            ans += it;
        }
        s = ans;
    }

    void make_matrix() {
        set<char> alpha;
        for(int i = 0 ; i < 26 ; ++i) {
            char c = i + 'A';
            if (c == 'J') continue;
            alpha.insert(c);
        }

        string new_key = "";

        int key_size = this->key.size();
        map<char, bool> key_char;
        for (int i = 0 ; i < key_size ; ++i) {
            if (key_char.find(this->key[i]) == key_char.end()) {
                new_key += this->key[i];
                key_char[this->key[i]] = true;
            }
        }

        int k = 0;
        for (int i = 0 ; i < 5 ; ++i) {
            for (int j = 0 ; j < 5 ; ++j) {
                mat[i][j] = '$';
                if (k < new_key.size()) {
                    mat[i][j] = new_key[k];
                    k++;
                    alpha.erase(alpha.find(mat[i][j]));
                }
            }
        }
        for (int i = 0 ; i < 5 ; ++i) {
            for (int j = 0 ; j < 5 ; ++j) {
                if (mat[i][j] == '$') {
                    char c = *alpha.begin();
                    alpha.erase(alpha.begin());
                    mat[i][j] = c;
                }

                position[mat[i][j]] = make_pair(i, j);

            }
        }
    }

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
        string c = this->cipher;
        this->make_matrix();
        int n = c.size();
        map<char, pair<int, int> > position = this->position;
        for (int i = 0 ; i < n ; i += 2) {
            char a = c[i];
            char b = c[i+1];

            pair<int, int> aa = position[a];
            pair<int, int> bb = position[b];

            if (aa.first == bb.first) {
                this->message += mat[aa.first][(aa.second-1 + 5)%5];
                this->message +=  mat[bb.first][(bb.second-1 + 5)%5];
            } else if (aa.second == bb.second) {
                this->message += mat[(aa.first - 1 + 5)%5][aa.second];
                this->message +=  mat[(bb.first - 1 + 5)%5][bb.second];
            } else {
                this->message += mat[aa.first][bb.second];
                this->message += mat[bb.first][aa.second];
            }
        }

        this->remove_char(this->message, 'X');
        this->remove_char(this->message, 'Z');
    }

};

signed main() {

    string message = "balle balle balle balle";
    string key = "shaava shaava";
    _capitalise(message);
    _capitalise(key);

    message = _remove_spaces(message);
    key = _remove_spaces(key);

    if (_check_specific_char(message, 'X') 
            or _check_specific_char(message, 'Z')) {
        cerr << "No X/Z allowed.";
        exit(1);
    };


    Encoder *  encoder = new  Encoder(message, key);

    cout << "Encoding Process: \n";

    cout << "M: " <<  encoder->get_message() << endl;
    cout << "K: " << encoder->get_key() << endl;

    encoder->encode();

    cout << "\nMatrix: " ;encoder->show_matrix(); cout <<  endl;
    cout << "Pairs: ";encoder->show_pairs(); cout << endl;
    string cipher = encoder->get_cipher();
    cout << "Cipher: \n"; 
    for (int i = 0 ; i < cipher.size() ; ++i) {
        cout << cipher[i];
        if (i%2 == 1) 
            cout << " ";
    } cout << endl;


    Decoder *  decoder = new  Decoder(encoder->get_cipher(), key);
    decoder->decode();
    cout << "\nDecoding Process: \n";
    cout << "Message: " <<  decoder->get_message() << endl;

    /**
    Output:
    Encoding Process: 
    M: BALLEBALLEBALLEBALLE
    K: SHAAVASHAAVA

    Matrix: 

    S H A V B
    C D E F G
    I K L M N
    O P Q R T
    U W X Y Z


    Pairs: 
    BA LX LE BA LX LE BA LX LE BA LX LE 

    Cipher: 
    SV QA QL SV QA QL SV QA QL SV QA QL 

    Decoding Process: 
    Message: BALLEBALLEBALLEBALLE
    **/

    return 0;
}

