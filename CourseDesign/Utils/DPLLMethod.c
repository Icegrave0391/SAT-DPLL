//
//  DPLLMethod.c
//  CourseDesign
//
//  Created by 张储祺 on 2019/2/19.
//  Copyright © 2019 icegrave0391. All rights reserved.
//

#include "DPLLMethod.h"
extern int totalLiteralCount, totalClauseCount ;
extern int * allLiteralArr ;
int DPLLWithFormula(formulaList fmList){
//    extern int totalLiteralCount, totalClauseCount ;
    allLiteralArr = (int *)malloc(sizeof(int) * totalLiteralCount) ;
    printf( "%d %d", totalLiteralCount, totalClauseCount) ;
    //remove&mark all unit clause and save unit literal
#pragma mark - REMOVE ALL UNIT CLAUSE
    dealUnitClause(fmList, allLiteralArr) ;
#pragma mark - CREATE UNIT STRATEGTY
    return  0 ;
}

void dealUnitClause(formulaList fmList, int * literalArr){
    clause cls = NULL ;
    while ((cls = findUnitClause(fmList))) {
        int literal = cls -> literals[0] ;
#pragma mark - save literal status
        literalArr[abs(literal) - 1] = literal ;
#pragma mark - remove clause & literal
        formulaList currP = fmList ;
        while (currP) {
            //remove clause
            if(literalStatusWithClause(* currP -> clause, literal) == LiteralContainStatusContain || literalStatusWithClause( * currP -> clause, literal) == LiteralContainStatusContainBoth){
                deleteClause(fmList, currP -> clause) ;
            }
            //remove literal
            else if(literalStatusWithClause(* currP -> clause, literal) == LiteralContainStatusContainInverse){
                deleteLiteral(currP -> clause, -literal) ;
            }
            currP = currP -> next ;
        }
    }
}
