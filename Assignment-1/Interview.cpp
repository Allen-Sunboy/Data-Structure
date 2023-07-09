#include <iostream>
using namespace std;

struct node{
    int id;
    node *prev; //prev为顺时针
    node *next; //next为逆时针
    node(int i): id(i) {}
};

class List{
    private:
    int _size = 1;
    node *first;
    node *latest; //标记前一个节点的位置

    public:

    node *latestNode()
    {
        return latest;
    }

    int size()
    {
        return _size;
    }

    List(int firstID)
    {
        first = new node(firstID);

        first->prev = first;
        first->next = first;
        latest = first;
    }

    void insert(int n, node *Node)
    {
        node *pre = latest;
        while(n-- > 1)
        {
            pre = pre->next;
        }
        Node->next = pre->next;
        Node->prev = pre;

        pre->next = Node;
        Node->next->prev = Node;
        latest = Node;

        _size++;
    }

    ~List()
    {
        while(_size-- > 1)
        {
            node *x = first->next;
            x->prev->next = x->next;
            x->next->prev = x->prev;
            delete x;
        }
        delete first;
    }
};


int main()
{
    int n, m;
    cin >> n >> m;

    int firstID;
    cin >> firstID;

    List a(firstID);
    
    int c;

    for(int i = 0; i < n - 1; i++)
    {
        cin >> c;
        node *newNode = new node(c);
        a.insert(m, newNode);
    }

    node *l = a.latestNode();
    while(n--)
    {
        cout << l->id << " ";
        l = l->prev;
    }


}