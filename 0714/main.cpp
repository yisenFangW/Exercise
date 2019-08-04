#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <queue>
#include "smartPtr.h"

using namespace std;

struct TreeNode{
    TreeNode* left;
    TreeNode* right;
    int val;
    TreeNode(int i):val(i),left(nullptr),right(nullptr){}
};

TreeNode* arrayToBST(vector<int>& nums, int start, int end){
    if(end < start)
        return nullptr;
    if(end  == start)
        return new TreeNode(nums[start]);;
    int mid = start+(end-start)/2;
    TreeNode* root = new TreeNode(nums[mid]);
    root->left = arrayToBST(nums, start, mid-1);
    root->right = arrayToBST(nums, mid+1, end);
    return root;
}

TreeNode* sortedArrayToBST(vector<int>& nums) {
    return arrayToBST(nums, 0, nums.size()-1);
}

void preTravel(TreeNode* root, vector<TreeNode*>& vec){
    if(root){
        vec.push_back(root);
        preTravel(root->left, vec);
        preTravel(root->right, vec);
    }
}

void flatten(TreeNode* root) {
    vector<TreeNode*> vec;
    //TreeNode* node = root;
    preTravel(root, vec);
    for(int i=0;i<vec.size();++i){
        vec[i]->left = nullptr;
        if(i+1<vec.size())
            vec[i]->right = vec[i+1];
    }
}

void flatten2(TreeNode* root) {
    if(!root) return;
    if(root->left) flatten2(root->left);
    if(root->right) flatten2(root->right);
    TreeNode* tmp = root->right;
    root->right = root->left;
    root->left = nullptr;
    while(root->right) root = root->right;
    root->right = tmp;
}

void flatten3(TreeNode* root) {
    if(!root) return;
    while(root){
        if(root->left) {
            TreeNode *tmp = root->right;
            TreeNode *node = root;
            root->right = root->left;
            root->left = nullptr;
            while (node->right) node = node->right;
            node->right = tmp;
        }
        root = root->right;
    }
}

void getMinmunDiff(TreeNode* root, int& minDiff){
    if(root){
        getMinmunDiff(root->left, minDiff);
        if(root->left)
            minDiff = min(minDiff, abs(root->val-root->left->val));
        getMinmunDiff(root->right, minDiff);
        if(root->right)
            minDiff = min(minDiff, abs(root->val-root->right->val));
    }
}


void inTravel(TreeNode* root, int& pre, int &minDiff){
    if(!root) return;
    inTravel(root->left, pre, minDiff);
    if(pre!=-1)
        minDiff = min(minDiff, root->val - pre);
    inTravel(root->right, root->val, minDiff);
}

int getMinimumDifference(TreeNode* root) {
    int minDiff = INT_MAX, pre = -1;
    inTravel(root, pre, minDiff);
    return minDiff;
}


int getMinimumDifference2(TreeNode* root) {
    vector<int> nums;
    //inTravel(root, nums);
    int minDiff = INT_MAX;
    for(int i=0;i<nums.size()-1;++i)
        minDiff = min(minDiff, abs(nums[i+1]- nums[i]));
    return minDiff;
}

void serialize(TreeNode* root, ostringstream& os) {
    if(!root) os<<"#";
    else{
        os<<root->val<<" ";
        serialize(root->left, os);
        serialize(root->right, os);
    }
}

// Encodes a tree to a single string.
string serialize(TreeNode* root) {
    ostringstream os;
    serialize(root, os);
    return os.str();
}

TreeNode* deserialize(istringstream& is) {
    string str = "";
    is>>str;
    if(str == "#") return nullptr;
    TreeNode* root = new TreeNode(stoi(str));
    root->left = deserialize(is);
    root->right = deserialize(is);
    return root;
}

// Decodes your encoded data to tree.
TreeNode* deserialize(string data) {
    istringstream is(data);
    return deserialize(is);
}

vector<int> largestValues(TreeNode* root) {
    if(!root) return {};
    vector<vector<TreeNode*>> vec;
    vec.push_back({root});
    while(1){
        vector<TreeNode*> tmp;
        vector<TreeNode*> end = vec.back();
        for(auto tree:end){
            if(!tree)
                continue;
            if(tree->left)
                tmp.push_back(tree->left);
            if(tree->right)
                tmp.push_back(tree->right);
        }
        if(tmp.empty())
            break;
        vec.push_back(tmp);
    }
    vector<int> res;
    for(auto arr:vec){
        int max = INT_MIN;
        for(auto tree:arr) {
            if(!tree) continue;
            if (tree->val > max)
                max = tree->val;
        }
        res.push_back(max);
    }
    return res;
}

vector<int> largestValues2(TreeNode* root){
    if(!root) return{};
    queue<TreeNode*> q;
    q.push(root);
    vector<int> res;
    while(!q.empty()){
        int n = q.size();
        int maxNum = INT_MIN;
        for(int i=0;i<n;++i){
            TreeNode* node = q.front();
            q.pop();
            maxNum = max(maxNum, node->val);
            if(node->left)
                q.push(node->left);
            if(node->right)
                q.push(node->right);
        }
        res.push_back(maxNum);
    }
    return res;
}

TreeNode* constructMaximumBinaryTree(vector<int>& nums, int left, int right){
    if(left>right)
        return nullptr;
    if(left == right)
        return new TreeNode(nums[left]);
    int maxNum = nums[left], index = left;
    for(int i=left;i<=right;++i){
        if(nums[i]>maxNum){
            maxNum = nums[i];
            index = i;
        }
    }
    TreeNode* root = new TreeNode(maxNum);
    root->left = constructMaximumBinaryTree(nums, left, index-1);
    root->right = constructMaximumBinaryTree(nums, index+1, right);
    return root;
}

TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
    return constructMaximumBinaryTree(nums, 0, nums.size()-1);
}

vector<int> rightSideView(TreeNode* root) {
    if(!root) return {};
    queue<TreeNode*> q;
    q.push(root);
    vector<int> res;
    while(!q.empty()){
        int n = q.size();
        for(int i=0;i<n;++i){
            if(i == n-1) {
                res.push_back(q.front()->val);
            }
            if(q.front()->left)
                q.push(q.front()->left);
            if(q.front()->right)
                q.push(q.front()->right);
            q.pop();

        }
    }
    return res;
}

int depth(TreeNode* root, int num){
    if(!root)
        return num;
    return max(depth(root->left, num+1), depth(root->right, num+1));
}

void Travel(TreeNode* root, vector<TreeNode*>& vec){
    if(root){
        vec.push_back(root);
        Travel(root->left, vec);
        Travel(root->right, vec);
    }
}

int diameterOfBinaryTree(TreeNode* root) {
    if(!root) return 0;
    vector<TreeNode*> roots;
    Travel(root, roots);
    int maxLen = 0;
    for(auto root:roots){
        int num = depth(root->left, 0)+ depth(root->right, 0) - 1;
        maxLen = max(maxLen, num);
    }
    return maxLen;
}

int countNodes(TreeNode* root) {
    if(!root) return 0;
    queue<TreeNode*> q;
    q.push(root);
    int res = 0;
    while(!q.empty()){
        int num = q.size();
        res+=num;
        for(int i=0;i<num;++i){
            if(q.front()->left)
                q.push(q.front()->left);
            if(q.front()->right)
                q.push(q.front()->right);
            q.pop();
        }
    }
    return res;
}



int countNodes2(TreeNode* root){
    if(!root) return 0;
    TreeNode* left = root, * right = root;
    int leftCount = 0, rightCount = 0;
    while(left){
        ++leftCount;
        left = left->left;
    }
    while(right){
        ++rightCount;
        right = right->right;
    }
    if(leftCount == rightCount)
        return pow(2, leftCount) - 1;
    return countNodes2(root->left) + countNodes2(root->right)+1;
}

TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if(!root || root == p || root == q)
        return root;
    TreeNode* left = lowestCommonAncestor(root->left, p, q);
    TreeNode* right = lowestCommonAncestor(root->right, p, q);
    if(left && right) return root;
    return left?left:right;
}

int findBottomLeftValue(TreeNode* root) {
    queue<TreeNode*> q;
    q.push(root);
    int res = 0;
    while(!q.empty()){
        int num = q.size();
        for(int i=0;i<num;++i){
            if(i == 0)
                res = q.front()->val;
            if(q.front()->left)
                q.push(q.front()->left);
            if(q.front()->right)
                q.push(q.front()->right);
            q.pop();
        }
    }
    return res;
}

//原来是自己傻逼了，写了两个left，然后导致right不传进去，就说引用怎么可能不对呢
void leftTravel(TreeNode* node, unordered_map<int, int>& m){
    if(!node) return;
    leftTravel(node->left, m);
    ++m[node->val];
    leftTravel(node->right, m);
}

vector<int> findMode(TreeNode* root) {
    if(!root) return {};
    unordered_map<int, int> m;
    vector<int> res;
    leftTravel(root, m);
    int maxLen = 0;
    for(auto iter = m.begin();iter!=m.end();++iter)
        maxLen = max(maxLen, iter->second);
    for(auto iter = m.begin();iter!=m.end();++iter) {
        if (iter->second == maxLen)
            res.push_back(iter->first);
    }
    return res;
}

int tilt(TreeNode* root){
    if(root == nullptr) return 0;
    return root->val+tilt(root->left)+tilt(root->right);
}

int findTilt(TreeNode* root) {
    if(!root) return 0;
    int left = tilt(root->left);
    int right = tilt(root->right);
    return abs(left-right) + findTilt(root->left) + findTilt(root->right);;
}

bool isSame(TreeNode* s, TreeNode* t){
    if(!s && !t) return true;
    if(!s || !t) return false;
    if(s->val != t->val) return false;
    return isSame(s->left, t->left) && isSame(s->right, t->right);
}

bool isSubtree(TreeNode* s, TreeNode* t) {
    if(!s) return false;
    if(isSame(s,t)) return true;
    return isSubtree(s->left, t) || isSubtree(s->right, t);
}

void findSubtrees(TreeNode* root, vector<TreeNode*> res){

}

vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {

}

class Test{
public:
    Test(){cout<<"test construct!"<<endl;}
    ~Test(){cout<<"test disconstruct"<<endl;}
};

int main() {
    Test* t = new Test();
    SmartPtr<Test> sm(t);
    //sm.getStr();
    return 0;
}























