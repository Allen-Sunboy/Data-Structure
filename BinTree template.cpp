#include <iostream>
using namespace std; //max()

enum RBColor{
    RB_RED, RB_BLACK
};

template <typename T>
struct BinNode{
    T data;
    BinNode<T> *parent;
    BinNode<T> *lc;
    BinNode<T> *rc;
    int height;
    int npl;
    RBColor color;

    BinNode(): parent(nullptr), lc(nullptr), rc(nullptr), height(0), npl(0), color(RB_RED){}

    BinNode(T e, BinNode<T> *p = nullptr, BinNode<T> *lc = nullptr, BinNode<T> *rc = nullptr, int h = 0, int l = 1, RBColor c = RB_RED):
        data(e), parent(p), lc(lc), rc(rc), height(h), npl(l), color(c){}
    
    // int size();

    BinNode<T> *insertAsLC(const T &e){
        BinNode<T> *lc = new BinNode<T>;
        lc->data = e;
        lc->parent = this;
        this.lc = lc;
        return lc;
    }

    BinNode<T> *insertAsRC(const T &e){
        BinNode<T> *rc = new BinNode<T>;
        rc->data = e;
        rc->parent = this;
        this.rc = rc;
        return rc;
    }

    bool operator<(const BinNode &bn){ return data < bn.data; }

    bool operator>(const BinNode &bn){ return data > bn.data; }

    bool operator==(const BinNode &bn){ return data == bn.data; }

    bool operator!=(const BinNode &bn){ return data != bn.data; }

};

template <typename T>
int stature(BinNode<T> *p){ return p ? p->height : -1; }

template <typename T>
bool IsRoot(BinNode<T> x){ return !x.parent; }

template <typename T>
bool IsLChild(BinNode<T> x){ return !IsRoot(x) && ( &x == x.parent->lc); }

template <typename T>
bool IsRChild(BinNode<T> x){ return !IsRoot(x) && ( &x == x.parent->rc); }

template <typename T>
bool HasParent(BinNode<T> x){ return !IsRoot(x); }

template <typename T>
bool HasLChild(BinNode<T> x){ return x.lc; }

template <typename T>
bool HasRChild(BinNode<T> x){ return x.rc; }

template <typename T>
bool HasChild(BinNode<T> x){ return HasLChild(x) || HasRChild(x); }

template <typename T>
bool HasBothChild(BinNode<T> x){ return HasLChild(x) && HasRChild(x); }

template <typename T>
bool IsLeaf(BinNode<T> x){ return !HasChild(x); }

template <typename T>
BinNode<T> *sibling(BinNode<T> *p){ return IsLChild(*p) ? p->parent->rc : p->parent->lc; }

template <typename T>
BinNode<T> *uncle(BinNode<T> *p){ return IsLChild(*(p->parent)) ? p->parent->parent->rc : p->parent->parent->lc; }

template <typename T>
int removeAt(BinNode<T> *x)
{
    if (!x)
        return 0;
    int n = 1 + removeAt(x->lc) + removeAt(x->rc);
    // release(x->data); 
    // release(x);
    return n;
}

template <typename T>
class BinTree{
protected:
    int _size;
    BinNode<T> *_root;
    int updateHeight(BinNode<T> *x){ return x->height = 1 + max(stature(x->lc), stature(x->rc)); }

    void updateHeightAbove(BinNode<T> *x){
        while (x)
        {
            updateHeight(x);
            x = x->parent;
        }
    }

    BinNode<T> *fromParentTo(BinNode<T> x){ return IsRoot(x) ? _root : (IsLChild(x) ? x.parent->lc : x.parent->rc); }

public:
    BinTree(): _size(0), _root(nullptr){}

    ~BinTree(){
        if (_size > 0)
            remove(_root);
    }

    int size() const{ return _size; }

    bool empty() const{ return !_root; }

    BinNode<T> *root() const{ return _root; }

    BinNode<T> *insertAsRoot(const T &e){
        _size = 1;
        return _root = new BinNode<T>(e);
    }

    BinNode<T> *insertAsLC(BinNode<T> *x, const T &e){
        _size++;
        x->insertAsLC(e);
        updateHeightAbove(x);
        return x->lc;
    }

    BinNode<T> *insertAsRC(BinNode<T> *x, const T &e){
        _size++;
        x->insertAsRC(e);
        updateHeightAbove(x);
        return x->rc;
    }

    BinNode<T> *attachAsLC(BinNode<T> *x, BinTree<T> &S){
        if (x->lc = S._root)
            x->lc->parent = x;
        _size += S._size;
        updateHeightAbove(x);
        S._root = nullptr;
        S._size = 0;
        // release(S);
        // S = 0;
        return x;
    }
    BinNode<T> *attachAsRC(BinNode<T> *x, BinTree<T> &S){
        if (x->rc = S._root)
            x->rc->parent = x;
        _size += S._size;
        updateHeightAbove(x);
        S._root = nullptr;
        S._size = 0;
        // release(S);
        // S = 0;
        return x;
    }
    
};

int main()
{
    
}