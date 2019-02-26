//
//  UILink.c
//  CourseDesign
//
//  Created by 张储祺 on 2019/2/25.
//  Copyright © 2019 icegrave0391. All rights reserved.
//

#include "UILink.h"
int printSudoku(int sud[][9]) ;
int finishSudoku(int sud[][9], int sudAns[][9]) ;
void showModule(){
    printf("++++++++++++++++++++ CHOOSE THE FUNCTION ++++++++++++++++++++\n") ;
    printf("1.Solve SAT Problem                        2.Play Sudoku Game\n") ;
    printf("3.Transfer Sudoku To SAT                   4.Exit\n") ;
    printf("==============================================================\n") ;
    int func ;
    scanf("%d", & func) ;
    if(func == 1){
        printf("*** Please input the file :\n") ;
        char * filePathPre = "/Users/chuqiz/2018/CourseDesign/SAT/" ;
        char s[50] ;
        scanf("%s", s) ;
        char * filePath = (char *)malloc(sizeof(char) * 50) ;
        strcpy(filePath, filePathPre) ;
        strcat(filePath, s) ;
        formulaList list = loadCNFFileFormula(filePath) ;
        allLiteralArr = (int *)malloc(sizeof(int) * totalLiteralCount) ;
        for (int i = 0 ; i < totalLiteralCount ; i ++) {
            allLiteralArr[i] = 0 ;
        }
        //debug log
        unsigned long start_t, end_t ;
        double timeinterval ;
        int result = 0 ;
        start_t = clock() ;
        if(DPLLWithFormula(list)){
            end_t = clock() ;
            result = 1 ;
            printf("s 1\n") ;
            printf("v ") ;
            for (int i = 0 ; i < totalLiteralCount; i++) {
                printf("%d ",allLiteralArr[i]) ;
            }printf("\n") ;
        }else{
            end_t = clock() ;
            result = 0 ;
            printf("s 0\n") ;
        }
        timeinterval = end_t - start_t ;
        printf("t %.3fms\n", timeinterval / 1000 ) ;
        //export
            char * exportPath = (char *)malloc(sizeof(char) * 50) ;
            exportPath = strncpy(exportPath, filePath, strlen(filePath) - strlen(".cnf")) ;
            strcat(exportPath, ".res") ;
            exportDPLLResultFile(exportPath, allLiteralArr, result, timeinterval) ;
    }
    if(func == 2){
        while (!lasVegasCreateSudoku(11)) ;
        printf("Choose the degree of difficuty\n") ;
        printf("1.Normal   2.Medium   3.Hard   4.Abuse   5.WTFFF\n") ;
        int diff ;
        loop : scanf("%d",&diff) ;
        switch (diff) {
            case 1:
                generateSudokuByDigHoles(36) ;
                break;
            case 2:
                generateSudokuByDigHoles(28) ;
                break;
            case 3:
                generateSudokuByDigHoles(23) ;
                break;
            case 4:
                generateSudokuByDigHoles(20) ;
                break;
            case 5:
                generateSudokuByDigHoles(17) ;
                break;
            default:
                goto loop ;
                break;
        }
        
        printf("Just Have FUN XD\n") ;
        printSudoku(sudokuBoard) ;
        printf("Rules : to fill sudoku, please input the number. \nSuch as 123 => row 1 colume 2 filled by 3\n") ;
        int loc ;
        while (scanf("%d",&loc) && !finishSudoku(sudokuBoard, sudokuSolution)) {
            int row = loc / 100 ;
            int col = (loc / 10) % 10 ;
            int num = loc % 10 ;
            sudokuBoard[row - 1][col - 1] = num ;
            printSudoku(sudokuBoard) ;
        }
    }
    
    if(func == 3){
        while (!lasVegasCreateSudoku(11)) ;
        generateSudokuByDigHoles(20) ;
        printf("The Sudoku Problem : \n") ;
        printSudoku(sudokuBoard) ;
        if(transferConstraintToFile(sudokuBoard)){
            char * filePath = "/Users/chuqiz/2018/CourseDesign/SAT/sudoku/sudoku.cnf" ;
            formulaList list = loadCNFFileFormula(filePath) ;
            allLiteralArr = (int *)malloc(sizeof(int) * totalLiteralCount) ;
            for (int i = 0 ; i < totalLiteralCount ; i ++) {
                allLiteralArr[i] = 0 ;
            }
            //debug log
            unsigned long start_t, end_t ;
            double timeinterval ;
            int result = 0 ;
            start_t = clock() ;
            if(DPLLWithFormula(list)){
                end_t = clock() ;
                result = 1 ;
                printf("s 1\n") ;
                printf("v ") ;
                for (int i = 0 ; i < totalLiteralCount; i++) {
                    printf("%d ",allLiteralArr[i]) ;
                }printf("\n") ;
            }else{
                end_t = clock() ;
                result = 0 ;
                printf("s 0\n") ;
            }
            timeinterval = end_t - start_t ;
            printf("t %.3fms\n", timeinterval / 1000 ) ;
            //export
            char * exportPath = (char *)malloc(sizeof(char) * 50) ;
            exportPath = strncpy(exportPath, filePath, strlen(filePath) - strlen(".cnf")) ;
            strcat(exportPath, ".res") ;
            if(exportDPLLResultFile(exportPath, allLiteralArr, result, timeinterval)){
                transferSudokuAnswer(exportPath) ;
            }
            //print
            printf("The Solution Of The Sudoku Above Is : \n") ;
            printSudoku(sudokuSolution) ;
        }
    }
}

int printSudoku(int sud[][9]){
    int i,j;
    printf("        ");
    printf("* * * * * * * * * * * * * * * *\n");
    
    for(i = 1 ; i < 10 ; i++){
        printf("        ");
        printf("*");
        for(j = 1 ; j < 10 ; j++){
            if(sud[i - 1][j - 1]){
                printf(" %d ",sud[i - 1][j - 1]);
                if(j == 3 || j == 6 )printf(":");
            }
            else{
                printf("   ");
                if(j == 3 || j == 6 )printf(":");
                
            }
        }
        
        printf("*\n");
        if( i == 3 || i == 6 ){
            printf("        ");
            printf("*.........:.........:.........*\n");
            printf("        ");
            printf("*         :         :         *\n");
        }
    }
    printf("        ");
    printf("* * * * * * * * * * * * * * * *\n");
    return 1;
}

int finishSudoku(int sud[][9], int sudAns[][9]){
    int sameAns = 0 ;
    for (int i = 0 ; i < 9 ; i++) {
        for (int j = 0 ; j < 9 ; j++) {
            if(sud[i][j] == sudAns[i][j]) sameAns++ ;
        }
    }
    if(sameAns == 81)return 1 ;
    return 0 ;
}
