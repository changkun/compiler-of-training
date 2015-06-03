//
//  semantic.h
//  实验3
//
//  Created by 欧长坤 on 15/5/29.
//  Copyright (c) 2015年 欧长坤. All rights reserved.
//

#ifndef ____3__semantic__
#define ____3__semantic__

#define EXP_LEN 12
typedef struct quad {
    char result[EXP_LEN];
    char ag1[EXP_LEN];
    char op[EXP_LEN];
    char ag2[EXP_LEN];
} QUAD;

char* newtemp();
void emit(char *result, char *ag1, char *op, char *ag2);


#endif /* defined(____3__semantic__) */
