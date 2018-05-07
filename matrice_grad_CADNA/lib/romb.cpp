
#include "SAM.h"
#include <math.h>
#include <stdio.h>

mp_st f(const mp_st& x){
    mp_st aux, res, tt;
    aux=sqrt(sam_set_str(tt,"2.0")+x*x);
    res=atan(aux)/(aux*(sam_set_str(tt,"1.0")+x*x));
    return res;   
}

main()
{
	
	
	SAM_init(0, 138);
    int n=1,i=0,j;
    mp_st x, somme, a, b, integ, h, err, integold, aux, sommetot, exact, pi;
    mp_st tt;
    
    mp_st zero,one,two,three,four,coef;
    
    mp_st *T;
    T=new mp_st [20];
    
    sam_set_str(zero,"0.0");
    sam_set_str(one,"1.0");
    sam_set_str(two,"2.0");
    sam_set_str(three,"3.0");
    sam_set_str(four,"4.0");
    
    cout << "----------------------------------------------------------------" << endl;
	cout << "|  Approximation by using the composite Romberg's              |" << endl; 
	cout << "----------------------------------------------------------------" << endl;
    
    pi=four*atan(one);
    exact=sam_set_str(tt,"5.0")*pi*pi/sam_set_str(tt,"96.0");    printf("exact=%s\n",strp(exact));
    a=zero;
    b=one;
   
    h=b-a;
    integold=one;
    integ=zero;
    T[1]=h*(f(a)+f(b))/two;
    
   
    while ((integold != integ) && (i<=20)) {
        
        integold = integ;
        i=i+1;
        x=a+h/two;
        somme=zero;
        
        for (j=1; j<=n; j++) {
            somme=somme+f(x);
            x=x+h;
        }
        
        n=2*n;
        h=h/two;
        
        T[i+1]=T[i]/two+h*somme;
        coef=four;
        for (j=i; j>=1; j--) {
            T[j]=(coef*T[j+1]-T[j])/(coef-one);
            coef=coef*four;
        }
        
        integ=T[1];
        err=fabs(integ - exact);
        printf("i_%d=%s, err=%s\n", i,strp(integ),strp(err));
    }
    delete[] T;
    SAM_end();
}
