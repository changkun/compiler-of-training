//
//  scaner.h
//  实验2
//
//  Created by 欧长坤 on 27/5/15.
//  Copyright (c) 2015年 欧长坤. All rights reserved.
//

#ifndef ____1__scaner__
#define ____1__scaner__

#include <stdio.h>

// syn     token
//  0        #
//  1     function
//  2        if
//  3       then
//  4       while
//  5       do
//  6       end
//  7       return
//  8       int
//  9       double
// 10      标识符
// 11     整形数字
// 12       
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
// 24        ->
// 25         ,
// 26         ;
// 27         (
// 28         )
// 29         {
// 30         }


#define KEY_NUMBER 6
#define TOKEN_LENTH 256

// 实验1
void basic_scaner();
void lexical_analysis();

#endif /* defined(____1__scaner__) */
