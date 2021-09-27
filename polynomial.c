#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
// we did seperate polynomials into groups as it starts with + or - character and ends when it sees the + and - again
// for examp, for the poly. 2x^2+56x-4 we seperate the polynomial into 2x^2  +56x  and  -4. then we take input value to put it in place of x and put the result to the file
// I named this temporary buffers as "poly"s.
void remove_spaces(char* s) {
    const char* d = s;					// removes the spaces between elements
    do {
        while (*d == ' ') {
            ++d;
        }
    } while (*s++ = *d++);  
}
int findx(char* arr){
	int n=strlen(arr);
	int i;
	for(i=0;i<n;i++){
	 	if(arr[i]=='x')				// it returns x if it exist else returns -1 
	 	{
	 		return i;	
		}
	}
 	return -1;
}			
int findexp(char *arr){
	int n;
	n=findx(arr);
	if(n!=-1){
		if(arr[n+1]=='^'){
			return 1;			// if x and exp.exist returns 1
		}
		else {		
			return 2;				//  if x exist but exponent does not,returns 2 (which means degree 1 polynomial)
		}
	}
	return 0;						// there is no x, returns 0
}
double findcoef(char *arr){ // finds the coefficient of the polynomial
	int i=0;
	int mag;
	double coeff;
	mag= strlen(arr);
	char coef[mag];
	while(arr[i]!='x' && i<=mag){
		coef[i]=arr[i];
		i++;
	}	
	if(i==0 || arr[i-1] == '+')				//if the first polynomial looks like x^2 and the others look like +x^2 returns 1.0
	{
		return 1.0;
	}
	if(arr[i-1] == '-' )					//if it start with - like (-x^2) 
	{
		return -1.0;
	}
	coef[i]='\0';
	sscanf(coef,"%lf",&coeff);			// if it is more complex as (-123x^2)
	return coeff;
}

double* values(char *arr){
	double ret[2];	
	int i;
	double k;							
	int j=0;
	char pow[6];
	double *p;
	if(findexp(arr)==1){
		for(i=findx(arr)+2;i<=strlen(arr);i++){
			pow[j]=arr[i];
			j++;
		}
	pow[j]='\0';
	sscanf(pow,"%lf",&k);				
	ret[0]=findcoef(arr);				
	ret[1]=k;								
	}										// it returns an array which has its first element holds the coefficient and second element the exponent
	else if(findexp(arr)==2){				// if controlling polynomial is constant then coef=that number and exp=0
			ret[0]=findcoef(arr);
			ret[1]=1;
	}
	else if(findexp(arr)==0){
			ret[0]=findcoef(arr);
			ret[1]=0;
	}
	p=ret;
	return p;
}
double power(double base, double a) {		// evaluates the powers
    if (a != 0.0)
        return (base * power(base, a - 1.0));
    else
        return 1;
}
double result(char* arr,double x){
	double *valuearray;
	valuearray=values(arr);								// finding the results of the polynomials and returns 
	double ret =valuearray[0]*power(x,valuearray[1]);
	return ret; 
}
void printresult(){
	FILE *fp1,*fp2,*fp3;
	fp1=fopen("values.txt","r");
	fp2=fopen("polynomial.txt","r"); 
	fp3=fopen("evaluations.txt","w");
	double sum=0.0,input;
	if (fp1 == NULL|| fp2== NULL) {
      printf("Error occured during opening files");
      exit(1);
 	 } 
  	char allinputs[1000];
 	fgets(allinputs,999,fp2);						// all the values in poly are assigned to all inputs
	remove_spaces(allinputs);						// all the spaces have been removed
	char poly[15];									// pre acceptence: for each poly,max size could be 15
	int i,j=0,k=0;
  	
  	while (fscanf(fp1,"%lf ",&input) == 1)			// for each value taken from values
	{

 		for(i=0;i<strlen(allinputs);i++){
			if(allinputs[i]!='+' && allinputs[i]!= '-'){
				poly[j]=allinputs[i];
				j++;		
			}
			else {
			
			sum += result(poly,input);		// each element in polynomial is assigned to result function as 'poly'
			poly[0]=allinputs[i];				// for not losing the signs
			j=1;
			for(k=1;k<strlen(poly);k++){
				poly[k]=' ';					// we are assigning ' ' to poly to free the values in it and use again
				}				
			}
		}					
					// for the last element,same process has been done
		sum += result(poly,input);
		for(k=0;k<strlen(poly);k++){
				poly[k]=' ';
				} 
		j=0;			

	fprintf(fp3,"%.2lf\n",sum);
	sum=0.0;									// for each input, sum has been reseted
	}
  	fclose(fp1);
	fclose(fp2); 
	
}
int main(){
	printresult();
	return 0;
}


