//
//  main.c
//  CourseDesign
//
//  Created by 张储祺 on 2019/2/18.
//  Copyright © 2019 icegrave0391. All rights reserved.
//
#include "UILink.h"
#include <stdio.h>
#include <time.h>
#include "CNFFileManager.h"
#include "DPLLMethod.h"
#include "SudokuTransfer.h"
#include <string.h>

#pragma mark - extern members
int totalLiteralCount, totalClauseCount ;
int * allLiteralArr = NULL ;
int sudokuBoard[9][9] = {0} ;
int sudokuSolution[9][9] = {0} ;
int r[9][10] = {0} ;
int c[9][10] = {0} ;
int b[9][10] = {0} ;

int sudoku[9][9] = {
    {6, 0, 0, 3, 0, 2, 0, 0, 0},
    {0, 5, 0, 0, 0, 0, 0, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {7, 0, 2, 6, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 5, 4},
    {3, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 8, 0, 1, 5, 0, 0, 0, 0},
    {0, 0, 0, 0, 4, 0, 2, 0, 0},
    {0, 0, 0, 0, 0, 0, 7, 0, 0}
};

int main(int argc, const char * argv[]) {
//    while (!lasVegasCreateSudoku(11)) ;
//    generateSudokuByDigHoles(17) ;
//        for (int i = 0 ; i < 9 ; i++) {
//            for (int j = 0 ; j < 9 ; j++) {
//                printf("%d ", sudokuBoard[i][j]) ;
//            }printf("\n") ;
//        }
//        printf("\n") ;
//#pragma mark - sudoku //generate constraints file .sud and CNF file .cnf
////    transferConstraintToFile(sudoku) ;
//    char * sudokuCNF = "/Users/chuqiz/2018/CourseDesign/SAT/sudoku.cnf" ;
//#pragma mark - DPLL
//    formulaList list ;
////    list = loadCNFFileFormula("/Users/chuqiz/2018/CourseDesign/SAT/不满足算例/tst_v10_c100.cnf") ;
////    list = loadCNFFileFormula("/Users/chuqiz/2018/CourseDesign/SAT/不满足算例/eu-rand_net60-25-10.shuffled-3000.cnf") ;
////    list = loadCNFFileFormula("/Users/chuqiz/2018/CourseDesign/SAT/不满足算例/u-5cnf_3500_3500_30f1.shuffled-30.cnf") ;
////    list = loadCNFFileFormula("/Users/chuqiz/2018/CourseDesign/SAT/不满足算例/u-5cnf_3900_3900_060.shuffled-60.cnf") ;
////    list = loadCNFFileFormula("/Users/chuqiz/2018/CourseDesign/SAT/基准算例/功能测试/unsat-5cnf-30.cnf") ;
////    list = loadCNFFileFormula("/Users/chuqiz/2018/CourseDesign/SAT/hh.cnf") ;
////    char * filePathDPLL = "/Users/chuqiz/2018/CourseDesign/SAT/基准算例/功能测试/unsat-5cnf-30.cnf" ;
//    char * filePathDPLL = "/Users/chuqiz/2018/CourseDesign/SAT/基准算例/性能测试/ais10.cnf" ;
////    char * filePathDPLL = "/Users/chuqiz/2018/CourseDesign/SAT/满足算例/M/bart17.shuffled-231.cnf" ;
////    char * filePathDPLL = "/Users/chuqiz/2018/CourseDesign/SAT/sudoku.cnf" ;
////    list = loadCNFFileFormula(filePathDPLL) ;
//    list = loadCNFFileFormula(filePathDPLL) ;
//    allLiteralArr = (int *)malloc(sizeof(int) * totalLiteralCount) ;
//    for (int i = 0 ; i < totalLiteralCount ; i ++) {
//        allLiteralArr[i] = 0 ;
//    }
//
////debug log
//    unsigned long start_t, end_t ;
//    double timeinterval ;
//    int result = 0 ;
//    start_t = clock() ;
//    if(DPLLWithFormula(list)){
//        end_t = clock() ;
//        result = 1 ;
//        printf("s 1\n") ;
//        printf("v ") ;
//        for (int i = 0 ; i < totalLiteralCount; i++) {
//            printf("%d ",allLiteralArr[i]) ;
//        }printf("\n") ;
//    }else{
//        end_t = clock() ;
//        result = 0 ;
//        printf("s 0\n") ;
//    }
////    timeinterval = difftime(end_t, start_t) ;
//    timeinterval = end_t - start_t ;
//    printf("t %.3fms\n", timeinterval / 1000 ) ;
//#pragma mark - export DPLL File .res ANSWER
////    char * exportPath = (char *)malloc(sizeof(char) * 50) ;
////    exportPath = strncpy(exportPath, sudokuCNF, strlen(sudokuCNF) - strlen(".cnf")) ;
////    strcat(exportPath, ".res") ;
////    exportDPLLResultFile(exportPath, allLiteralArr, result, timeinterval) ;
//    free(allLiteralArr) ;
//#pragma mark - transfer .res ANSWER to sudoku answer
//    transferSudokuAnswer("/Users/chuqiz/2018/CourseDesign/SAT/sudoku.res") ;
    showModule() ;
    return 0;
}
