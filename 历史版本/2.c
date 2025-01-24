#include <stdio.h>
#include <string.h>

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
void extract_ban(const char *line, Role roles[MAX_ROLES], int *role_count) 
{
    char *ban_pos;

    // 查找是否包含 "ban"
    if ((ban_pos = strstr(line, "ban")) != NULL) 
    {
        // 跳过 "ban" 字符
        ban_pos += 3;

        // 跳过 "ban" 后的空格
        while (*ban_pos == ' ') 
        {
            ban_pos++;
        }

        // 如果提取的角色数量未超过最大限制
        if (*role_count < MAX_ROLES) 
        {
            // 将 "ban" 后的内容复制到 roles 数组中
            strncpy(roles[*role_count].name, ban_pos, MAX_ROLE_NAME_LENGTH - 1);
            roles[*role_count].name[MAX_ROLE_NAME_LENGTH - 1] = '\0'; // 确保字符串以 '\0' 结尾
            (*role_count)++; // 更新角色计数
        }
    }
}

int main() 
{
    Role roles[MAX_ROLES];  // 定义存储角色的数组
    int role_count = 0;     // 初始化角色计数为 0

    // 打开包含数据的文件
    FILE *file = fopen("data.txt", "r");
    if (file == NULL) // 如果文件无法打开，打印错误并退出
    {
        printf("无法打开文件！\n");
        return 1;
    }

    char line[MAX_LINE_LENGTH]; // 存储读取的每行内容

    // 逐行读取文件内容
    while (fgets(line, sizeof(line), file)) 
    {
        // 如果当前行包含 "ban"
        if (strstr(line, "ban") != NULL) 
        {
            // 如果以 "条件" 开头，跳过此行
            if (strncmp(line, "条件", 6) == 0) 
            {
                continue; // 跳过该行，读取下一行
            }

            // 调用函数提取 "ban" 后的内容
            extract_ban(line, roles, &role_count);
        }
    }

    fclose(file); // 关闭文件

    // 输出所有提取到的角色名
    for (int i = 0; i < role_count; i++) 
    {
        printf("%d: %s\n", i + 1, roles[i].name);
    }

    return 0; // 程序正常结束
}
