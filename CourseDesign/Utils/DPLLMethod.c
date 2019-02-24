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
extern int * depth ;
extern Stack * literalStack ;

int DPLLWithFormula(formulaList * fmList){
#pragma mark - REMOVE ALL UNIT CLAUSE
    dealUnitClause(fmList, allLiteralArr) ;
////    debug
//            formulaList curDebug = *fmList ;
//            printf("\n") ;
//    if(curDebug -> clause){
//        printf("打印公式\n") ;
//        while (curDebug) {
//            //                printf("status: %d\n", curDebug -> clause -> clauseStatus) ;
//            for (int i = 0; i < curDebug -> clause -> literalCount; i++) {
//                printf("%d ",curDebug -> clause -> literals[i]) ;
//            }printf("\n") ;
//            curDebug = curDebug -> next ;
//        }
//    }
    //condition
    if(isFormulaEmpty(*fmList))return 1 ;
    else if(emptyClauseInFormula(*fmList))return 0 ;
#pragma mark - CREATE UNIT STRATEGTY
    else{
//        (*depth) ++ ;         //增加递归深度
        (*depth) = 1 ;
        clause cls = findFirstStillClase(*fmList) ;
        int literal = findRandomLiteral(cls) ;
        push(literalStack, literal) ;   //入栈
        dealNewUnitClause(fmList, allLiteralArr, literal) ;
        if(DPLLWithFormula(fmList))return 1 ;
//        formulaList bugg = *fmList ;
//        while (bugg) {
//            //                printf("status: %d\n", curDebug -> clause -> clauseStatus) ;
//            printf("\n打印下一层公式\n") ;
//            for (int i = 0; i < bugg -> clause -> literalCount; i++) {
//                printf("%d ",bugg -> clause -> literals[i]) ;
//            }printf("\n") ;
//            bugg = bugg -> next ;
//        }
        
        int popLiteral ;
        while ((popLiteral = pop(literalStack)) != literal) {
            int inversePopLiteral = -popLiteral ;
            formulaList literalFormula = popLiteral > 0 ? literalClauseArr[popLiteral * 2 - 2] : literalClauseArr[popLiteral * (-2) - 1] ;
            formulaList inverseLiteralFormula = inversePopLiteral > 0 ? literalClauseArr[inversePopLiteral * 2 - 2] : literalClauseArr[inversePopLiteral * (-2) - 1] ;
            undoFormula(fmList, literalFormula, inverseLiteralFormula, popLiteral) ;
            allLiteralArr[abs(popLiteral) - 1] = 0 ;
        }
        int inversePopLiteral = -popLiteral ;
        formulaList literalFormula = popLiteral > 0 ? literalClauseArr[popLiteral * 2 - 2] : literalClauseArr[popLiteral * (-2) - 1] ;
        formulaList inverseLiteralFormula = inversePopLiteral > 0 ? literalClauseArr[inversePopLiteral * 2 - 2] : literalClauseArr[inversePopLiteral * (-2) - 1] ;
//        (*depth) -- ;
        undoFormula(fmList, literalFormula, inverseLiteralFormula, popLiteral) ;
        dealNewUnitClause(fmList, allLiteralArr, -literal) ;
        push(literalStack, -literal) ;
//        (*depth) ++ ;
//        int inve = - literal ;
//        clause clss = createClause(1, ClauseStatusStill, &inve) ;
//        addClause(fmList, clss) ;
//        dealNewUnitClause(fmList, allLiteralArr, inversePopLiteral) ;
        return DPLLWithFormula(fmList) ;
    }
} 

void dealUnitClause(formulaList * fmlist, int * literalArr){
    clause cls = NULL ;
    while ((cls = findUnitClause(* fmlist))) {
        int literal = findFirstLiteral(cls) ;
        if(*depth)push(literalStack, literal) ;       //依次入栈
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
//    //    debug
//    formulaList curDebug = *fmlist ;
//    printf("\n处理完单子句\n") ;
//    if(curDebug -> clause){
//        while (curDebug) {
//            for (int i = 0; i < curDebug -> clause -> literalCount; i++) {
//                printf("%d ",curDebug -> clause -> literals[i]) ;
//            }printf("\n") ;
//            curDebug = curDebug -> next ;
//        }
//    }
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
    //    debug
//    formulaList curDebug = *fmlist ;
//    printf("\n处理完新文字\n") ;
//    if(curDebug -> clause){
//        while (curDebug) {
//            //                printf("status: %d\n", curDebug -> clause -> clauseStatus) ;
//            for (int i = 0; i < curDebug -> clause -> literalCount; i++) {
//                printf("%d ",curDebug -> clause -> literals[i]) ;
//            }printf("\n") ;
//            curDebug = curDebug -> next ;
//        }
//    }
}

void undoFormula(formulaList * fmlist, formulaList literalList, formulaList inverseLiteralList, int literal){
//    allLiteralArr[abs(literal) - 1] = 0 ;   //撤销文字真值状态
    formulaList currP = literalList ;
    while (currP) {
        clause cls = currP -> clause ;
        int flag = 0 ;
        for (int i = 0 ; i < cls -> literalCount ; i++) {
            if(allLiteralArr[abs(cls -> literals[i]) - 1] && cls -> literals[i])flag++ ;
        }
        if(flag == 1)addClause(fmlist, cls) ;
        currP = currP -> next ;
    }
    formulaList currivsP = inverseLiteralList ;
    while (currivsP) {
        clause cls = currivsP -> clause ;
        recoverLiteral(cls, -literal) ;
        currivsP = currivsP -> next ;
    }
    //    debug
//    formulaList curDebug = *fmlist ;
//    printf("\n回滚一次文字\n") ;
//    while (curDebug) {
//        //                printf("status: %d\n", curDebug -> clause -> clauseStatus) ;
//        for (int i = 0; i < curDebug -> clause -> literalCount; i++) {
//            printf("%d ",curDebug -> clause -> literals[i]) ;
//        }printf("\n") ;
//        curDebug = curDebug -> next ;
//    }
}
