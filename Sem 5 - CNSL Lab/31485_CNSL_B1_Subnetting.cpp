/*
 * 31485_CNSL_B1.cpp
 *
 *  Created on: Sep 15, 2023
 *      Author: pict
 */
/* ---------------------------------------------
PROBLEM STATEMENT
Write a program to demonstrate Sub-netting and find subnet masks.
 --------------------------------------------- */

#include <iostream>
#include <string>
#include <math.h>
#include <iomanip>
using namespace std;

int* getAddressArray(string address){
	int* addressArray = new int[4];

	int k = 0;
	string token = " ";
	for(int i=0; i<address.size(); i++){
		if(address[i] == '.'){
			addressArray[k] = stoi(token);
			k++;
			token = " ";
		}
		else{
			token += address[i];
		}
	}

	return addressArray;
}

string getAddressString(int* addressArray){
	string address = " ";
	for(int i=0; i<4; i++){
		address += to_string(addressArray[i]);
		if(i!=3){
			address += '.';
		}
	}
	return address;
}

int nearestPowerOfTwo(int x){
	int n = 0;
	while(pow(2,n) < x){
		n++;
	}

	return n;
}


class SubnetTypeC {
	string NetworkAddress;
	string BroadcastAddress;
public:
	static string DefaultSubnetMask;

	SubnetTypeC(){
		NetworkAddress = "0.0.0.0";
		BroadcastAddress = "0.0.0.0";
	}

	SubnetTypeC(string NAdd, string BAdd){
		NetworkAddress = NAdd;
		BroadcastAddress = BAdd;
	}

	void setAddress(string NAdd, string BAdd){
		NetworkAddress = NAdd;
		BroadcastAddress = BAdd;
	}

	string n_addr(){
		return NetworkAddress;
	}

	string b_addr(){
		return BroadcastAddress;
	}

};


class subnetByNetwork {
	int N;					//No. of networks
	int H; 					//No. of hosts
	SubnetTypeC *subnets;	//All subnets
	string networkAddress;
	string subnetMask;

public:
	subnetByNetwork(){
		N = H = -1;
		subnets = NULL;
		networkAddress = "0.0.0.0";
		subnetMask = "255.255.255.0";
	}

	subnetByNetwork(string NAddr){
		N = H = -1;
		subnets = NULL;
		networkAddress = NAddr;
		subnetMask = "255.255.255.0";
	}

	subnetByNetwork(string NAddr, int n){
		N = n;
		H = -1;
		subnets = new SubnetTypeC[n];
		networkAddress = NAddr;
		subnetMask = "255.255.255.0";
	}

	string performSubnetting(){
		string SubnetString = "255.255.255.0";
		int* SubnetArray = getAddressArray(SubnetString);

		int n = nearestPowerOfTwo(N);

		int pos=7;
		for(int b=n; b>0; b--){
			SubnetArray[3] += pow(2,pos);
			pos--;
		}

		this->subnetMask = getAddressString(SubnetArray);

		H = pow(2, 8-n) - 2;

		int* defaultSubnetMaskArray = getAddressArray(SubnetTypeC::DefaultSubnetMask);
		int addrPerSubnet = defaultSubnetMaskArray[3] - SubnetArray[3];

		int* currNAddr = new int[4];
		int* currBAddr = new int[4];
		currNAddr = getAddressArray(networkAddress);
		currBAddr[3] = currNAddr[3] + addrPerSubnet;
		SubnetTypeC subnet;

		for(int i=0; i<N; i++){
			subnet.setAddress(getAddressString(currNAddr), getAddressString(currBAddr));
			subnets[i] = subnet;
			currNAddr[3] = currBAddr[3] + 1;
			currBAddr[3] = currNAddr[3] + addrPerSubnet;
		}
	}

	void showSubnets(){
		cout << "Subnet Mask = " << this->subnetMask << endl << endl;
		cout << "Subnet No.\tNetwork Address\tBroadcast Address" << endl;
		cout << "--------------------------------------------------------" << endl;
		for(int i=0; i<N; i++){
			cout << i+1 << "\t" << subnets[i].n_addr() << "\t" << subnets[i].b_addr() << endl;
		}
	}
};


string SubnetTypeC::DefaultSubnetMask = "255.255.255.255";

int main(){

	// To check working of string and array inter-conversion ------------------------
	/*
	string msg = "192.168.1.0";
	int* addressArray = getAddressArray(msg);

	cout << "addressArray = ";
	for(int i=0; i<4; i++){
		cout << addressArray[i] << " ";
	}
	cout << endl;
	string addressString = getAddressString(addressArray);
	cout << "addressString = " << addressString;
	*/

	// To check subnetAddress -------------------------------------------------------
	/*
	subnetByNetwork sbn("192.168.6.0", 4);
	string subnetAddr = sbn.performSubnetting();
	cout << subnetAddr << endl;
	*/

	// Driver Code ------------------------------------------------------------------
	cout << "# Subnetting Program for Type-C IP Address" << endl << endl;

	string naddr = " ";
	int n = 0;
	cout << "Enter network address = ";
	cin >> naddr;
	cout << "Enter no. of subnets = ";
	cin >> n;

	subnetByNetwork sbn(naddr, n);
	string subnetAddr = sbn.performSubnetting();
	sbn.showSubnets();

	return 0;
}




