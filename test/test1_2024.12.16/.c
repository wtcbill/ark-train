#include <stdio.h>
#include <string.h>
#include <stdlib.h>  // 用于 atoi 函数
#include <Windows.h>
#include <locale.h>
#include <wchar.h>

#define MAX_LINE_LENGTH 1024      // 每行的最大长度
#define MAX_ROLE_NAME_LENGTH 100 // 角色名的最大长度
#define MAX_ROLES 1000           // 最大角色数量

// 定义角色结构体
typedef struct 
{
    char name[MAX_ROLE_NAME_LENGTH];  // 角色名
    int count;                        // 角色出现的次数（未使用）
} Role;

// 提取包含 "ban" 的行并存储角色名
void extract_ban(const char *line, const char *marker, Role roles[MAX_ROLES], int *roles_count) 
{
    char *ban_pos;

    if ((ban_pos = strstr(line, marker)) != NULL) 
    {
        ban_pos += strlen(marker); // 跳过 marker
        while (*ban_pos == ' ') 
        ban_pos++; // 跳过空格
        {
            strncpy(roles[*roles_count].name,ban_pos,MAX_ROLE_NAME_LENGTH - 1);
            roles[*roles_count].name[MAX_ROLE_NAME_LENGTH - 1] = '\0';
            (*roles_count)++;
           
        } 
    }
    printf("%s\n", roles[*roles_count].name);
}


void cut(char role_collect[100],Role roles[MAX_ROLES])
{
    
    int len = strlen(role_collect);  // 获取字符串的长度
    int p_count = 0, times = 0;//p=part
    char word[50];  // 存储每个中文字符的字节
    role_collect[strcspn(role_collect, "\n")] = 0;
    int roles_count = 0;
    


    // 遍历字符串，按逗号分割中文字符
    for (int i = 0; i <= len; i++) 
    {
        if (role_collect[i] != ',' && role_collect[i] != '\0') 
        {
            word[p_count++] = role_collect[i];  // 如果是字符，添加到 word 数组
        } 
        
        else 
        
        {
            if (p_count > 0) 
            {
                word[p_count] = '\0';  // 结束当前字符
                int found = 0;
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
                p_count = 0;  // 重置计数器

            }
        }
    }
}



int main() 
{
    SetConsoleCP(65001);
    setlocale(LC_ALL,"");

    
    Role first_roles[MAX_ROLES]; // (first) 的角色数组
    Role then_roles[MAX_ROLES];  // (then) 的角色数组
    int first_roles_count = 0;   // (first) 的角色计数
    int then_roles_count = 0;    // (then) 的角色计数
    int count = 0;

    

    char line[MAX_LINE_LENGTH];
    line[1024] = "傀影，耀光" ;

        extract_ban(line, "(first)", first_roles, &first_roles_count);//通过传递指针，函数可以修改外部变量的值，而不需要返回该值(&first_roles_count)
        extract_ban(line, "(then)", then_roles, &then_roles_count);
    





    for (int i = 0; i < first_roles_count; i++) 
    {
        cut(first_roles[i].name, first_roles);  // 统计 (first) 角色
        cut(then_roles[i].name, then_roles);  // 统计 (then) 角色
    }
    

    // 输出 (first) 的角色及其出现次数
    printf("First Roles:\n");
    for (int i = 0; i < first_roles_count; i++) 
    {
        printf("%d: %s, Count: %d\n", i + 1, first_roles[i].name, first_roles[i].count);
    }

    // 输出 (then) 的角色及其出现次数
    printf("\nThen Roles:\n");
    for (int i = 0; i < then_roles_count; i++) 
    {
        printf("%d: %s, Count: %d\n", i + 1, then_roles[i].name, then_roles[i].count);
    }

    return 0;
}

