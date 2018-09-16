#include <iostream>
using namespace std;

double power(double x, int y)
{
    double z;
    if (y == 0)
    return 1;
    z = power (x, y / 2);
    if ((y % 2) == 0) {
        return z * z;
    } else {
        if (y > 0)
            return x * z * z;
        else
            return (z* z) / x;
    }
}

int main(){
	cout<<"result "<<power(2, 4)<<endl;
}
