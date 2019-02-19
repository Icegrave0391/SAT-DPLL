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
int formulaEmpty(formulaList Ls) ;
int clauseNum(formulaList Ls) ;

#pragma mark - clause operations
void addClause(formulaList Ls, clause cls) ;
DeleteClauseStatus deleteClause(formulaList Ls, clause cls) ;
clause findUnitClause(formulaList Ls) ;
#endif /* CNFFormula_h */
