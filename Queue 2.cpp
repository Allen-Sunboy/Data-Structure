//单链表实现
struct Node{
    int data;
    Node *next;
};

int size = 0;

Node *front = nullptr;
Node *rear = nullptr;

void enqueue(int x)
{
    Node *temp = new Node;
    temp->data = x;
    temp->next = nullptr;
    size++;
    if (front == nullptr && rear == nullptr)
    {
        front = rear = temp;
        return;
    }
    rear->next = temp;
    rear = temp;
}

void dequeue()
{
    if (front == nullptr)
        return;
    Node *del = front;
    if (front == rear)
        front = rear = nullptr;
    else
        front = front->next;
    delete del;
    size--;
}