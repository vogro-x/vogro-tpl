//
// Created by xvvx on 18-9-12.
//
#include <iostream>
#include <fstream>
#include <sstream>

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
                             "        {% if obj.show1 %}\n"
                             "            <p> {{ obj.foot1 }} </p>\n"
                             "              {% if obj.show2 %}\n"
                             "                  <p> {{ obj.foot2 }} </p>\n"
                             "              {% endif %}"
                             "        {% endif %}        \n"

                             "    </div>\n"
                             "</body>\n"
                             "</html>");


//    vtpl::Environment data;
//    data["obj"]["title"] = "这是标题";
//    data["obj"]["content"] = "这是内容";
//    data["obj"]["foot1"] = "这是页脚1";
//    data["obj"]["foot2"] = "这是页脚2";
//    data["obj"]["list"] = {"td1", "td2", "td3", "td4", "td5"};
//    data["obj"]["show1"] = true;
//    data["obj"]["show2"] = false;
//

    ifstream in("data.json");
    vtpl::Environment environment;
    in >> environment;
    cout << vtpl::TemplateRender(html, environment);
}
