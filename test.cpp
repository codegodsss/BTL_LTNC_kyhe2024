#include <iostream>
using namespace std;

// Hàm đếm số chữ số của một số nguyên
int countDigits(int number) {
    int count = 0;
    if (number == 0) {
        return 1; // Số 0 có 1 chữ số
    }
    while (number > 0) {
        number /= 10;
        count++;
    }
    return count;
}

int main() {
    int N, K;
    cin >> N >> K;

    int sum = 0;
    for (int i = 0; i < N; ++i) {
        int number;
        cin >> number;
        if (countDigits(number) == K) {
            sum += number;
        }
    }

    cout << sum << endl;

    return 0;
}


#include <iostream>
using namespace std;

// Hàm đếm số chữ số của một số nguyên
int countDigits(int number) {
    int count = 0;
    if (number == 0) {
        return 1; // Số 0 có 1 chữ số
    }
    while (number > 0) {
        number /= 10;
        count++;
    }
    return count;
}

int main() {
    int N, K;
    cin >> N >> K;

    int sum = 0;
    for (int i = 0; i < N; ++i) {
        int number;
        cin >> number;
        if (countDigits(number) == K) {
            sum += number;
        }
    }

    cout << sum << endl;

    return 0;
}
