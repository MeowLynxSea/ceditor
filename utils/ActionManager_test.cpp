#include <stdio.h>
#include "ActionManager.h"
#include "../mystl/my_vector.h"

using namespace std;

int main() {
    ActionManager am;

    std::string s_ = "hello,world!";
    am.setOriginContent(s_);
    s_ = s_.substr(0, 5);
    printf("%s\n", s_.c_str());
    printf("%s\n", am.getContent().c_str());
    am.updateContent(s_);
    printf("%s\n", am.getContent().c_str());
    am.undo();
    printf("%s\n", am.getContent().c_str());

    MyVector<EditAction> v;
    std::string s0 = "i can see you, but u dont love me";
    v = am.calculateEditActions("i can see you, but u dont love me", "i cant hug u, but i love you");
    printf("Actions: %zu\n", v.size());
    //replay test
    std::string s1 = "i can see you, but u dont love me";
    for(int i = 0; i < v.size(); i++) {
        if(v[i].type == EditActiontype::Insert) {
            s1.insert(v[i].pos, v[i].content);
        } else if(v[i].type == EditActiontype::Delete) {
            s1.erase(v[i].pos, v[i].content.size());
        }
    }
    printf("%s\n", s1.c_str());

    am.setOriginContent(s0);

    am.updateContent("i can not see you, but u dont love me");
    am.updateContent("i can not see you, but u love me");
    am.updateContent("i can not see you, but u love me too");

    printf("%s\n", am.getContent().c_str());

    am.undo();

    printf("%s\n", am.getContent().c_str());

    am.undo();

    printf("%s\n", am.getContent().c_str());

    am.redo();

    printf("%s\n", am.getContent().c_str());

    am.updateContent("i can not see you, but u still love me");

    printf("%s\n", am.getContent().c_str());
    return 0;
}