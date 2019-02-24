//
//  main.c
//  CourseDesign
//
//  Created by 张储祺 on 2019/2/18.
//  Copyright © 2019 icegrave0391. All rights reserved.
//

#include <stdio.h>
#include <time.h>
#include "CNFFileManager.h"
#include "DPLLMethod.h"
#include "CNFLiteralStack.h"

#pragma mark - extern members
int totalLiteralCount, totalClauseCount ;
int * allLiteralArr = NULL ;

formulaList * literalClauseArr = NULL ;
Stack * literalStack ;
int * depth ;


int sudoku[9][9] = {
    {6, 0, 0, 3, 0, 2, 0, 0, 0},
    {0, 5, 0, 0, 0, 0, 0, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {7, 0, 26, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 54},
    {3, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 8, 0, 15, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 4, 0, 2, 0, 0},
    {0, 0, 0, 0, 0, 0, 7, 0, 0}
};

int main(int argc, const char * argv[]) {
    //sudoku
    
    //init
    formulaList list ;
    literalStack = initStack() ;
    depth = (int *)malloc(sizeof(int)) ;
    *depth = 0 ;
//    list = loadCNFFileFormula("/Users/chuqiz/2018/CourseDesign/SAT/不满足算例/tst_v10_c100.cnf") ;
//    list = loadCNFFileFormula("/Users/chuqiz/2018/CourseDesign/SAT/不满足算例/eu-rand_net60-25-10.shuffled-3000.cnf") ;
//    list = loadCNFFileFormula("/Users/chuqiz/2018/CourseDesign/SAT/不满足算例/u-5cnf_3500_3500_30f1.shuffled-30.cnf") ;
//    list = loadCNFFileFormula("/Users/chuqiz/2018/CourseDesign/SAT/不满足算例/u-5cnf_3900_3900_060.shuffled-60.cnf") ;
//    list = loadCNFFileFormula("/Users/chuqiz/2018/CourseDesign/SAT/基准算例/功能测试/unsat-5cnf-30.cnf") ;
//    list = loadCNFFileFormula("/Users/chuqiz/2018/CourseDesign/SAT/基准算例/功能测试/sat-20.cnf") ;
//    list = loadCNFFileFormula("/Users/chuqiz/2018/CourseDesign/SAT/基准算例/性能测试/ais10.cnf") ;
//     list = loadCNFFileFormula("/Users/chuqiz/2018/CourseDesign/SAT/基准算例/性能测试/sud00009.cnf") ;
//    list = loadCNFFileFormula("/Users/chuqiz/2018/CourseDesign/SAT/hh.cnf") ;
//    char * filePath = "/Users/chuqiz/2018/CourseDesign/SAT/满足算例/M/bart17.shuffled-231.cnf" ;
//    list = loadCNFFileFormula(filePath) ;
//    list = loadCNFFileFormula("/Users/chuqiz/2018/CourseDesign/SAT/back.cnf") ;
    list = loadCNFFileFormula("/Users/chuqiz/2018/CourseDesign/SAT/backnew.cnf") ;
    allLiteralArr = (int *)malloc(sizeof(int) * totalLiteralCount) ;
    for (int i = 0 ; i < totalLiteralCount ; i++) {
//        allLiteralArr[i] = i+1 ;
        allLiteralArr[i] = 0 ;
    }
//debug log
    unsigned long start_t, end_t ;
    double timeinterval ;

    start_t = clock() ;
    if(DPLLWithFormula(&list)){
        end_t = clock() ;
        
        printf("s 1\n") ;
        printf("v ") ;
        for (int i = 0 ; i < totalLiteralCount; i++) {
            printf("%d ",allLiteralArr[i]) ;
        }printf("\n") ;
    }else{
        printf("s 0\n") ;
        end_t = clock() ;
    }
//    timeinterval = difftime(end_t, start_t) ;
    timeinterval = end_t - start_t ;
    printf("t %.3fms\n", timeinterval / 1000 ) ;
    free(allLiteralArr) ;
    return 0;
}
