//
//  CNFLiteralStack.c
//  CourseDesign
//
//  Created by 张储祺 on 2019/2/22.
//  Copyright © 2019 icegrave0391. All rights reserved.
//

#include "CNFLiteralStack.h"
#include <stdlib.h>
Stack * initStack(){
    Stack * s;
    s = (Stack *)malloc(sizeof(Stack));
    s->next = NULL;
    return s;
}

int isEmpty(Stack * s){
    return (s->next == NULL);
}

void push(Stack * s,int literal){
    Stack * cell = (Stack *)malloc(sizeof(Stack));
    cell->literal = literal ;
    cell->next = s->next ;
    s->next = cell;
}


int pop(Stack * s){
    Stack * firstCell;
    if(isEmpty(s)) return 0;
    firstCell = s->next;
    s->next = firstCell->next;
    int top = firstCell -> literal ;
    free(firstCell);
    return top;
}
