#ifndef ACTIONMANAGER_H
#define ACTIONMANAGER_H

#include "../mystl/my_stack.h"
#include <string>

enum class EditActiontype {
    Initialize,
    Insert,
    Delete,
};

struct EditAction {
    EditActiontype type;
    int pos;
    std::string content;
};

class ActionManager {
private:
    MyStack<MyVector<EditAction>> undoStack_, redoStack_;
    std::string content_;

    MyVector<EditAction> calculateEditActions(const std::string &str1, const std::string &str2) { // 规定Editor只会在删除或者插入时提交，因此只会同时存在一种操作
        int m = str1.length();
        int n = str2.length();
        MyVector<MyVector<int>> dp(m + 1, MyVector<int>(n + 1));

        for (int i = 0; i <= m; ++i) {
            dp[i][0] = i;
        }
        for (int j = 0; j <= n; ++j) {
            dp[0][j] = j;
        }

        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (str1[i - 1] == str2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    dp[i][j] = std::min(dp[i - 1][j], dp[i][j - 1]) + 1;
                }
            }
        }

        // 回溯以找到编辑操作
        MyVector<EditAction> actions;
        int i = m, j = n;
        while (i > 0 && j > 0) {
            if (str1[i - 1] == str2[j - 1]) {
                --i;
                --j;
            } else if (dp[i][j] == dp[i - 1][j] + 1) {
                actions.push_back({EditActiontype::Delete, i - 1, std::string(1, str1[i - 1])});
                --i;
            } else if (dp[i][j] == dp[i][j - 1] + 1) {
                actions.push_back({EditActiontype::Insert, i, std::string(1, str2[j - 1])});
                --j;
            }
        }

        while (i > 0) {
            actions.push_back({EditActiontype::Delete, i - 1, std::string(1, str1[i - 1])});
            --i;
        }

        while (j > 0) {
            actions.push_back({EditActiontype::Insert, i, std::string(1, str2[j - 1])});
            --j;
        }

        actions.reverse();

        // 考虑到先前进行的插入和删除操作，对随后插入和删除的位置进行修正
        int offset = 0;
        for (int i = 0; i < actions.size(); ++i) {
            if (actions[i].type == EditActiontype::Insert) {
                actions[i].pos += offset;
                offset++;
            } else if (actions[i].type == EditActiontype::Delete) {
                actions[i].pos += offset;
                offset--;
            }
        }

        return actions;
    }

    std::string applyEditAction(MyVector<EditAction> &actions, std::string &content) {
        std::string newContent = content;
        for(int i = 0; i < actions.size(); i++) {
            if(actions[i].type == EditActiontype::Insert) {
                newContent.insert(actions[i].pos, actions[i].content);
            } else if(actions[i].type == EditActiontype::Delete) {
                newContent.erase(actions[i].pos, actions[i].content.size());
            }
        }
        return newContent;
    }

public:
    ActionManager() {
    }
    ActionManager(const std::string &content) {
        content_ = content;
    }

    void updateContent(const std::string &content) {
        redoStack_.clear();
        MyVector<EditAction> actions = calculateEditActions(content_, content);
        content_ = content;
        undoStack_.push(actions);
    }

    void undo() {
        if (undoStack_.empty()) {
            return;
        }
        MyVector<EditAction> actions = undoStack_.top();
        undoStack_.pop();
        std::string newContent = applyEditAction(actions, content_);
        redoStack_.push(calculateEditActions(content_, newContent));
        content_ = newContent;
    }

    void redo() {
        if (redoStack_.empty()) {
            return;
        }
        MyVector<EditAction> actions = redoStack_.top();
        redoStack_.pop();
        std::string newContent = applyEditAction(actions, content_);
        undoStack_.push(calculateEditActions(content_, newContent));
        content_ = newContent;
    }

    void setContent(const std::string &content) {
        content_ = content;
        undoStack_.clear();
        redoStack_.clear();
    }

    std::string getContent() {
        return content_;
    }
};

#endif