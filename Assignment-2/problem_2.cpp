#include <iostream>
using namespace std;

int n;

const int MAXN = 4000057;

int pre[MAXN]; //前序遍历的序列
int post[MAXN]; //后序遍历的序列

int l[MAXN]; //记录每个数字的左儿子节点
int r[MAXN]; //记录每个数字的右儿子节点

int Stack[MAXN]; //栈

//中序遍历并输出
void visitMid(int root)
{
    if(root == 0)
        return;
    visitMid(l[root]);
    printf("%d ", root);
    visitMid(r[root]);
}

int main()
{
    cin >> n;

    for(int i = 0; i < n; i++)
        scanf("%d", &pre[i]);
    for(int i = 0; i < n; i++)
        scanf("%d", &post[i]);

    int p_pre = 1;
    int p_post = 0;

    int Stack_size = 1;
    Stack[0] = pre[0];
    //第一个数即根入栈

    l[0] = pre[0]; 
    r[0] = pre[0];
    //记0的左右节点均为pre[0]

    //通过栈标记左右儿子
    while(p_post < n - 1)
    {
        //栈顶的数值
        int top = Stack[Stack_size-1];
        //若栈顶等于post[p_post]，则标记儿子并出栈
        if(top == post[p_post])
        {
            //栈顶的下一位的数值
            int sub = Stack[Stack_size-2];
            if(l[sub] == 0)
                l[sub] = top;
            else
                r[sub] = top;
            Stack[Stack_size-1] = 0;
            Stack_size--;
            p_post++;
        }
        //否则入栈
        else
        {
            Stack[Stack_size] = pre[p_pre];
            Stack_size++;
            p_pre++;
        }
    }
    visitMid(pre[0]);
}