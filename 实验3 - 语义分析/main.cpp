// 语义分析
//
// 实验目的
//   通过实验，加深对语法制导翻译原理的理解，掌握将语法
//   掌握将语法分析所识别的语法成分变换为中间代码的语义
//   翻译方法。
//
// 实验内容
//   定义模拟的简单语言的语义成分，将语义分析程序编制成
//   一个子程序，在实验2分析出各语法单位后，分析其含义，
//   并将可执行语句或表达式翻译成为四元式输出，并将错误
//   信息输出。
//
// 实验要求
//   采用递归下降语法制导翻译法，对算数表达式、赋值语句
//   进行分析并生成四元式序列。输入是语法分析后提供的正
//   确地单词串，输入为三地址指令形式的四元式序列。

// 增加的功能：
//    1. 能够处理某行没有';'的情况
//    2. 能够提醒语法出错的所在行数
//    3. 详细输出了分析过程，对于能够在一条语句完成时就输出对应的四元式
//    4. 修复了源程序的逻辑错误

#include <iostream>

#include "include/utils.h"
#include "include/scaner.h"
#include "include/parser.h"
#include "include/semantic.h"

int main(int argc, const char * argv[]) {
    if (argc == 3) {
        
        std::string filepath = argv[1];
        std::string filename = argv[2];
        
        std::cout << filepath <<std::endl;
        std::cout << filename << std::endl;
        
        if (load_program(filepath, filename) == -1)
            return -1;
        
        // 开始词法分析
        lexical_analysis();
        
        // 进行语法和语义分析
        recursive_descent_parser();
        
        return 0;
    }
    
    std::cout << "Usage:   ./main.three [file_path] [file_name]" << std::endl;
    std::cout << "Example: ./main.three ./data/ data0.txt" << std::endl;
    
    return -1;
}

