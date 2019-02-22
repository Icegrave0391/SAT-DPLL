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
    int literal ;
    int literalNum, clauseNum ;
    extern formulaList * literalClauseArr ;
#pragma mark - create formula list
    formulaList list = NULL;
    init(&list) ;
    if(!(fp = fopen(filePath, "r"))){
        printf("File_Operate_Error\n") ;
        return NULL ;
    }else{
        //read comments
        char ch ;
        while ((ch = getc(fp) == 'c')) {
            while((ch = getc(fp)) != '\n') ;
        }
        //read p (literalNum and clauseNum)
        for(int i = 0 ; i < 5 ; i++)fgetc(fp) ;
        fscanf(fp, "%d %d", &literalNum, &clauseNum) ;
        //extern
        extern int totalLiteralCount, totalClauseCount ;
        totalLiteralCount = literalNum ;
        totalClauseCount = clauseNum ;
        literalClauseArr = (formulaList *)malloc(sizeof(formulaList) * totalLiteralCount * 2) ;
        for (int i = 0 ; i < totalLiteralCount * 2 ; i++) {
            literalClauseArr[i] = NULL ;
        }
#pragma mark - literals operate
        //read literals
        for(int i = 0 ; i < clauseNum ; i++){
            int count = 0 ;
            int * arr = (int *)malloc(sizeof(int) * literalNum) ;
            while(fscanf(fp, "%d",&literal) && literal){
                arr[count ++] = literal ;
            }
            clause cls = createClause(count, ClauseStatusStill, arr) ;
            for (int i = 0 ; i < count ; i++) {
                int literal = arr[i] ;
                literal > 0 ? addClause(&literalClauseArr[literal * 2 - 2], cls) : addClause(&literalClauseArr[literal * (-2) - 1], cls) ;
            }
            addClause(&list, cls) ;
            free(arr) ;
        }
    }
    fclose(fp) ;
    return list;
}

void exportDPLLResultFile(char * filePath, int * literalsArr, int DPLLResult){
    FILE * fp = NULL ;
    
}
