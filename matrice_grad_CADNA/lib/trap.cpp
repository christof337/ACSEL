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
    SAM_init(0, 70);
    
    int n=1,i=0,j;
    mp_st x, somme, a, b, integ, h, err, integold, aux, exact, pi;
    mp_st tt;
    mp_st zero,one,two,three,four;
    
    sam_set_str(zero,"0.0");
    sam_set_str(one,"1.0");
    sam_set_str(two,"2.0");
    sam_set_str(three,"3.0");
    sam_set_str(four,"4.0");
   
    cout << "----------------------------------------------------------------" << endl;
	cout << "|  Approximation by using the composite trapezoidal            |" << endl; 
	cout << "----------------------------------------------------------------" << endl;
    
    pi=four*atan(one);
    exact=sam_set_str(tt,"5.0")*pi*pi/sam_set_str(tt,"96.0");
    
    a=zero;
    b=one;
    
    somme=zero;
    aux=f(a)+f(b);
    h=b-a;
    integold=one;
    integ=zero;
    
    while (integold != integ) {
        
        integold = integ;
        i=i+1;
        x=a+h/two;
        
        for (j=1; j<=n; j++) {
            somme=somme+f(x);
            x=x+h;
        }
        
        n=2*n;
        h=h/two;
        integ=h*(aux+two*somme)/two;
        err=fabs(integ - exact);
    }
    printf("i=%d, I(f)=%s, err=%s\n", i,strp(integ),strp(err));

    SAM_end();
}

