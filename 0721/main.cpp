#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <string>
#include <queue>
#include <stack>

using namespace std;

struct TreeNode{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int i):val(i),left(nullptr),right(nullptr){}
};

void leftTravel(TreeNode* root, vector<TreeNode*>& vec, int L, int R){
    if(root){
        leftTravel(root->left, vec, L, R);
        if((root->val >= L) && (root->val <= R))
            vec.push_back(root);
        leftTravel(root->right, vec, L, R);
    }
}

TreeNode* trimBST2(TreeNode* root, int L, int R) {
    if(!root) return nullptr;
    vector<TreeNode*> vec;
    leftTravel(root, vec, L, R);
    if(vec.empty()) return nullptr;
    vec.front()->left = nullptr;
    vec.back()->right = nullptr;
    int index = -1;
    for(int i=0;i<vec.size()-1;++i){
        vec[i]->right = vec[i+1];
        vec[i+1]->left = vec[i];
        if(vec[i] == root)
            index = i;
        if(vec[i+1] == root)
            index = i+1;
    }
    return index == -1?vec.front():vec[index];
}

TreeNode* trimBST(TreeNode* root, int L, int R) {
    if(!root) return nullptr;
    if(root->val < L) return trimBST(root->right, L, R);
    if(root->val > R) return trimBST(root->left, L, R);
    root->left = trimBST(root->left, L, R);
    root->right = trimBST(root->right, L, R);
    return root;
}

bool isZeroTree(TreeNode* root){
    if(!root) return false;
    if(root->val) return true;
    return isZeroTree(root->left) || isZeroTree(root->right);
}

TreeNode* pruneTree2(TreeNode* root) {
    if(!root) return nullptr;
    if(root->val) {
        root->left = pruneTree2(root->left);
        root->right = pruneTree2(root->right);
    }
    if(root->val == 0)
        if(!isZeroTree(root))
            root = nullptr;
    return root;
}

TreeNode* pruneTree(TreeNode* root) {
    if(!root) return nullptr;
    root->left = pruneTree(root->left);
    root->right = pruneTree(root->right);
    return (root->val == 0 && !root->left && !root->right)? nullptr:root;
}

int calculateTree(TreeNode* root){
    if(!root) return 0;
    return root->val+calculateTree(root->left)+calculateTree(root->right);
}

void leftTravel(TreeNode* root, unordered_map<int, int>& m){
    if(!root) return;
    leftTravel(root->left, m);
    ++m[calculateTree(root)];
    leftTravel(root->right, m);
}

vector<int> findFrequentTreeSum(TreeNode* root) {
    unordered_map<int, int> m;
    leftTravel(root, m);
    vector<int> vec;
    int maxSize = 0;
    for(auto i = m.begin();i!=m.end();++i)
        maxSize = max(maxSize, i->second);
    for(auto i = m.begin();i!=m.end();++i)
        if(i->second == maxSize)
            vec.push_back(i->first);
    return vec;
}

void traveTree(TreeNode* root, vector<vector<string>>){
    if(!root) return;

}

int treeHeight(TreeNode* root){
    if(!root) return 0;
    return 1+treeHeight(root->left)+treeHeight(root->right);
}

vector<vector<string>> printTree(TreeNode* root) {
    if(!root) return {{}};
    vector<vector<string>> res;
    queue<TreeNode*> q;
    q.push(root);
    while(!q.empty()){
        int n = q.size();
        vector<string> vec;
        for(int i=0;i<n;++i){
            TreeNode* tmp = q.front();
            q.pop();
            if(tmp == nullptr) {
                vec.push_back("");
                continue;
            }
            vec.push_back(to_string(tmp->val));
            q.push(tmp->left);
            q.push(tmp->right);
        }
        res.push_back(vec);
    }
    return res;
}

vector<TreeNode*> helper(int start, int end){
    if(start > end) return {nullptr};
    vector<TreeNode*> res;
    for(int i=start;i<=end;++i){
        auto left = helper(start, i-1);
        auto right = helper(i+1, end);
        for(auto a:left)
            for(auto b:right){
                TreeNode* node = new TreeNode(i);
                node->left = a;
                node->right = b;
                res.push_back(node);
            }
    }
    return res;
}

vector<TreeNode*> generateTrees(int n) {
    if(n == 0) return {nullptr};
    return helper(0, n);
}

void rightTravel(TreeNode* root, stack<TreeNode*>& s){
    if(!root) return;
    rightTravel(root->left, s);
    s.push(root);
    rightTravel(root->right, s);
}

TreeNode* convertBST(TreeNode* root) {
    if(!root) return nullptr;
    stack<TreeNode*> s;
    rightTravel(root, s);
    int sum = 0;
    while(!s.empty()){
        TreeNode* tmp = s.top();
        tmp->val += sum;
        sum = tmp->val;
        s.pop();
    }
    return root;
}

void rightTravel2(TreeNode* root, int sum){
    if(!root) return;
    rightTravel2(root->right, sum);
    root->val += sum;
    sum = root->val;
    rightTravel2(root->left, sum);
}

TreeNode* convertBST2(TreeNode* root) {
    if(!root) return nullptr;
    int sum = 0;
    rightTravel2(root, sum);
    return root;
}

TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if(root->val > max(p->val, q->val))
        return lowestCommonAncestor(root->left, p, q);
    if(root->val < min(p->val, q->val))
        return lowestCommonAncestor(root->right, p, q);
    return root;
}

void isBST(TreeNode* root, vector<int>& nums){
    if(!root) return;
    isBST(root->left, nums);
    nums.push_back(root->val);
    isBST(root->right, nums);
}

bool isValidBST(TreeNode* root) {
    if(!root) return true;
    vector<int> nums;
    isBST(root, nums);
    for(int i=0;i<nums.size()-1;++i){
        if(nums[i]>=nums[i+1])
            return false;
    }
    return true;
}

bool isBST2(TreeNode* root, int maxNum, int minNum){
    if(!root) return true;
    if(root->val <= minNum || root->val >= maxNum)
        return false;
    return isBST2(root->left, root->val, minNum) && isBST2(root->right, maxNum, root->val);
}

bool isValidBST2(TreeNode* root) {
    if(!root) return true;
    return isBST2(root, INT_MAX, INT_MIN);
}

vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
    if(!root) return{};
    queue<TreeNode*> q;
    q.push(root);
    vector<vector<int>> res;
    bool flag = false;
    while(!q.empty()){
        int n = q.size();
        vector<int> vec;
        for(int i=0;i<n;++i){
            TreeNode* tmp = q.front();
            q.pop();
            if(flag){
                if(tmp->left)
                    q.push(tmp->left);
                if(tmp->right)
                    q.push(tmp->right);
            }else{
                if(tmp->right)
                    q.push(tmp->right);
                if(tmp->left)
                    q.push(tmp->left);
            }
            vec.push_back(tmp->val);
        }
        flag = !flag;
        res.push_back(vec);
    }
    return res;
}

void swapVec(vector<int> &vec){
    if(vec.size() <= 1)
        return;
    for(int i=0,j=vec.size()-1;i<=j;)
        swap(vec[i++], vec[j--]);
}

vector<vector<int>> zigzagLevelOrder2(TreeNode* root) {
    if(!root) return{};
    queue<TreeNode*> q;
    q.push(root);
    vector<vector<int>> res;
    while(!q.empty()){
        int n = q.size();
        vector<int> vec;
        for(int i=0;i<n;++i){
            TreeNode* tmp = q.front();
            q.pop();
            if(tmp->left)
                q.push(tmp->left);
            if(tmp->right)
                q.push(tmp->right);
            vec.push_back(tmp->val);
        }
        res.push_back(vec);
    }
    for(int i=0;i<res.size();++i) {
        if((i+1)%2 == 0)
            swapVec(res[i]);
    }
    return res;
}

int func(int a, int b){
    return a+b;
}

int minDepth(TreeNode* root) {
    if(!root) return 0;
    if(!root->left) return 1 + minDepth(root->left);
    if(!root->right) return 1 + minDepth(root->right);
    return 1+ min(minDepth(root->left), minDepth(root->right));
}

TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder, int inLeft,
        int inRight, int postLeft, int postRight){
    if (inLeft > inRight || postLeft > postRight) return nullptr;
    int nodeVal = postorder[postRight];
    TreeNode* node = new TreeNode(nodeVal);
    int index = inLeft;
    while(inorder[index] != nodeVal && index < inRight)
        ++index;
    node->left = buildTree(inorder, postorder, inLeft, index-1, postLeft,
            postLeft + index - inLeft - 1);
    node->right = buildTree(inorder, postorder, index+1, inRight,
            postLeft + index - inLeft, postRight - 1);
    return node;
}

TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
    if(inorder.empty() || postorder.empty())
        return nullptr;
    return buildTree(inorder, postorder, 0, inorder.size()-1,
            0, postorder.size()-1);
}

TreeNode* findNode(TreeNode* root, int key){
    if(!root) return nullptr;
    if(root->val > key)
        return findNode(root->left, key);
    if(root->val < key)
        return findNode(root->right, key);
    return root;
}

TreeNode* deleteNode(TreeNode* root, int key) {
    if(!root) return nullptr;
    if(root->val > key) deleteNode(root->left, key);
    if(root->val < key) deleteNode(root->right, key);
    //TreeNode* node = findNode(root, key);
    if(!root->left || !root->right)
        root = (root->left)?root->left:root->right;
    else{
        TreeNode* tmp = root->right;
        while(tmp->left) tmp = tmp->left;
        root->val = tmp->val;
        root->right = deleteNode(root->right, tmp->val);
    }
    return root;
}

struct Node{
    int val;
    Node* left;
    Node* right;
    Node* next;
    Node(){}
    Node(int _val, Node* _left, Node* _right, Node* _next){
        val = _val;
        left = _left;
        right = _right;
        next = _next;
    }
};

Node* connect(Node* root) {
    if(!root) return nullptr;
    queue<Node*> q;
    q.push(root);
    while(!q.empty()){
        int n = q.size();
        for(int i=0;i<n;++i){
            Node* tmp = q.front();
            q.pop();
            if(i == n-1)
                tmp->next = nullptr;
            else
                tmp->next = q.front();
            if(tmp->left)
                q.push(tmp->left);
            if(tmp->right)
                q.push(tmp->right);
        }
    }
    return root;
}

void helper(TreeNode* t, string& res){
    if(!t) return;
    res += "(" +to_string(t->val);
    if(!t->left && t->right) res += "()";
    helper(t->left, res);
    helper(t->right, res);
    res += ")";
}

string tree2str(TreeNode* t) {
    if(!t) return "";
    string res = "";
    helper(t, res);
    return string(res.begin()+1, res.end()-1);
}

Node* connect2(Node* root) {
    if(!root) return nullptr;
    if(root->left) root->left->next = root->right;
    if(root->right) root->right->next = (root->next)?root->next->left: nullptr;
    connect2(root->left);
    connect2(root->right);
    return root;
}

TreeNode* mergeTrees(TreeNode* t1, TreeNode* t2) {
    if(!t1) return t2;
    if(!t2) return t1;
    TreeNode* root = new TreeNode(t1->val+t2->val);
    root->left = mergeTrees(t1->left, t2->left);
    root->right = mergeTrees(t1->right, t2->right);
    return root;
}

int widthOfBinaryTree(TreeNode* root) {
    if(!root) return 0;
    queue<TreeNode*> q;
    q.push(root);
    int maxWidth = 0;
    while(!q.empty()){
        int n = q.size();
        maxWidth = max(n, maxWidth);
        for(int i=0;i<n;++i){
            TreeNode* tmp = q.front();
            q.pop();
            if(!tmp) continue;
            if(!tmp->left) q.push(nullptr);
            else q.push(tmp->left);
            if(!tmp->right) q.push(nullptr);
            else q.push(tmp->right);
        }
    }
    return maxWidth;
}

bool isCompleteTree(TreeNode* root) {
    if(!root) return true;
    queue<TreeNode*> q;
    bool flag = false;
    while(!q.empty()){
        TreeNode* node = q.front();
        q.pop();
        if(flag && (node->left || node->right)) return false;
        if(node->left) q.push(node->left);
        else flag = true;
        if(flag && !node->right) return false;
        if(node->right) q.push(node->right);
        else flag = true;
    }
    return true;
}

int calSum(int num){
    if(num == 0)
        return 0;
    else{
        if(num % 2 == 0)
            return calSum(num-1)+num;
        else
            return calSum(num-1);
    }
}

vector<double> averageOfLevels(TreeNode* root) {
    if(!root) return {};
    queue<TreeNode*> q;
    q.push(root);
    vector<double> res;
    while(!q.empty()){
        int n = q.size();
        int sum = 0;
        for(int i=0;i<n;++i){
            TreeNode* tmp = q.front();
            q.pop();
            sum+=tmp->val;
            if(tmp->left) q.push(tmp->left);
            if(tmp->right) q.push(tmp->right);
        }
        res.push_back(sum/n);
    }
    return res;
}

int main() {
    cout<<calSum(100)<<endl;
//    int (*Add1)(int, int);
//    Add1 = &func;
//    cout<<Add1(1, 2)<<endl;
    std::cout << "Hello, World!" << std::endl;
    return 0;
}















