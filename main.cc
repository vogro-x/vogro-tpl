//
// Created by xvvx on 18-9-12.
//
#include <iostream>

#include "template_engine.h"

using  namespace std;

int main() {
    std::string html("<!DOCTYPE html>\n"
                             "<html>\n"
                             "<head>\n"
                             "    <meta charset='utf-8'>\n"
                             "    <title>{{ obj.title }}</title>\n"
                             "</head>\n"
                             "<body>\n"
                             "    {# Hello world #}\n"
                             "    <div class=\"content\">\n"
                             "        <p> {{ obj.content }} </p>\n"
                             "        \n"
                             "        <table>\n"
                             "            {% for value in obj.list %}\n"
                             "                <td> {{ value }} </td>\n"
                             "            {% endfor %}\n"
                             "        </table>\n"
                             "        \n"
                             "        {% if obj.show %}\n"
                             "            <p> {{ obj.foot }} </p>\n"
                             "        {% endif %}        \n"
                             "    </div>\n"
                             "</body>\n"
                             "</html>");

//    {
//        "obj" : {
//            "title" : "这是标题",
//                    "content" : "这是内容",
//                    "foot": "这是页脚",
//                    "list":["td1","td2","td3","td5"],
//            "show":"True"}
//    };

    vtpl::Environment data;
    data["obj"]["title"] = "这是标题";
    data["obj"]["content"] = "这是内容";
    data["obj"]["foot"] = "这是页脚";
    data["obj"]["list"] = {"td1", "td2", "td3", "td4", "td5"};
    data["obj"]["show"] = true;

//    for (auto c : vtpl::ParseToTokens(html)) {
//        cout << c << "," << endl;
//    }
//
    for (auto x : data.Get("obj.list")) {
        cout << x << endl;
    }


    cout << vtpl::TemplateRender(html, data);
}
