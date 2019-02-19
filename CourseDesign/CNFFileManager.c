//
//  CNFFileManager.c
//  CourseDesign
//
//  Created by 张储祺 on 2019/2/18.
//  Copyright © 2019 icegrave0391. All rights reserved.
//

#include "CNFFileManager.h"

formulaList loadCNFFileFormula(char * filePath){
    FILE * fp = NULL ;
    int literal, count = 0 ;
    int literalNum, clauseNum ;
    formulaList list ;
    init(&list) ;
    
    if(!(fp = fopen(filePath, "r"))){
        printf("File_Operate_Error\n") ;
        return NULL ;
    }else{
        //read comments
        char ch = fgetc(fp) ;
        while (ch == 'c') {
            while (ch != '\n') {
                ch = fgetc(fp) ;
            }
        }
        //read p (literalNum and clauseNum)
        for(int i = 0 ; i < 5 ; i++)fgetc(fp) ;
        fscanf(fp, "%d %d", &literalNum, &clauseNum) ;
        //read literals
        for(int i = 0 ; i < clauseNum ; i++){
            int * arr = (int *)malloc(sizeof(int) * literalNum) ;
            while(fscanf(fp, "%d",&literal)){
                arr[count ++] = literal ;
            }
            clause cls = createClause(count, ClauseStatusStill, arr) ;
            addClause(list, cls) ;
            free(arr) ;
        }
    }
    return list;
}
