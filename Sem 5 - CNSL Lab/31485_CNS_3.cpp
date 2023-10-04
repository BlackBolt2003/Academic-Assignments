#include <iostream>
#include <math.h>
using namespace std;

class HammingCode {
    int m;  //code word length
    int r;  //redundent bits
    string bits; //actual code word
    int *msg;   //code word to be sent

    public:
    HammingCode(){
        m = r = 0;
        bits = " ";
        msg = NULL;
    }

    HammingCode(string bits){
        this->m = bits.length();
        this->bits = bits;
        r = 0;
        msg = NULL;
    }

    void CalcRedundentBits() {
        //calculate redundent bits
        this->r = 0;
        while(pow(2,r) < m + r + 1){
            r++;
        }

        //display value of r
        cout << "r = " << this->r << endl;
    }

    void GenerateCodeWord(){
        msg = new int[m+r+1];   //0th place unused
        msg[0] = 9;             //default 
        for(int i=1; i<m+r+1; ++i){
                msg[i] = 0;
        }

        //set 2^r values as default=9
        for(int i=0; i < r; ++i){
            int factor2 = pow(2,i);
            msg[factor2] = 9;
        }

        //Fill bits in msg
        int k=m-1;
        for(int i=1; i<m+r+1; ++i){
            if (msg[i] != 9) {
                msg[i] = bits[k] - '0';
                k--;
            }
        }

        //display code
        cout << "Code word = ";
        for(int i=m+r; i>0; --i){
            cout << msg[i];
        }
        cout << endl;
    }
};

int main(){
    string bits = "11001";
    HammingCode Code(bits);
    Code.CalcRedundentBits();
    Code.GenerateCodeWord();

    return 0;
}