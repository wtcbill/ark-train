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
        while (*ban_pos == ' ') ban_pos++; // 跳过空格

        if (*roles_count < MAX_ROLES) 
        {
            strncpy(roles[*roles_count].name, ban_pos, MAX_ROLE_NAME_LENGTH - 1);
            roles[*roles_count].name[MAX_ROLE_NAME_LENGTH - 1] = '\0';
            (*roles_count)++;
        }
    }
}

// 按逗号分割并处理角色名
void split_and_process_roles(char *role_str, char output[50][60], int *times)
{
    int len = strlen(role_str);
    int count = 0;
    char word[60];  // 存储每个角色的字节

    for (int i = 0; i <= len; i++)  
    {
        if (role_str[i] != ',' && role_str[i] != '\0') 
        {
            word[count++] = role_str[i];  // 如果是字符，添加到 word 数组
        } 
        else 
        {
            if (count > 0) 
            {
                word[count] = '\0';  // 结束当前角色
                strcpy(output[*times], word);  // 将角色字符串存入 output
                (*times)++;  // 增加计数器
                count = 0;  // 重置计数器
            }
        }
    }
}

int main() 
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    setlocale(LC_ALL,"");

    Role first_roles[MAX_ROLES]; // (first) 的角色数组
    Role then_roles[MAX_ROLES];  // (then) 的角色数组
    int first_roles_count = 0;   // (first) 的角色计数
    int then_roles_count = 0;    // (then) 的角色计数

    FILE *file = fopen("data.txt", "r");
    if (file == NULL) 
    {
        printf("无法打开文件！\n");
        return 1;
    }

    char line[MAX_LINE_LENGTH];

    // 遍历文件的每一行，提取角色
    while (fgets(line, sizeof(line), file)) 
    {
        // 提取包含 "(first)" 和 "(then)" 标记的角色名
        extract_ban(line, "(first)", first_roles, &first_roles_count);
        extract_ban(line, "(then)", then_roles, &then_roles_count);
    }

    fclose(file);

    // 输出 (first) 的角色名并按逗号分割
    printf("First Roles:\n");
    for (int i = 0; i < first_roles_count; i++) 
    {
        char output[50][60];  // 用于存储分割后的角色名
        int times = 0;  // 计数器

        split_and_process_roles(first_roles[i].name, output, &times);

        for (int j = 0; j < times; j++) 
        {
            printf("[%d]: %s\n", j + 1, output[j]);
        }
    }

    // 输出 (then) 的角色名并按逗号分割
    printf("\nThen Roles:\n");
    for (int i = 0; i < then_roles_count; i++) 
    {
        char output[50][60];  // 用于存储分割后的角色名
        int times = 0;  // 计数器

        split_and_process_roles(then_roles[i].name, output, &times);

        for (int j = 0; j < times; j++) 
        {
            printf("[%d]: %s\n", j + 1, output[j]);
        }
    }

    return 0;
}
