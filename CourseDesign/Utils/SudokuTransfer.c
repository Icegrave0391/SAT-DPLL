//
//  SudokuTransfer.c
//  CourseDesign
//
//  Created by 张储祺 on 2019/2/23.
//  Copyright © 2019 icegrave0391. All rights reserved.
//

#include "SudokuTransfer.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define constraintCount 11988
//private API
int recursionSudoku(int sudoku[9][9], int i, int j) ;

int transferConstraintToFile(int sudoku[9][9]){
    FILE * fp = NULL ;
    FILE * fpCNF = NULL ;
    char * sudFilePath = "/Users/chuqiz/2018/CourseDesign/SAT/sudoku/sudoku.sud" ;
    char * CNFFilePath = "/Users/chuqiz/2018/CourseDesign/SAT/sudoku/sudoku.cnf" ;
    if(!(fp = fopen(sudFilePath, "w"))){
        printf("File_Transfer_Error\n") ;
        return 0;
    }else{
        if(!(fpCNF = fopen(CNFFilePath, "w"))){
            printf("CNFFile_Transfer_Error\n") ;
            return 0;
        }
        else{
            //sudoku unit
            int unitcount = 0 ;
            for (int i = 0 ; i < 9 ; i++) {
                for (int j = 0 ; j < 9 ; j++) {
                    if(sudoku[i][j])unitcount++ ;
                }
            }
            fprintf(fp, "c\np cnf %d %d\n",729, unitcount + constraintCount) ;
            fprintf(fpCNF, "c\np cnf %d %d\n",729, unitcount + constraintCount) ;
#pragma mark - all 11988
            //
            for (int row = 1 ; row <= 9 ; row++) {
                for (int line = 1 ; line <= 9 ; line++) {
                    for (int num = 1 ; num <=9 ; num++) {
                        int sudliteral = row * 100 + line * 10 + num ;
                        char str_lit[4] ;
                        sprintf(str_lit, "%d",sudliteral) ;
                        fprintf(fp, "%s ",str_lit) ;
                        int literal = mapSudokuToLiteral(sudliteral) ;
                        sprintf(str_lit, "%d",literal) ;
                        fprintf(fpCNF, "%s ",str_lit) ;
                    }
                    fprintf(fp, "%d\n",0) ;
                    fprintf(fpCNF, "%d\n", 0) ;
                }
            }
            //        fputs("\n", fp) ;
        }
        
        for (int line = 1 ; line <= 9 ; line++) {
            for (int num = 1 ; num <= 9 ; num++) {
                for (int row = 1 ; row <=8 ; row++) {
                    for (int i = row + 1 ; i<=9  ; i++) {
                        int sudivsLiteral1 = -(row * 100 + line * 10 + num) ;
                        int sudivsLiteral2 = -(i * 100 + line * 10 + num) ;
                        char str_ivs1[5], str_ivs2[5] ;
                        sprintf(str_ivs1, "%d",sudivsLiteral1) ;
                        sprintf(str_ivs2, "%d",sudivsLiteral2) ;
                        fprintf(fp, "%s %s %d\n",str_ivs1, str_ivs2, 0) ;
                        int literal1 = mapSudokuToLiteral(sudivsLiteral1) ;
                        int literal2 = mapSudokuToLiteral(sudivsLiteral2) ;
                        sprintf(str_ivs1, "%d", literal1) ;
                        sprintf(str_ivs2, "%d", literal2) ;
                        fprintf(fpCNF, "%s %s %d\n", str_ivs1, str_ivs2, 0) ;
                    }
                }
            }
        }
        //    fprintf(fp, "above : row , below : line \n") ;
        
        for (int row = 1 ; row <= 9 ; row++) {
            for (int num = 1 ; num <= 9 ; num++) {
                for (int line = 1 ; line <= 8 ; line++) {
                    for (int i = line + 1 ; i <= 9 ; i++) {
                        int sudivsLiteral1 = -(row * 100 + line * 10 + num) ;
                        int sudivsLiteral2 = -(row * 100 + i * 10 + num) ;
                        char str_ivs1[5], str_ivs2[5] ;
                        sprintf(str_ivs1, "%d",sudivsLiteral1) ;
                        sprintf(str_ivs2, "%d",sudivsLiteral2) ;
                        fprintf(fp, "%s %s %d\n",str_ivs1, str_ivs2, 0) ;
                        
                        int literal1 = mapSudokuToLiteral(sudivsLiteral1) ;
                        int literal2 = mapSudokuToLiteral(sudivsLiteral2) ;
                        sprintf(str_ivs1, "%d", literal1) ;
                        sprintf(str_ivs2, "%d", literal2) ;
                        fprintf(fpCNF, "%s %s %d\n", str_ivs1, str_ivs2, 0) ;
                    }
                }
            }
        }
        
        //    fprintf(fp, "==========above : line & row , below : 3*3===========\n") ;
        for (int num = 1 ; num <= 9 ; num++) {
            for (int i = 0 ; i <= 2 ; i++) {
                for (int j = 0 ; j <= 2 ; j++) {
                    for (int x =1 ; x <=3 ; x++) {
                        for (int y = 1 ; y <= 3 ; y++) {
                            for (int k = y+1 ; k <= 3 ; k++) {
                                int sudivsLiter1 = -((3 * i + x) * 100 + (3 * j + y)*10 + num) ;
                                int sudivsLiter2 = -((3 * i + x) * 100 + (3 * j + k)*10 + num) ;
                                char str_ivs1[5], str_ivs2[5] ;
                                sprintf(str_ivs1, "%d", sudivsLiter1) ;
                                sprintf(str_ivs2, "%d", sudivsLiter2) ;
                                fprintf(fp, "%s %s %d\n",str_ivs1, str_ivs2, 0) ;
                                
                                int literal1 = mapSudokuToLiteral(sudivsLiter1) ;
                                int literal2 = mapSudokuToLiteral(sudivsLiter2) ;
                                sprintf(str_ivs1, "%d", literal1) ;
                                sprintf(str_ivs2, "%d", literal2) ;
                                fprintf(fpCNF, "%s %s %d\n", str_ivs1, str_ivs2, 0) ;
                            }
                        }
                    }
                }
            }
        }
        //    fprintf(fp, "==========separate===========\n") ;
        for (int num = 1 ; num <= 9 ; num++) {
            for (int i = 0 ; i <= 2 ; i++) {
                for (int j = 0 ; j <= 2 ; j++) {
                    for (int x = 1 ; x <= 3 ; x++) {
                        for (int y = 1 ; y <= 3 ; y++) {
                            for (int k = x + 1 ; k <= 3 ; k++) {
                                for (int l = 1 ; l <= 3 ; l++) {
                                    int sudivsLiter1 = -((3 * i + x) * 100 + (3 * j + y)*10 + num) ;
                                    int sudivsLiter2 = -((3 * i + k) * 100 + (3 * j + l)*10 + num) ;
                                    char str_ivs1[5], str_ivs2[5] ;
                                    sprintf(str_ivs1, "%d", sudivsLiter1) ;
                                    sprintf(str_ivs2, "%d", sudivsLiter2) ;
                                    fprintf(fp, "%s %s %d\n",str_ivs1, str_ivs2, 0) ;
                                    
                                    int literal1 = mapSudokuToLiteral(sudivsLiter1) ;
                                    int literal2 = mapSudokuToLiteral(sudivsLiter2) ;
                                    sprintf(str_ivs1, "%d", literal1) ;
                                    sprintf(str_ivs2, "%d", literal2) ;
                                    fprintf(fpCNF, "%s %s %d\n", str_ivs1, str_ivs2, 0) ;
                                }
                            }
                        }
                    }
                }
            }
        }
        
        //    fprintf(fp, "++++++++++++above : all minimal encoding ++++++++++++++++++++++++\n") ;
        //
        for (int row = 1 ; row <= 9 ; row++) {
            for (int line = 1 ; line <= 9 ; line++) {
                for (int num = 1 ; num <= 8 ; num++) {
                    for (int i = num + 1 ; i <= 9 ; i++) {
                        int sudivsLiteral1 = -(row * 100 + line * 10 + num) ;
                        int sudivsLiteral2 = -(row * 100 + line * 10 + i) ;
                        char str_ivs1[5], str_ivs2[5] ;
                        sprintf(str_ivs1, "%d",sudivsLiteral1) ;
                        sprintf(str_ivs2, "%d",sudivsLiteral2) ;
                        fprintf(fp, "%s %s %d\n",str_ivs1, str_ivs2, 0) ;
                        
                        int literal1 = mapSudokuToLiteral(sudivsLiteral1) ;
                        int literal2 = mapSudokuToLiteral(sudivsLiteral2) ;
                        sprintf(str_ivs1, "%d", literal1) ;
                        sprintf(str_ivs2, "%d", literal2) ;
                        fprintf(fpCNF, "%s %s %d\n", str_ivs1, str_ivs2, 0) ;
                    }
                }
            }
        }
        //    fprintf(fp, "++++++++++++above : most one entry ++++++++++++++++++++++++\n") ;
        //
        for (int line = 1 ; line <= 9 ; line++) {
            for (int num = 1 ; num <= 9 ; num++) {
                for (int row = 1 ; row <= 9 ; row++) {
                    int sudliteral = row * 100 + line * 10 + num ;
                    char str_lit[4] ;
                    sprintf(str_lit, "%d",sudliteral) ;
                    fprintf(fp, "%s ",str_lit) ;
                    
                    int literal = mapSudokuToLiteral(sudliteral) ;
                    sprintf(str_lit, "%d",literal) ;
                    fprintf(fpCNF, "%s ", str_lit) ;
                }
                fprintf(fp, "%d\n",0) ;
                fprintf(fpCNF, "%d\n", 0) ;
            }
        }
        //    fprintf(fp, "++++++++++++above : most row ++++++++++++++++++++++++\n") ;
        //
        for (int row = 1 ; row <= 9 ; row++) {
            for (int num = 1 ; num <= 9 ; num++) {
                for (int line = 1 ; line <= 9 ; line++) {
                    int sudliteral = row * 100 + line * 10 + num ;
                    char str_lit[4] ;
                    sprintf(str_lit, "%d",sudliteral) ;
                    fprintf(fp, "%s ",str_lit) ;
                    
                    int literal = mapSudokuToLiteral(sudliteral) ;
                    sprintf(str_lit, "%d", literal) ;
                    fprintf(fpCNF, "%s ",str_lit) ;
                }
                fprintf(fp, "%d\n",0) ;
                fprintf(fpCNF, "%d\n", 0) ;
            }
        }
        //    fprintf(fp, "++++++++++++above : most colume ++++++++++++++++++++++++\n") ;
        //
        for (int num = 1 ; num <= 9 ; num++) {
            for (int i = 0 ; i <= 2 ; i++) {
                for (int j = 0 ; j <= 2 ; j++) {
                    int count = 0 ;
                    for (int x = 1 ; x <= 3 ; x++) {
                        for (int y = 1 ; y <= 3 ; y++) {
                            count ++ ;
                            int sudliter = (3 * i + x) * 100 + (3 * j + y) * 10 + num ;
                            char str_lit[4] ;
                            sprintf(str_lit, "%d", sudliter) ;
                            fprintf(fp, "%s ",str_lit) ;
                            if(count == 9)fprintf(fp, "%d\n",0) ;
                            
                            int liter = mapSudokuToLiteral(sudliter) ;
                            sprintf(str_lit, "%d",liter) ;
                            fprintf(fpCNF, "%s ", str_lit) ;
                            if(count == 9)fprintf(fpCNF, "%d\n", 0) ;
                        }
                        
                    }
                }
            }
        }
        //unit
        for (int i = 0 ; i < 9 ; i++) {
            for (int j = 0 ; j < 9 ; j++) {
                if(sudoku[i][j]){
                    int sudliteral = (i+1) * 100 + (j + 1) * 10 + sudoku[i][j] ;
                    fprintf(fp, "%d 0\n",sudliteral) ;
                    
                    int literal = mapSudokuToLiteral(sudliteral) ;
                    fprintf(fpCNF, "%d 0\n",literal) ;
                }
            }
        }
        fprintf(fpCNF, "0") ;
    }
    fclose(fp) ;
    fclose(fpCNF) ;
    return 1 ;
}

int mapSudokuToLiteral(int sudoku){
    int index = 0 ;
    for (int i = 1 ; i <= 9 ;i++) {
        for (int j = 1 ; j <= 9 ; j++) {
            for (int num = 1 ; num <= 9 ; num++) {
                int sud = 100 * i + 10 * j + num ;
                if(sud == sudoku)return index + 1 ;
                else if (sud == -sudoku) return -(index + 1 ) ;
                else index++ ;
            }
        }
    }
    return 0 ;
}

int mapLiteralToSudoku(int literal){
    int * sudoku = (int *)malloc(sizeof(int) * 729) ;
    int index = 0 ;
    for (int i = 1 ; i <= 9 ;i++) {
        for (int j = 1 ; j <= 9 ; j++) {
            for (int num = 1 ; num <= 9 ; num++) {
                int sud = 100 * i + 10 * j + num ;
                sudoku[index++] = sud ;
            }
        }
    }
    int sud = literal ? sudoku[literal - 1] : -sudoku[-literal - 1] ;
    free(sudoku) ;
    return sud ;
}

char * transferSudToCNFFile(char * sudPath){
    char * CNFPath = (char *)malloc(sizeof(char) * 50) ;
    CNFPath = strncpy(CNFPath, sudPath, strlen(sudPath) - strlen(".sud")) ;
    strcat(CNFPath, ".cnf") ;
    FILE * fpSUD ;
    FILE * fpCNF ;
    if (!(fpSUD = fopen(sudPath, "r"))) {
        printf("SUD_File_Error\n") ;
        return NULL ;
    }
    else{
        if(!(fpCNF = fopen(CNFPath, "w"))){
            printf("CNF_Create_Error\n") ;
            return NULL ;
        }
        else{
#pragma mark - read comment
            int literalNum, clauseNum ;
            char ch ;
            while ((ch = getc(fpSUD) == 'c')) {
                while((ch = getc(fpSUD)) != '\n') ;
            }
            //read sud (literalNum and clauseNum)
            for(int i = 0 ; i < 5 ; i++)fgetc(fpSUD) ;
            fscanf(fpSUD, "%d %d", &literalNum, &clauseNum) ;
            //write cnf
            fprintf(fpCNF, "c\np cnf %d %d\n",literalNum, clauseNum) ;
#pragma mark - transfer sud to cnf line
            int sudLiteral ;
//            for(int i = 0 ; i < clauseNum ; i++){
//                while(fscanf(fpSUD, "%d",&sudLiteral) && sudLiteral){
//                    int literal = mapSudokuToLiteral(sudLiteral) ;
//                    fprintf(fpCNF, "%d ", literal) ;
//                }fprintf(fpCNF, "0 \n") ;
//            }
            while(fscanf(fpSUD, "%d",&sudLiteral)){
                if(sudLiteral){
                    int literal = mapSudokuToLiteral(sudLiteral) ;
                    fprintf(fpCNF, "%d ", literal) ;
                }
                else{
                    fprintf(fpCNF, "0 \n") ;
                }
            }
        }
    }
    return CNFPath ;
}

void transferSudokuAnswer(char * filePath){
    FILE * fp = NULL ;
    if(!(fp = fopen(filePath, "r"))){
        printf("Sudoku_Answer_Transfer_Error\n") ;
    }
    else{
        char c = fgetc(fp) ;
        int ans ;
        fscanf(fp, "%d", &ans) ;
        c = fgetc(fp) ;
        if(ans){
            int sudLiteral, row, line, num ;
            int sudoku[9][9] ;
            if((c = fgetc(fp) == 'v')){
                while (fscanf(fp, "%d", &sudLiteral)) {
                    if(sudLiteral > 0){
                        int sud = mapLiteralToSudoku(sudLiteral) ;
                        row = sud / 100 ;
                        line = (sud / 10) % 10 ;
                        num = sud % 10 ;
                        sudoku[row - 1][line - 1] = num ;
                    }
                }
            }
            FILE * fpSd = NULL ;
            
            if(!(fpSd = fopen("/Users/chuqiz/2018/CourseDesign/SAT/sudoku/sudoku_answer.txt", "w"))){
                printf("put_SUDOKU_ANSWER_ERROR\n") ;
            }else{
                for (int i = 0 ; i < 9 ; i++) {
                    for (int j = 0 ; j < 9 ; j++) {
                        fprintf(fpSd, "%d ", sudoku[i][j]) ;
                    }fprintf(fpSd, "\n") ;
                }
                fclose(fpSd) ;
            }
        }
    }
}

void createSudoku(int sudoku[9][9]){
    //随机生成第一行
    int j ;
    srand((unsigned int)time(NULL)) ;
    for (int i = 0; i < 9 ; i++) {
        sudoku[0][i] = rand() % 9 + 1 ; //random from sudoku[0][0] - sudoku[0][9] with random 1 - 9
        j = 0 ;
        while (j < i) {                 //checkout duplication
            if(sudoku[0][i] == sudoku[0][j]){
                sudoku[0][i] = rand() % 9 + 1 ;
                j = 0 ;
            }else{
                j++ ;
            }
        }
    }
    //generate other rows
    int bool = recursionSudoku(sudoku, 1, 0);
    while (!bool) {
        bool = recursionSudoku(sudoku, 1, 0) ;
    }
}
int recursionSudoku(int sudoku[9][9], int arow , int aline){
    if( arow < 9 && aline < 9){
        int saver[10] = {1,1,1,1,1,1,1,1,1,1} ;  //占位
        int step ;
        //check duplication numbers and mark 0
        for (step = 0 ; step < arow; step++) {
            saver[sudoku[step][aline]] = 0 ;     //mark the number that the line used
        }
        for (step = 0 ; step < aline ; step++){
            saver[sudoku[arow][step]] = 0 ;      //mark the number that the row used
        }
        for (step = arow / 3 * 3; step <= arow ; step++) {            //mark 3*3 grids used
            if(step == arow){
                for (int lineStp = aline / 3 * 3 ; lineStp < aline ; lineStp++) {
                    saver[sudoku[step][lineStp]] = 0 ;
                }
            }
            else{
                for (int lineStp = aline / 3 * 3; lineStp < aline / 3 * 3 + 3; lineStp++) {
                    saver[sudoku[step][lineStp]] = 0 ;
                }
            }
        }
        
        int flag = 0 ;
        for (int num = 1 ; num <= 9 && flag == 0 ; num++) {
            if(saver[num]){
                flag = 1 ;
                sudoku[arow][aline] = num ;
                if(aline == 8 && arow != 8){     //recursion the next row until the row9
                    if(recursionSudoku(sudoku, arow + 1 , 0)) return 1 ;
                    else flag = 0 ;
                }
                else if(aline != 8){             //recursion the next line until the line9
                    if(recursionSudoku(sudoku, arow, aline + 1)) return 1 ;
                    else flag = 0 ;
                }
            }
        }
        if(!flag){
            sudoku[arow][aline] = 0 ;
            return 0 ;
        }
    }
    return 1 ;
}

void createStartingBoard(int sudoku[9][9], int board[9][9], int holes){
//    int i, j, k ;
    srand((unsigned int)time(NULL)) ;
    //copy sudoku
    for (int i = 0 ; i < 9 ; i++) {
        for (int j = 0 ; j < 9 ; j++) {
            board[i][j] = sudoku[i][j] ;
        }
    }
    
}

//solve
int DFSSovleSudoku(int sudokuBoard[9][9], int r[9][10], int c[9][10], int b[9][10]){
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if(sudokuBoard[i][j] == 0) {
                int k = i / 3 * 3 + j / 3;
                // 尝试填入1~9
                for(int n = 1; n < 10; n++) {
                    if(!r[i][n] && !c[j][n] && !b[k][n]) {
                        // 尝试填入一个数
                        r[i][n] = 1;
                        c[j][n] = 1;
                        b[k][n] = 1;
                        sudokuBoard[i][j] = n;
                        // 检查是否满足数独正解
                        if(DFSSovleSudoku(sudokuBoard, r, c, b))return 1 ;
                        // 不满足则回溯
                        r[i][n] = 0;
                        c[j][n] = 0;
                        b[k][n] = 0;
                        sudokuBoard[i][j] = 0;
                    }
                }
                // 尝试所有数字都不满足则回溯
                return 0;
            }
        }

    }
    
    return 1;
}

int lasVegasCreateSudoku(int n){
    extern int sudokuBoard[9][9] ;
    extern int r[9][10] ;
    extern int c[9][10] ;
    extern int b[9][10] ;
    int i, j, k, value;
    srand((unsigned int)time(NULL)) ;
    // 初始化
    for(i = 0; i < 9; i++) {
        for(j = 0; j < 9; j++) {
            sudokuBoard[i][j] = 0;
            r[i][j+1] = 0;
            c[i][j+1] = 0;
            b[i][j+1] = 0;
        }
    }
    
    // 随机填入数字
    while(n > 0) {
        i = rand() % 9;
        j = rand() % 9;
        if(sudokuBoard[i][j] == 0) {
            k = i / 3 * 3 + j / 3;
            value = rand() % 9 + 1 ;
            if(!r[i][value] && !c[j][value] && !b[k][value]) {
                sudokuBoard[i][j] = value;
                r[i][value] = 1;
                c[j][value] = 1;
                b[k][value] = 1;
                n--;
            }
        }
    }
    // 检查并且生成一个数组解
    if(DFSSovleSudoku(sudokuBoard, r, c, b))
        return 1;
    else
        return 0;
}

void generateSudokuByDigHoles(int remains){
    extern int sudokuBoard[9][9] ;
    extern int sudokuSolution[9][9] ;
    extern int r[9][10] ;
    extern int c[9][10] ;
    extern int b[9][10] ;
    for (int i = 0 ; i < 9 ; i++) {
        for (int j = 0 ; j < 9 ; j++) {
            sudokuSolution[i][j] = sudokuBoard[i][j] ;
        }
    }
    // 从上到下从左到右的顺序挖洞
    int level = 0 ;
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if(uniqueSolution(i, j)) {
                int k = i / 3 * 3 + j / 3;
                r[i][sudokuBoard[i][j]] = 0;
                c[j][sudokuBoard[i][j]] = 0;
                b[k][sudokuBoard[i][j]] = 0;
                sudokuBoard[i][j] = 0;
                level++;
                if(81 == level)
                    break;
            }
        }
    }
}

int uniqueSolution(int row, int col){
    extern int sudokuBoard[9][9] ;
    extern int r[9][10] ;
    extern int c[9][10] ;
    extern int b[9][10] ;
    // 挖掉第一个位置一定有唯一解
    if(row == 0 && col == 0)
        return 1;
    
    int k = row / 3 * 3 + col / 3;
//    boolean[][] trows = new boolean[9][10];
//    boolean[][] tcols = new boolean[9][10];
//    boolean[][] tblocks = new boolean[9][10];
    int trows[9][10] = {0} ;
    int tcols[9][10] = {0} ;
    int tblocks[9][10] = {0} ;
//    int[][] tfield = new int[9][9];
    int tfield[9][9] = {0} ;
    
    // 临时数组
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            trows[i][j+1] = r[i][j+1];
            tcols[i][j+1] = c[i][j+1];
            tblocks[i][j+1] = b[i][j+1];
            tfield[i][j] = sudokuBoard[i][j];
        }
    }
    
    // 假设挖掉这个数字
    trows[row][sudokuBoard[row][col]] = 0;
    tcols[col][sudokuBoard[row][col]] = 0;
    tblocks[k][sudokuBoard[row][col]] = 0;
    
    for(int i = 1; i < 10; i++)
        if(i != sudokuBoard[row][col]) {
            tfield[row][col] = i;
            if(!trows[row][i] && !tcols[col][i] && !tblocks[k][i]) {
                trows[row][i] = 1;
                tcols[col][i] = 1;
                tblocks[k][i] = 1;
                // 更换一个数字之后检查是否还有另一解
                if(DFSSovleSudoku(tfield, trows, tcols, tblocks))
                    return 0;
                trows[row][i] = 0;
                tcols[col][i] = 0;
                tblocks[k][i] = 0;
            }
        }
    // 已尝试所有其他数字发现无解即只有唯一解
    return 1 ;
}
