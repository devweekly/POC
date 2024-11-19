#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <string>
#include <vector>

using namespace std;

// step1: 开始词hit入列(add to queue)，当前level为1
// step2: hit变化到index为1，找到hot，入列（hot:2)
// step3: hit变化了所有字母的a-z可能性，没有了，到达while loop结尾，hit结束
// step4: hot出列，开始字母循环，hot的level是2
// step5: hot找到dot (when index is 0)，入列（dot:3)
// step6: hot继续变化 (index is still 0)，找到lot，入列(lot:3)，lot和dot是同一级的，都是3
// step7: hot找完了，到达while loop结尾
// step8: dot出列，当前等级3
// step9: dot循环找到dog，入列（dog:4)
// step10：dot找完了，到达while loop结尾
// step11: lot出列，当前等级仍然是3
// step12: lot找到log，入列（log：4）
// step13: lot到达while loop结尾
// step14: dog出列，level是4
// step15: dog变换找到cog这个结束词，完成任务！level是5，函数返回。

int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
    // 将 wordList 转换为哈希集合，方便查找
    unordered_set<string> wordSet(wordList.begin(), wordList.end());
    if (wordSet.find(endWord) == wordSet.end()) {
        return 0; // 如果 endWord 不在 wordList 中，无法转换
    }

    // 队列存储当前单词和转换步数
    queue<pair<string, int>> q;
    q.push({beginWord, 1});

    cout << "---- ladderLength begin, current level is 1 --- " << endl;

    while (!q.empty()) {
        auto [currentWord, level] = q.front();
        q.pop();

        cout << "-------- whileloop begin, level: " << level << ", queue front: " << currentWord << endl;

        // 遍历当前单词的每一个字符
        for (int i = 0, loopSize = currentWord.size(); i < loopSize; ++i) {

            cout << "---------- currentWord forloop begin: index " << i << ", currentWord is " << currentWord << endl;
            string tempWord = currentWord;

            // 尝试将第 i 个字符替换成 'a' 到 'z'
            for (char c = 'a'; c <= 'z'; ++c) {
                tempWord[i] = c;

                // 如果新单词等于 endWord，返回步数
                if (tempWord == endWord) {
                    cout << "---------------- find endWord!!! level is " << level + 1 << ", tempWord: " << tempWord << ", currentWord: " << currentWord << endl;
                    return level + 1;
                }

                // 如果新单词在 wordSet 中，加入队列并从集合中移除
                if (wordSet.find(tempWord) != wordSet.end()) {
                    cout << "-------------- find tempWord in dictionary: level is " << level + 1 << ", tempWord: " << tempWord  << ", currentWord: " << currentWord << endl;

                    // 注意事项：下面的level+1不能是level++，因为我们在当前for循环会继续寻找单词，押入队列，这些单词是同一个level的，比如hot变化到[dot, lot]，dot和lot都是level3
                    q.push({tempWord, level + 1});
                    // 避免重复访问
                    wordSet.erase(tempWord); 
                }
            }
        }

        cout << "---------- currentWord forloop finished: " <<  "currentWord: " << currentWord << ", can NOT find more, will switch back to queue front ---------- " << endl;
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
