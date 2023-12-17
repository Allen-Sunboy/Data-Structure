//数组实现
const int MAXN = 10003;
int Queue[MAXN];
int front = -1;
int rear = -1;

bool empty(){ return (rear == -1 && front == -1); }

int size()
{
    if (empty())
        return 0;
    else
        return rear - front + 1;
}

//front()直接使用Queue[front]

void enqueue(int x)
{
    if (empty())
    {
        front = 0;
        rear = 0;
        Queue[rear] = x;
    }
    else
    {
        ++rear;
        Queue[rear] = x;
    }
}

int dequeue()
{
    if (empty())
        return 0;
    else if (front == rear)
    {
        int temp = front;
        front = -1;
        rear = -1;
        return Queue[temp];
    }
    else
    {
        ++front;
        return Queue[front-1];
    }
}