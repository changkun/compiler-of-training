//
//  utils.cpp
//  实验3
//
//  Created by 欧长坤 on 15/5/29.
//  Copyright (c) 2015年 欧长坤. All rights reserved.
//

#include "../include/utils.h"

#include "../include/scaner.h"
extern int p;
extern char ch;
extern char prog[1000000];

int load_program(std::string filepath, std::string filename) {
    p = 0;
    FILE *file;
    //    手动输入程序串
    //    printf("请输入程序串（Please input string）: \n");
    //    do {
    //        scanf("%c", &ch); // 依次程序串按字符读入到ch中, scanf会读入\n
    //        prog[p++] = ch;   // 并保存到prog数组中
    //    } while (ch != '#');  // 当遇到'#'字符时候停止读入
    
    
    if ((file = fopen((filepath+filename).c_str(), "r")) == NULL) {
        printf("无法打开文件。");
        return -1;
    }
    else
        printf("打开文件成功，");
    
    std::cout << "正在载入" << filename << "中的程序..." << std::endl;
    
    do {
        ch = fgetc(file);
        prog[p++] = ch;
    } while (!feof(file));
    fclose(file);
    return 0;
}

void show_program() {
    printf("载入的程序为:\n");
    printf("%s\n\n", prog);
}


char* itoa(int num,char* str,int radix)
{
    // 索引表
    char index[]="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    unsigned unum;          // 中间变量
    int i=0,j,k;
    // 确定unum的值
    if(radix == 10 && num<0)  // 十进制负数*/
    {
        unum = (unsigned)-num;
        str[i++] = '-';
    }
    else unum=(unsigned)num;/*其他情况*/
    /*转换*/
    do{
        str[i++] = index[unum % (unsigned)radix];
        unum /= radix;
    }while(unum);
    str[i]='\0';
    /*逆序*/
    if(str[0]=='-')
        k=1;/*十进制负数*/
    else
        k = 0;
    char temp;
    for(j = k; j <= (i-1)/2; j++)
    {
        temp         = str[j];
        str[j]       = str[i-1+k-j];
        str[i-1+k-j] = temp;
    }
    return str;
}

