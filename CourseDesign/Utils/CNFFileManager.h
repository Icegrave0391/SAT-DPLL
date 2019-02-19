//
//  CNFFileManager.h
//  CourseDesign
//
//  Created by 张储祺 on 2019/2/18.
//  Copyright © 2019 icegrave0391. All rights reserved.
//

#ifndef CNFFileManager_h
#define CNFFileManager_h

#include <stdio.h>
#include "CNFClause.h"
#include "CNFFormula.h"

#pragma mark - read CNF file
formulaList loadCNFFileFormula(char * filePath) ;

#endif /* CNFFileManager_h */
