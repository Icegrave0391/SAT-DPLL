//
//  SudokuTransfer.h
//  CourseDesign
//
//  Created by 张储祺 on 2019/2/23.
//  Copyright © 2019 icegrave0391. All rights reserved.
//

#ifndef SudokuTransfer_h
#define SudokuTransfer_h

#include <stdio.h>
//return both constraint .sud file and sudoku.cnf file
void transferConstraintToFile(int sudoku[9][9]) ;
//char * transferSudToCNFFile(char * sudPath) ;
//should only be sudoku constraint literal (111 - 999 without number 0)
int mapSudokuToLiteral(int sudoku) ;
int mapLiteralToSudoku(int literal) ;

//operate param : .res sudoku file
void transferSudokuAnswer(char * filePath) ;
#endif /* SudokuTransfer_h */
