#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "tpl.hpp"

int main (void){
    Template tpl("hello,wolrd!");

    tpl.setString("key","value");

    std::vector<std::string> v {"Item1","Item2","Item3"};
    tpl.setStringList("vec1",v);

    std::vector<std::map<std::string,std::string>> vm {{{"id","25"},{"name","andrew"}},{{"id","23"},{"name","Bob"}}};

    tpl.setMapList("maplist",vm);

    tpl.printData();


    return 0;
}