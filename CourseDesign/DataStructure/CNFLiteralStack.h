//
//  CNFLiteralStack.h
//  CourseDesign
//
//  Created by 张储祺 on 2019/2/22.
//  Copyright © 2019 icegrave0391. All rights reserved.
//

#ifndef CNFLiteralStack_h
#define CNFLiteralStack_h

#include <stdio.h>
typedef struct stack{
    int literal;
    struct stack * next;
}Stack;

Stack * initStack(void);
int isEmpty(Stack * s);
void push(Stack * s,int literal);
int pop(Stack * s);
#endif /* CNFLiteralStack_h */
