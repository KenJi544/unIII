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
	/*
	 * Not ready yet
	 */
	double sum = x;
	std::cout<<"check\n";
	if (sum > eps)
		std::cout<<sum<<">"<<eps<<"\n";
		for (int k=2; sum<eps; k++){
		std::cout<<sum<<">"<<eps<<"\n";
			sum += power(x, k)/k;
			std::cout<<"in func "<<std::setprecision(9)<<sum<<std::endl;
		}
	return sum;
}
	

int main(){
	/*
	 * -1 <= x < 1
	 */
	std::cout<<"result "<<power(2, 4)<<std::endl;
	std::cout<<"result "<<std::setprecision(9)<<ln_1_min_x(0.2, 0.0001);
}
