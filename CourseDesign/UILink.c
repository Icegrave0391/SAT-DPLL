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
void printEnd(void) ;
void showModule(void){
    printf("++++++++++++++++++++ CHOOSE THE FUNCTION ++++++++++++++++++++\n") ;
    printf("1.Solve SAT Problem                        2.Play Sudoku Game\n") ;
    printf("3.Transfer Sudoku To SAT                   4.Exit\n") ;
    printf("==============================================================\n") ;
    int func ;
    while(scanf("%d", & func)) {
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
            printEnd() ;
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
                    printf("Please input with the correct format, try again : \n") ;
                    goto loop ;
                    break;
            }
            
            printf("Just Have FUN XD\n") ;
            printSudoku(sudokuBoard) ;
            printf("Rules : to fill sudoku, please input the number. \nSuch as 123 => row 1 colume 2 filled by 3\n") ;
            printf("To view some tips, input the row and the colume. Such as 12 => row 1 colume 2.\nYou have 5 tips :)\n") ;
            printf("To quit the game, input 0 :)\n") ;
            int loc, tipCount = 0 ;
            while (scanf("%d",&loc) && !finishSudoku(sudokuBoard, sudokuSolution)) {
                if(!loc){
                    printf("Failure is the mother of success. GoodLuck next time :)\n") ;
                    break ;
                }
                else if(loc < 100 && tipCount < 5){
                    tipCount++ ;
                    int row = loc / 10 ;
                    int col = loc % 10 ;
                    printf("row : %d, colume : %d, the answer is : %d, you have %d tips left\n",row, col, sudokuSolution[row - 1][col - 1], 5 - tipCount) ;
                }
                else if(loc < 100 && tipCount >= 5){
                    printf("You have no tips left, just embrace yourself\n") ;
                }
                else{
                    int row = loc / 100 ;
                    int col = (loc / 10) % 10 ;
                    int num = loc % 10 ;
                    sudokuBoard[row - 1][col - 1] = num ;
                    printSudoku(sudokuBoard) ;
                    printf("Keep on!(press 0 to quit), you have %d tips left :)\n", 5 - tipCount) ;
                }
            }
            if(finishSudoku(sudokuBoard, sudokuSolution)){
                printf("Congratulations! You Just Bet me ! \n") ;
            }
            printEnd() ;
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
            printEnd() ;
        }
        if (func == 4) {
            printf("XXXXXXXXXXXXXX     Welcome     XXXXXXXXXXXXXXX\n") ;
            break ;
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

void printEnd(void){
    printf("\n==============================================================\n") ;
    printf("Now this module is finished, wanna have mor fun? \n") ;
    printf("1.Solve SAT Problem                        2.Play Sudoku Game\n") ;
    printf("3.Transfer Sudoku To SAT                   4.Exit\n") ;
}
