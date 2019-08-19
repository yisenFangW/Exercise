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
        if (it == m.end()) return -1;
        int res = m[key];
        for (auto i = queue_.begin(); i != queue_.end(); ++i) {
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
        if (it == m.end())
            queue_.push_back(make_pair(key, value));
        else {
            for (auto i = queue_.begin(); i != queue_.end(); ++i) {
                if ((*i).first == key) {
                    queue_.erase(i);
                    break;
                }
            }
            queue_.push_back(make_pair(key, value));
        }
        if (queue_.size() > capacity_) {
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

char intToString(int i) {
    if (i > 9 || i < 0)
        return -1;
    return i + '0';
}

template<typename T>
string convert(T t) {
    T tmp = t;
    string res = string();
    while (tmp != 0) {
        int num = static_cast<int> (tmp % 10);
        char c = intToString(num);
        res += c;
        tmp = tmp / 10;
    }
    reverse(res.begin(), res.end());
    return res;
}

int search(vector<int> &nums, int target) {
    int left = 0, right = nums.size() - 1;
    while (left <= right) {
        if (nums[left] == target)
            return left;
        if (nums[right] == target)
            return right;
        int mid = left + (right - left) / 2;
        if (nums[mid] == target)
            return mid;
        if (nums[mid] < nums[right]) {
            if (target > nums[mid] && target < nums[right])
                left = mid + 1;
            else
                right = mid - 1;
        } else {
            if (target > nums[left] && target < nums[mid])
                right = mid - 1;
            else
                left = mid + 1;
        }
    }
    return -1;
}

TreeNode *invertTree(TreeNode *root) {
    if (!root) return nullptr;
    TreeNode *tmp = root->right;
    root->right = invertTree(root->left);
    root->left = invertTree(tmp);
    return root;
}

//这样写会超时
vector<int> findAnagrams2(string s, string p) {
    if (s.empty() || p.empty() || s.size() < p.size())
        return {};
    vector<int> res;
    int pn = p.size();
    sort(p.begin(), p.end());
    for (int i = 0; i < s.size() - pn + 1; ++i) {
        string tmp = s.substr(i, pn);
        sort(tmp.begin(), tmp.end());
        if (tmp == p) res.push_back(i);
    }
    return res;
}


//what fuck！还是会超时；
vector<int> findAnagrams3(string s, string p) {
    if (s.empty() || p.empty() || s.size() < p.size())
        return {};
    vector<int> res;
    int ns = s.size(), np = p.size();
    unordered_map<int, int> m;
    for (auto c:p) ++m[c];
    unordered_map<int, int> tm = m;
    bool flag = true;
    for (int i = 0; i < ns - np + 1; ++i) {
        flag = true;
        tm = m;
        for (int count = 0; count < np; ++count) {
            if (tm.count(s[i + count]) == 0 || tm[s[i + count]] == 0) {
                flag = false;
                break;
            } else
                --tm[s[i + count]];
        }
        if (flag) res.push_back(i);
    }
    return res;
}

vector<int> findAnagrams(string s, string p) {
    if (s.empty() || p.empty() || s.size() < p.size())
        return {};
    vector<int> win_s(26, 0), win_p(26, 0), res;
    int l = 0, r = -1;
    for (int i = 0; i < p.size(); ++i) {
        ++win_p[p[i] - 'a'];
        ++win_s[s[++r] - 'a'];
    }
    if (win_s == win_p) res.push_back(l);
    while (r < s.size() - 1) {
        --win_s[s[l++] - 'a'];
        ++win_s[s[++r] - 'a'];
        if (win_s == win_p)
            res.push_back(l);
    }
    return res;
}

vector<vector<int>> reconstructQueue(vector<vector<int>> &people) {
    sort(people.begin(), people.end(), [](vector<int> v1, vector<int> v2) {
        if (v1[0] == v2[0]) return v1[1] < v2[1];
        else return v1[0] > v2[0];
    });
    vector<vector<int>> res;
    for (auto p:people)
        res.insert(res.begin() + p[1], p);
    return res;
}

//设定这个start参数应该是为了去重，如果不加这个参数，应该是会存在很多重复的？
void combinationSum(vector<int> &candidates, int target, int start, vector<int> &vec, vector<vector<int>> &res) {
    if (target < 0) return;
    if (0 == target) {
        res.push_back(vec);
        return;
    }
    for (int i = start; i < candidates.size(); ++i) {
        vec.push_back(candidates[i]);
        combinationSum(candidates, target - candidates[i], i, vec, res);
        vec.pop_back();
    }
}

vector<vector<int>> combinationSum(vector<int> &candidates, int target) {
    if (candidates.empty() || target <= 0) return {};
    vector<vector<int>> res;
    vector<int> vec;
    combinationSum(candidates, target, 0, vec, res);
    return res;
}

void letterCombinations(string &digits, vector<string> &dict, int level, string &out, vector<string> &res) {
    if (level == digits.size()) {
        res.push_back(out);
        return;   //注意这个return一定要加啊，不然就会完全停不下来；
    }
    string str = dict[digits[level] - '0'];
    for (auto c:str) {
        out += c;
        letterCombinations(digits, dict, level + 1, out, res);
        out.pop_back();
    }
}

vector<string> letterCombinations(string digits) {
    if (digits.empty()) return {};
    //因为是从2开始，所以前面两个为空啊
    vector<string> dict{"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
    vector<string> res;
    string out;
    letterCombinations(digits, dict, 0, out, res);
    return res;
}

int hammingDistance2(int x, int y) {
    int res = 0;
    while (x != 0 || y != 0) {
        int tmpx = x % 2;
        x /= 2;
        int tmpy = y % 2;
        y /= 2;
        if (tmpx != tmpy)
            ++res;
    }
    return res;
}

int hammingDistance(int x, int y) {
    int res = 0;
    for (int i = 0; i < 32; ++i) {
        if ((x & 1 << i) ^ (y & 1 << i))
            ++res;
    }
    return res;
}

//前缀树学习实现
struct TrieNode {
    bool isWord;
    TrieNode *next[26];

    TrieNode() {
        memset(next, NULL, sizeof(next));
        isWord = false;
    }

    ~TrieNode() {
        for (int i = 0; i < 26; ++i)
            delete next[i];
    }
};

class Trie {
    TrieNode *root;
public:
    /** Initialize your data structure here. */
    Trie() {
        root = new TrieNode();
    }

    ~Trie() {
        delete root;
    }

    /** Inserts a word into the trie. */
    void insert(string word) {
        if (word.empty()) return;
        TrieNode *p = root;
        for (int i = 0; i < word.size(); ++i) {
            if (p->next[word[i] - 'a'] == NULL) {
                p->next[word[i] - 'a'] = new TrieNode();
            }
            p = p->next[word[i] - 'a'];
        }
        p->isWord = true;
    }

    /** Returns if the word is in the trie. */
    bool search(string word) {
        if (word.empty()) return true;
        TrieNode *p = root;
        for (int i = 0; i < word.size() && p; ++i)
            p = p->next[word[i] - 'a'];
        return p && p->isWord;
    }

    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        if (prefix.empty()) return true;
        TrieNode *p = root;
        for (int i = 0; i < prefix.size() && p; ++i)
            p = p->next[prefix[i] - 'a'];
        return p;
    }
};

bool canPartition(vector<int> &nums) {
    if (nums.empty()) return false;
    int sum = 0;
    for (auto num : nums) sum += num;
    if (sum & 1) return false;
    int target = sum >> 1;
    vector<bool> dp(target, false);
    dp[0] = true;
    for (auto num : nums) {
        for (int i = target; i >= num; i--) {
            dp[i] = dp[i] || dp[i - num];
        }
    }
    return dp[target];
}

vector<int> productExceptSelf2(vector<int> &nums) {
    if (nums.empty()) return {};
    vector<int> res(nums.size(), 1);
    for (int i = 0; i < nums.size(); ++i) {
        int sum = 1;
        for (int j = 0; j < nums.size(); ++j) {
            if (i == j) continue;
            sum *= nums[j];
        }
        res[i] = sum;
    }
    return res;
}

vector<int> productExceptSelf(vector<int> &nums) {
    if (nums.empty()) return {};
    vector<int> lefRes(nums.size(), 1), rightRes(nums.size(), 1), res(nums.size(), 1);
    for (int i = 0; i < nums.size() - 1; ++i)
        lefRes[i + 1] = nums[i] * lefRes[i];
    for (int i = nums.size() - 1; i > 0; --i)
        rightRes[i - 1] = rightRes[i] * nums[i];
    for (int i = 0; i < nums.size(); ++i)
        res[i] = lefRes[i] * rightRes[i];
    return res;
}

vector<int> findDisappearedNumbers(vector<int> &nums) {
    if (nums.empty()) return {};
    vector<int> res;
    for (auto num : nums) {
        int index = abs(num) - 1;
        nums[index] = nums[index] > 0 ? -nums[index] : nums[index];
    }
    for (int i = 0; i < nums.size(); ++i) {
        if (nums[i] > 0)
            res.push_back(i + 1);
    }
    return res;
}

vector<int> searchRange(vector<int> &nums, int target) {
    if (nums.empty() || target > nums.back() || target < nums.front()) return {-1, -1};
    int left = 0, right = nums.size() - 1;
    int mid = 0;
    while (left <= right) {
        mid = left + (right - left) / 2;
        if (target == nums[mid])
            break;
        if (target > nums[mid])
            left = mid + 1;
        else
            right = mid - 1;
    }
    if (left > right) return {-1, -1};
    left = right = mid;
    while (left >= 0 && nums[left] == target)
        --left;
    while (right < nums.size() && nums[right] == target)
        ++right;
    return {left + 1, right - 1};
}

int search2(vector<int> &nums, int target) {
    if (nums.empty()) return -1;
    int left = 0, right = nums.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] == target) return mid;
        if (nums[mid] < nums[right]) {
            if (target > nums[mid] && target <= nums[right])
                left = mid + 1;
            else
                right = mid - 1;
        } else {
            if (target >= nums[left] && target < nums[mid])
                right = mid - 1;
            else
                left = mid + 1;
        }
    }
    return -1;
}

void stringtodata() {
    string s = "2019-03-20";
    int month = stoi(s.substr(5, 2));
    cout << month << endl;
}

bool isInVector(vector<int> &nums, int target) {
    int left = 0, right = nums.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (nums[left] == target || nums[right] == target || nums[mid] == target)
            return true;
        if (nums[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return false;
}

vector<int> intersection2(vector<int> &nums1, vector<int> &nums2) {
    if (nums1.empty() || nums2.empty()) return {};
    sort(nums1.begin(), nums1.end());
    sort(nums2.begin(), nums2.end());
    vector<int> res;
    for (auto num : nums2) {
        if (num > nums1.back() || num < nums1.front())
            continue;
        if (isInVector(nums1, num)) {
            if (res.empty() || num != res.back())
                res.push_back(num);
        }
    }
    return res;
}

vector<int> intersection(vector<int> &nums1, vector<int> &nums2) {
    if (nums1.empty() || nums2.empty()) return {};
    unordered_set<int> s(nums1.begin(), nums1.end()), s2;
    for (auto num : nums2)
        if (s.count(num))
            s2.insert(num);
    vector<int> res(s2.begin(), s2.end());
    return res;
}

int minSubArrayLen(int s, vector<int> &nums) {
    if (nums.empty()) return 0;
    int left = 0, right = 0, sum = 0, minlen = INT_MAX;
    while (right < nums.size()) {
        while (right < nums.size() && sum < s)
            sum += nums[right++];
        while (sum >= s) {
            minlen = min(minlen, right - left);
            sum -= nums[left++];
        }
    }
    return minlen == INT_MAX ? 0 : minlen;
}

//2019-03-20
int dayOfYear(string date) {
    int p_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int r_month[] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int year = stoi(date.substr(0, 4));
    int month = stoi(date.substr(5, 2));
    int day = stoi(date.substr(8, 2));
    //cout<<year<<"-"<<month<<"-"<<day<<endl;
    bool run = false;
    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
        run = true;
    int daycount = 0;
    for (int i = 0; i < month - 1; ++i)
        daycount += !run ? p_month[i] : r_month[i];
    daycount += day;
    return daycount;
}

#define mod 1000000007

int numRollsToTarget(int d, int f, int target) {
    int dp[d + 1][target + 1];
    memset(dp, 0, sizeof(dp));
    for (int i = 1; i <= f && i <= target; i++) dp[1][i] = 1;
    for (int i = 1; i <= d; i++) {
        for (int j = 1; j <= target; j++) {
            for (int k = 1; k <= f && j >= k; k++) {
                dp[i][j] = (dp[i][j] + dp[i - 1][j - k]) % mod;
            }
        }
    }
    return dp[d][target];
}

int findMin(vector<int> &nums) {
    int left = 0, right = nums.size() - 1;
    if (nums.size() == 1) return nums[0];
    while (left <= right) {
        if (nums[left] <= nums[right])
            return nums[left];
        int mid = left + (right - left) / 2;
        if (nums[mid] >= nums[left])
            left = mid + 1;
        else
            right = mid;
    }
    return nums[left];
}

int findPeakElement(vector<int> &nums) {
    if (nums.size() == 1) return 0;
    int before = INT_MIN;
    for (int i = 0; i < nums.size() - 1; ++i) {
        if (nums[i] > before)
            if (nums[i] > nums[i + 1])
                return i;
        before = nums[i];
    }
    if (nums.back() > before) return nums.size() - 1;
    return -1;
}

bool isPerfectSquare(int num) {
    if (num == 1) return true;
    int left = num / 2;
    while ((left * left) > num)
        left = left / 2;
    int right = left * 2;
    for (int i = left + 1; i <= right; ++i)
        if (i * i == num)
            return true;
    return false;
}

char nextGreatestLetter(vector<char> &letters, char target) {
    if (target == 'z') return letters.front();
    sort(letters.begin(), letters.end());
    int left = 0, right = letters.size() - 1;
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (letters[mid] < target)
            left = mid + 1;
        else
            right = mid;
    }
    for (int i = left; i < letters.size(); ++i)
        if (letters[i] > target)
            return letters[i];
    return letters[0];
}

int arrangeCoins(int n) {
    if (n == 1) return 1;
    int left = n / 2;
    int cal = (left * (left + 1)) / 2;
    int right = n;
    while (cal > n) {
        left = left / 2;
        cal = (left * (left + 1)) / 2;
    }
    int i = left;
    for (; i < right; ++i) {
        cal = i * (i + 1) / 2;
        if (cal > n)
            break;
    }
    return i - 1;
}

double myPow(double x, int n) {
    if (x == 0.0) return 0;
    if (n == 0) return 1;
    double res = 0.0;
    for (int i = n; i != 0; i /= 2) {
        if (i % 2 != 0) res *= x;
        x *= x;
    }
    return n < 0 ? 1 / res : res;
}

int hIndex(vector<int> &citations) {
    sort(citations.begin(), citations.end(), greater<int>());
    for (int i = 0; i < citations.size(); ++i) {
        if (citations[i] < i)
            return i - 1;
    }
    return citations.size();
}

bool isHappy(int n) {
    if (n == 1) return true;
    unordered_map<int, int> m;
    int sum = 0;
    while (m[sum] != 2) {
        sum = 0;
        while (n != 0) {
            int count = n % 10;
            n = n / 10;
            sum += count * count;
        }
        if(sum == 1) return true;
        cout<<sum<<endl;
        n = sum;
        ++m[sum];
    }
    return false;
}

int main() {
    vector<int> nums1{1, 2, 1, 3, 5, 6, 4};
    vector<int> nums2{3, 0, 6, 1, 5};
    //vector<int> res = intersection(nums1, nums2);
    cout<<isHappy(19)<<endl;
    return 0;
}














