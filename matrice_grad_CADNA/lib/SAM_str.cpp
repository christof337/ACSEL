/*-----------------------------------------------------------------------
Copyright 2013 S. GRAILLAT, F. JEZEQUEL, S. WANG, Y. ZHU

This file is part of SAM.

    SAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU Lesser General Public License as
    published by the Free Software Foundation, either version 3 of the
    License, or (at your option) any later version.

    SAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
    or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General
    Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with SAM. If not, see
    <http://www.gnu.org/licenses/>.
-----------------------------------------------------------------------*/
///////////////////////////////////////////////////
//
// SAM SOFTWARE
//
///////////////////////////////////////////////////
// Last Modifications
// 
//
///////////////////////////////////////////////////

#include "SAM.h"
#include "SAM_private.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <cstdio>
#include <math.h>
#include <stack>

#define MAXCHAINE 256
static char chstr[MAXCHAINE][64];
static int numstr=0; 

using namespace std;

//////////////////////////////////////////////////////////
//****m* SAM_str/display
//    NAME
//      display
//
//    SYNOPSIS
//      display()
//      display(char *)
//
//    FUNCTION
//      The display method prints the triplet associated with 
//      a stochastic variable.
//    INPUTS
//   
//    RESULT
//      void
//    SEE ALSO
//      str(3)
//*****
//   You can use this space for remarks that should not be included
//   in the documentation.
//    EXAMPLE
//      
//  
//    NOTES
//  
//  
//    BUGS
//  
//  
//      
//      
//  /

void mp_st::display() const 
{ 
    int default_prec_digit = DEFAULT_PREC *LOG;
    mpfr_out_str(stdout, 10, default_prec_digit, x, MPFR_RNDN);
    cout<<" -- ";
    mpfr_out_str(stdout, 10, default_prec_digit, y, MPFR_RNDN);
    cout<<" -- ";
    mpfr_out_str(stdout, 10, default_prec_digit, z, MPFR_RNDN);
	cout << "\n";
}

///////////////////////////////////////////////////////////////////////////////////////////

void mp_st::display(const char *s) const 
{ 
    int default_prec_digit = DEFAULT_PREC *LOG;
    cout<<"s ";
    mpfr_out_str(stdout, 10, default_prec_digit, x, MPFR_RNDN);
    cout<<" -- ";
    mpfr_out_str(stdout, 10, default_prec_digit, y, MPFR_RNDN);
    cout<<" -- ";
    mpfr_out_str(stdout, 10, default_prec_digit, z, MPFR_RNDN);
}

//////////////////////////////////////////////////////////
//****m* SAM_str/operator<<
//    NAME
//     operator<<
//
//    SYNOPSIS
//      ostream& operator <<(ostream&, const mp_st &) 
//    FUNCTION
//      << operator for stochastic variables
//    INPUTS
//   
//    RESULT
//      void
//    SEE ALSO
//      str(3)
//*****
//   You can use this space for remarks that should not be included
//   in the documentation.
//    EXAMPLE
//      
//  
//    NOTES
//  
//  
//    BUGS
//  
//  
//      
//      
//  /

ostream& operator <<(ostream& s, const mp_st &a) 
{

	int CL = 10 +  DEFAULT_PREC;
	char ch[CL];
	return s << a.str(ch);
}

//////////////////////////////////////////////////////////
//****m* SAM_str/operator>>
//    NAME
//     operator>>
//
//    SYNOPSIS
//      ostream& operator >>(ostream&, const mp_st &) 
//    FUNCTION
//      >> operator for stochastic variables
//    INPUTS
//   
//    RESULT
//      void
//    SEE ALSO
//      str(3)
//*****
//   You can use this space for remarks that should not be included
//   in the documentation.
//    EXAMPLE
//      
//  
//    NOTES
//  
//  
//    BUGS
//  
//  
//      
//      
//  /

istream& operator >>(istream& s, mp_st& a)
{
	double d;
	s>>d;
	mp_rnd_t sb = mpfr_get_default_rounding_mode();
	mpfr_set_d (a.x, d, sb);
	mpfr_set_d (a.y, d, sb);
	mpfr_set_d (a.z, d, sb);
	a.accuracy=DIGIT_NOT_COMPUTED;
	return s;
}

//////////////////////////////////////////////////////////

//****f* SAM_str/str
//    NAME
//     str
//
//    SYNOPSIS
//      char* mp_st::str(char *s) const 
//
//      char* str(char *, mp_st&)
//    FUNCTION
//      The output string contains the scientific notation of the 
//      stochastic argument; only the exact significant digits appear 
//      in the string. 
//    INPUTS
//      The str function has a string argument and a stochastic argument.
//    RESULT
//      It returns a pointer to the first argument.
//    SEE ALSO
//      str(3)
//*****
//   You can use this space for remarks that should not be included
//   in the documentation.
//    EXAMPLE
//      
//  
//    NOTES
//  
//  
//    BUGS
//  
//  
//      
//      
//  /

char* mp_st::str(char *s) const 
{
	int /*b,*/  nres, naux;
	long int nn;
	mpfr_t fract_res,res,sum;
	
	int tmp;
	char *t/*,*t_tmp*/;
	//double fract;
	
	mp_rnd_t default_rnd = mpfr_get_default_rounding_mode();
	mpfr_set_default_rounding_mode(MPFR_RNDN);
	mp_rnd_t tmp_rnd = mpfr_get_default_rounding_mode();
	
	mpfr_t x_mpfr,y_mpfr,z_mpfr,im,two,ten,pow;
	mpfr_init2(fract_res,DEFAULT_PREC);
	mpfr_init2(res,DEFAULT_PREC);
	mpfr_init2(sum,DEFAULT_PREC);
	mpfr_init2(x_mpfr,DEFAULT_PREC);
	mpfr_init2(y_mpfr,DEFAULT_PREC);
	mpfr_init2(z_mpfr,DEFAULT_PREC);
	mpfr_init2(im,DEFAULT_PREC);
	mpfr_init2(two,DEFAULT_PREC);
	mpfr_init2(ten,DEFAULT_PREC);
	mpfr_init2(pow,DEFAULT_PREC);
	
	mpfr_set(x_mpfr,x,tmp_rnd);
	mpfr_set(y_mpfr,y,tmp_rnd); 
	mpfr_set(z_mpfr,z,tmp_rnd);
	
	if (accuracy==DIGIT_NOT_COMPUTED) this->nb_significant_digit();
	strcpy(s,"                     ");
	if (accuracy==0) {
		strncpy(s," @.0",4);
	}
	else {
		accuracy=(accuracy<(int)(DEFAULT_PREC*LOG)) ? accuracy : (int)(DEFAULT_PREC*LOG);

		mpfr_add(sum,x_mpfr,y_mpfr,tmp_rnd);
		mpfr_add(sum,sum,z_mpfr,tmp_rnd);
		mpfr_div_d(res,sum,3.0,tmp_rnd);
		mpfr_clear(x_mpfr);
		mpfr_clear(y_mpfr);
		mpfr_clear(z_mpfr);
		mpfr_clear(sum);
		
		if (mpfr_cmp_d(res,0.0)<0) strncpy(s,"-0.",3);
		else strncpy(s," 0.",3);
		mpfr_abs(res,res,tmp_rnd);
		
		if (mpfr_cmp_d(res,0.0)==0){
			nn=0;
			mpfr_set_d(fract_res,0.0,tmp_rnd);
		}
		else{
			
			mpfr_log10(im,res,tmp_rnd);
			
			if (mpfr_cmp_d(res,1.0)>=0) nn=mpfr_get_si(im,MPFR_RNDZ)+1;
			else nn=mpfr_get_si(im,MPFR_RNDZ);
			
			mpfr_set_d(ten,10.,tmp_rnd);
			mpfr_pow_si(pow,ten,-nn,tmp_rnd);
			mpfr_mul(fract_res,res,pow,tmp_rnd);

			mpfr_clear(res);
			mpfr_clear(pow);
			mpfr_clear(two);
			mpfr_clear(im);

			mpfr_t one,point_one;
			mpfr_init2(one,DEFAULT_PREC);
			mpfr_init2(point_one,DEFAULT_PREC);
			mpfr_set_d(one,1,tmp_rnd);
			mpfr_div(point_one,one,ten,tmp_rnd);
			
			if (mpfr_cmp_d(fract_res,0.1)<0) mpfr_set(fract_res,point_one,tmp_rnd);
			if (mpfr_cmp_d(fract_res,1.0)>=0){
				mpfr_set(fract_res,point_one,tmp_rnd);
				nn=nn+1;
			}
			mpfr_clear(one);
			mpfr_clear(point_one);
		}
		naux= accuracy+3;
		t=s+3;
		for(int i=4;i<naux;i++){
			mpfr_mul(fract_res,fract_res,ten,tmp_rnd);
			nres=mpfr_get_si(fract_res,MPFR_RNDD);
			*t++=48+nres;
			mpfr_sub_si(fract_res,fract_res,nres,tmp_rnd);
		}
		mpfr_mul(fract_res,fract_res,ten,tmp_rnd);
		tmp=mpfr_get_si(fract_res,tmp_rnd);
		nres = tmp < 9 ? tmp : 9 ;
		*t++=48+nres;
		if(nn>0){
			*t++='E';
			*t++='+';
			stack<int> p;
			while (nn!=0){
				p.push(nn%10);
				nn=nn/10;
			}
			int p_size=p.size();
			for (int i=0; i<p_size; i++){
				*t++=48+p.top();
				p.pop();
			}
		}
		else if(nn<0){
			*t++='E';
			*t++='-';
			stack<int> p;
			nn=-nn;
			while (nn!=0){
				p.push(nn%10);
				nn=nn/10;
			}
			int p_size=p.size();
			for (int i=0; i<p_size; i++){
				*t++=48+p.top();
				p.pop();
			}
		}
		*t='\0';
	}
	mpfr_set_default_rounding_mode(default_rnd);
	return(s);
}


char* str(char *s, mp_st& a)
{
	return(a.str(s));
}

//////////////////////////////////////////////////////////



//****f* SAM_str/strp
//    NAME
//     strp
//
//    SYNOPSIS
//      char* strp(mp_st&)
//    FUNCTION
//      The output string contains the scientific notation of the 
//      stochastic argument; only the exact significant digits appear 
//      in the string. The strp function must be used only with
//      the family of printf functions. The only restriction is that
//      it is not possible to have more than 256 calls to the strp
//      function in one call to the printf function.
//    INPUTS
//      The strp function has a stochastic argument.  
//    RESULT
//      It returns a string.
//    SEE ALSO
//      str(3)
//*****
//   You can use this space for remarks that should not be included
//   in the documentation.
//    EXAMPLE
//      
//  
//    NOTES
//  
//  
//    BUGS
//  
//  
//      
//      
//  /

char* strp(const mp_st& a)
{
	char *s;
	
	s=chstr[numstr];
	if ((++numstr) == MAXCHAINE)  numstr=0; 
	return a.str(s);
}


