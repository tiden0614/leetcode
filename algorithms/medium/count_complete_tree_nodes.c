/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
#include <math.h>
int height(struct TreeNode* root) {
    // compute the height of the tree
    int l = 0;
    struct TreeNode* p = root;
    while (p != NULL) {
        l += 1;
        p = p->left;
    }
    return l;
}
int countNodes(struct TreeNode* root) {
    if (root == NULL) return 0;
    // compute the height of the tree
    int h = height(root);
    
    if (root->right == NULL) {
        if (root->left == NULL) return 1;
        return 2;
    }
    
    int rh = height(root->right);
    if (rh < h - 1) {
        // left child is a complete tree and right child is a full tree
        return countNodes(root->left) + pow(2, rh);
    }
    
    // left child is a full tree and right child is a complete tree
    return pow(2, h - 1) + countNodes(root->right);
}