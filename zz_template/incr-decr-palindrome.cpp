#include <string>
using std::string;

void decrementPalindrome(string& a) {
    if(a.length() == 1) {
        a[0]--;
        return;
    }
    int L = (int) (a.length()-1)/2, R = (int) a.length()/2;
    while(L >= 0) {
        if(a[L] == '0') {
            a[L] = a[R] = '9';
            L--; R++;
        }else {
            if(L == 0 && a[L] == '1') {
                a[L] = '9';
                a.pop_back();
                return;
            }
            a[L] = a[R] = (char) (a[L] - 1);
            return;
        }
    }
}
void incrementPalindrome(string& a) {
    int L = (int) (a.length()-1)/2, R = (int) a.length()/2;
    while(L >= 0) {
        if(a[L] == '9') {
            a[L] = a[R] = '0';
            L--; R++;
        }else {
            a[L] = a[R] = (char) (a[L] + 1);
            return;
        }
    }
    a[0] = '1';
    a += '1';
}