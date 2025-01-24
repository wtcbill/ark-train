#include <stdio.h>
#include <string.h>
#include <stdlib.h>  // 用于 atoi 函数
#include <Windows.h>
#include <locale.h>
#include <wchar.h>
int main() 
{
    SetConsoleCP(65001);
    setlocale(LC_ALL,"");
    char a[100] = "傀影,耀光,";

    // 删除输入字符串末尾的换行符
    a[strcspn(a, "\n")] = 0;
    int len = strlen(a);  // 获取字符串的长度
    int count = 0, times = 0;
    char word[20];  // 存储每个中文字符的字节
    char output[10][20];  // 存储解析出的中文字符


    // 遍历字符串，按逗号分割中文字符
    for (int i = 0; i <= len; i++) 
    {
        if (a[i] != ',' && a[i] != '\0') 
        {
            word[count++] = a[i];  // 如果是字符，添加到 word 数组
        } 
        
        else 
        
        {
            if (count > 0) 
            {
                word[count] = '\0';  // 结束当前字符
                strcpy(output[times++], word);  // 将字符字符串存入 output
                count = 0;  // 重置计数器
            }
        }
    }

    // 打印结果
    for (int i = 0; i < times; i++) 
    {
        printf("[%d]:%s\n", i, output[i]);
    }
    return 0;
}
