#ifndef AVLTREE_H
#define AVLTREE_H

/** Node of AVL tree. */
struct avlnode;

/** Insert key to AVL tree with root in specified node.
 *  O(log(n)), where n - number of nodes in tree
 *
 *  @return new root node
 **/
avlnode* avlinsert(avlnode* root, int key);

/** Check if key exists in AVL tree with root in specified node.
 *  O(log(n)), where n - number of nodes in tree
 *
 *  @return true if key exists in tree else false
 **/
bool avlexists(avlnode* root, int key);

#endif //AVLTREE_H

