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
#pragma mark - literals operate
        //read literals
        for(int i = 0 ; i < clauseNum ; i++){
            int count = 0 ;
            int * arr = (int *)malloc(sizeof(int) * literalNum) ;
            while(fscanf(fp, "%d",&literal) && literal){
                arr[count ++] = literal ;
            }
            
//            for (int i = 0; i < count; i ++) {
//                printf("%d ",arr[i]) ;
//            }printf("\n");
            clause cls = createClause(count, ClauseStatusStill, arr) ;
            for(int i = 0 ; i < cls -> literalCount ; i++){
                printf("%d ", cls -> literals[i]) ;
            }printf("\n") ;
            addClause(list, cls) ;
            free(arr) ;
        }
    }
    list ;
    return list;
}
