//
//  CNFClause.c
//  CourseDesign
//
//  Created by 张储祺 on 2019/2/18.
//  Copyright © 2019 icegrave0391. All rights reserved.
//

#include "CNFClause.h"
#include <string.h>
int initClause(clause * cls){
    *cls = (clause)malloc(sizeof(Clause)) ;
    if(!*cls)return 0 ;
    (*cls) -> literal = 0 ;
    (*cls) -> next = NULL ;
    return 1 ;
}
//clause createClause(int literalNum, int * literals){
//    clause cls = (clause)malloc(sizeof(Clause)) ;
////    cls -> clauseStatus = clsStatus ;
//    cls -> literalCount = literalNum ;
//    cls -> literals = (int *)malloc(sizeof(int) * literalNum) ;
//    memcpy(cls -> literals, literals, literalNum * sizeof(int)) ;
//    return cls ;
//}

clause deepCpyClause(clause aclause){
//    int literalNum = aclause -> literalCount ;
//    ClauseStatus clsStatus = aclause -> clauseStatus ;
//    int * literals = (int *)malloc(sizeof(int) * literalNum) ;
//    memcpy(literals, aclause -> literals, literalNum * sizeof(int)) ;
//    clause cls = createClause(literalNum, literals) ;
    clause cpyCls = NULL ;
    initClause(&cpyCls) ;
    while (aclause) {
        addLiteral(&cpyCls, aclause -> literal) ;
        aclause = aclause -> next ;
    }
    return cpyCls ;
}

void addLiteral(clause * cls, int literal){
    if(!(*cls)){
        (*cls) = (clause)malloc(sizeof(Clause)) ;
        (*cls) -> literal = literal ;
        (*cls) -> next = NULL ;
    }else{
        if(!(*cls) -> literal){
            //        formulaList newElemP = (formulaList)malloc(sizeof(struct FormulaNode)) ;
            //        newElemP -> next = NULL ;
            //        newElemP -> clause = cls ;
            //        (*ls) = newa
            (*cls) -> literal = literal ;
        }else{
            clause currP = (*cls) ;   //init : head
            clause tailP = NULL ;
            while (currP) {
                tailP = currP ;
                currP = currP -> next ;
            }
            clause newElemP = (clause)malloc(sizeof(Clause)) ;
            newElemP -> next = NULL ;
            newElemP -> literal = literal ;
            tailP -> next = newElemP ;
        }
    }
}
//unit clause : 1.statusStill 2.literals contains only 1 elem not 0
int isUnitClause (Clause cls){
//    int flag = 0 ;
//    for(int i = 0 ; i < cls.literalCount ; i++){
//        if(cls.literals[i]) flag++ ;
//    }
//    if (flag == 1)return 1 ;
//    return 0;
    if(!cls.next && cls.literal) return 1 ;
    return 0 ;
}

int isEmptyClause(Clause cls){
//    for (int i = 0 ; i < cls.literalCount ; i++) {
//        if(cls.literals[i])return 0 ;
//    }
//    return 1 ;
    if(!cls.literal && !cls.next)return 1 ;
    return 0 ;
}

LiteralContainStatus literalStatusWithClause(Clause Cls, int literal){
    clause currP = &Cls ;
    while (currP) {
        if(currP -> literal == literal) return LiteralContainStatusContain ;
        else if (currP -> literal == - literal) return LiteralContainStatusContainInverse ;
        currP = currP -> next ;
    }
//    int iter = 0 ;
//    while (iter < Cls.literalCount) {
//        if(Cls.literals[iter] == literal) return LiteralContainStatusContain ;
//        else if(Cls.literals[iter] == - literal) return LiteralContainStatusContainInverse ;
//        iter ++ ;
//    }
    return LiteralContainStatusNotContain ;
}

void deleteLiteral(clause * cls, int literal){
    extern int emptyClause ;
    //only one
    if(! (*cls) -> next){
        if((*cls) -> literal == literal) (*cls) -> literal = 0 ;
        emptyClause = 1 ;
    }
    else if((*cls) -> next && (*cls) -> literal == literal){
        * cls = (*cls) -> next ;
    }
    else{
        clause * currp = cls ;
        clause * prevp = cls ;
        while ((*currp) -> next && (*currp) -> literal != literal) {
            prevp = currp ;
            currp = &(*currp) -> next ;
        }
        if((*currp) -> literal == literal){
            if((*currp) -> next){
                (*prevp) -> next = (*currp) -> next ;
            }else{
                (*prevp) -> next = NULL ;
            }
        }
    }
}

int findRandomLiteral(clause cls){
//    if(cls -> clauseStatus == ClauseStatusDeleted || isEmptyClause( *cls)) return 0 ;
//    if(isEmptyClause( *cls)) return 0 ;
    if(cls -> literal) return cls -> literal ;
    return 0 ;
}

int findFirstLiteral(clause cls){
//    for (int i = 0 ; i < cls -> literalCount ; i++) {
//        if (cls -> literals[i]) {
//            return cls -> literals[i] ;
//        }
//    }
    if(cls -> literal) return cls -> literal ;
    return 0 ;
    return  0 ;
}
