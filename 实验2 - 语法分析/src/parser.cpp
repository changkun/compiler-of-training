//
//  parser.cpp
//  实验2
//
//  Created by 欧长坤 on 15/5/29.
//  Copyright (c) 2015年 欧长坤. All rights reserved.
//

#include "../include/parser.h"
#include <cstdio>

#include "../include/scaner.h"
// 位于 scaner.cpp
extern char prog[1000000];
extern char token[TOKEN_LENTH];
extern char ch;
extern int syn;
extern int p;
extern int integer;
extern const char * rwtab[KEY_NUMBER];
extern int is_slash_n;
extern int lines;

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
void factor() {                     // 因子分析函数
    if (syn == 10 || syn == 11) {   // 如果是标示符或者整形数字，则忽略，继续读取
        basic_scaner();
        // 处理某行没有出现';'的情况
        if (is_slash_n == true) {
            temp_syn = syn;
            kk = 1;
            syn = 26;
            return;
        }
        print_syn();
        
    } else {                        // 看是否是表达式
        if (syn == 27) {            // 出现括号 '('
            basic_scaner();
            
            print_syn();
            
            expression();           // 对括号内层进一步进行表达式分析
            if (syn == 28) {        // 出现括号 ')'
                // 处理')'结束后没有';'的情况
                basic_scaner();
                if (is_slash_n == true) {
                    temp_syn = syn;
                    kk = 1;
                    syn = 26;
                    return;
                }
                print_syn();
                
            } else {
                printf("语法分析错误! 右括号缺失！出错所在行为: %d\n", lines+1);
                kk = 1;
            }
        } else {
            printf("语法分析错误! 表达式错误！出错所在行为：%d\n", lines+1);
            kk = 1;
        }
    }
}

void term() { // 项分析函数
    factor();
    while (syn == 15 || syn == 16) {    // 直到读到 乘法 或者 除法
        basic_scaner();
        
        print_syn();
        
        factor();
    }
    return ;
}

void expression() {                     // 表达式分析函数
    term();
    while (syn == 13 || syn == 14) {    // 出现 '+' 或者 '-'
        basic_scaner();
        
        print_syn();
        
        term();                         // 进行项分析
    }
    return;
}

void statement() {
    if (syn == 10) {                    // 标识符
        basic_scaner();
        
        print_syn();
        
        if (syn == 21) {                // 等号'='，说明是赋值语句，处理表达式是否合法
            printf("分析到'='，即赋值语句...\n");
            basic_scaner();
            print_syn();
            expression();               // 分析表达式，这里实现语法分析判断语句
        } else {
            printf("语法分析错误! evaluate tag error！出错所在行为：%d\n", lines+1);
            kk = 1;
        }
    } else {
        if (syn == 6) {                 // 如果遇到了end
            return;
        } else { // 分析出错
            printf("语法分析错误! 语句出错！出错所在行为：%d\n", lines+1);
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
            printf("语法分析出错！第 %d 句没有';'，继续分析下一句...\n", lines+1);
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
    return;
}



void recursive_descent_parser() {
    printf("\n\n开始进行语法、语义分析：\n");
    
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
            }
        } else {
            if (kk == 1) {      // 没有以end结束
                printf("语法分析出错！缺少 'endfunc'，出错所在行为：%d\n", lines+1);
                printf("语法分析完成！\n");
                kk = 1;
            }
        }
    } else {
        printf("语法分析出错! 缺少函数开始符'function'，出错所在行为：%d\n", lines+1);
        kk = 1;
    }
    
    if (kk == 1) {
        printf("本程序有语法错误，无法进行编译！\n");
    } else {
        printf("本程序没有句法错误，可以进行下一步编译！\n");
    }
    
}