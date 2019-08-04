#include <iostream>
#include "cal.h"
#include <map>
#include "timestamp.h"
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <list>
#include "ThreadTest.h"
#include "MessageQueue.h"
#include "Thread.h"

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int i) : val(i) {}
};

int add(int a, int b) { return a + b; }

int plus(int a, int b) { return abs(a - b); }

std::map<std::string, std::function<int(int, int)>> m = {
        {"+", add},
        {"-", ::plus},
        {"*", [](int i, int j) { return i * j; }},
        {"%", [](int i, int j) { return i / j; }}};

TreeNode *insertIntoBST(TreeNode *root, int val) {
    if (!root) return new TreeNode(val);
    if (root->val > val) root->left = insertIntoBST(root->left, val);
    if (root->val < val) root->right = insertIntoBST(root->right, val);
    return root;
}

void parents(TreeNode *root, unordered_map<TreeNode *, TreeNode *> &m) {
    if (!root) return;
    if (root->left) m[root->left] = root;
    if (root->right) m[root->right] = root;
    parents(root->left, m);
    parents(root->right, m);
}

void helper(TreeNode *root, int K, unordered_map<TreeNode *, TreeNode *> &m,
            unordered_set<TreeNode *> &s, vector<int> &res) {
    if (s.count(root) || K < 0) return;
    s.insert(root);
    if (K == 0) {
        res.push_back(root->val);
        return;
    }
    if (root->left) helper(root->left, K - 1, m, s, res);
    if (root->right) helper(root->right, K - 1, m, s, res);
    if (m[root]) helper(m[root], K - 1, m, s, res);
}

vector<int> distanceK(TreeNode *root, TreeNode *target, int K) {
    if (!root) return {};
    unordered_set<TreeNode *> s;
    unordered_map<TreeNode *, TreeNode *> m;
    vector<int> res;
    parents(root, m);
    helper(target, K, m, s, res);
    return res;
}

int depth(TreeNode *node) {
    return node ? 0 : (max(depth(node->left), depth(node->right)) + 1);
}

TreeNode *subtreeWithAllDeepest(TreeNode *root) {
    if (!root) return nullptr;
    int diff = depth(root->left) - depth(root->right);
    return (diff == 0) ? root : subtreeWithAllDeepest(diff > 0 ? root->left : root->right);
}

int threeSumClosest(vector<int> &nums, int target) {
    int diff = INT_MAX;
    int sum = INT_MAX;
    int res = INT_MAX;
    sort(nums.begin(), nums.end());
    for (int i = 0; i < nums.size(); ++i) {
        int left = i + 1, right = nums.size() - 1;
        while (left < right) {
            sum = nums[i] + nums[left] + nums[right];
            if (sum == target)
                return target;
            if (diff > abs(target - sum)) {
                res = sum;
                diff = abs(target - sum);
            }
            if (sum < target)
                ++left;
            else
                --right;
        }
    }
    return res;
}

void nextPermutation(vector<int> &nums) {
    if (nums.empty())
        return;
    int i = nums.size() - 1;
    for (; i > 0; --i) {
        if (nums[i] > nums[i - 1])
            break;
    }
    int j = nums.size() - 1;
    for (; j > i && i != 0; j--)
        if (nums[j] > nums[i - 1])
            break;
    if (i != 0)
        swap(nums[i - 1], nums[j]);
    reverse(nums.begin(), nums.end());
}

vector<int> twoSum(vector<int> &numbers, int target) {
    vector<int> res;
    int left = 0, right = numbers.size() - 1;
    int sum = numbers[left] + numbers[right];
    while (left < right && sum != target) {
        if (sum < target)
            ++left;
        else
            --right;
        sum = numbers[left] + numbers[right];
    }
    res.push_back(left + 1);
    res.push_back(right + 1);
    return res;
}

void fun() {
    cout << "func" << endl;
}

int pathSum(TreeNode *root, int sum, int &target) {
    if (!root) return 0;
    sum += root->val;
    return (sum == target) + pathSum(root->left, sum, target) + pathSum(root->right, sum, target)
           + pathSum(root->left, 0, target) + pathSum(root->right, 0, target);
}

int pathSum(TreeNode *root, int sum) {
    if (!root) return 0;
    return pathSum(root, 0, sum); //+ pathSum(root->left, 0, sum) + pathSum(root->right, 0, sum);
}

class TestFather {
public:
    TestFather(int i = 0) : numFather(i) {}

    void test() {
        cout << numFather << endl;
    }

    class TestSon {
    public:
        TestSon(int i = 0) : numSon(i) {}

        void test() {
            cout << numSon << endl;
        }

    private:
        int numSon;
    };

private:
    int numFather;
};

//函数内的static函数只属于函数体，内存只被分配一次，在下次调用时，会维持上次结束后的值；
void staticTest() {
    static int a = 1;
    cout << a << endl;
    ++a;
}

class Test {
public:
    Test(int t = 0) : ctest_(t) {
        static int test_ = t;
        cout << test_ << endl;
        cout << ctest_ << endl;
    }

private:
    const int ctest_;
};

int tribonacci(int n) {
    vector<int> vec{0, 1, 1};
    for (int i = 3; i <= n; ++i) {
        vec.push_back(vec[i - 3] + vec[i - 2] + vec[i - 1]);
    }
    return vec.back();
}

string alphabetBoardPath(string target) {
    int len = target.size();
    int path[len][2];
    string res = string();
    for (int i = 0; i < len; ++i) {
        path[i][0] = (target[i] - 'a') / 5;
        path[i][1] = (target[i] - 'a') % 5;
    }
    for (int i = 0; i < len; ++i) {
        int row = 0, col = 0;
        if (i == 0) {
            row = path[0][0];
            col = path[0][1];
        } else {
            row = path[i][0] - path[i - 1][0];
            col = path[i][1] - path[i - 1][1];
        }
        while (row != 0) {
            if (row > 0) {
                res += "D";
                --row;
            }
            if (row < 0) {
                res += "U";
                ++row;
            }
        }
        while (col != 0) {
            if (col > 0) {
                res += "R";
                --col;
            }
            if (col < 0) {
                res += "L";
                ++col;
            }
        }
        res += '!';
    }
    return res;
}

string decodeString(string s, int &i) {
    string res = string();
    int n = s.size();
    while (i < n && s[i] != ']') {
        if (s[i] < '0' || s[i] > '9')
            res += s[i++];
        else {
            int count = 0;
            while (s[i] >= '0' && s[i] <= '9')
                count = count * 10 + s[i++] - '0';
            ++i;
            string t = decodeString(s, i);
            ++i;
            while (count-- > 0)
                res += t;
        }
    }
    return res;
}

string decodeString(string s) {
    if (s.empty()) return "";
    int i = 0;
    return decodeString(s, i);
}

//class LRUCache {
//public:
//    LRUCache(int capacity) : capacity_(capacity) {
//    }
//
//    int get(int key) {
//        int res = -1;
//        auto it = m.find(key);
//        if(it!=m.end()){
//            res = it->second->second;
//            l.erase(it->second);
//            l.push_front(make_pair(key, res));
//            m[key] = l.begin();
//        }
//        return res;
//    }
//
//    void put(int key, int value) {
//        auto it = m.find(key);
//        if(it != m.end())
//            l.erase(it->second);
//        l.push_front(make_pair(key, value));
//        m[key] = l.begin();
//        if(m.size() > capacity_){
//            int k = l.rbegin()->first;
//            l.pop_back();
//            m.erase(k);
//        }
//    }
//
//private:
//    unordered_map<int, list<pair<int, int>>::iterator> m;
//    list<pair<int, int>> l;
//    int capacity_;
//};

class LRUCache {
public:
    LRUCache(int capacity) : capacity_(capacity) {
    }

    int get(int key) {
        auto it = m.find(key);
        if(it == m.end()) return -1;
        int res = m[key];
        for(auto i = queue_.begin();i!=queue_.end();++i) {
            if ((*i).first == key) {
                queue_.erase(i);
                break;
            }
        }
        queue_.push_back(make_pair(key, res));
        return res;
    }

    void put(int key, int value) {
        auto it = m.find(key);
        if(it == m.end())
            queue_.push_back(make_pair(key, value));
        else{
            for(auto i = queue_.begin();i!=queue_.end();++i) {
                if ((*i).first == key) {
                    queue_.erase(i);
                    break;
                }
            }
            queue_.push_back(make_pair(key, value));
        }
        if(queue_.size() > capacity_){
            int tmp = queue_.front().first;
            queue_.pop_front();
            m.erase(tmp);
        }
        m[key] = value;
    }

private:
    unordered_map<int, int> m;
    deque<pair<int, int>> queue_;
    int capacity_;
};


int main() {
    LRUCache lc(2);
    lc.put(1,1);
    lc.put(2,2);
    cout<<lc.get(1)<<endl;
    lc.put(3,3);
    cout<<lc.get(2)<<endl;
    cout<<"hello world;";
    return 0;
}