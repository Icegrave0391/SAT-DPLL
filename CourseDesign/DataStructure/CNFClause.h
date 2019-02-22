//
//  CNFClause.h
//  CourseDesign
//
//  Created by 张储祺 on 2019/2/18.
//  Copyright © 2019 icegrave0391. All rights reserved.
//

#ifndef CNFClause_h
#define CNFClause_h

#include <stdio.h>
#include <stdlib.h>
#pragma mark - status
enum ClauseStatus{         //子句保留状态
    ClauseStatusDeleted = 0,        //子句被删除
    ClauseStatusStill
};
typedef enum ClauseStatus ClauseStatus;

enum LiteralContainStatus{
    LiteralContainStatusNotContain = 0,
    LiteralContainStatusContain,
    LiteralContainStatusContainInverse,
    LiteralContainStatusContainBoth 
};

typedef enum LiteralContainStatus LiteralContainStatus;

#pragma mark - Clause struct
typedef struct {
    int literalCount ;      //via file
    ClauseStatus clauseStatus ;
    int * literals ;
} Clause ;

typedef Clause * clause ;

//clause operate functions

clause createClause(int literalNum, ClauseStatus clsStatus, int * literals) ;
clause deepCpyClause(clause aclause) ;
//int destoryClause(clause cls) ;
int isUnitClause (Clause cls) ;
int isEmptyClause(Clause cls) ;
LiteralContainStatus literalStatusWithClause(Clause Cls, int literal) ;
void deleteLiteral(clause cls, int literal) ;
int findRandomLiteral(clause cls) ;
void recoverLiteral(clause cls, int literal) ;
#pragma mark - WARNING!!! THIS METHOD SHOULD ONLY BE USED IN DPLL UNIT
int findFirstLiteral(clause cls) ;
#endif /* CNFClause_h */
