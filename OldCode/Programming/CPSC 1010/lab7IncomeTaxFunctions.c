/*AJ Garner
Lab Section 1
Lindsey Kirtley, Ashley Moody, Davis Little*/

#include <stdio.h>
#include <math.h>

int CalcAGI(int wage, int taxInt, int unemploy);//agi = wage + taxInt + unemploy
//these are all just prototypes
int GetDeduction(int status);

int CalcTaxable(int AGI, int Deduction);//agi = agi - deduction

int CalcTax(int status, int taxableincome);//determines fed taxes

int CalcTaxDue(int fedtax, int taxkept);//determines if money is owed to whom

int main(void){
    int wage; //user's wage earned
    int taxInt; //taxable interest 
    int unemploy; //unemployment comp
    int status; // married or single
    int taxkept; // taxes withheld

//prompt the user to enter needed data
    printf("Please enter wages, taxable interest, and unemployment compensation: \n");
    scanf("%d %d %d", &wage, &taxInt, &unemploy);

    printf("Please enter status (0 dependent, 1 single, 2 married): \n");
    scanf("%d", &status);
    if (status < 0 || status > 2){//needed to see if there is a valid integer entered
        printf("Error: Must input status 0 (dependent), 1 (single), or 2 (married).\n");
        return -1;
    }

    printf("Please enter taxes withheld: \n");
    scanf("%d", &taxkept);
    if (taxkept < 0){//needed to see if there is a valid integer entered
        printf("Error: taxes withheld cannot be less than 0.\n");
        return -1;
    }
/*These printf statments also have the call to functions in them as well.
  They well call the functions and then print the integer in the output to the user.
  This is to make the code more readable and allows anyone to see the purpose by just looking at the functions*/
    printf("AGI: $%d\n", CalcAGI(wage, taxInt, unemploy));
    printf("Deduction: $%d\n", GetDeduction(status));
    printf("Taxable Income: $%d\n", CalcTaxable(CalcAGI(wage, taxInt, unemploy), GetDeduction(status)));
    printf("Federal Tax: $%d\n", CalcTax(status, CalcTaxable(CalcAGI(wage, taxInt, unemploy), GetDeduction(status))));
//Taxdue is declared because it must be check to see if user gets a refund
    int taxdue = CalcTaxDue(CalcTax(status, CalcTaxable(CalcAGI(wage, taxInt, unemploy), GetDeduction(status))), taxkept);
    if (taxdue >= 0) {// if the user owes taxes it will print what they owe
      printf("Taxes Owed: $%d\n", taxdue);
    }
    else if (taxdue < 0) {//if the user is owed taxes it will print their refund
      taxdue = taxdue * -1;//used to make the negative a positive
       printf("Tax Refund: $%d\n", taxdue);
    }

    return 0;
}

int CalcAGI(int wage, int taxInt, int unemploy){//this is a simple addition function
    int agi;
    agi = wage + taxInt + unemploy;
    return agi;
}

int GetDeduction(int status){//this function checks to see what type of deduction they are owed
    int deduction;
    if(status == 0){//dependent
        deduction = 6000;
    }
    else if(status == 1){//single
        deduction = 12000;
    }
    else if(status == 2){//married
        deduction = 24000;
    }
    return deduction;
}

int CalcTaxable(int AGI, int Deduction){//this fucntion determines if there is taxable income and by how much
    int taxableincome;
    taxableincome = AGI - Deduction;
    if(taxableincome < 0){//if the taxable income is less than 0, then the integer is set to 0
        taxableincome = 0;
        return taxableincome;
    }
    else{//this will just return what the taxable income is
        return taxableincome;
    }
}

int CalcTax(int status, int taxableincome){//this function determines the federal taxes that are owed
    double fedtax;//needs to start as a double

    if (status == 1 || status == 0){//if single or a dependent
        if (taxableincome <= 10000) {
            fedtax = taxableincome * .1;
        }
        else if(taxableincome <= 40000) {
            fedtax = ((taxableincome - 10000) * 0.12) + 1000;
        }
        else if(taxableincome <= 85000) {
            fedtax = ((taxableincome - 40000) * 0.22) + 4600;
        }
        else {
            fedtax = ((taxableincome - 85000) * 0.24) + 14500;
        }
    }
    else if (status == 2) {//else if married

        if (taxableincome <= 20000) {
            fedtax = taxableincome * 0.1;
        }
        else if(taxableincome <= 80000) {
            fedtax = ((taxableincome - 20000) * 0.12) + 2000;
        }
        else{
            fedtax = ((taxableincome - 80000) * 0.22) + 9200;
        }
    }
    fedtax = round(fedtax);//need the round function to round the amount and turn it back from a double
    return fedtax;
}

int CalcTaxDue(int fedtax, int taxkept){//simple subtration function
    int taxdue;
    taxdue = fedtax - taxkept;
    return taxdue;
}