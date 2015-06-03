// 递归下降语法分析器
//
// 实验目的
//   构造文法的语法分析程序，要求采用递归下降语法分析方
//   法对输入的字符串进行语法分析，实现对词法分析程序所
//   提供的单词序列的语法检查和结构分析，进一步掌握递归
//   下降的语法分析方法。
//
// 实验内容
//   编写为一上下无关文法构造递归下降语法分析程序，并对
//   任给的一个输入串进行语法分析检查。程序要求能对输入
//   串进行递归下降语法分析，能判别程序是否符合已知的语
//   法规则，如果不符合（编译出错），则输出错误信息。
//
// 实验要求
//   利用C语言编制递归下降分析程序，并对Training语言进行语法分析。
//   (1)待分析的Training语言的语法。
//      用扩充的BNF表示如下：
//      1. <程序>::=    function<语句串>endfunc
//      2. <语句串>::=   <语句>{;<语句>}
//      3. <语句>::=    <赋值语句>
//      4. <赋值语句>::= ID=<表达式>
//      5. <表达式>::=  <项>{+<项>|-<项>}
//      6. <项>::=     <因子>{*<因子>|/<因子>}
//      7. <因子>::=    ID|NUM|(<表达式>)
//   输入单词串以"#"结束，如果文法是正确地句子，则输出success，否则输出error


// 增加的功能：
//    1. 能够处理某行没有';'的情况;
//    2. 能够输出出错语法所在的行数;
//    3. 详细输出了分析过程;
//    4. 修复了源程序不会成功的bug.

#include <iostream>
#include "include/utils.h"
#include "include/scaner.h"
#include "include/parser.h"

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
    
        // 进行语法分析
        recursive_descent_parser();
    
        return 0;
    }
    
    std::cout << "用法: ./main.two file_path file_name" << std::endl;
    std::cout << "举例: ./main.two ~/编译原理提交/实验2/ data.txt" << std::endl;
    return -1;
}

