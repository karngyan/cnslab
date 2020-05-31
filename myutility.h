#include<bits/stdc++.h>
using namespace std;

template<typename _Ty1, typename _Ty2>
std::ostream& operator<<(std::ostream& _os, const std::pair<_Ty1, _Ty2>& _p) {
    _os << _p.first << ' ' << _p.second;
    return _os;
}

void _capitalise(string &s) {
    for (auto &it: s) {
        if (it >= 'a' and it <= 'z') {
            it = it - 'a' + 'A';
        }
    }
}


// legacy
// now it removes anything thats not a
// capital letter
string _remove_spaces(string s) {

    string ans = "";
    for (auto it: s) {
        if (it >= 'A' and it <= 'Z') 
            ans += it;
    }
    return ans;
}

bool _check_specific_char(string &s, char c) {
    for (auto it : s) {
        if (it == c)
            return true;
    }
    return false;
}