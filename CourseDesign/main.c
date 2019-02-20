//
//  main.c
//  CourseDesign
//
//  Created by 张储祺 on 2019/2/18.
//  Copyright © 2019 icegrave0391. All rights reserved.
//

#include <stdio.h>
#include "CNFFileManager.h"
#include "DPLLMethod.h"

#pragma mark - extern members
int totalLiteralCount, totalClauseCount ;
int * allLiteralArr = NULL ;

int main(int argc, const char * argv[]) {
    formulaList list ;
    list = loadCNFFileFormula("/Users/chuqiz/2018/CourseDesign/SAT/不满足算例/tst_v10_c100.cnf") ;
//    list = loadCNFFileFormula("/Users/chuqiz/2018/CourseDesign/SAT/hh.cnf") ;
    
//debug log
//    formulaList fmList = list ;
//    clause cls  = NULL ;
//    int * allLiteralArr = (int *)malloc(sizeof(int) * totalLiteralCount) ;
//
//    while ((cls = findUnitClause(fmList))) {
//        int literal = cls -> literals[0] ;
//#pragma mark - save literal status
//        allLiteralArr[abs(literal) - 1] = literal ;
//#pragma mark - remove clause & literal
//        formulaList currP = fmList ;
//        while (currP) {
//            //remove clause
//            if(literalStatusWithClause(* currP -> clause, literal) == LiteralContainStatusContain || literalStatusWithClause( * currP -> clause, literal) == LiteralContainStatusContainBoth){
//                deleteClause(fmList, currP -> clause) ;
//            }
//            //remove literal
//            else if(literalStatusWithClause(* currP -> clause, literal) == LiteralContainStatusContainInverse){
//                deleteLiteral(currP -> clause, -literal) ;
//            }
//            currP = currP -> next ;
//        }
//    }
//    printf("%p %p", allLiteralArr, fmList) ;
//    for (int i = 0; i < totalLiteralCount; i ++) {
//        printf("%d ", allLiteralArr[i]) ;
//    }
//    DPLLWithFormula(list) ;
    if(DPLLWithFormula(list)){
        printf("可以的！") ;
    }else{
        printf("不行！！！") ;
    }
    return 0;
}
