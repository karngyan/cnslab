#include <bits/stdc++.h>
using namespace std;

int multiplicative_inverse(int a, int m) { 
	// ax + my = 1
	int m0 = m;
	int y = 0, x = 1; 

	if (m == 1) 
	    return 0;

	while (a > 1) { 
		int q = a / m; 
		int t = m;

		m = a % m, a = t; 
		t = y; 
		
        y = x - q * y; 
		x = t; 
	} 
	
	if (x < 0) 
		x += m0; 

	return x; 
} 

// signed main() 
// { 
// 	int a = 3, m = 11;
	
// 	if (__gcd(a, m) != 1) {
// 		cout << "Multiplicative Inverse doesn't exist\n\n";
// 		return 0;
// 	}

// 	int mi = multiplicative_inverse(a, m);
// 	cout << "Multiplicative Inverse: " << mi << endl;
	
	
// 	return 0; 
// } 
