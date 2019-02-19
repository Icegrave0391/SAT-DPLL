//
//  main.c
//  CourseDesign
//
//  Created by 张储祺 on 2019/2/18.
//  Copyright © 2019 icegrave0391. All rights reserved.
//

#include <stdio.h>
#include "CNFFileManager.h"

int main(int argc, const char * argv[]) {
    formulaList list ;
    list = loadCNFFileFormula("/Users/chuqiz/2018/CourseDesign/SAT/不满足算例/tst_v10_c100.cnf") ;
    
    return 0;
}
