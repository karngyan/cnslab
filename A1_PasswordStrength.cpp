/*
Author: @karngyan
*/

#include<bits/stdc++.h>

using namespace std;

void check_password_strength(string &password) {

    int n = password.size();

    bool has_lower = false, has_upper = false;
    bool has_digit = false, special_char = false;

    string normal_characters = "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890 ";

    for (char ch: password) {
        has_lower |= islower(ch);
        has_upper |= isupper(ch);
        has_digit |= isdigit(ch);

        size_t special = password.find_first_not_of(normal_characters);

        special_char = (special != string::npos);
    }

    cout << "Strength of password: ";

    if (has_lower and has_upper and has_digit and special_char and (n >= 8))
        cout << "Strong";
    else if ((has_lower or has_upper) and special_char and (n >= 6))
        cout << "Moderate";
    else
        cout << "Weak";
    cout << endl;
}

signed main() {

    string password = "AbcdfGdjh23@";
    
    check_password_strength(password);
    /**
    Output:
    Strength of password: Strong
    **/
    return 0;
}