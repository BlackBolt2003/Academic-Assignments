/*
	----
Create class of complex numbers and overload +, *, << and >> operators
to perform operations on complex numbers
	----
*/

#include <iostream>
using namespace std;

class complex{
private :
	float real, imag;

public:
	//default constructor
	complex(){
		real = 0;
		imag = 0;
	}

	//overload + operator
	complex operator + (complex z){
		z.real += real;
		z.imag += imag;
		return z;
	}

	//overload * operator
	complex operator * (complex z){
		// (a+ib) * (c+id) = (ac - bd) + (ad + cb)i
		complex ans;
		ans.real = (this->real * z.real) - (this->imag * z.imag);
		ans.imag = (this->real * z.imag) + (this->imag * z.real);
		return ans;
	}

	//overload << operator
	friend ostream & operator << (ostream &os, const complex &z);

	//overload >> operator
	friend istream & operator >> (istream &is, complex &z);
};

//overload << operator
ostream & operator << (ostream &os, const complex &z){
	os << "(" <<  z.real << ")" <<  "+i" << "(" <<  z.imag << ")";
	return os;
}

//overload >> operator
istream & operator >> (istream &is, complex &z){
	is >> z.real >> z.imag;
	return is;
}

int main()
{
	int option;
	char cont;
	complex z1, z2;

	cout << "Welcome to Complex Calculator!";
	while(true){
		cout <<	"\nOptions Menu : "
			 << "\n1 - Addition"
			 << "\n2 - Multiplication"
			 << "\n\nEnter your choice :";
		cin >> option;

		switch(option){
			case 1: //addition

				cout << "\nEnter real and imaginary part of complex number z1 :\n";
				cin >> z1;
				cout << "\nEnter real and imaginary part of complex number z2 :\n";
				cin >> z2;
				cout << "Addition of complex numbers = ";
				cout << z1+z2;
				break;

			case 2: //multiplication

				cout << "\nEnter real and imaginary part of complex number z1 :\n";
				cin >> z1;
				cout << "\nEnter real and imaginary part of complex number z2 :\n";
				cin >> z2;
				cout << "Product of complex numbers = ";
				cout << z1*z2;
				break;

			default:
				cout << "\nInvalid choice!" << endl;
				break;
		}

		cout << "\nDo you wish to continue? (y/n)\n";
		cin >> cont;
		if (cont == 'n' || cont == 'N'){
			break;
		}
	}

	cout << "Exited Complex Calculator . . ." << endl;

	return 0;
}
