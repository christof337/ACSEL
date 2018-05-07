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

extern int nbre_trace_SAM;
extern int nbre_stability_count;

int  _SAM_max_instability;
int  _SAM_instability_detected;

extern FILE *unit_stability;

//
//
//=====================================================
//	"INSTABILITY" function
//=====================================================
//
//

//****f* SAM_unstab/instability
//    NAME
//     instability
//
//    SYNOPSIS
//      void  instability(unsigned long *unstab)
//    FUNCTION
//      It is an internal subroutine of the SAM library. It manages 
//      the different kinds of instabilities detected by SAM.
//    INPUTS
//      An unsigned long integer which indicates the kind of instability 
//      that has been detected.
//    RESULT
//    
//    SEE ALSO
//*****
//   You can use this space for remarks that should not be included
//   in the documentation.
//    EXAMPLE
//      
//  
//    NOTES
//      This function is called exclusively when an instability has been 
//      detected. Therefore, under a symbolic debugger like gdb, one has
//      only to put a breakoint at this function to stop the run each
//      time an instability occurs. 
//  
//    BUGS
//  
//  
//      
//      
//  /

void instability(unsigned long *unstab)
{ 
	(*unstab)++;
	_SAM_instability_detected++;
	if (_SAM_max_instability<0) return;    
	if (_SAM_instability_detected==_SAM_max_instability) {
		_SAM_div_tag=0; 
		_SAM_mul_tag=0;  
		_SAM_math_tag=0; 
		_SAM_intrinsic_tag=0; 
		_SAM_cancel_tag=0; 
		_SAM_branching_tag=0;
		
		_SAM_div_change=1; 
		_SAM_mul_change=1;  
		_SAM_power_change=1;  
		_SAM_branching_change=1;
		_SAM_cancel_change=1; 
		_SAM_intrinsic_change=1; 
		_SAM_math_change=1;
		
		_SAM_max_instability=-2;
		
		
	}
} 




