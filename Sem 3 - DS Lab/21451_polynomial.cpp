# include <bits/stdc++.h>
using namespace std;

class Term
{
    int exp;        // Exponent of Term
    float coeff;    // Coefficient of Term
    friend class Poly; 

    public:
    Term(){         // Default Constructor
        exp = 0;
        coeff = 0.0;
    }

    Term(int exp, float coeff){     // Parameterized Constructor
        this->exp = exp;
        this->coeff = coeff;
    }
};


class Poly
{
    int n;      // No. of terms in array
    Term *arr;  // Store terms of polynomial
    
    public:
    void acceptPoly();          // Accept terms of polynomial
    void displayPoly();         // Display terms of polynomial
    Poly operator + (Poly);     // Add two polynomials
    Poly operator * (Poly);     // Multiply two polynomials
};


// Accept terms of polynomial
void Poly :: acceptPoly()
{
    int texp;       // temporary variables
    float tcoeff;
    cout << "Enter number of terms in polynomial: " << endl;
    cin >> this->n;
    arr = new Term[n];
    cout << "Enter polynomial in form 'exponent<space>coefficient' :" << endl;
    for (int i=0; i<n; i++){
        cin >> texp >> tcoeff;
        this->arr[i].exp = texp;
        this->arr[i].coeff = tcoeff;
    }
}

// Display terms of polynomial
void Poly :: displayPoly()
{
    cout << "P(x) = ";
    int i = 0;
    while (i < n && arr[i].exp != -1){
        cout << arr[i].coeff << "x^" << arr[i].exp << " + ";
        i++;
    }
    cout << 0 << endl;
    if (arr[i].exp == -1){
        cout << endl;
        return;
    }
    
}

// Add two polynomials
Poly Poly:: operator + (Poly p){
    int i=0, j=0, k=0;
    // i = traverse p1 polynomial
    // j = traverse p2 polynomial
    // k = traverse sum polynomial 

    // store sum of polynomials
    Poly sum;
    sum.n = this->n + p.n;
    sum.arr = new Term[sum.n];

    // traverse p1 and p2 by 2 pointer method
    while (i < this->n && j < p.n && this->arr[i].exp != -1 && p.arr[j].exp != -1){
        
        // Add if exponents are same
        if (this->arr[i].exp == p.arr[j].exp){
            sum.arr[k].coeff = this->arr[i].coeff + p.arr[j].coeff;
            sum.arr[k].exp = this->arr[i].exp;
            i++;
            j++;
        }

        // Append p1 term if it is greater
        else if (this->arr[i].exp > p.arr[j].exp && this->arr[i].exp != -1){
            sum.arr[k].coeff = this->arr[i].coeff;
            sum.arr[k].exp = this->arr[i].exp;
            i++;
        }

        // Append p2 term if it is greater
        else if (p.arr[j].exp != -1){
            sum.arr[k].coeff = p.arr[j].coeff;
            sum.arr[k].exp = p.arr[j].exp;
            j++;
        }       
        k++;
    }

    // If p1 not exhausted but p2 exhausted
    // Append p1 terms
    while(i < this->n && this->arr[i].exp != -1){
        sum.arr[k].coeff = this->arr[i].coeff;
        sum.arr[k].exp = this->arr[i].exp;
        i++;
        k++;
    }

    // If p1 exhausted but p2 not exhausted
    // Append p2 terms
    while(j < p.n && p.arr[j].exp != -1){
        sum.arr[k].coeff = p.arr[j].coeff;
        sum.arr[k].exp = p.arr[j].exp;
        j++;      
        k++;  
    }
    // store sum of polynomials
    // If k < i+j
    while(k < sum.n){
        sum.arr[k].coeff = 0.0;
        sum.arr[k].exp = -1;
        k++;
    }

    return sum;
}     

// Multiply two polynomials
Poly Poly:: operator * (Poly p){

    // store product of polynomials
    Poly mul;
    mul.n = this->n * p.n;
    mul.arr = new Term[mul.n];

    Poly temp;
    temp.n = p.n;
    temp.arr = new Term[temp.n];

    for (int i=0; i < this->n; i++){
        if (this->arr[i].exp != -1){
            for (int j=0; j < p.n; j++){
                if (p.arr[j].exp != -1){
                    temp.arr[j] = Term(this->arr[i].exp + p.arr[j].exp, this->arr[i].coeff * p.arr[j].coeff);
                    if(i==0){
                        mul.arr[j] = temp.arr[j];
                    }
                }
            }            
            if(i>0){
                mul = mul + temp;
            }
        }
    }
    return mul;
}

int main()
{
    Poly p1;
    p1.acceptPoly();
    p1.displayPoly();

    Poly p2;
    p2.acceptPoly();
    p2.displayPoly();

    Poly Sum = p1 + p2;
    Sum.displayPoly();

    Poly Product = p1 * p2;
    Product.displayPoly();

    return 0;
}

