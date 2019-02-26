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
//    formulaList currP = Ls ;
//    while (currP) {
//        if(currP -> clause -> clauseStatus == ClauseStatusStill) return 0 ;
//        currP = currP -> next ;
//    }
//    return 1 ;
    if(!(Ls -> clause) && !(Ls -> next))return 1 ;
    return 0 ;
}

int clauseNum(formulaList Ls){
    int count = 0 ;
    formulaList currP = Ls ;
//    while(currP){
//        if(currP -> clause -> clauseStatus == ClauseStatusStill) count ++ ;
//        currP = currP -> next;
//    }
    while (currP) {
        if(currP -> clause)count++ ;
        currP = currP -> next ;
    }
    return count ;
}

void addClause(formulaList * ls, clause cls){
    if(!(*ls)){
        (*ls) = (formulaList)malloc(sizeof(struct FormulaNode)) ;
        (*ls) -> clause = cls ;
        (*ls) -> next = NULL ;
    }else{
        if(!(*ls) -> clause){
            //        formulaList newElemP = (formulaList)malloc(sizeof(struct FormulaNode)) ;
            //        newElemP -> next = NULL ;
            //        newElemP -> clause = cls ;
            //        (*ls) = newa
            (*ls) -> clause = cls ;
        }else{
            formulaList currP = (*ls) ;   //init : head
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
DeleteClauseStatus deleteClause(formulaList * ls, clause cls){
    #pragma mark - real delete
// only one node
    if(!((*ls) -> next)){
        if ((*ls) -> clause == cls) {
            (*ls) -> clause = NULL ;
//            free(cls) ;
            return DeleteClauseStatusSuccessful ;
        }else{
            return DeleteClauseStatusNotFound ;
        }
    }
//delete first node
    else if((*ls) -> next && (*ls) -> clause == cls){
        *ls =  (*ls) -> next ;
//        free(cls) ;
        return DeleteClauseStatusSuccessful ;
    }
    else{
        formulaList * currp = ls ;
        formulaList * prevp = ls ;
        while( ((*currp) -> next) && ((*currp) -> clause != cls)){
            prevp = currp ;
            currp = &(*currp) -> next ;
        }
        if((*currp) -> clause == cls){
            if((*currp) -> next){
                (*prevp) -> next = (*currp) -> next ;
            }else{
                (*prevp) -> next = NULL ;
            }
//            free(cls) ;
            return DeleteClauseStatusSuccessful ;
        }
        return DeleteClauseStatusNotFound ;
    }
   #pragma mark - delete via status
//    formulaList currP = Ls ;
//    while (currP) {
//        if(currP -> clause -> clauseStatus == ClauseStatusStill && currP -> clause == cls){
//            currP -> clause -> clauseStatus = ClauseStatusDeleted ;
//            return DeleteClauseStatusSuccessful ;
//        }
//        currP = currP -> next ;
//    }
//    return DeleteClauseStatusNotFound ;
}

clause findUnitClause(formulaList Ls){
    if(isFormulaEmpty(Ls))return NULL ;
    formulaList currP = Ls ;
    while (currP) {
        if(isUnitClause(* (currP -> clause)))return currP -> clause ;
        currP = currP -> next ;
    }
    return NULL ;
}

clause findFirstStillClase(formulaList Ls){
//    formulaList currP = Ls ;
//    while (currP) {
//        if(currP -> clause -> clauseStatus == ClauseStatusStill)return currP -> clause ;
//        currP = currP -> next ;
//    }
//    return NULL ;
    if(isFormulaEmpty(Ls))return NULL ;
    else return Ls -> clause ;
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
        addClause(&cpyList, cls) ;
        currP = currP -> next ;
    }
    return cpyList ;
}
