#include <iostream>
#include <string>

using namespace std;

struct Key {
    long long e;
    long long mod;
};

bool isPrime(long long x) {
    for(long long i = 2; i * i <= x; i++) {
        if(x % i == 0)
            return false;
    }
    return true;
}

string encrypt(string m, Key key) {
    string ans = "";
    for(int i = 0; i < m.size(); i++) {
        long long c = 1;
        long long charcode = m[i];
        for(int j = 0; j < key.e; j++) {
            c = (c * charcode) % key.mod;
        }
        ans.push_back(static_cast<char>(c));
    }
    return ans;
}

int main() {
    Key publicKey, privateKey;
    string message;
    getline(cin, message);
    cout << endl;
    long long p = 3, q = 41;
    long long phi = (p - 1) * (q - 1);
    for(int i = 2; i < phi; i++) {
        if(isPrime(i) && phi % i > 0) {
            publicKey.e = i;
            publicKey.mod = p * q;
            break;
        }
    }
    for(int i = 2;;i++) {
        if((i * publicKey.e) % phi == 1) {
            privateKey.e = i;
            privateKey.mod = p * q;
            break;
        }
    }
    string enc = encrypt(message,publicKey);
    cout << enc << endl;
    string dec = encrypt(enc, privateKey);
    cout << dec << endl;
    return 0;
}