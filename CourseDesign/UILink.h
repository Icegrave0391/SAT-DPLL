//
//  UILink.h
//  CourseDesign
//
//  Created by 张储祺 on 2019/2/25.
//  Copyright © 2019 icegrave0391. All rights reserved.
//

#ifndef UILink_h
#define UILink_h

#include <stdio.h>
#include <time.h>
#include "CNFFileManager.h"
#include "DPLLMethod.h"
#include "SudokuTransfer.h"
#include <string.h>
extern int totalLiteralCount, totalClauseCount ;
extern int * allLiteralArr ;
extern int sudokuBoard[9][9] ;
extern int sudokuSolution[9][9] ;
extern int r[9][10] ;
extern int c[9][10] ;
extern int b[9][10] ;

void showModule(void) ;

#endif /* UILink_h */
