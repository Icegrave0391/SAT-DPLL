//
//  DPLLMethod.c
//  CourseDesign
//
//  Created by 张储祺 on 2019/2/19.
//  Copyright © 2019 icegrave0391. All rights reserved.
//

#include "DPLLMethod.h"

int DPLLWithFormula(formulaList fmList){
    extern int totalLiteralCount, totalClauseCount ;
    allLiteralArr = (int *)malloc(sizeof(int) * totalLiteralCount) ;
    //remove&mark all unit clause and save unit literal
    clause cls ;
    while ((cls = findUnitClause(fmList))) {
        int literal = cls -> literals[0] ;
#pragma mark - save literal status
        allLiteralArr[abs(literal) - 1] = literal ;
#pragma mark - remove clause & literal
        formulaList currP = fmList ;
        while (currP) {
            //remove clause
            if(literalStatusWithClause(* currP -> clause, literal) == LiteralContainStatusContain || literalStatusWithClause( * currP -> clause, literal) == LiteralContainStatusContainBoth){
                deleteClause(fmList, cls) ;
            }
            //remove literal
            else if(literalStatusWithClause(* currP -> clause, literal) == LiteralContainStatusContainInverse){
                deleteLiteral(cls, literal) ;
            }
        }
    }
    
    
    return  0 ;
}
