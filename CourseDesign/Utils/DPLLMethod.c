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
    //remove&mark all unit clause and save unit literal
#pragma mark - REMOVE ALL UNIT CLAUSE
    dealUnitClause(fmList, allLiteralArr) ;
    //debug
    
//            formulaList curDebug = fmList ;
//            printf("\n") ;
//            while (curDebug) {
//                printf("status: %d\n", curDebug -> clause -> clauseStatus) ;
//                for (int i = 0; i < curDebug -> clause -> literalCount; i++) {
//                    printf("%d ",curDebug -> clause -> literals[i]) ;
//                }printf("\n") ;
//                curDebug = curDebug -> next ;
//            }

    //condition
    if(isFormulaEmpty(fmList))return 1 ;
    else if(emptyClauseInFormula(fmList))return 0 ;
#pragma mark - CREATE UNIT STRATEGTY
    else{
        clause cls = findFirstStillClase(fmList) ;
        int literal = findRandomLiteral(cls) ;
        int inverseLiteral = - literal ;
        clause newUnitCls = createClause(1, ClauseStatusStill, &literal) ;
        clause newUnitClsInverse = createClause(1, ClauseStatusStill, &inverseLiteral) ;
        formulaList cpyList = deepCpyFormulaList(fmList) ;
//        addUnitClause(&cpyList, newUnitCls) ;
        addClause(cpyList, newUnitCls) ;
       // arr 未处理
        if(DPLLWithFormula(cpyList))return 1 ;
//        addUnitClause(&fmList, newUnitClsInverse) ;
        addClause(fmList, newUnitClsInverse) ;
        return DPLLWithFormula(fmList) ;
    }
} 

void dealUnitClause(formulaList fmList, int * literalArr){
    clause cls = NULL ;
    while ((cls = findUnitClause(fmList))) {
        int literal = findFirstLiteral(cls) ;
#pragma mark - save literal status
        literalArr[abs(literal) - 1] = literal ;
#pragma mark - remove clause & literal
        formulaList currP = fmList ;
        while (currP) {
            //remove clause
            if(literalStatusWithClause(* (currP -> clause), literal) == LiteralContainStatusContain || literalStatusWithClause( * currP -> clause, literal) == LiteralContainStatusContainBoth){
                deleteClause(fmList, currP -> clause) ;
            }
            //remove literal
            else if(literalStatusWithClause(* (currP -> clause), literal) == LiteralContainStatusContainInverse){
                deleteLiteral(currP -> clause, -literal) ;
            }
            currP = currP -> next ;
        }
    }
}
