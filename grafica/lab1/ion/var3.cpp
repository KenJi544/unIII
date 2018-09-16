#include <iostream> 
#include <cmath>

const float PI = 3.1415926;

using namespace std;

float my_pow(float x, int n) {
    if (n < 0) {
        x = 1 / x;
        n = -n; 
    }
    if (n == 0) {
        return 1;
    }
    float y = 1;
    while (n > 1) {
        if (n % 2 == 0) {
            x = x * x;
            n = n / 2;
        } else {
            y = x * y;
            x = x * x;
            n = (n - 1) / 2;
        }
    } 
    return x * y;
}
//arcctg
float formula(int x, int epsilon) {
    if (x < -1 || x > 0)
		throw "ValueError\n\t!!! -1 <= x < 1";
    float summ_result = 0;
    for (int i = 0; i < epsilon; i++) {
        summ_result += (my_pow(-1, i + 1) * ( my_pow(x, 2 * i + 1) / (2 * i + 1) ) );
    }
    return PI / 2 + summ_result;
}

int main() {
    //formulea mea pentr arc cotagenta
    cout << formula(1, 5000) << endl;
    // din bibloteca math
    cout << PI / 2 - atan(1) << endl;
}
