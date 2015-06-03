//
//  semantic.cpp
//  实验3
//
//  Created by 欧长坤 on 15/5/29.
//  Copyright (c) 2015年 欧长坤. All rights reserved.
//

#include "../include/semantic.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "../include/parser.h"
#include "../include/utils.h"

// 用于记录临时变量的个数
int k = 0;
// 用来记录共有多少条四元式
int count = 0;
// 保存三元式
QUAD quad[30];


// 返回临时变量 t1, t2..
char* newtemp() {
    char *p;
    char m[8];
    p = (char*)malloc(8);
    k++;
    itoa(k, m, 10); // 将整数转换为字符串，并将值保存在m中
    strcpy(p+1, m);
    p[0] = 't';
    return p;
    
}

// 将三地址代码送到四元式表
void emit(char *result, char *ag1, char *op, char *ag2) {
    strcpy(quad[count].result, result);
    strcpy(quad[count].ag1, ag1);
    strcpy(quad[count].op, op);
    strcpy(quad[count].ag2, ag2);
    printf("四元式 %d :", count);
    printf("%s = ", result);
    printf("%s", ag1);
    printf("%s", op);
    printf("%s\n", ag2);
    count++;
    return;
}