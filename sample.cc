//
// Created by xvvx on 18-9-12.
//
#include <iostream>
#include <fstream>
#include <sstream>

#include "template_engine.h"

using  namespace std;

string ReadFile(const string &filename) {

}

int main() {
    ifstream t("test.txt");
    string html((std::istreambuf_iterator<char>(t)),
                    std::istreambuf_iterator<char>());
    ifstream in("data.json");
    vtpl::Environment environment;
    in >> environment;
    cout << vtpl::TemplateRender(html, environment);
}
