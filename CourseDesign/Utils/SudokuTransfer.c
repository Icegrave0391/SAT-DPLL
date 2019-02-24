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
#define constraintCount 11988
void transferConstraintToFile(int sudoku[9][9]){
    FILE * fp = NULL ;
    FILE * fpCNF = NULL ;
    char * sudFilePath = "/Users/chuqiz/2018/CourseDesign/SAT/sudoku.sud" ;
    char * CNFFilePath = "/Users/chuqiz/2018/CourseDesign/SAT/sudoku.cnf" ;
    if(!(fp = fopen(sudFilePath, "w"))){
        printf("File_Transfer_Error\n") ;
        return ;
    }else{
        if(!(fpCNF = fopen(CNFFilePath, "w"))){
            printf("CNFFile_Transfer_Error\n") ;
            return ;
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
            
            if(!(fpSd = fopen("/Users/chuqiz/2018/CourseDesign/SAT/sudoku_answer.txt", "w"))){
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
