#include<bits/stdc++.h>
using namespace std;

template<typename _Ty1, typename _Ty2>
std::ostream& operator<<(std::ostream& _os, const std::pair<_Ty1, _Ty2>& _p) {
    _os << _p.first << ' ' << _p.second;
    return _os;
}

string _remove_spaces(string s) {
    string ans = "";
    for (auto it: s) {
        if (it != ' ') ans += it;
    }
    return ans;
}

void _check_lower_case(string &s) {
    for (auto it : s) {
        if (it == ' ') {
            s.erase(it);
            continue;
        }
        if (it < 'a' or it > 'z') {
            cout << "Program only supports lower case characters currently.";
            exit(1);
        }
    }
}

bool _check_specific_char(string &s, char c) {
    for (auto it : s) {
        if (it == c)
            return true;
    }
    return false;
}