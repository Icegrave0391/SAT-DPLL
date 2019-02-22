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
extern formulaList * literalClauseArr ;
int DPLLWithFormula(formulaList fmList){
    //remove&mark all unit clause and save unit literal
#pragma mark - REMOVE ALL UNIT CLAUSE
    dealUnitClause(&fmList, allLiteralArr) ;
//    debug
//    
            formulaList curDebug = fmList ;
            printf("\n") ;
            while (curDebug && curDebug -> clause) {
//                printf("status: %d\n", curDebug -> clause -> clauseStatus) ;
                for (int i = 0; i < curDebug -> clause -> literalCount; i++) {
                    printf("%d ",curDebug -> clause -> literals[i]) ;
                }printf("\n") ;
                curDebug = curDebug -> next ;
            }
    //condition
    if(isFormulaEmpty(fmList))return 1 ;
    else if(emptyClauseInFormula(fmList))return 0 ;
#pragma mark - CREATE UNIT STRATEGTY
    else{
        clause cls = findFirstStillClase(fmList) ;
        int literal = findRandomLiteral(cls) ;
        int inverseLiteral = - literal ;
        dealNewUnitClause(&fmList, allLiteralArr, literal) ;
        if(DPLLWithFormula(fmList))return 1 ;
        formulaList literalFormula = literal > 0 ? literalClauseArr[literal * 2 - 2] : literalClauseArr[literal * (-2) - 1] ;
        undoFormula(&fmList, literalFormula, literal) ;
        dealNewUnitClause(&fmList, allLiteralArr, inverseLiteral) ;
        return DPLLWithFormula(fmList) ;
    }
}

void dealUnitClause(formulaList * fmlist, int * literalArr){
    clause cls = NULL ;
    while ((cls = findUnitClause(* fmlist))) {
        int literal = findFirstLiteral(cls) ;
#pragma mark - save literal status
        literalArr[abs(literal) - 1] = literal ;
#pragma mark - remove clause & literal
        formulaList currP = * fmlist ;
        while (currP) {
            //remove clause
            if(literalStatusWithClause(* (currP -> clause), literal) == LiteralContainStatusContain || literalStatusWithClause( * currP -> clause, literal) == LiteralContainStatusContainBoth){
                deleteClause(fmlist, currP -> clause) ;
            }
            //remove literal
            else if(literalStatusWithClause(* (currP -> clause), literal) == LiteralContainStatusContainInverse){
                deleteLiteral(currP -> clause, -literal) ;
            }
            currP = currP -> next ;
        }
    }
}

void dealNewUnitClause(formulaList * fmlist, int * literalArr, int literal){
#pragma mark - save literal status
    literalArr[abs(literal) - 1] = literal ;
#pragma mark - remove clause & literal
    formulaList currP = * fmlist ;
    while (currP) {
        //remove clause
        if(literalStatusWithClause(* (currP -> clause), literal) == LiteralContainStatusContain || literalStatusWithClause( * currP -> clause, literal) == LiteralContainStatusContainBoth){
            deleteClause(fmlist, currP -> clause) ;
        }
        //remove literal
        else if(literalStatusWithClause(* (currP -> clause), literal) == LiteralContainStatusContainInverse){
            deleteLiteral(currP -> clause, -literal) ;
        }
        currP = currP -> next ;
    }
}

void undoFormula(formulaList * fmlist, formulaList literalList, int literal){
    formulaList currP = literalList ;
    while (currP) {
        clause cls = currP -> clause ;
        recoverLiteral(cls, literal) ;
        int flag = 0 ;
        for (int i = 0 ; i < cls -> literalCount ; i++) {
            if(!allLiteralArr[abs(cls -> literals[i]) - 1])flag++ ;
        }
        if(flag == 1)addClause(fmlist, cls) ;
        currP = currP -> next ;
    }
    
}
