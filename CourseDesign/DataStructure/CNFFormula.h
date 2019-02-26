//
//  CNFFormula.h
//  CourseDesign
//
//  Created by 张储祺 on 2019/2/18.
//  Copyright © 2019 icegrave0391. All rights reserved.
//

#ifndef CNFFormula_h
#define CNFFormula_h
#include <stdio.h>
#include "CNFClause.h"
#include <stdlib.h>
#pragma mark - status
enum DeleteClauseStatus{
    DeleteClauseStatusNotFound = 0,
    DeleteClauseStatusSuccessful
};
typedef enum DeleteClauseStatus DeleteClauseStatus;
#pragma mark - structure
struct FormulaNode{
    clause clause ;
    struct FormulaNode * next ;
};
typedef struct FormulaNode * formulaList;

// Formula functions
int init(formulaList * ls) ;
int isFormulaEmpty(formulaList Ls) ;
int clauseNum(formulaList Ls) ;

int emptyClauseInFormula(formulaList Ls) ;
#pragma mark - clause operations
#pragma mark - *****WARNING ONLY USE ADD UNIT WHILE DPLL
void addClause(formulaList * ls, clause cls) ;
void addUnitClause(formulaList * ls, clause cls) ;

DeleteClauseStatus deleteClause(formulaList * ls, clause cls) ;
clause findUnitClause(formulaList Ls) ;
clause findFirstStillClase(formulaList Ls) ;
#pragma mark - formula cpy
formulaList deepCpyFormulaList(formulaList Ls) ;
#endif /* CNFFormula_h */
