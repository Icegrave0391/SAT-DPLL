//
//  CNFFileManager.c
//  CourseDesign
//
//  Created by 张储祺 on 2019/2/18.
//  Copyright © 2019 icegrave0391. All rights reserved.
//

#include "CNFFileManager.h"
extern int totalLiteralCount, totalClauseCount ;
formulaList loadCNFFileFormula(char * filePath){
    FILE * fp = NULL ;
    int literal ;
    int literalNum, clauseNum ;
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
        totalLiteralCount = literalNum ;
        totalClauseCount = clauseNum ;
#pragma mark - literals operate
        //read literals
        for(int i = 0 ; i < clauseNum ; i++){
//            int count = 0 ;
//            int * arr = (int *)malloc(sizeof(int) * literalNum) ;
            clause cls = NULL ;
            initClause(&cls) ;
            while(fscanf(fp, "%d",&literal) && literal){
//                arr[count ++] = literal ;
                addLiteral(&cls, literal) ;
            }
//            clause cls = createClause(count, arr) ;
            addClause(&list, cls) ;
//            free(arr) ;
        }
    }
    fclose(fp) ;
    return list;
}

int exportDPLLResultFile(char * filePath, int * literalsArr, int DPLLResult, double timeinterval){
    FILE * fp = NULL ;
    if(!(fp = fopen(filePath, "w"))){
        printf("File_Export_Error!\n") ;
        return 0 ;
    }
    else{
        fprintf(fp, "s %d\n", DPLLResult) ;
        if (DPLLResult) {
            fprintf(fp, "v ") ;
            for (int i = 0 ; i < totalLiteralCount ; i++) {
                fprintf(fp, "%d ",literalsArr[i]) ;
            }
            fprintf(fp, "\n") ;
        }
        fprintf(fp, "t %.3fms\n",timeinterval/1000) ;
        fclose(fp) ;
        return 1 ;
    }
}
