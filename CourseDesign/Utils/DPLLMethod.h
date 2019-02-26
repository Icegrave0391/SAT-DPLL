//
//  DPLLMethod.h
//  CourseDesign
//
//  Created by 张储祺 on 2019/2/19.
//  Copyright © 2019 icegrave0391. All rights reserved.
//

#ifndef DPLLMethod_h
#define DPLLMethod_h

#include <stdio.h>
#include "CNFClause.h"
#include "CNFFormula.h"

int DPLLWithFormula(formulaList fmList) ;
#pragma mark - WARNING !!! THESE METHOD SHOULD BE ONLY USED IN DPLL
void dealUnitClause(formulaList * fmlist, int * literalArr) ;
void dealNewUnitClause(formulaList * fmlist, int * literalArr, int literal) ;
int findLiteral() ;
#endif /* DPLLMethod_h */
