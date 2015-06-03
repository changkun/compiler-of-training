//
//  scaner.h
//  实验1
//
//  Created by 欧长坤 on 15/5/15.
//  Copyright (c) 2015年 欧长坤. All rights reserved.
//

#ifndef ____1__scaner__
#define ____1__scaner__

#include <cstdio>
#include <cstring>
// syn     token
//  0    -1 or \377
//  1     function
//  2        if
//  3       then
//  4       while
//  5       do
//  6       end
//  7
//  8
//  9
// 10      标识符
// 11     整形数字
// 12       实数
// 13        +
// 14        -
// 15        *
// 16        /
// 17        >
// 18        >=
// 19        <
// 20        <=
// 21        =
// 22        ==
// 23        !=
// 24
// 25         ,
// 26         ;
// 27         (
// 28         )
// 29         {
// 30         }


#define KEY_NUMBER 6
#define TOKEN_LENTH 256

void basic_scaner();
void start_lexical_analysis();
//double read_number_recognize();

#endif /* defined(____1__scaner__) */
