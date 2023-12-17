#include <iostream>
#include "temperature.h"
const int MAXN = 50003;
using namespace std;

int n;
long long result = 0; //查找的总气温之和
int sum; //总的气象站个数

class rangeNode;

struct station
{
    int x, y;
    int temp;
    station &operator=(const station &data)
    {
        temp = data.temp;
        x = data.x;
        y = data.y;
        return *this;
    }
    rangeNode *c;
    rangeNode *road;
};
station stations[MAXN];


//存储栈
station stack1[3300], stack2[3300];
int roadX1, roadX2;

class YTree
{
public:
    station data;
    bool operator>(const YTree &a)
    {
        if (data.y > a.data.y)
            return true;
        else if (data.y == a.data.y)
        {
            if (data.x > a.data.x)
                return true;
            else
                return false;
        }
        else
            return false;
    }
    bool operator<(const YTree&a)
    {
        if (data.y < a.data.y)
            return true;
        else if (data.y == a.data.y)
        {
            if (data.x < a.data.x)
                return true;
            else
                return false;
        }
        else return false;
    }
};


class rangeNode{
public:
    rangeNode *rc, *lc, *parent;
    YTree *YT;
    int YTsize = 0;
    station data;
    int height = 0;
    rangeNode(const station &e, rangeNode *p, YTree *YT1 = nullptr, rangeNode *lc1 = nullptr, rangeNode *rc1 = nullptr):
        data(e), parent(p), YT(YT1), lc(lc1), rc(rc1) {}
};

void mergeY(YTree*&tem, YTree data_lc[], YTree data_rc[], int n_lc, int n_rc)
{
    tem = new YTree[n_lc + n_rc];
    int i = 0, j = 0, k = 0;
    while (i < n_lc&&j < n_rc)
    {
        if (data_lc[i] < data_rc[j])
            tem[k++].data = data_lc[i++].data;
        else
            tem[k++].data = data_rc[j++].data;
    }
    if (i == n_lc)
        while (k < n_lc + n_rc)
        {
            tem[k++].data = data_rc[j++].data;
        }
    else
        while (k < n_lc + n_rc)
        {
            tem[k++].data = data_lc[i++].data;
        }
}

int stature(rangeNode*a)
{
    return a ? a->height : -1;
}

bool Balance(rangeNode a)
{
    return(stature(a.lc) - stature(a.rc)) > -2 && stature(a.lc) - stature(a.rc) < 2;
}
bool islchild(rangeNode*g){
    return g->parent &&(g->parent->lc == g);
}
bool isrchild(rangeNode*g){
    return g->parent &&(g->parent->rc == g);
}
void updateheight(rangeNode*g)
{
    if (stature(g->lc)>stature(g->rc))
    {
        g->height = stature(g->lc) + 1;
    }
    else
    {
        g->height = stature(g->rc) + 1;
    }
}
rangeNode*tallerchild(rangeNode*g)
{
    return(stature(g->lc) > stature(g->rc)) ? g->lc :(((stature(g->lc) <stature(g->rc)) ? g->rc :(islchild(g) ? g->lc : g->rc)));
}

class rangetree{
public:
    rangeNode *_hot;
    rangeNode*_root;
    rangeNode*&search(const int&e);
    void insertAsRoot(const station&e)
    {
        _root = new rangeNode(e, nullptr); size++;
    }
    rangeNode*insert(const station&data);
    rangeNode*&check(rangeNode*g);
    rangeNode*connect34(rangeNode*a, rangeNode*b, rangeNode*c, rangeNode*T0, rangeNode*T1, rangeNode*T2, rangeNode*t3)
    {
        a->lc = T0; if (T0) { T0->parent = a; }
        a->rc = T1; if (T1) { T1->parent = a; }
        updateheight(a);
        c->lc = T2; if (T2) { T2->parent = c; }
        c->rc = t3; if (t3) { t3->parent = c; }
        updateheight(c);
        b->lc = a; a->parent = b;
        b->rc = c; c->parent = b; updateheight(b);
        return b;
    }
    rangeNode*rotateAt(rangeNode*v)
    {
    rangeNode*p = v->parent;
    rangeNode*g = p->parent;
    if (islchild(p))
    {
        if (islchild(v)){
            p->parent = g->parent;
            return connect34(v, p, g, v->lc, v->rc, p->rc, g->rc);
        }
        else
        {
            v->parent = g->parent;
            return connect34(p, v, g, p->lc, v->lc, v->rc, g->rc);
        }
    }
    else
    {
        if (islchild(v))
        {
            v->parent = g->parent;
            return connect34(g, v, p, g->lc, v->lc, v->rc, p->rc);
        }
        else
        {
            p->parent = g->parent;
            return connect34(g, p, v, g->lc, p->lc, v->lc, v->rc);
        }
    }
}
    void search_leaf(rangeNode*&v, int&i, rangeNode*hot);
    int size = 0;
};
bool operator==(const station&data1, const station&data2)
{
    return((data1.x == data2.x) &&(data1.y == data2.y));
}

rangeNode *&searchin(rangeNode*&v, const int&e, rangeNode*&hot)
{
    if (!v)return v;
    hot = v;
    return searchin((e <= v->data.x) ? v->lc : v->rc, e, hot);
}
rangeNode*&rangetree::search(const int&e)
{
    return searchin(_root, e, _hot = nullptr);
}

rangeNode*&rangetree::check(rangeNode*g)
{
    if (g->parent) { return islchild(g) ? g->parent->lc : g->parent->rc; }
    else { return _root; }
}
rangeNode*rangetree::insert(const station &data)
{
    rangeNode*&x = search(data.x);
    rangeNode*xx = x = new rangeNode(data, _hot);
    for (rangeNode*g = _hot; g; g = g->parent)
    {
        if (!Balance(*g)) {
            rangeNode *&temp = check(g);
            temp = rotateAt(tallerchild(tallerchild(g)));
            break;
        }
        else updateheight(g);
    }
    size++;
    return xx;
}

bool isleaf(rangeNode*root)
{
    return root && (!root->lc && !root->rc);
}


void rangetree::search_leaf(rangeNode*&v, int&i, rangeNode*hot)
{
    if (!v) {
        if (i < n)
        {
            stations[i].c = v = new rangeNode(stations[i], hot);
            v->YT = new YTree[1]; 
            v->YT->data = stations[i++];
           (v->YTsize)++;
        }
    }
    else {
        hot = v;
        search_leaf(v->lc, i, hot);
        search_leaf(v->rc, i, hot);
        if (v->lc && v->rc)
        {
            mergeY(v->YT, v->lc->YT, v->rc->YT, v->lc->YTsize, v->rc->YTsize);
            v->YTsize = v->lc->YTsize + v->rc->YTsize;
        }
        else
        {
            v->YT = new YTree[v->lc->YTsize];
            for (int i = 0; i < v->lc->YTsize; i++)v->YT[i].data = v->lc->YT[i].data;
            v->YTsize = v->lc->YTsize;
        }
    }
}
void merge_x(station data[], int lo, int mi, int hi)
{
    station *tem = new station[mi - lo];
    int k = lo, i = 0, t = mi - lo;
    for (int i = 0; i < mi - lo; i++)tem[i] = data[k++];
    while ((mi < hi) && (i < t))
    {
        if (tem[i].x < data[mi].x)
            data[lo++] = tem[i++];
        else if (tem[i].x == data[mi].x&&tem[i].y < data[mi].y)
            data[lo++] = tem[i++];
        else 
            data[lo++] = data[mi++];
    }
    if (i == t);
    else while (lo < hi)
        data[lo++] = tem[i++];
    delete[] tem;
}
void mergesortX(station data[], int lo, int hi)
{
    int mi;
    if (hi - lo > 1) {
        mi =(hi + lo) >> 1;
        mergesortX(data, lo, mi);
        mergesortX(data, mi, hi);
        merge_x(data, lo, mi, hi);
    }
    else return;
}

void searchX1(rangeNode*root, int x1, int x2, station stack[], int&road, int lo, int hi)
{
    int lenght = hi;
    while (hi > lo)
    {
        int mi =(hi + lo) / 2;
       stations[mi].x<x1 ? lo = mi + 1 : hi = mi;
    }
    if (lo<lenght && stations[lo].x <= x2) {
        rangeNode *root = stations[lo].c;
        while (root)
        {
            stack[road] = root->data;
            stack[road].c = root;
            if (!isleaf(stack[road].c))stack[road].road = stack[road - 1].c;
            road++;
            root = root->parent;
            
        }
    }
}
void searchX2(rangeNode *root, int x1, int x2, station stack[], int &road, int lo, int hi)
{
    int lenght = hi;
    while (hi > lo)
    {
        int mi =(hi + lo) / 2;
        stations[mi].x > x2 ? hi = mi : lo = mi + 1;
    }
    --lo;
    if (lo > -1 && stations[lo].x >= x1) {
        rangeNode *root = stations[lo].c;
        while (root)
        {
            stack[road] = root->data;
            stack[road].c = root;
            if (!isleaf(stack[road].c))
                stack[road].road = stack[road - 1].c;
            road++;
            root = root->parent;
        }
    }
    else;
}

rangeNode *commonRoot()
{
    while (0 < roadX1 && 0 < roadX2 && stack1[--roadX1] == stack2[--roadX2]);
    return(stack1[roadX1] == stack2[roadX2]) ? stack1[roadX1].c : stack1[++roadX1].c;
}
void searchY(rangeNode *root, int lo, int hi, int y1, int y2)
{
    while (lo < hi)
    {
        int mi =(lo + hi) / 2;
        (y1 <= root->YT[mi].data.y) ? hi = mi : lo = mi + 1;
    }
    while (lo < root->YTsize && root->YT[lo].data.y <= y2)
    {
        result += root->YT[lo].data.temp;
        sum++;
        lo++;
    }
}
void travelReport(int x1, int x2, int y1, int y2)
{
    while (roadX1 >= 0)
    {
        rangeNode *rc = stack1[roadX1].c->rc;
        rangeNode *lc = stack1[roadX1].c->lc;
        rangeNode *road = stack1[roadX1].road;
        if (rc && rc!=road)
            searchY(rc, 0, rc->YTsize, y1, y2);
        roadX1--;
    }
    rangeNode *now = stack1[roadX1 + 1].c;
    if (now->data.x >= x1 &&now->data.x <= x2 && now->data.y >= y1 && now->data.y <= y2)
    {
        sum++;
        result += now->data.temp;
    }
    while (roadX2 >= 0)
    {
        rangeNode *rc = stack2[roadX2].c->rc;
        rangeNode *lc = stack2[roadX2].c->lc;
        rangeNode *road = stack2[roadX2].road;
        if (lc&&lc != road)searchY(lc, 0, lc->YTsize, y1, y2);
        roadX2--;
    }
    rangeNode *now2 = stack2[roadX2 + 1].c;
    if (now2->data.x >= x1 && now2->data.x <= x2 && now2->data.y >= y1 && now2->data.y <= y2)
    {
        sum++;
        result += now2->data.temp;
    }
}

rangetree t; //二维range tree

int main()
{
    n = GetNumOfStation();

    for (int i = 0; i < n; i++)
        GetStationInfo(i, &(stations[i].x), &(stations[i].y), &(stations[i].temp));
    
    //建立根节点
    t.insertAsRoot(stations[0]);
    for (int i = 1; i < n; i++)
        //其他节点插入
        t.insert(stations[i]);

    //X排序
    mergesortX(stations, 0, n);
    int i = 0;
    t._hot = nullptr;
    t.search_leaf(t._root, i, t._hot);
    
    int x1, x2, y1, y2;
    while (GetQuery(&x1, &y1, &x2, &y2))
    {
        //先后查找x1，x2
        searchX1(t._root, x1, x2, stack1, roadX1, 0, n);
        searchX2(t._root, x1, x2, stack2, roadX2, 0, n);
        int t1 = roadX1, t2 = roadX2;
        if (roadX1 && roadX2)
        {
            rangeNode *v = commonRoot();
            roadX1--;
            //回溯，查找y，计数
            travelReport(x1, x2, y1, y2);
            if (sum != 0)
            {
                Response(result / sum);
            }
            else
            {
                Response(0);
            }
        }
        else
        {
            Response(0);
        }
        for (int i = 0; i < t1; i++)
        {
            stack1[i].c = nullptr; stack1[i].road = nullptr; stack1[i].x = 0; stack1[i].y = 0; stack1[i].temp = 0;
        }
        for (int i = 0; i < t2; i++){
            stack2[i].c = nullptr; stack2[i].road = nullptr; stack2[i].x = 0; stack2[i].y = 0; stack2[i].temp = 0;
        }
        t1 = t2 = roadX1 = roadX2 = result = sum = 0;
    }
}