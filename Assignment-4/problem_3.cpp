#include <iostream>
#include <cstring>
using namespace std;

const int MAXN = 600017;

struct node
{
    bool visited = 0; //单词是否重复，初始化为0
    char *word;
    node *next; //后继
};
node table[MAXN]; //使用独立链，有表头节点

//字符串哈希值
int getHash(char str[])
{
    int hash = 0;
    int len = strlen(str);
    for (int i = 0; i < len; i++)
        hash += (str[i] - 'a' + 1) * (i + 1);
    
    return hash;
}

int n;
char str[MAXN][45];

int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> str[i];
        int hash = getHash(str[i]);

        node *p = table[hash].next;

        //遍历链表，查看单词是否已存在
        while (p != nullptr)
        {
            //若找到重复单词
            if (strcmp(p->word, str[i]) == 0)
            {
                //若为第一次重复
                if (p->visited == 0)
                {
                    cout << p->word << endl;
                    p->visited = 1;
                }
                break;
            }
            else
                p = p->next;
        }

        //若不存在该单词，则从表头插入新节点
        if (p == nullptr)
        {
            node *s = new node;
            s->word = str[i];
            s->next = table[hash].next;
            table[hash].next = s;
        }
    }

}