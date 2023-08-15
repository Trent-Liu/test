/***
 * 来源：力扣（LeetCode）
 * 链接：https://leetcode.cn/problems/daily-temperatures/description/
 *
 * 给定一个整数数组 temperatures ，表示每天的温度，返回一个数组 answer ，其中 answer[i] 是指对于第 i 天，下一个更高温度出现在几天后。如果气温在这之后都不会升高，请在该位置用 0 来代替。
 *
 * 示例
 * 输入: temperatures = [73,74,75,71,69,72,76,73]
 * 输出: [1,1,4,2,1,1,0,0]
 *
 * 输入: temperatures = [30,40,50,60]
 * 输出: [1,1,1,0]
 *
 * 输入: temperatures = [30,60,90]
 * 输出: [1,1,0]
 *
 * 提示：
 * 1 <= temperatures.length <= 105
 * 30 <= temperatures[i] <= 100
 *
***/
#include <stdlib.h>
#include<string.h>

typedef struct Pair {
    int first;
    int second;
} Pair;

typedef struct Stack {
    Pair *data;
    int size, top;
} Stack;

Stack *InitStack(int n)
{
    Stack *st = malloc(sizeof(Stack));
    st->data = malloc(sizeof(Pair) * n);
    st->size = n;
    st->top = -1;
    return st;
}

int IsEmpty(Stack *st)
{
    return st->top == -1;
}

Pair Top(Stack *st)
{
    return st->data[st->top];
}

int Push(Stack *st, int num, int i)
{
    if (st == NULL) {
        return 0;
    }
    if (st->top == st->size-1) {
        return 0;
    }
    ++st->top;
    st->data[st->top].first = num;
    st->data[st->top].second = i;
    return 1;
}

int Pop(Stack *st)
{
    if (st == NULL) {
        return 0;
    }
    if (IsEmpty(st)) {
        return 0;
    }
    --st->top;
    return 1;
}

void ClearStack(Stack *st)
{
    if (st == NULL) {
        return;
    }
    free(st->data);
    free(st);
    return;
}

int* DailyTemperatures(int* temperatures, int temperaturesSize, int* returnSize)
{
    int *res = malloc(sizeof(int) * temperaturesSize);
    memset(res, 0, sizeof(int) * temperaturesSize);
    if (res == NULL) {
        return NULL;
    }

    Stack *st = InitStack(temperaturesSize);
    *returnSize = temperaturesSize;

    for (int i = 0; i < temperaturesSize; ++i) {
        int num = temperatures[i];
        while (!IsEmpty(st) && Top(st).first < num) {
            res[Top(st).second] = i - Top(st).second;
            Pop(st);
        }
        Push(st, num, i);

    }
    return res;
}
