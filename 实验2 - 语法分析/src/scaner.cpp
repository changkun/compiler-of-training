


//
//  scaner.cpp
//  实验1
//
//  Created by 欧长坤 on 27/5/15.
//  Copyright (c) 2015年 欧长坤. All rights reserved.
//

#include "../include/scaner.h"
#include <cstring>

// 全部初始化为0
char prog[1000000] = { 0 };
// Traning 语言的关键字/标示符的最大长度
// 为255个字符故开辟九个字符大小的数组，最
// 后一个单元用于存放'\0'
char token[TOKEN_LENTH] = { 0 };
// 字符缓存
char ch = 0;
// 编码
int syn = 0;
// 索引
int p = 0;
// 整形数字
int integer;
// 是否读到回车
bool is_slash_n = false;
// 记录出错行数
int lines = 0;

// 七个关键字
const char * rwtab[KEY_NUMBER] = {
    "function",
    "if",
    "then",
    "while",
    "do",
    "end",
};

double read_number_recognize() {
    return 0.0;
}

void lexical_analysis() {
    printf("开始进行词法分析：\n");
    p = 0;
    do {
        // 进行词法分析
        basic_scaner();
        switch (syn) {
            case 11: printf("(%d, %d)\n", syn, integer);   break;
            case -1: printf("erron\n");                    break;
            case  0: break;
            default: printf("(%d, %s)\n", syn, token);     break;
        }
    } while (syn != 0); // 处理到syn == 0停止分析
}



void basic_scaner() {
    int m;
    // 将 token 数组置为空
    for (int n = 0; n < TOKEN_LENTH-1; n++)
        token[n] = 0;
    // 开始读取prog数组中的程序串
    ch = prog[p++];
    // 处理空格和回车
    while (ch == ' ' || ch == '\n' || ch == '\t') {
        if (ch == '\n') {
            is_slash_n = true;
            lines++;
        }
        ch = prog[p++];
    }
    
    // 如果读到字符，怀疑是关键字or标示符
    if ((ch >= 'a' && ch <= 'z') || ch == '_') {
        m = 0;
        // 则一直继续读，直到读到的不是数字和字符
        while ((ch >= 'a' && ch <= 'z') || (ch >= '0' && ch <= '9') || ch == '_') {
            token[m] = ch; m++;
            ch = prog[p]; p++;
        }
        // 结束后，p指向两个偏移字符位置，ch为一个偏移位置的字符
        // 如果与关键词不吻合，则不妨定义为标识符
        syn = 10;
        
        // 判断是否与关键字吻合
        for (int n = 0; n < KEY_NUMBER; n++) {
            // 如果是关键字，则设置syn = n+1 ，例如当为关键字function时,syn=1
            if (strcmp(token, rwtab[n]) == 0) {
                syn = n + 1;
                break;
            }
        }
    } else {
        // 如果是数字
        if (ch >= '0' && ch <= '9') {
            syn = 11;
            integer = 0;
            // 继续读后面的数字
            while (ch >= '0' && ch <= '9') {
                //printf("%d", ch-'0');
                integer = integer * 10 + (ch - '0');  // 忽略前面的0
                ch = prog[p++];
            }
        } else {
            // 如果是其他字符
            switch (ch) {
                case '<':
                    m = 0;
                    token[m++] = ch;
                    ch = prog[p++];
                    if (ch == '=') {        // <=
                        syn = 20;
                        token[m++] = ch;
                        ch = prog[p++];
                    } else                  // <
                        syn = 19;
                    break;
                case '>':
                    m = 0;
                    token[m++] = ch;
                    ch = prog[p++];
                    if (ch == '=') {        // >=
                        syn = 18;
                        token[m++] = ch;
                        ch = prog[p++];
                    } else                  // >
                        syn = 17;
                    break;
                case '=':
                    m = 0;
                    token[m++] = ch;
                    ch = prog[p++];
                    if (ch == '=') {        // ==
                        syn = 22;
                        token[m++] = ch;
                        ch = prog[p++];
                    } else                  // =
                        syn = 21;
                    break;
                case '!':
                    m = 0;
                    token[m++] = ch;
                    ch = prog[p++];
                    if (ch == '=') {        // !=
                        syn = 23;
                        token[m++] = ch;
                        ch = prog[p++];
                    } else
                        syn = -1;           // 未定义'!'
                    break;
                case '+': syn = 13; token[0] = ch; ch = prog[p++];break;
                case '-': syn = 14; token[0] = ch; ch = prog[p++];break;
                case '*': syn = 15; token[0] = ch; ch = prog[p++];break;
                case '/': syn = 16; token[0] = ch; ch = prog[p++];break;
                case ',': syn = 25; token[0] = ch; ch = prog[p++];break;
                case ';': syn = 26; token[0] = ch; ch = prog[p++];break;
                case '(': syn = 27; token[0] = ch; ch = prog[p++];break;
                case ')': syn = 28; token[0] = ch; ch = prog[p++];break;
                case '{': syn = 29; token[0] = ch; ch = prog[p++];break;
                case '}': syn = 30; token[0] = ch; ch = prog[p++];break;
                case -1:  syn =  0; token[0] = ch; ch = prog[p++];break;
                default:  syn = -1; break;
            }
        }
    }
    p--;return;
}

