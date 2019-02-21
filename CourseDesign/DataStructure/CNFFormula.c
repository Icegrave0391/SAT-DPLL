//
//  CNFFormula.c
//  CourseDesign
//
//  Created by 张储祺 on 2019/2/18.
//  Copyright © 2019 icegrave0391. All rights reserved.
//

#include "CNFFormula.h"
#include <string.h>
int init(formulaList * ls){
    *ls = (formulaList)malloc(sizeof(struct FormulaNode)) ;
    if(*ls == NULL) return 0 ;
    (*ls) -> clause = NULL ;
    (*ls) -> next = NULL ;
    return 1 ;
}

int isFormulaEmpty(formulaList Ls){
    formulaList currP = Ls ;
    while (currP) {
        if(currP -> clause -> clauseStatus == ClauseStatusStill) return 0 ;
        currP = currP -> next ;
    }
    return 1 ;
}

int clauseNum(formulaList Ls){
    int count = 0 ;
    formulaList currP = Ls ;
    while(currP){
        if(currP -> clause -> clauseStatus == ClauseStatusStill) count ++ ;
        currP = currP -> next;
    }
    return count ;
}

void addClause(formulaList Ls, clause cls){
    if(!Ls -> clause){
//        formulaList newElemP = (formulaList)malloc(sizeof(struct FormulaNode)) ;
//        newElemP -> next = NULL ;
//        newElemP -> clause = cls ;
//        Ls = newa
        Ls -> clause = cls ;
    }else{
        formulaList currP = Ls ;   //init : head
        formulaList tailP = NULL ;
        while (currP) {
            tailP = currP ;
            currP = currP -> next ;
        }
        formulaList newElemP = (formulaList)malloc(sizeof(struct FormulaNode)) ;
        newElemP -> next = NULL ;
        newElemP -> clause = cls ;
        tailP -> next = newElemP ;
    }
}

void addUnitClause(formulaList * ls, clause cls){
//    if(!Ls -> clause){
//        Ls -> clause = cls ;
//    }else{
//        formulaList currP = Ls ;   //init : head
//        formulaList newElemP = (formulaList)malloc(sizeof(struct FormulaNode)) ;
//        newElemP -> next = currP ;
//        newElemP -> clause = cls ;
//        Ls = newElemP ;
//        printf("%p", Ls) ;
    if(! (*ls) -> clause){
        (*ls) -> clause = cls ;
    }else{
        formulaList currp = * ls ;
        *ls = (formulaList )malloc(sizeof(struct FormulaNode)) ;
        (*ls) -> next = currp ;
        (*ls) -> clause = cls ;
    }
}
DeleteClauseStatus deleteClause(formulaList Ls, clause cls){
    #pragma mark - real delete
//    formulaList currP = Ls ; //init : head
//    formulaList prevP = NULL ;
//    while((currP -> next) && (currP -> clause != cls)){
//        prevP = currP ;
//        currP = currP -> next ;
//    }
//    if(currP -> clause == cls){
//        if(currP -> next){
//            prevP -> next = currP -> next ;
//        }
//        else{
//            prevP -> next = NULL ;
//        }
//        return 1 ;
//    }else{     // no match clause
//        return 0 ;
//    }
   #pragma mark - delete via status
    formulaList currP = Ls ;
    while (currP) {
        if(currP -> clause -> clauseStatus == ClauseStatusStill && currP -> clause == cls){
            currP -> clause -> clauseStatus = ClauseStatusDeleted ;
            return DeleteClauseStatusSuccessful ;
        }
        currP = currP -> next ;
    }
    return DeleteClauseStatusNotFound ;
}

clause findUnitClause(formulaList Ls){
    formulaList currP = Ls ;
    while (currP) {
        if(isUnitClause(* (currP -> clause)))return currP -> clause ;
        currP = currP -> next ;
    }
    return NULL ;
}

clause findFirstStillClase(formulaList Ls){
    formulaList currP = Ls ;
    while (currP) {
        if(currP -> clause -> clauseStatus == ClauseStatusStill)return currP -> clause ;
        currP = currP -> next ;
    }
    return NULL ;
}

int emptyClauseInFormula(formulaList Ls){
    formulaList currP = Ls ;
    while (currP) {
        if(isEmptyClause(* (currP -> clause)))return 1 ;
        currP = currP -> next ;
    }
    return 0 ;
}

formulaList deepCpyFormulaList(formulaList Ls){
    formulaList cpyList = NULL ;
    init(&cpyList) ;
    
    formulaList currP = Ls ;
    while (currP) {
        clause cls = deepCpyClause(currP -> clause) ;
        addClause(cpyList, cls) ;
        currP = currP -> next ;
    }
    return cpyList ;
}
