#include<stdio.h>
#include<string.h>
#include<math.h>
#include <stdbool.h>
 
int main()
{
    char a[20];  // 声明一个字符数组用于存储输入的字符串
    printf("字符串：");  // 提示用户输入字符串
    gets(a);  // 获取用户输入的字符串，注意：`gets` 函数不安全，容易导致缓冲区溢出，建议用 `fgets` 替代

    int len = strlen(a), i, j, count = 0, wei[20], num[10] = {0}, times = 0;  // 初始化相关变量
    bool ctoi = 0, befctoi = 0;  // ctoi：用于检测字符是否为数字；befctoi：用于判断前一个字符是否是数字

    // 遍历输入的字符串
    for(i = 0; i < len + 1; i++) 
    {
        // 判断当前字符是否是数字
        if(a[i] >= '0' && a[i] <= '9') 
        {
            ctoi = 1;  // 如果是数字，则设置 ctoi 为 1
        }
        else 
        {
            ctoi = 0;  // 如果不是数字，则设置 ctoi 为 0
        }

        // 如果前一个字符不是数字，当前字符是数字，开始提取数字
        if(befctoi == 0 && ctoi == 1) 
        {
            wei[count] = a[i];  // 将字符转换为对应的数字
            befctoi = 1;  // 设置 befctoi 为 1，表示当前字符是数字
            count++;  // 数字个数增加
        }
        // 如果当前字符还是数字，继续存储该数字
        else if(befctoi == 1 && ctoi == 1) 
        {
            wei[count] = a[i];  // 将字符转换为对应的数字
            count++;  // 数字个数增加
        }
        // 如果前一个字符是数字，当前字符不是数字，说明一个数字提取完毕
        else if(befctoi == 1 && ctoi == 0) 
        {
            // 将提取到的数字存储到 num 数组中
            for(j = 0; j < count; j++) 
            {
                num[times] += wei[j] * pow(10, count - j - 1);  // 通过每个数字乘以 10 的相应次方，构成完整的数字
            }
            times++;  // 数字个数增加
            befctoi = 0;  // 重置 befctoi 为 0，表示数字提取完成
            count = 0;  // 重置计数器，准备提取下一个数字
        }
    }

    // 输出提取到的数字个数
    printf("%d个数\n", times);
    // 输出提取到的每个数字
    for(i = 0; i < times; i++) 
    {
        printf("a[%d]=%d\n", i, num[i]);
    }

    return 0;
}
