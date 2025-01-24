#include <stdio.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

void extract_ban(char *line) {
    char *ban_pos;
    // 查找是否包含 "ban" 字符串
    if ((ban_pos = strstr(line, "ban")) != NULL) {
        // 只取"ban"后面的字符
        ban_pos += 3;  // 跳过 "ban"
        
        // 跳过可能的空格
        while (*ban_pos == ' ') {
            ban_pos++;
        }
        
        // 输出 ban 后面的角色
        printf("ban 后的角色: %s\n", ban_pos);
    }
}

int main() {
    FILE *file = fopen("data.txt", "r");  // 打开文件进行读取
    if (file == NULL) {
        printf("无法打开文件！\n");
        return 1;  // 文件打开失败，退出程序
    }

    char line[MAX_LINE_LENGTH];  // 用于存储每一行数据

    // 逐行读取文件内容
    while (fgets(line, sizeof(line), file)) {
        // 检查是否包含 "(先)xxxban" 或 "(后)xxxban"
        if (strstr(line, "ban") != NULL) {
            if (strncmp(line, "条件", 6) == 0) {
    continue;  // 如果该行以"条件"开头，则跳过
}
            extract_ban(line);  // 提取 "ban" 后面的角色
        }
    }

    fclose(file);  // 关闭文件
    return 0;
}
