#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <regex>
#include "tpl.hpp"

int main (void) {
    Template tpl("hello,wolrd!");

    tpl.setString("key","value");
    tpl.setString("user_name", "xvvx");

    std::vector<std::string> v {"Item1","Item2","Item3"};
    tpl.setStringList("vec1",v);

    std::vector<std::map<std::string,std::string>> vm {{{"id","25"},{"name","andrew"}},{{"id","23"},{"name","Bob"}}};

    tpl.setMapList("maplist",vm);

    std::string html("<p>Welcome, {{ user_name }}!</p>\n"
                             "\n"
                             "{% if show_yes %}\n"
                             "    Your name: {{ user_name }}\n"
                             "{% endif %}\n"
                             " {% if show_no %}\n"
                             "    Your name: {{ user_name }}\n"
                             "{% endif %}\n"
                             "\n"
                             "<p>Fruits:</p>\n"
                             "<ul>\n"

                             "{% for product in test_list %}\n"
                             "    <li>{{ product }}</li>\n"
                             "{% endfor %}\n"
                             "</ul>\n");
    Template test(html);
    test.setString("user_name", "xvvx");
    test.setString("show_yes", "true");
    test.setString("show_no", "false");

    std::vector<std::string> test_vec {"test1", "test2", "test3"};
    test.setStringList("test_list", test_vec);

    std::cout << test.fillTemplate(html) << std::endl;

    return 0;
}