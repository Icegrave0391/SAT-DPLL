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
//this method create beginning board to both constraints .sud file and .cnf file
int transferConstraintToFile(int sudoku[9][9]) ;
//char * transferSudToCNFFile(char * sudPath) ;
//should only be sudoku constraint literal (111 - 999 without number 0)
int mapSudokuToLiteral(int sudoku) ;
int mapLiteralToSudoku(int literal) ;
// this method should only be used in .res file
void transferSudokuAnswer(char * filePath) ;
#pragma mark - create sudoku & beginning board
void createSudoku(int sudoku[9][9]) ;
void createStartingBoard(int sudoku[9][9], int board[9][9], int holes) ;


int DFSSovleSudoku(int sudokuBoard[9][9], int r[9][10], int c[9][10], int b[9][10]) ;
// n means write n random nums
int lasVegasCreateSudoku(int n) ;
void generateSudokuByDigHoles(int remains) ;
int uniqueSolution(int row, int line) ;
#endif /* SudokuTransfer_h */
