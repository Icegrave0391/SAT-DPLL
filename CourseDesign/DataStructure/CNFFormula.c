//
//  CNFFormula.c
//  CourseDesign
//
//  Created by 张储祺 on 2019/2/18.
//  Copyright © 2019 icegrave0391. All rights reserved.
//

#include "CNFFormula.h"
int init(formulaList * ls){
    *ls = (formulaList)malloc(sizeof(struct FormulaNode)) ;
    if(*ls == NULL) return 0 ;
    (*ls) -> clause = NULL ;
    (*ls) -> next = NULL ;
    return 1 ;
}

int formulaEmpty(formulaList Ls){
    if(Ls -> next == NULL)return 1 ;
    return 0 ;
}

int clauseNum(formulaList Ls){
    int count = 0 ;
    formulaList currP = Ls ;
    while(currP){
        count++ ;
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

int deleteClause(formulaList Ls, clause cls){
    formulaList currP = Ls ; //init : head
    formulaList prevP = NULL ;
    while((currP -> next) && (currP -> clause != cls)){
        prevP = currP ;
        currP = currP -> next ;
    }
    if(currP -> clause == cls){
        if(currP -> next){
            prevP -> next = currP -> next ;
        }
        else{
            prevP -> next = NULL ;
        }
        return 1 ;
    }else{     // no match clause
        return 0 ;
    }
}
