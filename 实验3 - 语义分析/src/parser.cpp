//
//  parser.cpp
//  实验3
//
//  Created by 欧长坤 on 15/5/29.
//  Copyright (c) 2015年 欧长坤. All rights reserved.
//


#include "../include/parser.h"
#include "../include/utils.h"
#include "../include/semantic.h"

#include <cstdlib>
#include <cstring>

#include "../include/scaner.h"
extern char prog[1000000];
extern char token[TOKEN_LENTH];
extern char ch;
extern int syn;
extern int p;
extern int integer;
extern const char * rwtab[KEY_NUMBER];

extern int lines;
extern bool is_slash_n;

extern QUAD quad[30];
extern int count;

char * empty = (char *)" ";


// 用于标识当前程序是否具有语法错误
int kk = 0;

void print_syn() {
    switch (syn) {
        case 11: printf("(%d, %d)\n", syn, integer);   break;
        case -1: printf("erron\n");                    break;
        case  0: break;
        default: printf("(%d, %s)\n", syn, token);     break;
    }
}


// 用于保存出现了\n后的下一句标示符的syn值
int temp_syn = 0;
char* factor() {                     // 因子分析函数
    char *fplace;
    fplace = (char *)malloc(12);
    strcpy(fplace, empty);
    
    if (syn == 10) {   // 如果是标示符或者整形数字，则忽略，继续读取
        strcpy(fplace, token);
        basic_scaner();
        // 处理某行没有出现';'的情况
        if (is_slash_n == true) {
            temp_syn = syn;
            kk = 1;
            syn = 26;
            return fplace;
        }
        print_syn();
        
    } else if (syn == 11) {
        itoa(integer, fplace, 10);
        basic_scaner();
        // 处理某行没有出现';'的情况
        if (is_slash_n == true) {
            temp_syn = syn;
            kk = 1;
            syn = 26;
            return fplace;
        }
        print_syn();
    } else {                        // 看是否是表达式
        if (syn == 27) {            // 出现括号 '('
            basic_scaner();
            print_syn();
            fplace = expression();           // 对括号内层进一步进行表达式分析
            if (syn == 28) {            // 出现括号 ')'
                basic_scaner();
                if (is_slash_n == true) {
                    temp_syn = syn;
                    kk = 1;
                    syn = 26;
                    return fplace;
                }
                print_syn();
            } else {
                printf("语法分析错误! 右括号缺失！\n");
                kk = 1;
            }
        } else {
                printf("语法分析错误! 表达式错误！\n");
                kk = 1;
        }
    }
    return fplace;
}

char* term() {                          // 项分析函数
    char *tp, *ep2, *eplace, *tt;
    tp = (char *)malloc(12);
    ep2 = (char *)malloc(12);
    eplace = (char *)malloc(12);
    tt = (char *)malloc(12);
    strcpy( eplace, factor());
    
    
    while (syn == 15 || syn == 16) {    // 直到读到 乘法 或者 除法
        if (syn == 15) {
            tt[0] = '*';
            tt[1] = '\0';
        } else if(syn == 16) {
            tt[0] = '/';
            tt[1] = '\0';
        }
        
        basic_scaner();
        print_syn();
        
        strcpy(ep2, factor());
        strcpy(tp, newtemp());
        emit(tp, eplace, tt, ep2);
        strcpy(eplace, tp);
    }
    return eplace;
}

char* expression() {                     // 表达式分析函数
    char *tp, *ep2, *eplace, *tt;
    tp = (char *)malloc(12);
    ep2 = (char *)malloc(12);
    eplace = (char *)malloc(12);
    tt = (char *)malloc(12);
    strcpy(eplace, term());
    
    while (syn == 13 || syn == 14) {    // 出现 '+' 或者 '-'
        
        if (syn == 13) {
            tt[0] = '+';
            tt[1] = '\0';
        } else if (syn == 14) {
            tt[0] = '-';
            tt[1] = '\0';
        }
        
        
        basic_scaner();
        print_syn();
        
        strcpy(ep2, term());                         // 进行项分析
        strcpy(tp, newtemp());
        emit(tp, eplace, tt, ep2);
        strcpy(eplace, tp);
    }
    return eplace;
}


void statement() {
    
    char tt[8] = {0}, eplace[8] = {0};
    
    if (syn == 10) {                    // 标识符
        strcpy(tt, token);
        basic_scaner();
        
        print_syn();
        
        if (syn == 21) {                // 等号'='，说明是赋值语句，处理表达式是否合法
            printf("分析到'='，即赋值语句...\n");
            basic_scaner();
            
            print_syn();
            
            strcpy(eplace, expression());               // 分析表达式，这里实现语法分析判断语句
            emit(tt, eplace, empty, empty);
        } else {
            printf("语法分析错误! 没有赋值符号\n");
            kk = 1;
        }
    } else {
        if (syn == 6) {                 // 如果遇到了end
            ;
        } else { // 分析出错
            printf("语法分析错误! 语句出错！\n");
            basic_scaner();
            
            print_syn();
            kk = 1;
        }
    }
    
}

void yucu() {
    statement();            // 调用语句分析函数
    while (syn == 26) {     // 发现分号 ';' 说明一个语句识别结束，继续识别
        
        // 处理某行没有出现';'的情况
        if (is_slash_n == true ) {
            printf("语法分析出错！第 %d 句没有';'，继续分析下一句...\n", lines);
            is_slash_n = false;
            syn = temp_syn;
            print_syn();
            statement();
        } else {
            printf("发现';',一条语句分析完成...\n");
            basic_scaner();
            print_syn();
            is_slash_n = false;
            statement();
        }
    }
}



void recursive_descent_parser() {
    printf("\n\n开始进行语法分析：\n");
    
    p = 0;
    kk = 0;
    lines = 0;
    
    basic_scaner();
    print_syn();
    
    
    if (syn == 1) {
        
        printf("分析到函数开始符'function'...\n");
        
        basic_scaner();
        
        print_syn();
        
        is_slash_n = false;
        
        yucu();                 // 语句串分析
        
        if (syn == 6) {         // 读到end
            basic_scaner();
            
            print_syn();
            
            if (syn == 0 ) {    //&& kk == 0) { // 程序分析识别完
                printf("分析到'end'\n");
                printf("语法分析完成！\n");
                printf("语义分析的结果(三地址指令)为：\n");
                for (int i = 0; i < count; i++) {
                    printf("四元式 %d :", i);
                    printf("%s = ", quad[i].result);
                    printf("%s", quad[i].ag1);
                    printf("%s", quad[i].op);
                    printf("%s ", quad[i].ag2);
                    printf("\t<%s, \t%s, \t%s, \t%s>\n", quad[i].op, quad[i].ag1, quad[i].ag2, quad[i].result);
                }
            }
        } else {
            if (kk == 1) {      // 没有以end结束
                printf("语法分析出错！缺少 'endfunc'.\n");
                printf("语法分析完成！\n");
                kk = 1;
            }
        }
    } else {
        printf("语法分析出错! 缺少函数开始符'function'.\n");
        kk = 1;
    }
    
    if (kk == 1) {
        printf("本程序有语法错误，无法进行编译！\n");
    } else {
        printf("本程序没有句法错误，可以进行下一步编译！\n");
    }

}