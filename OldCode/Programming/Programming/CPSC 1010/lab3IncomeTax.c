/* AJ Garner
Lindsey Kirtley
Ashley Moody
Davis Little
Lab Section 1
*/

#include <stdio.h>
#include <string.h>
#include <math.h>

int main(void) {

   int wage;
   int taxInt; //taxable interest 
   int unemploy; //unemployment comp
   int status; // married or single
   int taxkept; // taxes withheld
   int agi; //annual gross income
   int deduction;
   int taxableincome;
   double fedtax;
   int taxdue;   
   
   char colon = ':';
   char AGI[] = "AGI";
   char Deduction[] = "Deduction";
   char Taxableincome[] = "Taxable Income";
   char Fedtax[] = "Federal Tax";
   char Taxowed[] = "Tax Owed";
   char Taxrefund[] = "Tax Refund";

   
   scanf("%d %d %d %d %d", &wage, &taxInt, &unemploy, &status, &taxkept);
   
   agi = wage + taxInt + unemploy;
   
//Block of code---------------------------------------------------------
   if (status == 1) {
      deduction = 12000;
   }
   else if (status == 2) {
      deduction = 24000;
   }
   else {
      printf("Error: Must input status 1 (single) or 2 (married).\n");
      return 0;
   }
   
   
//block of code----------------------------------------------------
   if (agi < 120000) {
      printf("%-15s%c%7d\n", AGI, colon, agi);
   }
   else {
      printf("AGI: %d\nError: Income too high to use this form.\n", agi);
      return 0;
   }
   
//block of code------------------------------------------------
   taxableincome = agi - deduction;
   
   if (taxableincome < 0) {
      taxableincome = 0;
   }
   
   printf("%-15s%c%7d\n", Deduction, colon, deduction);
   printf("%-15s%c%7d\n", Taxableincome, colon, taxableincome);
   
//block of code---------------------------------------------------------
   if (status == 1){
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
   else if (status == 2) { 
//blcok of code----------------------------------------------
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
   fedtax = round(fedtax);
   printf("%-15s%c%7.0f\n", Fedtax, colon, (fedtax));
//blcok of code----------------------------------------------
   
   taxdue = fedtax - taxkept;
   if (taxdue >= 0) {
      printf("%-15s%c%7d\n", Taxowed, colon, taxdue);
   }
   else if (taxdue < 0) {
      taxdue = taxdue * -1;
       printf("%-15s%c%7d\n", Taxrefund, colon, taxdue);
   }
   
   
   return 0;
}

