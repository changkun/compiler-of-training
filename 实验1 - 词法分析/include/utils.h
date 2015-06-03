//
//  utils.h
//  实验1
//
//  Created by 欧长坤 on 15/6/2.
//  Copyright (c) 2015年 欧长坤. All rights reserved.
//

#ifndef ____1__utils__
#define ____1__utils__

#include <cstdio>
#include <string>
#include <iostream>
#include "scaner.h"

extern int p;
extern char ch;
extern char prog[1000000];

int load_program(std::string filepath, std::string filename);
void show_program();

#endif /* defined(____1__utils__) */
