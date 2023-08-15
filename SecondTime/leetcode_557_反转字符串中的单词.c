/***
 * 来源：力扣（LeetCode）
 * 链接：https://leetcode.cn/problems/reverse-words-in-a-string-iii/
 *
 * 给定一个字符串 s ，你需要反转字符串中每个单词的字符顺序，同时仍保留空格和单词的初始顺序。
 *
 * 示例
 * 输入：s = "Let's take LeetCode contest"
 * 输出："s'teL ekat edoCteeL tsetnoc"
 *
 * 输入： s = "God Ding"
 * 输出："doG gniD"
 *
 * 提示：
 * 1 <= s.length <= 5 * 104
 * s 包含可打印的 ASCII 字符。
 * s 不包含任何开头或结尾空格。
 * s 里 至少 有一个词。
 * s 中的所有单词都用一个空格隔开。
***/

#include<string.h>

void swap(char* s, int i, int j)
{
    char temp = s[i];
    s[i] = s[j];
    s[j] = temp;
}

void ReverseString(char* s, int left, int right)
{
    while (left < right) {
        swap(s, left , right);
        ++left;
        --right;
    }
}

char* ReverseWords(char* s)
{
    int wordBegin = 0, wordEnd = 0;
    int sLength = strlen(s);

    while (wordEnd < sLength) {
        while (wordEnd < sLength && s[wordEnd] != ' ') {
            wordEnd++;
        }
        ReverseString(s, wordBegin, wordEnd - 1);
        ++wordEnd;
        wordBegin = wordEnd;
    }
    return s;
}