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
#ifndef __SAM__
#define __SAM__

#include <iostream>
#include <stdio.h>
#include <cmath>
#include <time.h>
#include <stdint.h>
//extern "C" {
	#include "gmp.h"
	#include "mpfr.h"
//}

#define SAM_DIV       0x1
#define SAM_MUL       0x2
#define SAM_POWER     0x4
#define SAM_MATH      0x8
#define SAM_BRANCHING 0x10
#define SAM_INTRINSIC 0x20
#define SAM_CANCEL    0x40
#define SAM_ALL       0xFFFFFFFF

#define LOG log10(2)
#define DEFAULT_PREC mpfr_get_default_prec()
#define DIGIT_NOT_COMPUTED -1

using namespace std;

class mp_st 
{
	
protected:
	mpfr_t x,y,z;  
	typedef mpfr_t TYPEBASE;
	
	
private:
	mutable int accuracy;
	
public:
	
	// Constructors

	inline mp_st() 
	{ 
		
		mp_prec_t default_prec = mpfr_get_default_prec();
		mpfr_init2 (x,default_prec); 
		mpfr_set_ui (x,0,MPFR_RNDN);
		mpfr_init2 (y,default_prec); 
		mpfr_set_ui (y,0,MPFR_RNDN);
		mpfr_init2 (z,default_prec); 
		mpfr_set_ui (z,0,MPFR_RNDN);
		accuracy = DIGIT_NOT_COMPUTED;
	}
	
	inline mp_st(const mp_st& u)
	{   
		
		mp_prec_t default_prec = mpfr_get_default_prec();
		mpfr_init2 (x, default_prec);
		mpfr_set (x, u.x, MPFR_RNDN);
		mpfr_init2 (y, default_prec);
		mpfr_set (y, u.y, MPFR_RNDN);
		mpfr_init2 (z, default_prec);
		mpfr_set (z, u.z, MPFR_RNDN);
		accuracy = DIGIT_NOT_COMPUTED;
	}
	
	inline mp_st(const mpfr_t u)
	{
		
		mp_prec_t default_prec = mpfr_get_default_prec();
		mpfr_init2 (x, default_prec); 
		mpfr_set (x, u, MPFR_RNDN);
		mpfr_init2 (y, default_prec); 
		mpfr_set (y, u, MPFR_RNDN);
		mpfr_init2 (z, default_prec); 
		mpfr_set (z, u, MPFR_RNDN);
		accuracy = DIGIT_NOT_COMPUTED;
	}
	
	inline mp_st(const double u)
	{
		
		mp_prec_t default_prec = mpfr_get_default_prec();
		
		mpfr_init2(x,default_prec);
		mpfr_set_d(x,u,MPFR_RNDN);
		mpfr_init2(y,default_prec);
		mpfr_set_d(y,u,MPFR_RNDN);
		mpfr_init2(z,default_prec);
		mpfr_set_d(z,u,MPFR_RNDN);
		accuracy = DIGIT_NOT_COMPUTED;
	}
	
	inline mp_st(const float u)
	{
		
		mp_prec_t default_prec = mpfr_get_default_prec();
		
		mpfr_init2(x,default_prec);
		mpfr_set_d(x,u,MPFR_RNDN);
		mpfr_init2(y,default_prec);
		mpfr_set_d(y,u,MPFR_RNDN);
		mpfr_init2(z,default_prec);
		mpfr_set_d(z,u,MPFR_RNDN);
		accuracy = DIGIT_NOT_COMPUTED;
	}
	
	
	inline mp_st(const unsigned long u)
	{
		
		mp_prec_t default_prec = mpfr_get_default_prec();
		mpfr_init2(x,default_prec);
		mpfr_set_ui(x,u,MPFR_RNDN);
		mpfr_init2(y,default_prec);
		mpfr_set_ui(y,u,MPFR_RNDN);
		mpfr_init2(z,default_prec);
		mpfr_set_ui(z,u,MPFR_RNDN);
		accuracy = DIGIT_NOT_COMPUTED; 
	}
	
	inline mp_st(const long u)
	{
		
		mp_prec_t default_prec = mpfr_get_default_prec();
		mpfr_init2(x,default_prec);
		mpfr_set_si(x,u,MPFR_RNDN);
		mpfr_init2(y,default_prec);
		mpfr_set_si(y,u,MPFR_RNDN);
		mpfr_init2(z,default_prec);
		mpfr_set_si(z,u,MPFR_RNDN);
		accuracy = DIGIT_NOT_COMPUTED; 
	}
	
	inline mp_st(const unsigned int u)
	{
		//mp_rnd_t default_rnd =mpfr_get_default_rounding_mode();
		mp_prec_t default_prec = mpfr_get_default_prec();
		mpfr_init2(x,default_prec);
		mpfr_set_ui(x,u,MPFR_RNDN);
		mpfr_init2(y,default_prec);
		mpfr_set_ui(y,u,MPFR_RNDN);
		mpfr_init2(z,default_prec);
		mpfr_set_ui(z,u,MPFR_RNDN);
		accuracy = DIGIT_NOT_COMPUTED; 
	}
	
	inline mp_st(const int u)
	{
		
		mp_prec_t default_prec = mpfr_get_default_prec();
		mpfr_init2(x,default_prec);
		mpfr_set_si(x,u,MPFR_RNDN);
		mpfr_init2(y,default_prec);
		mpfr_set_si(y,u,MPFR_RNDN);
		mpfr_init2(z,default_prec);
		mpfr_set_si(z,u,MPFR_RNDN); 
		accuracy = DIGIT_NOT_COMPUTED;
	}
	
	inline ~mp_st() 
	{ 
		mpfr_clear(x);
		mpfr_clear(y);
		mpfr_clear(z);	 
	} 
	
  
	// ASSIGNMENT
	
	mp_st& operator=(const mp_st&);
	mp_st& operator=(const mpfr_t&);
	mp_st& operator=(const double&);
	mp_st& operator=(const float&);
	mp_st& operator=(const unsigned long long&);
	mp_st& operator=(const long long&);
	mp_st& operator=(const unsigned long&);
	mp_st& operator=(const long&);
	mp_st& operator=(const unsigned int&);
	mp_st& operator=(const int&);
	mp_st& operator=(const unsigned short&);
	mp_st& operator=(const short&);
	mp_st& operator=(const unsigned char&);
	mp_st& operator=(const char&);
	friend mp_st sam_set_str(mp_st &x, const char *s);

	// ADDITION
	
	mp_st operator+() const; 
	mp_st operator++();
	mp_st operator++(int);
	
	mp_st& operator+=(const mp_st&);
	mp_st& operator+=(const mpfr_t&);
	mp_st& operator+=(const double&);
	mp_st& operator+=(const float&);
	mp_st& operator+=(const unsigned long&);
	mp_st& operator+=(const long&);
	mp_st& operator+=(const unsigned int&);
	mp_st& operator+=(const int&);
	
	friend mp_st operator+(const mp_st&, const mp_st&);
	
    friend mp_st operator+(const mp_st&, const mpfr_t&);
	friend mp_st operator+(const mp_st&, const float&);
	friend mp_st operator+(const mp_st&, const double&);
	friend mp_st operator+(const mp_st&, const unsigned long&);
	friend mp_st operator+(const mp_st&, const long&);
	friend mp_st operator+(const mp_st&, const unsigned int&);
	friend mp_st operator+(const mp_st&, const int&);
	
	friend mp_st operator+(const mpfr_t&, const mp_st&);	
	friend mp_st operator+(const float&, const mp_st&);
	friend mp_st operator+(const double&, const mp_st&);
	friend mp_st operator+(const unsigned long&, const mp_st&);
	friend mp_st operator+(const long&, const mp_st&);
	friend mp_st operator+(const unsigned int&, const mp_st&);
	friend mp_st operator+(const int&, const mp_st&);
	
	
	// SUBTRACTION
	
	mp_st operator--();
	mp_st operator--(int);
	mp_st operator-() const ; 
	
	mp_st& operator-=(const mp_st&);                                         
	mp_st& operator-=(const mpfr_t&);
	mp_st& operator-=(const double&);
	mp_st& operator-=(const float&);
	mp_st& operator-=(const unsigned long&);
	mp_st& operator-=(const long&);
	mp_st& operator-=(const unsigned int&);
	mp_st& operator-=(const int&);
	
	
	friend mp_st operator-(const mp_st&, const mp_st&);
    
	friend mp_st operator-(const mp_st&, const mpfr_t&);                                                                    
	friend mp_st operator-(const mp_st&, const double&);
	friend mp_st operator-(const mp_st&, const float&);
	friend mp_st operator-(const mp_st&, const unsigned long&);
	friend mp_st operator-(const mp_st&, const long&);
	friend mp_st operator-(const mp_st&, const unsigned int&);
	friend mp_st operator-(const mp_st&, const int&);
	
	friend mp_st operator-(const mpfr_t&, const mp_st&);
	friend mp_st operator-(const double&, const mp_st&);
	friend mp_st operator-(const float&, const mp_st&);
	friend mp_st operator-(const unsigned long&, const mp_st&);
	friend mp_st operator-(const long&, const mp_st&);
	friend mp_st operator-(const unsigned int&, const mp_st&);
	friend mp_st operator-(const int&, const mp_st&);
	
	
	// MULTIPLICATION
	
	mp_st& operator*=(const mp_st&);
	mp_st& operator*=(const mpfr_t&);
	mp_st& operator*=(const double&);
	mp_st& operator*=(const float&);
	mp_st& operator*=(const unsigned long&);
	mp_st& operator*=(const long&);
	mp_st& operator*=(const unsigned int&);
	mp_st& operator*=(const int&);
	
	friend mp_st operator*(const mp_st&, const mp_st&);    
	
	friend mp_st operator*(const mp_st&, const mpfr_t&);
	friend mp_st operator*(const mp_st&, const double&);
	friend mp_st operator*(const mp_st&, const float&);
	friend mp_st operator*(const mp_st&, const unsigned long&);
	friend mp_st operator*(const mp_st&, const long&);
	friend mp_st operator*(const mp_st&, const unsigned int&);
	friend mp_st operator*(const mp_st&, const int&);
	
	friend mp_st operator*(const mpfr_t&, const mp_st&);
	friend mp_st operator*(const double&, const mp_st&);
	friend mp_st operator*(const float&, const mp_st&);
	friend mp_st operator*(const unsigned long&, const mp_st&);
	friend mp_st operator*(const long&, const mp_st&);
	friend mp_st operator*(const unsigned int&, const mp_st&);
	friend mp_st operator*(const int&, const mp_st&);
	
	
	// DIVISION
	
	mp_st& operator/=(const mp_st&);
	mp_st& operator/=(const mpfr_t&);
	mp_st& operator/=(const double&);
	mp_st& operator/=(const float&);
	mp_st& operator/=(const unsigned long&);
	mp_st& operator/=(const long&);
	mp_st& operator/=(const unsigned int&);
	mp_st& operator/=(const int&);
	
	friend mp_st operator/(const mp_st&, const mp_st&);
    
	friend mp_st operator/(const mp_st&, const mpfr_t&);   
	friend mp_st operator/(const mp_st&, const double&);
	friend mp_st operator/(const mp_st&, const float&);
	friend mp_st operator/(const mp_st&, const unsigned long&);
	friend mp_st operator/(const mp_st&, const long&);
	friend mp_st operator/(const mp_st&, const unsigned int&);
	friend mp_st operator/(const mp_st&, const int&);
	
	friend mp_st operator/(const mpfr_t&, const mp_st&);
	friend mp_st operator/(const double&, const mp_st&);
	friend mp_st operator/(const float&, const mp_st&);
	friend mp_st operator/(const unsigned long&, const mp_st&);
	friend mp_st operator/(const long&, const mp_st&);
	friend mp_st operator/(const unsigned int&, const mp_st&);
	friend mp_st operator/(const int&, const mp_st&);
	
	
	// RELATIONAL OPERATORS
	
	friend int operator==(const mp_st&, const mp_st&);    
	
	friend int operator==(const mp_st&, const mpfr_t&);
	friend int operator==(const mp_st&, const double&);
	friend int operator==(const mp_st&, const float&);
	friend int operator==(const mp_st&, const unsigned long&);
	friend int operator==(const mp_st&, const long&);
	friend int operator==(const mp_st&, const unsigned int&);
	friend int operator==(const mp_st&, const int&);
	
	friend int operator==(const mpfr_t&, const mp_st&);
	friend int operator==(const double&, const mp_st&);
	friend int operator==(const float&, const mp_st&);
	friend int operator==(const unsigned long&, const mp_st&);
	friend int operator==(const long&, const mp_st&);
	friend int operator==(const unsigned int&, const mp_st&);
	friend int operator==(const int&, const mp_st&);
	
	
	friend int operator!=(const mp_st&, const mp_st&);    
	
	friend int operator!=(const mp_st&, const mpfr_t&);
	friend int operator!=(const mp_st&, const double&);
	friend int operator!=(const mp_st&, const float&);
	friend int operator!=(const mp_st&, const unsigned long&);
	friend int operator!=(const mp_st&, const long&);
	friend int operator!=(const mp_st&, const unsigned int&);
	friend int operator!=(const mp_st&, const int&);
	
	friend int operator!=(const mpfr_t&, const mp_st&);
	friend int operator!=(const double&, const mp_st&);
	friend int operator!=(const float&, const mp_st&);
	friend int operator!=(const unsigned long&, const mp_st&);
	friend int operator!=(const long&, const mp_st&);
	friend int operator!=(const unsigned int&, const mp_st&);
	friend int operator!=(const int&, const mp_st&);
	
	
	friend int operator>=(const mp_st&, const mp_st&);    
	
	friend int operator>=(const mp_st&, const mpfr_t&);
	friend int operator>=(const mp_st&, const double&);
	friend int operator>=(const mp_st&, const float&);
	friend int operator>=(const mp_st&, const unsigned long&);
	friend int operator>=(const mp_st&, const long&);
	friend int operator>=(const mp_st&, const unsigned int&);
	friend int operator>=(const mp_st&, const int&);
	
	friend int operator>=(const mpfr_t&, const mp_st&);
	friend int operator>=(const double&, const mp_st&);
	friend int operator>=(const float&, const mp_st&);
	friend int operator>=(const unsigned long&, const mp_st&);
	friend int operator>=(const long&, const mp_st&);
	friend int operator>=(const unsigned int&, const mp_st&);
	friend int operator>=(const int&, const mp_st&);
	
	
	friend int operator>(const mp_st&, const mp_st&);    
	
	friend int operator>(const mp_st&, const mpfr_t&);
	friend int operator>(const mp_st&, const double&);
	friend int operator>(const mp_st&, const float&);
	friend int operator>(const mp_st&, const unsigned long&);
	friend int operator>(const mp_st&, const long&);
	friend int operator>(const mp_st&, const unsigned int&);
	friend int operator>(const mp_st&, const int&);
	
	friend int operator>(const mpfr_t&, const mp_st&);
	friend int operator>(const double&, const mp_st&);
	friend int operator>(const float&, const mp_st&);
	friend int operator>(const unsigned long&, const mp_st&);
	friend int operator>(const long&, const mp_st&);
	friend int operator>(const unsigned int&, const mp_st&);
	friend int operator>(const int&, const mp_st&);
	
	
	friend int operator<=(const mp_st&, const mp_st&);    
	
	friend int operator<=(const mp_st&, const mpfr_t&);
	friend int operator<=(const mp_st&, const double&);
	friend int operator<=(const mp_st&, const float&);
	friend int operator<=(const mp_st&, const unsigned long&);
	friend int operator<=(const mp_st&, const long&);
	friend int operator<=(const mp_st&, const unsigned int&);
	friend int operator<=(const mp_st&, const int&);
	
	friend int operator<=(const mpfr_t&, const mp_st&);
	friend int operator<=(const double&, const mp_st&);
	friend int operator<=(const float&, const mp_st&);
	friend int operator<=(const unsigned long&, const mp_st&);
	friend int operator<=(const long&, const mp_st&);
	friend int operator<=(const unsigned int&, const mp_st&);
	friend int operator<=(const int&, const mp_st&);
	
	
	friend int operator<(const mp_st&, const mp_st&);    
	
	friend int operator<(const mp_st&, const mpfr_t&);
	friend int operator<(const mp_st&, const double&);
	friend int operator<(const mp_st&, const float&);
	friend int operator<(const mp_st&, const unsigned long&);
	friend int operator<(const mp_st&, const long&);
	friend int operator<(const mp_st&, const unsigned int&);
	friend int operator<(const mp_st&, const int&);
	
	friend int operator<(const mpfr_t&, const mp_st&);
	friend int operator<(const double&, const mp_st&);
	friend int operator<(const float&, const mp_st&);
	friend int operator<(const unsigned long&, const mp_st&);
	friend int operator<(const long&, const mp_st&);
	friend int operator<(const unsigned int&, const mp_st&);
	friend int operator<(const int&, const mp_st&);
	
	
	// MATHEMATICAL FUNCTIONS 
	
	friend mp_st  log(const mp_st&);
	friend mp_st  log2(const mp_st&);
	friend mp_st  log10(const mp_st&);
	friend mp_st  log1p(const mp_st&);
	friend mp_st  exp(const mp_st&); 
	friend mp_st  exp2(const mp_st&); 
	friend mp_st  expm1(const mp_st&); 
	friend mp_st  sqrt(const mp_st&);
	friend mp_st  cbrt(const mp_st&);
	friend mp_st  sin(const mp_st&);
	friend mp_st  cos(const mp_st&);
	friend mp_st  tan(const mp_st&);
	friend mp_st  asin(const mp_st&);
	friend mp_st  acos(const mp_st&);
	friend mp_st  atan(const mp_st&);
	friend mp_st  atan2(const mp_st&, const mp_st&);
	friend mp_st  sinh(const mp_st&);
	friend mp_st  cosh(const mp_st&);
	friend mp_st  tanh(const mp_st&);
	friend mp_st  asinh(const mp_st&);
	friend mp_st  acosh(const mp_st&);
	friend mp_st  atanh(const mp_st&);
	friend mp_st  hypot(const mp_st&, const mp_st&);
	
	
	friend mp_st pow(const mp_st&, const mp_st&);  
	
	friend mp_st pow(const mp_st&, const mpfr_t&);    
	friend mp_st pow(const mp_st&, const double&);
	friend mp_st pow(const mp_st&, const float&);
	friend mp_st pow(const mp_st&, const unsigned long&);
	friend mp_st pow(const mp_st&, const long&);
	friend mp_st pow(const mp_st&, const unsigned int&);
	friend mp_st pow(const mp_st&, const int&);
	
	friend mp_st pow(const mpfr_t&, const mp_st&);
	friend mp_st pow(const double&, const mp_st&);
	friend mp_st pow(const float&, const mp_st&);
	friend mp_st pow(const unsigned long&, const mp_st&);
	friend mp_st pow(const long&, const mp_st&);
	friend mp_st pow(const unsigned int&, const mp_st&);
	friend mp_st pow(const int&, const mp_st&);
	
	
	friend mp_st fmax(const mp_st&, const mp_st&);  
	
	friend mp_st fmax(const mp_st&, const mpfr_t&);
	friend mp_st fmax(const mp_st&, const double&);
	friend mp_st fmax(const mp_st&, const float&);;
	friend mp_st fmax(const mp_st&, const unsigned long&);
	friend mp_st fmax(const mp_st&, const long&);
	friend mp_st fmax(const mp_st&, const unsigned int&);
	friend mp_st fmax(const mp_st&, const int&);
	
	friend mp_st fmax(const mpfr_t&, const mp_st&);
	friend mp_st fmax(const double&, const mp_st&);
	friend mp_st fmax(const float&, const mp_st&);
	friend mp_st fmax(const unsigned long&, const mp_st&);
	friend mp_st fmax(const long&, const mp_st&);
	friend mp_st fmax(const unsigned int&, const mp_st&);
	friend mp_st fmax(const int&, const mp_st&);
	
	
	friend mp_st fmin(const mp_st&, const mp_st&);   
	
	friend mp_st fmin(const mp_st&, const mpfr_t&);
	friend mp_st fmin(const mp_st&, const double&);
	friend mp_st fmin(const mp_st&, const float&);
	friend mp_st fmin(const mp_st&, const unsigned long&);
	friend mp_st fmin(const mp_st&, const long&);
	friend mp_st fmin(const mp_st&, const unsigned int&);
	friend mp_st fmin(const mp_st&, const int&);
	
	friend mp_st fmin(const mpfr_t&, const mp_st&);
	friend mp_st fmin(const double&, const mp_st&);
	friend mp_st fmin(const float&, const mp_st&);
	friend mp_st fmin(const unsigned long&, const mp_st&);
	friend mp_st fmin(const long&, const mp_st&);
	friend mp_st fmin(const unsigned int&, const mp_st&);
	friend mp_st fmin(const int&, const mp_st&);
	
	
	// INTRINSIC FUNCTIONS
	
	friend mp_st fabs(const mp_st&);
	friend mp_st floor(const mp_st&);
	friend mp_st ceil(const mp_st&);
	friend mp_st trunc(const mp_st&);
	friend mp_st nearbyint(const mp_st&);
	friend mp_st rint(const mp_st&);
	friend long int  lrint(const mp_st&);
	friend long long int llrint(const mp_st&);
	
	
	// Conversion
	 
	operator int();  
	operator unsigned int();  
	operator long();  
	operator unsigned long();  
	operator float();
	operator double();
	
	
	int nb_significant_digit() const;  
	int computedzero() const;
	void display() const ; 
	void display(const char *) const ; 
	char* str( char *)  const ;
	
	friend char* strp(const mp_st&);
	friend char* str( char *, const mp_st&);
	
	friend std::istream& operator >>(std::istream& s, mp_st& );  
	
	void data_st();
	void data_st(const double&, const int&);
	
	inline int getAccuracy(){
		return accuracy;
	}
};


void  SAM_init(int, unsigned int, unsigned int, unsigned int,unsigned int);
void  SAM_init(int, unsigned int,unsigned int);
void  SAM_init(int, unsigned int);
void  SAM_end();

void self_validation_only();
void SAM_enable(unsigned int);
void SAM_disable(unsigned int);

std::ostream& operator<<(std::ostream&, const mp_st&);
std::istream& operator >>(std::istream&, mp_st& );

#endif











