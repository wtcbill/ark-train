#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <Windows.h>
#include <locale.h>

#define MAX_LINE_LENGTH 1024      // 每行的最大长度
#define MAX_ROLE_NAME_LENGTH 100 // 角色名的最大长度
#define MAX_ROLES 1000           // 最大角色数量

// 定义角色结构体
typedef struct 
{
    char name[MAX_ROLE_NAME_LENGTH]; // 角色名
    int count;                      // 角色出现次数
} Role;



// 提取包含指定 marker 的行，并解析其中的角色名
void extract_ban(const char *line, const char *marker, Role roles[MAX_ROLES], int *roles_count) 
{
    char *ban_pos;

    // 检查 marker 是否出现在当前行中
    if ((ban_pos = strstr(line, marker)) != NULL) // 查找比对字符串
    {
        ban_pos += strlen(marker); // 跳过 marker
        while (*ban_pos == ' ') ban_pos++; // 跳过可能的空格

        char buffer[MAX_LINE_LENGTH]; // 用于存储 marker 之后的内容（缓存）
        strncpy(buffer, ban_pos, MAX_LINE_LENGTH - 1); // 复制字符串
        buffer[MAX_LINE_LENGTH - 1] = '\0'; // 确保字符串以 null 结尾

        char *start = buffer; // 指向要解析的起始位置
        char *end;

        // 按逗号、中文逗号和换行符分割字符
        while ((end = strpbrk(start, "，,\n")) != NULL) // 查询
        { 
            *end = '\0'; // 用结束符替换分隔符
            if (strlen(start) > 0) 
            { // 确保非空字符串
                int found = 0;

                // 检查当前角色是否已经存在于角色数组中
                for (int i = 0; i < *roles_count; i++) 
                {
                    if (strcmp(roles[i].name, start) == 0) // 比较两个字符串 
                    {
                        roles[i].count++; // 如果存在，计数加 1
                        found = 1;
                        break;
                    }
                }

                // 如果角色不存在，则添加到数组中
                if (!found && *roles_count < MAX_ROLES) 
                {
                    strncpy(roles[*roles_count].name, start, MAX_ROLE_NAME_LENGTH - 1); // 复制角色名
                    roles[*roles_count].name[MAX_ROLE_NAME_LENGTH - 1] = '\0'; // 确保 null 结尾
                    roles[*roles_count].count = 1; // 初始化计数为 1
                    (*roles_count)++; // 增加角色计数
                }
            }
            start = end + 1; // 移动到下一个分割位置
        }
    }
}

int main() 
{
    // 设置控制台为 UTF-8 编码以正确显示中文
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    setlocale(LC_ALL,"");
    // 定义两个角色数组，分别存储 (first) 和 (then) 的角色数据
    Role first_roles[MAX_ROLES]; // (first) 的角色数组
    Role then_roles[MAX_ROLES];  // (then) 的角色数组
    int first_roles_count = 0;   // (first) 的角色计数
    int then_roles_count = 0;    // (then) 的角色计数

    // 打开数据文件
    FILE *file = fopen("data.txt", "r");
    if (file == NULL) 
    {
        printf("无法打开文件！\n");
        return 1; // 如果文件打开失败，退出程序
    }

    char line[MAX_LINE_LENGTH]; // 用于存储每行的内容

    // 按行读取文件内容
    while (fgets(line, sizeof(line), file)) 
    {
        // 提取 (first) 和 (then) 的角色
        extract_ban(line, "(first)", first_roles, &first_roles_count);
        extract_ban(line, "(then)", then_roles, &then_roles_count);
    }

    fclose(file); // 关闭文件

    // 输出 (first) 的角色名及出现次数
    printf("First Roles:\n");
    for (int i = 0; i < first_roles_count; i++) 
    {
        printf(" %s, 出现次数: %d\n", first_roles[i].name, first_roles[i].count);
    }

    // 输出 (then) 的角色名及出现次数
    printf("\nThen Roles:\n");
    for (int i = 0; i < then_roles_count; i++) 
    {
        printf(" %s, 出现次数: %d\n", then_roles[i].name, then_roles[i].count);
    }

    return 0; // 程序执行成功
}
