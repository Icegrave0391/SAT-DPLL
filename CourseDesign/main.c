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
//    list = loadCNFFileFormula("/Users/chuqiz/2018/CourseDesign/SAT/不满足算例/tst_v10_c100.cnf") ;
//    list = loadCNFFileFormula("/Users/chuqiz/2018/CourseDesign/SAT/不满足算例/eu-rand_net60-25-10.shuffled-3000.cnf") ;
//    list = loadCNFFileFormula("/Users/chuqiz/2018/CourseDesign/SAT/不满足算例/u-5cnf_3500_3500_30f1.shuffled-30.cnf") ;
//    list = loadCNFFileFormula("/Users/chuqiz/2018/CourseDesign/SAT/不满足算例/u-5cnf_3900_3900_060.shuffled-60.cnf") ;
    list = loadCNFFileFormula("/Users/chuqiz/2018/CourseDesign/SAT/基准算例/功能测试/unsat-5cnf-30.cnf") ;
//    list = loadCNFFileFormula("/Users/chuqiz/2018/CourseDesign/SAT/hh.cnf") ;
    
//debug log
//    formulaList fmList = list ;
//    clause cls = NULL ;
//    while ((cls = findUnitClause(fmList))) {
//        int literal = cls -> literals[0] ;
//#pragma mark - save literal status
////        literalArr[abs(literal) - 1] = literal ;
//#pragma mark - remove clause & literal
//        formulaList currP = fmList ;
//        while (currP) {
//            //remove clause
//            if(literalStatusWithClause(* (currP -> clause), literal) == LiteralContainStatusContain || literalStatusWithClause( * currP -> clause, literal) == LiteralContainStatusContainBoth){
//                deleteClause(fmList, currP -> clause) ;
//            }
//            //remove literal
//            else if(literalStatusWithClause(* (currP -> clause), literal) == LiteralContainStatusContainInverse){
//                deleteLiteral(currP -> clause, -literal) ;
//            }
//            currP = currP -> next ;
//        }
//
//        formulaList curDebug = fmList ;
//        printf("\n") ;
//        while (curDebug) {
//            printf("status: %d\n", curDebug -> clause -> clauseStatus) ;
//            for (int i = 0; i < curDebug -> clause -> literalCount; i++) {
//                printf("%d ",curDebug -> clause -> literals[i]) ;
//            }printf("\n") ;
//            curDebug = curDebug -> next ;
//        }
//    }
    if(DPLLWithFormula(list)){
        printf("可以的！\n") ;
    }else{
        printf("不行！！！\n") ;
    }
    return 0;
}
