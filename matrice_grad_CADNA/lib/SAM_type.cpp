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
///////////////////////////////////////////////////

#include <iostream>
#include <stdlib.h>
#include "SAM.h"
#include "SAM_private.h"

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

int nb_stability_count = 0;

using namespace std;

//=====================================================
//   "SAM_INIT"
//=====================================================

//  global variables

unsigned long _SAM_div_count;
unsigned long _SAM_mul_count;  
unsigned long _SAM_power_count;  
unsigned long _SAM_branching_count; 
unsigned long _SAM_cancel_count;  
unsigned long _SAM_intrinsic_count;  
unsigned long _SAM_math_count; 

unsigned int _SAM_div_tag=1; 
unsigned int _SAM_mul_tag=1;  
unsigned int _SAM_power_tag=1;  
unsigned int _SAM_branching_tag=1;
unsigned int _SAM_cancel_tag=1; 
unsigned int _SAM_intrinsic_tag=1; 
unsigned int _SAM_math_tag=1; 

unsigned int _SAM_div_change=0; 
unsigned int _SAM_mul_change=0;  
unsigned int _SAM_power_change=0;  
unsigned int _SAM_branching_change=0;
unsigned int _SAM_cancel_change=0; 
unsigned int _SAM_intrinsic_change=0; 
unsigned int _SAM_math_change=0; 


int _SAM_cancel_value = 4;

const char* _SAM_div_err_msg       = "UNSTABLE DIVISION(S)";
const char* _SAM_mul_err_msg       = "UNSTABLE MULTIPLICATION(S)";
const char* _SAM_power_err_msg     = "UNSTABLE POWER FUNCTION(S)";
const char* _SAM_branching_err_msg = "UNSTABLE BRANCHING(S)";
const char* _SAM_cancel_err_msg    = "LOSS OF ACCURACY DUE TO CANCELLATION(S)";
const char* _SAM_intrinsic_err_msg = "UNSTABLE INTRINSIC FUNCTION(S)";
const char* _SAM_math_err_msg      = "UNSTABLE MATHEMATICAL FUNCTION(S)";

//****f* SAM_type/SAM_init
//    NAME
//     SAM_init
//
//    SYNOPSIS
//      void SAM_init(int max_nb_instability, unsigned int precision)  
//      void SAM_init(int max_nb_instability, unsigned int tag, unsigned int precision)   
//      void SAM_init(int max_instability, unsigned int tag, unsigned int seed, 
//                      unsigned int cancellation, unsigned int precision)  
//
//    FUNCTION
//     The SAM_init function initializes the SAM library
//     (see documentation).
//      
//    INPUTS
//   
//    RESULT

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


void  SAM_init(int max_nb_instability,unsigned int precision) 
{
	SAM_init(max_nb_instability,0,51,_SAM_cancel_value,precision);
}

void  SAM_init(int max_nb_instability,unsigned int tag, unsigned int precision) 
{
	SAM_init(max_nb_instability,tag,51,_SAM_cancel_value,precision);
}


void  SAM_init(int max_instability, unsigned int tag, unsigned int seed, unsigned int cancellation, unsigned int precision)
{
	
	_SAM_cancel_value=cancellation;
	
	_SAM_init_table(seed);
	
	_SAM_max_instability=max_instability;
	_SAM_instability_detected=0;
	
	_SAM_div_count=0;
	_SAM_mul_count=0;  
	_SAM_power_count=0;  
	_SAM_math_count=0; 
	_SAM_intrinsic_count=0;  
	_SAM_cancel_count=0;  
	_SAM_branching_count=0; 
	
	if ( !  max_instability ){
		_SAM_div_change=1; 
		_SAM_mul_change=1;  
		_SAM_power_change=1;  
		_SAM_branching_change=1;
		_SAM_cancel_change=1; 
		_SAM_intrinsic_change=1; 
		_SAM_math_change=1;
		_SAM_div_tag=0; 
		_SAM_mul_tag=0;  
		_SAM_power_tag=0;  
		_SAM_branching_tag=0;
		_SAM_cancel_tag=0; 
		_SAM_intrinsic_tag=0; 
		_SAM_math_tag=0; 
	}
	else {
		if ((tag & SAM_DIV) || ! max_instability)  {
			_SAM_div_tag=0; 
			_SAM_div_change=1; 
		}
		if ((tag & SAM_MUL) || ! max_instability)  {
			_SAM_mul_tag=0; 
			_SAM_mul_change=1; 
		}
		if ((tag & SAM_POWER) || ! max_instability)  {
			_SAM_power_tag=0; 
			_SAM_power_change=1; 
		}
		if ((tag & SAM_MATH) || ! max_instability)  {
			_SAM_math_tag=0; 
			_SAM_math_change=1; 
		}
		if ((tag & SAM_INTRINSIC) || ! max_instability) {
			_SAM_intrinsic_tag=0; 
			_SAM_intrinsic_change=1; 
		}
		if ((tag & SAM_CANCEL) ||  ! max_instability) {
			_SAM_cancel_tag=0; 
			_SAM_cancel_change=1; 
		}
		if ((tag & SAM_BRANCHING) || ! max_instability) {
			_SAM_branching_tag=0; 
			_SAM_branching_change=1; 
		}
	}
	
	cout << "----------------------------------------------------------------" << endl;
    
	cout << "SAM software" << endl;
	if (_SAM_div_tag & _SAM_mul_tag & _SAM_power_tag) 
		cout << "Self-validation detection: ON" << endl;
	else     cout << "Self-validation detection: OFF" << endl;
	//cout << "Self-validation detection: ON" << endl;
	cout << "Mathematical instabilities detection: " <<  (_SAM_math_tag ? "ON": "OFF") << endl;
	cout << "Branching instabilities detection: " << (_SAM_branching_tag ? "ON": "OFF") << endl;
	cout << "Intrinsic instabilities detection: " << (_SAM_intrinsic_tag ? "ON": "OFF") << endl;
	cout << "Cancellation instabilities detection: " << (_SAM_cancel_tag ? "ON": "OFF") << endl;
	cout << "----------------------------------------------------------------" << endl;
	mpfr_set_default_rounding_mode (MPFR_RNDD);
	mpfr_set_default_prec(precision);
}


//****f* SAM_type/SAM_end
//    NAME
//      SAM_end
//
//    SYNOPSIS
//      void SAM_end()
//    FUNCTION
//      The SAM_end function "closes" the SAM library
//      (see documentation).
//    INPUTS
//      no input parameter  
//    RESULT
//      void
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

void SAM_end()
{
	unsigned long long sum;
	
	cout << "----------------------------------------------------------------" << endl;
	cout << "SAM software" << endl;
	sum= _SAM_div_count+_SAM_mul_count+_SAM_math_count+
    _SAM_intrinsic_count+_SAM_cancel_count+_SAM_branching_count+_SAM_power_count;

	if (!sum) cout << "No instability detected" << endl;
	else {
		if (_SAM_div_count+_SAM_mul_count+_SAM_power_count){
			cout << endl;
			cout << "CRITICAL WARNING: the self-validation detects major problem(s)." << endl;
			cout << "The results are NOT guaranteed." << endl ;
			cout << endl;
		}
		else if (_SAM_div_change || _SAM_mul_change || _SAM_power_change){
			cout << endl;
			cout << "BE CAREFUL: the self-validation has been deactivated." << endl;
			cout << "The results are NOT guaranteed." << endl ;
			cout << endl;
		}
		
		
		if (sum==1) cout << "There is  1 numerical instability" << endl;
		else cout << "There are " << sum << " numerical instabilities" << endl;
		
		if  (_SAM_div_tag && _SAM_div_count) 
			cout <<  _SAM_div_count << " " <<  _SAM_div_err_msg << endl;
		if  (_SAM_mul_tag && _SAM_mul_count) 
			cout <<  _SAM_mul_count << " " <<  _SAM_mul_err_msg << endl;
		if  (_SAM_power_tag && _SAM_power_count) 
			cout <<  _SAM_power_count << " " <<  _SAM_power_err_msg << endl;
		if  (_SAM_branching_tag && _SAM_branching_count) 
			cout <<  _SAM_branching_count << " " <<  _SAM_branching_err_msg << endl;
		if (_SAM_intrinsic_tag && _SAM_intrinsic_count) 
			cout <<  _SAM_intrinsic_count << " " <<  _SAM_intrinsic_err_msg << endl;
		if  (_SAM_math_tag && _SAM_math_count) 
			cout <<  _SAM_math_count << " " <<  _SAM_math_err_msg << endl;
		if  (_SAM_cancel_tag && _SAM_cancel_count) 
			cout <<  _SAM_cancel_count << " " <<  _SAM_cancel_err_msg << endl;
	}
	cout << "----------------------------------------------------------------" << endl;
	
}

//****f* SAM_type/SAM_enable
//    NAME
//     SAM_enable
//
//    SYNOPSIS
//      void SAM_enable(unsigned int tag)
//    FUNCTION
//      The SAM_enable function enables the detection of a kind of
//      numerical instability.
//    INPUTS
//      unsigned int tag (see documentation)
//    RESULT
//      
//    SEE ALSO
//        SAM_disable(3)
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



void SAM_enable(unsigned int tag)
{
	if (_SAM_max_instability==-2) {
		cerr << "-----------------------------------------------------------" << endl;
		cerr << " SAM: The maximum number of instabilities has been reached" << endl;
		cerr << " The SAM_select_instability is not performed"    << endl;
		cerr << "-----------------------------------------------------------" << endl;
	}
	
	if (tag & SAM_DIV)  { 
		if (!_SAM_div_tag) _SAM_div_change=1;
		_SAM_div_tag=1;
	}
	
	if (tag & SAM_MUL)  { 
		if (!_SAM_mul_tag) _SAM_mul_change=1;
		_SAM_mul_tag=1;
	}
	
	if (tag & SAM_POWER)  { 
		if (!_SAM_power_tag) _SAM_power_change=1;
		_SAM_power_tag=1;
	}
	
	if (tag & SAM_BRANCHING){ 
		if (!_SAM_branching_tag) _SAM_branching_change=1;
		_SAM_branching_tag=1;
	}
	
	if (tag & SAM_CANCEL){ 
		if (!_SAM_cancel_tag) _SAM_cancel_change=1;
		_SAM_cancel_tag=1;
	}
	
	if (tag & SAM_INTRINSIC){ 
		if (!_SAM_intrinsic_tag) _SAM_intrinsic_change=1;
		_SAM_intrinsic_tag=1;
	}
	
	if (tag & SAM_MATH){ 
		if (!_SAM_math_tag) _SAM_math_change=1;
		_SAM_math_tag=1;
	}
}



//****f* SAM_type/SAM_disable
//    NAME
//     SAM_disable
//
//    SYNOPSIS
//      void SAM_disable(unsigned int tag)
//    FUNCTION
//      The SAM_disable function disables the detection of a kind of
//      numerical instability.
//    INPUTS
//      unsigned int tag (see documentation)
//    RESULT
//    
//    SEE ALSO
//      SAM_enable(3)
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


void SAM_disable(unsigned int tag)
{
	if (tag & SAM_DIV){ 
		if (_SAM_div_tag) _SAM_div_change=1;
		_SAM_div_tag=0;
	}
	
	if (tag & SAM_MUL){ 
		if (_SAM_mul_tag) _SAM_mul_change=1;
		_SAM_mul_tag=0;
	}
	
	if (tag & SAM_POWER){ 
		if (_SAM_power_tag) _SAM_power_change=1;
		_SAM_power_tag=0;
	}
	
	if (tag & SAM_BRANCHING){ 
		if (_SAM_branching_tag) _SAM_branching_change=1;
		_SAM_branching_tag=0;
	}
	
	if (tag & SAM_CANCEL){ 
		if (_SAM_cancel_tag) _SAM_cancel_change=1;
		_SAM_cancel_tag=0;
	}
	
	if (tag & SAM_INTRINSIC){ 
		if (_SAM_intrinsic_tag) _SAM_intrinsic_change=1;
		_SAM_intrinsic_tag=0;
	}
	
	if (tag & SAM_MATH){ 
		if (_SAM_math_tag) _SAM_math_change=1;
		_SAM_math_tag=0;
	}
}


//****f* SAM_type/self_validation_only
//    NAME
//     self_validation_only
//
//    SYNOPSIS
//      void self_validation_only()
//    FUNCTION
//      The self_validation_only function enables the detection of 
//      the multiplication instability, the division instability 
//      and the power instability. It disables the others.
//    INPUTS
//     
//    RESULT
//    
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

void self_validation_only(){
	
	SAM_disable(SAM_BRANCHING);
	SAM_disable(SAM_CANCEL);
	SAM_disable(SAM_INTRINSIC);
	SAM_disable(SAM_MATH);
	
	SAM_enable(SAM_MUL);
	SAM_enable(SAM_DIV);
	SAM_enable(SAM_POWER);
	
	cout << endl;
	cout << "BE CAREFUL: the self-validation has been activated." << endl;
	
}




