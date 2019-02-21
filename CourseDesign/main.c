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

#pragma mark - extern members
int totalLiteralCount, totalClauseCount ;
int * allLiteralArr = NULL ;

int main(int argc, const char * argv[]) {
    formulaList list ;
//    list = loadCNFFileFormula("/Users/chuqiz/2018/CourseDesign/SAT/不满足算例/tst_v10_c100.cnf") ;
//    list = loadCNFFileFormula("/Users/chuqiz/2018/CourseDesign/SAT/不满足算例/eu-rand_net60-25-10.shuffled-3000.cnf") ;
//    list = loadCNFFileFormula("/Users/chuqiz/2018/CourseDesign/SAT/不满足算例/u-5cnf_3500_3500_30f1.shuffled-30.cnf") ;
//    list = loadCNFFileFormula("/Users/chuqiz/2018/CourseDesign/SAT/不满足算例/u-5cnf_3900_3900_060.shuffled-60.cnf") ;
    
//    list = loadCNFFileFormula("/Users/chuqiz/2018/CourseDesign/SAT/基准算例/功能测试/unsat-5cnf-30.cnf") ;
//    list = loadCNFFileFormula("/Users/chuqiz/2018/CourseDesign/SAT/基准算例/功能测试/sat-20.cnf") ;
//    list = loadCNFFileFormula("/Users/chuqiz/2018/CourseDesign/SAT/基准算例/性能测试/ais10.cnf") ;
    list = loadCNFFileFormula("/Users/chuqiz/2018/CourseDesign/SAT/基准算例/性能测试/sud00009.cnf") ;
    
//    list = loadCNFFileFormula("/Users/chuqiz/2018/CourseDesign/SAT/hh.cnf") ;
//    u-5cnf_3900_3900_060.shuffled-60.cnf
//    char * filePath = "/Users/chuqiz/2018/CourseDesign/SAT/满足算例/M/bart17.shuffled-231.cnf" ;
//    list = loadCNFFileFormula(filePath) ;
    allLiteralArr = (int *)malloc(sizeof(int) * totalLiteralCount) ;
    for (int i = 0 ; i < totalLiteralCount ; i ++) {
        allLiteralArr[i] = i+1 ;
    }
    //log
    unsigned long start_t, end_t ;
    double timeinterval ;

    start_t = clock() ;
    if(DPLLWithFormula(list)){
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
    timeinterval = end_t - start_t ;
    printf("t %.3fms\n", timeinterval / 1000 ) ;
    free(allLiteralArr) ;
    return 0;
}
