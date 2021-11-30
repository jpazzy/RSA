#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

//Returns true if valid pair.
bool checkIfValid(int e, int n);

bool checkIfPrime(int num);

bool getPQ(int source, int &p, int &q);

int getPhi(int p, int q);

int getDecryptionKey(int e, int phi);

int getMessage(int encryptedMessage, int n, int d);

int decrypt(int e, int n, int message, int &p, int &q, int &phi, int &d);

void printDecrypt(int decodedMessage);

int main() {
    vector<int> encryptedMessages;
    vector<int> decryptedMessages;
    int p, q, phi, d;
    int e, n, m;
    cin >> e >> n;
    //Number of messages
    cin >> m;
    for (int i = 0; i < m; i++) {
        int temp;
        cin >> temp;
        encryptedMessages.push_back(temp);
    }
    if (!checkIfValid(e, n)) {
        cout << "Public key not valid!";
    }
    else {
    decryptedMessages.reserve(m);
    for (int i = 0; i < m; i++) {
        decryptedMessages.push_back(decrypt(e, n, encryptedMessages[i], p, q, phi, d));
    }

    //check if its valid

        //Now output the messages.

        cout << p << " " << q << " " << phi << " " << d << "\n";
        for (int i = 0; i < m; i++) {
            cout << decryptedMessages[i];
            if (i != 14) {
                cout << " ";
            }
        }
        cout << "\n";
        for (int i = 0; i < m; i++) {
            printDecrypt(decryptedMessages[i]);
        }
        cout << "\n";
    }
    return 0;
}


bool getPQ(int source, int &p, int &q) {
    bool isDone = false;
    int i = 2;
    while (!isDone && i < source) {

        //True if it finds a factor
        if (source % i == 0) {
            p = i;
            isDone = true;
            //Now get the corresponding q;
            q = source / p;
        }
        i++;
    }
    if(i>= source){
        return false;
    }
    return true;
}

int getPhi(int p, int q) {
    return ((p - 1) * (q - 1));
}

int getDecryptionKey(int e, int phi) {
    // de mod phi =1
    bool isDone = false;
    int decryptionKey = 0;
    int i = 2;
    while (!isDone) {

        //True if it finds a factor
        if ((e * i) % phi == 1) {
            decryptionKey = i;
            isDone = true;
        }
        i++;
    }
    return decryptionKey;

}

int getMessage(int encryptedMessage, int n, int d) {
    int temp = 1;
    while (d > 1) {

        if (d % 2 == 0) {
            encryptedMessage *= encryptedMessage;
            encryptedMessage %= n;
            d /= 2;
        } else {
            temp *= encryptedMessage;
            encryptedMessage *= encryptedMessage;
            encryptedMessage %= n;
            d -= 1;
            d /= 2;
        }
    }
    int product = encryptedMessage * temp;
    return (product % n);
}

int decrypt(int e, int n, int message, int &p, int &q, int &phi, int &d) {
    getPQ(n, p, q);
    phi = getPhi(p, q);
    d = getDecryptionKey(e, phi);
    message = getMessage(message, n, d);
    return message;
}

void printDecrypt(int decodedMessage) {
    const int x = 3;

    //Checks to see if its a letter
    if (decodedMessage < (x + 26)) {
        int temp = decodedMessage + 62;
        cout << char(temp);
    } else {
        switch (decodedMessage) {
            case (x + 26):
                cout << " ";
                break;
            case (x + 27):
                cout << "\"";
                break;
            case (x + 28):
                cout << ".";
                break;
            case (x + 29):
                cout << ",";
                break;
            case (x + 30):
                cout << "'";
                break;
            default:
                break;

        }
    }
}

bool checkIfPrime(int num) {
    bool isDone = false;
    int i = 2;
    while (i < num) {

        //If it finds a factor,end and return false;
        if (num % i == 0) {

            return false;
        }
        i++;
    }
    return true;
}

bool checkIfValid(int e, int n) {
    int p, q;
    getPQ(n, p, q);
    //p!=q
    if(p==0||p==1||q==0||q==1||e==0||e==1||n==1||n==0)
        return false;
    if (p == q)
        return false;
    //check to see if p and q are prime or not.
    if (!checkIfPrime(p) || !checkIfPrime(q))
        return false;
    //make sure they are relatively prime
    int phi = getPhi(p, q);
    if(__gcd(e,phi)!=1)
        return false;

    return true;
}