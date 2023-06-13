// 21451_Assignment_11.cpp

/* PROBLEM STATEMENT ------------------------------------------------------------------

A Dictionary stores keywords & its meanings. Provide facility for
adding new keywords, deleting keywords, updating values of any
entry. Provide facility to display whole data sorted in ascending/
Descending order. Also find how many maximum comparisons may
require for finding any keyword. Use Height balance tree and find the
complexity for finding a keyword.

------------------------------------------------------------------------------------ */

#include <iostream>
#include <string>
using namespace std;

class node
{
    node *lc, *rc;
    string key, mean;
    int height;

public:
    node(string k, string m)
    {
        key = k;
        mean = m;
        lc = rc = NULL;
        height = 0;
    }
    friend class avl;
};

class avl
{
public:
    node *root;

    avl()
    {
        root = NULL;
    }

    int node_height(node *p)
    {
        int hl = 0, hr = 0;
        hl = p && p->lc ? p->lc->height : 0;
        hr = p && p->rc ? p->rc->height : 0;

        return (hl > hr ? hl + 1 : hr + 1);
    }

    int BF(node *p)
    {
        int hl, hr;
        hl = p && p->lc ? p->lc->height : 0;
        hr = p && p->rc ? p->rc->height : 0;

        return (hl - hr);
    }

    node *LL(node *p)
    {
        node *pl = p->lc;
        // node *plr = pl->rc;
        p->lc = pl->rc;
        pl->rc = p;
        p->height = node_height(p);
        pl->height = node_height(pl);
        if (root == p)
            root = pl;
        return pl;
    }

    node *LR(node *p)
    {
        node *pl = p->lc;
        node *plr = pl->rc;

        pl->rc = plr->lc;
        p->lc = plr->rc;

        plr->lc = pl;
        plr->rc = p;

        p->height = node_height(p);
        pl->height = node_height(pl);
        plr->height = node_height(plr);

        if (root == p)
            root = plr;
        if (root->rc == p)
            root->rc = plr;

        return root;
    }

    node *RR(node *p)
    {
        node *pr = p->rc;
        node *prl = pr->lc;

        pr->lc = p;
        p->rc = prl;

        p->height = node_height(p);
        pr->height = node_height(pr);

        if (root == p)
            root = pr;
        return pr;
    }

    node *RL(node *p)
    {
        node *pr = p->rc;
        node *prl = pr->lc;

        pr->lc = prl->rc;
        p->rc = prl->lc;

        prl->lc = p;
        prl->rc = pr;

        p->height = node_height(p);
        pr->height = node_height(pr);
        prl->height = node_height(prl);

        if (root == p)
            root = prl;
        if (root->lc == p)
            root->lc = prl;
        return root;
    }

    node *insert(node *p, string k, string m)
    {
        // p - root, t - new node, k - key, m - meaning
        node *t = NULL;
        if (p == NULL) // if tree is empty
        {
            t = new node(k, m);
            t->height = 1;
            return t;
        }

        if (k < p->key) // if key is less than root
            p->lc = insert(p->lc, k, m);
        else if (k > p->key) // if key is greater than root
            p->rc = insert(p->rc, k, m);

        p->height = node_height(p); // update height of root

        if (BF(p) == 2 && BF(p->lc) == 1) // LL Rotation
            return LL(p);
        else if (BF(p) == 2 && BF(p->lc) == -1) // LR Rotation
            return LR(p);
        else if (BF(p) == -2 && BF(p->rc) == -1) // RR Rotation
            return RR(p);
        else if (BF(p) == -2 && BF(p->rc) == 1) // RL Rotation
            return RL(p);
        return p;
    }

    void inorder(node *t)
    {
        if (t != NULL) // if tree is not empty
        {
            inorder(t->lc);
            cout << t->key << " : " << t->mean << " : " << BF(t) << endl;
            inorder(t->rc);
        }
    }
};
int main()
{
    avl a;
    int ch;
    string x, y;
    do
    {
        cout << "1. INSERT" << endl;
        cout << "2. ASCENDING ORDER (INORDER)" << endl;
        cout << "3. EXIT" << endl;
        cout << "ENTER YOUR CHOICE" << endl;
        cin >> ch;
        switch (ch)
        {
        case 1:
        {
            cout << "ENTER KEYWORD AND MEANING " << endl;
            cin >> x >> y;
            a.root = a.insert(a.root, x, y);
            break;
        }
        case 2:
        {
            cout << "INORDER(ASCENDING ORDER)" << endl;
            a.inorder(a.root);
            break;
        }
        case 3:
        {
            exit(1);
            break;
        }
        default:
            cout << "INVALID INPUT " << endl;
        }
    } while (1);

    return 0;
}