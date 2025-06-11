

#include <iostream>
using namespace std;

int main()
{
    float annualSalary;
    cout << "Enter your Salary:";
    cin >> annualSalary;
    

    float monthSalary = annualSalary / 12;
    cout << "Your montly salary is: " << monthSalary<< endl;
    cout << "IN 10 Years you will earn: " << annualSalary * 10 << "\n";

    char character = 'a';
    cout << "This is as single CHARACTER: " << character;
        
    system("Pause>0");
}


