#include<stack>
using std::stack;
struct TreeNode{
    int val;
    TreeNode*left;
    TreeNode*right;
    TreeNode(int x):val(x),left(nullptr),right(nullptr){}
};
void preorder(TreeNode*root){
    if(root==nullptr){
        return;
    }
    stack<TreeNode*>st;
    st.push(root);
    while(st.size()){
        TreeNode* cur=st.top();
        st.pop();
        /*
        前序位置
        */
       if(cur->right!=nullptr){
        st.push(cur->right);
       }
       if(cur->left!=nullptr){
        st.push(cur->left);
       }
    }
}
void inorder(TreeNode*root){
    if(root==nullptr){
        return;
    }
    stack<TreeNode*>st;
    TreeNode*cur=root;
    while(st.size()||cur!=nullptr){
        if(cur!=nullptr){
            st.push(cur);
            cur=cur->left;
        }
        else{
            cur=st.top();
            st.pop();
            /*
            中序位置
            */
           cur=cur->right;
        }
    }
}
void postorder(TreeNode*root){
    if(root==nullptr){
        return;
    }
    stack<TreeNode*>st;
    st.push(root);
    while(st.size()){
        TreeNode*cur=st.top();
        if(cur->left!=nullptr&&cur->left!=root&&cur->right!=root){
            st.push(cur->left);
        }
        else if(cur->right!=nullptr&&cur->right!=root){
            st.push(cur->right);
        }
        else{
            /*
            后序位置
            */
           root=st.top();
           st.pop();
        }
    }
}