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
//****m* SAM_to/operator=
//    NAME
//      operator=
//    SYNOPSIS
//      res = v
//    FUNCTION
//      Define all the functions involving at least one argument
//      of stochastic type which overload the assignment statement "=".
//      
//    INPUTS
//      a           - an integer, a float, a double, an mpfr_t or an mp_st 
//  
//    RESULT
//      res         - an mp_st
//             
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
//    SEE ALSO
//      
//      
//  /

#include "SAM.h"
#include "SAM_private.h"





mp_st& mp_st::operator=(const mp_st &v) 
{
	
    mpfr_set(x, v.x, MPFR_RNDN);
    mpfr_set(y, v.y, MPFR_RNDN);
    mpfr_set(z, v.z, MPFR_RNDN);
	
    accuracy=DIGIT_NOT_COMPUTED;
    return *this;
}

mp_st& mp_st::operator=(const mpfr_t &v) 
{ 
	
	mpfr_set(x, v, MPFR_RNDN);
    mpfr_set(y, v, MPFR_RNDN);
    mpfr_set(z, v, MPFR_RNDN);
	
    accuracy=DIGIT_NOT_COMPUTED;
    return *this;
}


mp_st& mp_st::operator=(const float &v)
{

    mpfr_set_d(x, v, MPFR_RNDN);
    mpfr_set_d(y, v, MPFR_RNDN);
    mpfr_set_d(z, v, MPFR_RNDN);
    accuracy=(int)(DEFAULT_PREC*LOG);
    return *this;
	
}

mp_st& mp_st::operator=(const double &v) 
{
	mpfr_set_d(x, v,MPFR_RNDN);
	mpfr_set_d(y, v, MPFR_RNDN);
    mpfr_set_d(z, v, MPFR_RNDN);
    accuracy=(int)(DEFAULT_PREC*LOG);
    return *this;
}

mp_st& mp_st::operator=(const unsigned long &v)
{
	mpfr_set_ui(x, v, MPFR_RNDN);
    mpfr_set_ui(y, v, MPFR_RNDN);
    mpfr_set_ui(z, v, MPFR_RNDN);
    accuracy=(int)(DEFAULT_PREC*LOG);
    return *this;
}

mp_st& mp_st::operator=(const long &v)
{
    mpfr_set_si(x, v, MPFR_RNDN);
    mpfr_set_si(y, v, MPFR_RNDN);
    mpfr_set_si(z, v, MPFR_RNDN);
    accuracy=(int)(DEFAULT_PREC*LOG);
    return *this;
}

mp_st& mp_st::operator=(const unsigned int &v)
{
    mpfr_set_ui(x, v, MPFR_RNDN);
    mpfr_set_ui(y, v, MPFR_RNDN);
    mpfr_set_ui(z, v, MPFR_RNDN);
    accuracy=(int)(DEFAULT_PREC*LOG); 
    return *this;
}

mp_st& mp_st::operator=(const int &v)
{
    mpfr_set_si(x, v, MPFR_RNDN);
    mpfr_set_si(y, v, MPFR_RNDN);
    mpfr_set_si(z, v, MPFR_RNDN);
    accuracy=(int)(DEFAULT_PREC*LOG); 
    return *this;
}

//****f* SAM_to/sam_set_str
//    NAME
//     sam_set_str
//
//    SYNOPSIS
//      mp_st sam_set_str(mp_st &v, const char *s)
//    FUNCTION
//      The sam_set_str function set v to the value of the string s in base 10, 
//      rounded in the direction MPFR_RNDN. 
//    INPUTS
//      v          - a stochastic number
//      s          - a string
//    RESULT
//      v          - a stochastic number

//    SEE ALSO
//    
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

mp_st sam_set_str(mp_st &v, const char *s)
{
	mpfr_t y;
	mpfr_init2(y,DEFAULT_PREC);
	mpfr_set_str(y,s,10,MPFR_RNDN);
		
	mpfr_set(v.x,y,MPFR_RNDN);
	mpfr_set(v.y,y,MPFR_RNDN);
	mpfr_set(v.z,y,MPFR_RNDN);
	
	return v;
	
}




