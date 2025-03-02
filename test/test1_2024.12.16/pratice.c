#include <stdio.h>
#include <string.h>
#include <stdlib.h>  // 用于 atoi 函数
#include <Windows.h>
#include <locale.h>
#include <wchar.h>

#define MAX_ROLES 10
#define MAX_ROLE_NAME_LENGTH 20

// 定义一个角色结构体，包含角色名称和数量
typedef struct {
    char name[MAX_ROLE_NAME_LENGTH];
    int count;  // 记录该角色出现的次数
} Role;

int main() 
{
    SetConsoleCP(65001);
    setlocale(LC_ALL,"");
    char a[100] = "傀影,耀光,傀影,光明,";  // 输入字符串，包含多个角色
    int len = strlen(a);  // 获取字符串的长度
    int count = 0, times = 0;
    char word[20];  // 存储当前的角色名称
    Role roles[MAX_ROLES];  // 存储所有的角色
    int roles_count = 0;  // 当前角色的数量

    // 删除输入字符串末尾的换行符
    a[strcspn(a, "\n")] = 0;

    // 遍历字符串，按逗号分割角色
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
                int found = 0;
                
                // 检查角色是否已存在
                for (int j = 0; j < roles_count; j++) 
                {
                    if (strcmp(roles[j].name, word) == 0) 
                    {
                        roles[j].count++;  // 如果角色已存在，增加计数
                        found = 1;  // 标记为找到该角色
                        break;
                    }
                }

                // 如果没有找到相同的角色，添加到数组中
                if (!found && roles_count < MAX_ROLES) 
                {
                    strcpy(roles[roles_count].name, word);  // 将角色名称存入角色数组
                    roles[roles_count].count = 1;  // 初始化角色数量为 1
                    roles_count++;  // 增加角色计数
                }

                count = 0;  // 重置计数器
            }
        }
    }

    // 打印结果
    for (int i = 0; i < roles_count; i++) 
    {
        printf("角色: %s, 出现次数: %d\n", roles[i].name, roles[i].count);
    }

    return 0;
}
