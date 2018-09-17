#include <iostream>
#include <iomanip>

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
	if(x < -1 || x >= 1)
		throw "ValueError\n\t!!! -1 <= x < 1";
	double sum = x;
	if (eps > 1)
		for (int k=2; k<eps; k++){
			sum += power(x, k)/k;
		}
	return sum;
}
	

int main(){
	/*
	 * -1 <= x < 1
	 */
	double x, eps;
	std::cout<<"x="; std::cin>>x;
	std::cout<<"eps="; std::cin>>eps;
	std::cout<<"result "<<std::setprecision(9)<<ln_1_min_x(x, eps);
}
