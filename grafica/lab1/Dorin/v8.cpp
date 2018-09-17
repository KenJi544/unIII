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

int factorial(int k){
    int fact = k;
    while(--k){
        fact *= k;
    }
    return fact;
}

double formula(double x, double eps){
	double sum = x;
	if (eps > 1)
		for (int k=2; k<eps; k++){
			sum += power(x, k)/factorial(k);
		}
	return sum;
}
	

int main(){
	double x, eps;
	std::cout<<"x="; std::cin>>x;
	std::cout<<"eps="; std::cin>>eps;
	std::cout<<"result "<<std::setprecision(9)<<formula(x, eps);
}
