//
//  CNFClause.c
//  CourseDesign
//
//  Created by 张储祺 on 2019/2/18.
//  Copyright © 2019 icegrave0391. All rights reserved.
//

#include "CNFClause.h"

clause createClause(int literalNum, ClauseStatus clsStatus, int * literals){
    clause cls = (clause)malloc(sizeof(Clause)) ;
    cls -> clauseStatus = clsStatus ;
    cls -> literalCount = literalNum ;
    cls -> literals = literals ;
    return cls ;
}

int isUnitClause (Clause cls){
    if(cls.literalCount == 1 && cls.clauseStatus == ClauseStatusStill)return 1 ;
    return 0 ;
}

LiteralContainStatus literalStatusWithClause(Clause Cls, int literal){
    int iter = 0 ;
    int flag = 0 ;
    while (iter < Cls.literalCount) {
        if(!flag){
            if(Cls.literals[iter] == literal && !flag)flag = 1 ;  //contain
            else if(Cls.literals[iter] == - literal && !flag)flag = 2 ;  //contain inverse
        }
        else if(flag == 1){
            if(Cls.literals[iter] ==  - literal)return LiteralContainStatusContainBoth ;
        }
        else{
            if(Cls.literals[iter] == literal)return LiteralContainStatusContainBoth ;
        }
        iter ++ ;
    }
    switch (flag) {
        case 0:
            return LiteralContainStatusNotContain ;
            break;
        case 1:
            return LiteralContainStatusContain ;
            break ;
        case 2:
            return LiteralContainStatusContainInverse ;
            break ;
        default:
            break;
    }
    return 0 ;
}

int evaluateClauseWithLiteral (Clause Cls, int literal){
    int iter = 0 ;
    while(iter < Cls.literalCount){
        if(Cls.literals[iter++] == literal) return 1 ;
    }
    return 0 ;
}
