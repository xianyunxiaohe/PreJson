#include <iostream>
#include "x2struct/x2struct.hpp" // 包含这个头文件

using namespace std;

struct User {
    int64_t id;
    string  name;
    string  mail;
    User(int64_t i=0, const string& n="", const string& m=""):id(i),name(n),mail(m){}
    XTOSTRUCT(O(id, name, mail)); // 添加宏定义XTOSTRUCT在结构体定义结尾
};

struct Group {
    string  name;
    int64_t master;
    vector<User> members;
    XTOSTRUCT(O(name, master, members)); // 添加宏定义XTOSTRUCT在结构体定义结尾
};

int main(int argc, char *argv[]) {
    Group g;
    g.name = "C++";
    g.master = 2019;
    g.members.resize(2);
    g.members[0] = User(1, "Jack", "jack@x2struct.com");
    g.members[1] = User(2, "Pony", "pony@x2struct.com");

    string json = x2struct::X::tojson(g);  // 结构体转json
    cout<<"JSON:"<<json<<":JSONEND"<<endl;

    Group n;
    x2struct::X::loadjson(json, n, false); // json转结构体
    cout<<n.name<<endl;

    vector<int> vi;
    x2struct::X::loadjson("[1,2,3]", vi, false); // 直接加载vector
    cout<<vi.size()<<','<<vi[1]<<endl;

    map<int, int> m;
    x2struct::X::loadjson("{\"1\":10, \"2\":20}", m, false); // 直接加载map
    cout<<m.size()<<','<<m[2]<<endl;

    return 0;
}
