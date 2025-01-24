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



int main() 
{
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

    while (fgets(line, sizeof(line), file)) 
    {
        extract_ban(line, "(first)", first_roles, &first_roles_count);
        extract_ban(line, "(then)", then_roles, &then_roles_count);
    }

    fclose(file);

    // 输出 (first) 的角色名
    printf("First Roles:\n");
    for (int i = 0; i < first_roles_count; i++) 
    {
        printf("%d: %s\n", i + 1, first_roles[i].name);
    }

    // 输出 (then) 的角色名
    printf("\nThen Roles:\n");
    for (int i = 0; i < then_roles_count; i++) 
    {
        printf("%d: %s\n", i + 1, then_roles[i].name);
    }

    return 0;
}

