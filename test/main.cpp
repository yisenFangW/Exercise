#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stack>
#include <queue>

using namespace std;

int majorityElement2(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    return nums[nums.size()/2];
}

int majorityElement(vector<int>& nums) {
    int tmp  = nums[0];
    int count = 1;
    for(int i=1;i<nums.size();++i){
        if(nums[i] == tmp) ++count;
        else --count;
        tmp = count?tmp:nums[i];
    }
    return tmp;
}

vector<int> searchRange(vector<int>& nums, int target) {
    if(nums.empty() || target<nums.front() || target > nums.back())
        return vector<int> {-1,-1};
    int left = 0, right = nums.size()-1;
    while(left <= right){
        int mid = left + (right-left)/2;
        if(left == right && nums[left]!= target)
            break;
        if(nums[mid] == target){
            int i = mid,j = mid;
            while(i>=left && nums[i] == target)
                --i;
            while(j<=right && nums[j] == target)
                ++j;
            return vector<int> {i+1,j-1};
        }
        else if(nums[mid] > target)
            right = mid;
        else
            left = mid+1;
    }
    return vector<int> {-1,-1};
}

//二叉树的数据结构
 struct TreeNode{
    TreeNode* left;
    TreeNode* right;
    int val;
    TreeNode(int i):val(i),left(nullptr),right(nullptr){}
};

//树的前序遍历 递归
void preTravesal(TreeNode* root){
    if(root) {
        cout << root->val << endl;
        preTravesal(root->left);
        preTravesal(root->right);
    }
}

//树的中序遍历 递归
void inTravesal(TreeNode* root){
    if(root) {
        preTravesal(root->left);
        cout << root->val << endl;
        preTravesal(root->right);
    }
}

//树的后序遍历 递归
void postTravesal(TreeNode* root){
    if(root) {
        preTravesal(root->left);
        preTravesal(root->right);
        cout << root->val << endl;
    }
}

//树的先序遍历 非递归
void preTravesal2(TreeNode* root){
    stack<TreeNode *> st;
    while(root!= nullptr || !st.empty()){
        while(root!= nullptr){
            st.push(root);
            cout<<root<<endl;
            root = root->left;
        }
        if(!st.empty()){
            root = st.top();
            st.pop();
            root = root->right;
        }
    }
}

//树的中序遍历 非递归
void inTravesal2(TreeNode* root){
    stack<TreeNode *> st;
    while(root!= nullptr || !st.empty()){
        while(root!= nullptr){
            st.push(root);
            root = root->left;
        }
        if(!st.empty()){
            root = st.top();
            st.pop();
            cout<<root<<endl;
            root = root->right;
        }
    }
}

//树的后序遍历 非递归 (将先序遍历的中左右变为中右左，再存入栈中即得到左右中)
void postTravesal2(TreeNode* root){
    stack<TreeNode *> st1;
    stack<int> st2;
    while(!st1.empty() || root!=nullptr){
        while(root != nullptr){
            st1.push(root);
            st2.push(root->val);
            root = root->right;
        }
        if(!st1.empty()){
            root = st1.top();
            st1.pop();
            root = root->left;
        }
    }
    while(!st2.empty()){
        cout<<st2.top()<<endl;
        st2.pop();
    }
}
//这个地方树的遍历可以写一个博客；

bool isSameTree(TreeNode* p, TreeNode* q) {
    if(p==nullptr && q==nullptr)
        return true;
    if(p->val != q->val)
        return false;
        if((p==nullptr && q!=nullptr) || (p!=nullptr && q== nullptr))
        return false;
    return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
}

//构建二叉树 递归建立
//这个函数在这里写的应该是有问题的
TreeNode *createTree(vector<int> nums, int n, int start)//按层序输入，结点为空时，输入'#'
{
    if(nums[start] == 0) return nullptr;
    TreeNode* root = new TreeNode(nums[start]);
    int lnode = 2 * start + 1;
    int rnode = 2 * start + 2;
    if (lnode > n - 1) root->left = NULL;
    else root->left = createTree(nums, n, lnode);
    if (rnode > n - 1) root->right = NULL;
    else root->right = createTree(nums, n, rnode);
    return root;
}

//这题的难度难就难在怎么给他分层
vector<vector<int>> levelOrder2(TreeNode* root) {
    vector<vector<int>> res;
    if(root == nullptr)
        return res;
    vector<TreeNode*> vec;
    vec.push_back(root);
    res.push_back(vector<int>(1,root->val));
    while(!vec.empty()){
        vector<int> tmp2;
        vector<TreeNode *> tmp1;
        for(int i=0;i<vec.size();++i) {
            if(vec[i]!= nullptr) {
                if (vec[i]->left) {
                    tmp1.push_back(vec[i]->left);
                    tmp2.push_back(vec[i]->left->val);
                }
                if (vec[i]->right) {
                    tmp1.push_back(vec[i]->right);
                    tmp2.push_back(vec[i]->right->val);
                }
            }
        }
        vec = tmp1;
        if(!tmp2.empty())
            res.push_back(tmp2);
    }
    return res;
}

vector<vector<int>> levelOrder(TreeNode* root) {
    vector<vector<int>> res;
    if (root == nullptr)
        return res;
    queue<TreeNode*>q{{root}};
    while(!q.empty()){
        vector<int> vec;
        //这个地方要用q.size()给i赋初值，因为q.size()是在不断变化的
        for(int i=q.size();i>0;--i){
            TreeNode* node = q.front();
            q.pop();
            vec.push_back(node->val);
            if(node->left) q.push(node->left);
            if(node->right) q.push(node->right);
         }
        res.push_back(vec);
    }
    return res;
}

int depth(TreeNode* root, int dep){
    if(root == nullptr)
        return dep;
    return max(depth(root->left, dep+1),depth(root->right, dep+1));
}

int maxDepth(TreeNode* root) {
    if(root == nullptr)
        return 0;
    int num = 0;
    return depth(root, num);
}

int sumNumber(TreeNode* root, int sum){
    if(root == nullptr)
        return 0;
    sum = sum * 10 + root->val;
    if(!root->left && !root->right) return sum;
    return sumNumber(root->left, sum) + sumNumber(root->right, sum);
}

int sumNumbers(TreeNode* root) {
    int sum = 0;
    return sumNumber(root, sum);
}

void sumNumber2(TreeNode* root, int num, int &sum){
    if(root == nullptr)
        return;
    num = num * 10 + root->val;
    if(!root->left && !root->right) {
        sum += num;
        return;
    }
    sumNumber2(root->left, num, sum);
    sumNumber2(root->right, num, sum);
}

int sumNumbers2(TreeNode* root) {
    int sum = 0;
    sumNumber2(root, 0, sum);
    return sum;
}

int inTrevelTree(TreeNode* root, int& k){
    if(!root) return -1;
    int val = inTrevelTree(root->left, k);
    if(k == 0) return val;
    if(--k == 0) return root->val;
    return inTrevelTree(root->right, k);
}

int kthSmallest(TreeNode* root, int k) {
    vector<int> vec;
    return inTrevelTree(root, k);
}

int count(TreeNode* root){
    if(!root) return 0;
    return 1+max(count(root->left), count(root->right));
}

int kthSmallest2(TreeNode* root, int k) {
    int n = count(root->left);
    if(n >= k)
        return kthSmallest2(root->left, k);
    if(n < k)
        return kthSmallest2(root->right, k-n-1);
    return root->val;
}


//这样写就是用一个标志位来标示是否是左子树，或者是右子树。
//程序结束的标志，就是root == nullptr，
void inTraTree(TreeNode* root, bool flag, int& res){
    if(!root)
        return;
    if(!root->left && !root->right && flag){
        res+=root->val;
    }
    inTraTree(root->left, true, res);
    inTraTree(root->right, false, res);
}

int sumOfLeftLeaves(TreeNode* root) {
    int res = 0;
    if(!root || (!root->left && !root->right)) return 0;
    inTraTree(root->left, true, res);
    inTraTree(root->right, false, res);
    return res;
}

int sumOfLeftLeaves2(TreeNode* root) {
    if(!root) return 0;
    if(root->left && !root->left->left && !root->left->right)
        return root->left->val + sumOfLeftLeaves2(root->right);
    return sumOfLeftLeaves2(root->left)+sumOfLeftLeaves2(root->right);
}

void binary(TreeNode* root, string str, vector<string>& res){
    if(!root) return;
    if(str.empty())
        str += to_string(root->val);
    else
        str = str + "->" + to_string(root->val);
    if(!root->left && !root->right) {
        res.push_back(str);
        str.pop_back();
    }
    binary(root->left, str, res);
    binary(root->right, str, res);
}

vector<string> binaryTreePaths(TreeNode* root) {
    vector<string> res;
    if(!root)
        return res;
    string str = "";
    binary(root, str, res);
    return res;
}

int countDepth(TreeNode* root){
    if(!root) return 0;
    int left = countDepth(root->left);
    if(left == -1)
        return -1;
    int right = countDepth(root->right);
    if(right == -1)
        return -1;
    if(abs(left - right) > 1)
        return -1;
    return 1+max(left, right);
}

bool isBalanced(TreeNode* root) {
    if(!root)
        return true;
    int left = countDepth(root->left);
    int right = countDepth((root->right));
    if(left == -1 || right == -1 || abs(left - right) > 1)
        return false;
    return isBalanced(root->left) && isBalanced(root->right);
}

bool isBalanced2(TreeNode* root) {
    if(!root)
        return true;
    if(abs(count(root->left) - count(root->right)) > 1)
        return false;
    return isBalanced2(root->left) && isBalanced2(root->right);
}

int main() {
    vector<int> nums = {4,9,0,5,1};
    TreeNode* root = createTree(nums, nums.size(), 0);
    vector<string> res = binaryTreePaths(root);
    for(auto str:res)
        cout<<str<<" ";

//    vector<vector<int>> res = levelOrder(root);
//    for(auto i:res) {
//        for (auto j:i)
//            cout << j << " ";
//        cout<<endl;
//    }
    return 0;
}





















