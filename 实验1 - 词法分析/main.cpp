// 词法分析器
//
// 实验目的
//   构造Training语言的词法分析程序，程序要求能对输入
//   的字符串流进行词法分析。在实验过程中，学会对单词分
//   析的方法NFA和DFA，加深对词法分析原理的理解。
//
// 实验内容
//   了解 Training 语言的基本词法，并为之构造一个NFA，
//   并将其转化成DFA，然后据此DFA编写 Training语言的
//   词法分析程序
//
// (1) Training 语言的关键词
//    function if then while do endfunc
//    所有关键字都是保留字，并且必须是小写。
// (2) 下面是专用符号
//    =,+,-,*,/,<,<=,!=,>,>=,==,;,(,),#
// (3) 其他单词是标识符(id)和整型常数(num)
//    id = letter(letter|digit)*
//    num = digit digit *
//    letter = a | ... | z | A | ... | Z
//    digit = 0 | ... | 9
//    大小写敏感
//    思考：构造实数的正规表达式，自己实现对实数的识别及表示。
// (4) 空格由空白、换行符和指标符组成。空格一般用来分割
//     id/num/运算符和关键字，词法分析阶段通常被忽略。
// (5) 各种单词符号对应的种别码如下表所示。

// 要求
//   输入为所给文法的源程序字符串
//   程序的输出形式为单词的输出形式
//     所输出的每一单词，均按形式如(syn, token 和 num)的二元式编码。其中，syn为单词种别码
//     token 为存放的单词自身字符串；sum为整形常数。


// 增加的功能：
//    1. 可以识别'{','}'
//    2. 将关键字'endfunc'替换成了'end'
//    3. 可以跳过识别'\t'tab符号
//    4. 标示符可以使用下划线'_'甚至是'_'开头
//    5. 可以识别运算符->

#include <iostream>
#include "include/scaner.h"
#include "include/utils.h"

int main(int argc, const char * argv[]) {
    
    if (argc == 3) {
        
        std::string filepath = argv[1];
        std::string filename = argv[2];
        
        std::cout << filepath <<std::endl;
        std::cout << filename << std::endl;
        
        if (load_program(filepath, filename) == -1)
            return -1;
        show_program();
        
        // 开始词法分析
        start_lexical_analysis();
        return 0;
    }
    
    std::cout << "用法: ./main.one file_path file_name" << std::endl;
    std::cout << "举例: ./main.one ~/编译原理提交/实验1/ data.txt" << std::endl;
    return -1;
}


