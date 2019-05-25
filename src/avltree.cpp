#include "avltree.h"

struct avlnode {
    int key;
    avlnode* left;
    avlnode* right;
    unsigned char height;
    explicit avlnode(int key) : key(key), left(nullptr), right(nullptr), height(1) {}
};

unsigned char avlheight(avlnode* node) {
    return node != nullptr ? node->height : 0;
}

int avlbfactor(avlnode* node) {
    return avlheight(node->right) - avlheight(node->left);
}

void avlfixheight(avlnode* node) {
    unsigned char lh = avlheight(node->left);
    unsigned char rh = avlheight(node->right);
    node->height = (lh > rh ? lh : rh) + 1;
}

avlnode* avlrotateright(avlnode* node) {
    avlnode* l = node->left;
    node->left = l->right;
    l->right = node;
    avlfixheight(node);
    avlfixheight(l);
    return l;
}

avlnode* avlrotateleft(avlnode* node) {
    avlnode* r = node->right;
    node->right = r->left;
    r->left = node;
    avlfixheight(node);
    avlfixheight(r);
    return r;
}

avlnode* avlbalance(avlnode* node) {
    avlfixheight(node);
    if (avlbfactor(node) == 2) {
        if (avlbfactor(node->right) < 0) {
            node->right = avlrotateright(node->right);
        }
        return avlrotateleft(node);
    }
    if (avlbfactor(node) == -2) {
        if (avlbfactor(node->left) > 0) {
            node->left = avlrotateleft(node->left);
        }
        return avlrotateright(node);
    }
    return node;
}

avlnode* avlinsert(avlnode* root, const int key) {
    if (root == nullptr) {
        return new avlnode(key);
    } else if (key < root->key) {
        root->left = avlinsert(root->left, key);
    } else if (root->key == key) {
        return root;
    } else {
        root->right = avlinsert(root->right, key);
    }
    return avlbalance(root);
}

bool avlexists(avlnode* root, const int key) {
    if (root == nullptr) {
        return false;
    } else if (key < root->key) {
        return avlexists(root->left, key);
    } else if (root->key == key) {
        return true;
    } else {
        return avlexists(root->right, key);
    }
}

