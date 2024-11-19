// #include <unordered_set>
// #include <vector>
// #include <iostream>
// #include <queue>

// using namespace std;

// class Solution {
// public:
//     int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
//         unordered_set<string> words(wordList.begin(), wordList.end());
//         queue<string> q{{beginWord}};
//         int ans = 1;
//         while (!q.empty()) {
//             ++ans;
//             for (int i = q.size(); i > 0; --i) {
//                 string s = q.front();
//                 q.pop();
//                 for (int j = 0; j < s.size(); ++j) {
//                     char ch = s[j];
//                     for (char k = 'a'; k <= 'z'; ++k) {
//                         s[j] = k;
//                         if (!words.count(s)) continue;
//                         if (s == endWord) return ans;
//                         q.push(s);
//                         words.erase(s);
//                     }
//                     s[j] = ch;
//                 }
//             }
//         }
//         return 0;
//     }
// };

// int main() {
//     Solution s {};
//     std::vector<std::string> vec = {"hot","dot","dog","lot","log","cog"};
//     auto len = s.ladderLength("hit", "cog", vec);
//     std::cout << "The shortest transformation sequence length is: " << len << std::endl;
//     return 0;
// }


#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <string>
#include <vector>

using namespace std;

int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
    // 将 wordList 转换为哈希集合，方便查找
    unordered_set<string> wordSet(wordList.begin(), wordList.end());
    if (wordSet.find(endWord) == wordSet.end()) {
        return 0; // 如果 endWord 不在 wordList 中，无法转换
    }

    // 队列存储当前单词和转换步数
    queue<pair<string, int>> q;
    q.push({beginWord, 1});

    while (!q.empty()) {
        auto [currentWord, level] = q.front();
        q.pop();

        // 遍历当前单词的每一个字符
        for (int i = 0; i < currentWord.size(); ++i) {
            string tempWord = currentWord;

            // 尝试将第 i 个字符替换成 'a' 到 'z'
            for (char c = 'a'; c <= 'z'; ++c) {
                tempWord[i] = c;

                // 如果新单词等于 endWord，返回步数
                if (tempWord == endWord) {
                    return level + 1;
                }

                // 如果新单词在 wordSet 中，加入队列并从集合中移除
                if (wordSet.find(tempWord) != wordSet.end()) {
                    q.push({tempWord, level + 1});
                    // 避免重复访问
                    wordSet.erase(tempWord); 
                }
            }
        }
    }

    return 0; // 如果无法转换，返回 0
}

int main() {
    string beginWord = "hit";
    string endWord = "cog";
    vector<string> wordList = {"hot", "dot", "dog", "lot", "log", "cog"};

    int result = ladderLength(beginWord, endWord, wordList);
    cout << "The shortest transformation sequence length is: " << result << endl;

    return 0;
}
