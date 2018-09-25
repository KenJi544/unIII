#include <iostream>
#include <iomanip>
#include <cmath>

double formula(double x, double eps){
	if(x < -1 || x >= 1){
        std::cerr<<"wrong value\n";
        return 0;
	}
	double sum = x;
	double t = x;
	double k = 2;

	do{
        t *=x/k;

        sum += t;
        std::cout<<sum<<"\n";
	}while(fabs(t)>eps);
	return sum;
}


int main(){
	/*
	 * -1 <= x < 1
	 */
	double x, eps;
	std::cout<<"x="; std::cin>>x;
	std::cout<<"eps="; std::cin>>eps;
	std::cout<<"result "<<std::setprecision(9)<<formula(x, eps);
    /*
     * poti sa stergi si linia 36 sau in "pune formula ta din cmath"
     * si in loc de log(1-x) la fel formula ta din varianta ta
     */
    std::cout<<"log 1 -x " <<std::cout<<log(1 - x)<<"\n";
}
