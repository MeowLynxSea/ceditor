#include <stdio.h>
#include "ActionManager.h"
#include "../mystl/my_vector.h"

using namespace std;

int main() {
    ActionManager am;
    MyVector<EditAction> v;
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
    return 0;
}