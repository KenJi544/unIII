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

double ln_1_min_x(double x, double eps){
	/*
	 * Not ready yet
	 */
	if (x < -1) or (x > 0)
		throw "ValueError\n\t!!! -1<=x<1 !!!";
	double sum = x;
	for (int k=2; k<5; k++){
		sum = power(x, k)/k;
		cout<<sum<<endl;
	}
	return sum;
}
	

int main(){
	/*
	 * -1 <= x < 1
	 */
	cout<<"result "<<power(2, 4)<<endl;
	cout<<"result "<<ln_1_min_x(0.2, 0.0001)
}
