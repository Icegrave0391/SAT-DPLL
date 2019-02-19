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
//Clause struct

typedef struct {
    int literalNum ;      //via file 
    ClauseStatus clauseStatus ;
    int * literals ;
} Clause ;

typedef Clause * clause ;

//clause operate functions

clause createClause(int literalNum, enum ClauseStatus clsStatus, int * literals) ;
//int destoryClause(clause cls) ;
int isUnitClause (Clause cls) ;

LiteralContainStatus literalStatusWithClause(Clause Cls, int literal) ;
int evaluateClauseWithLiteral (Clause Cls, int literal) ;

#endif /* CNFClause_h */
