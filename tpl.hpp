#ifndef __TPL_HPP__
#define __TPL_HPP__

#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>
#include <iterator>


class Template {
    private:
    std::string sourceString;
    std::map<std::string,std::string> dataMap; //{{  name }}
    std::map<std::string,std::vector<std::string> > listMap; //{% for i in data %} {{ i }} {{% endfor %}}
    std::map<std::string,std::vector<std::map<std::string,std::string> > >maplistMap; //{% for i in data %} {{ i.item1 }} {{% endfor %}}

    public:

    Template(std::string src): sourceString(src) {

    }

    void setString(std::string key, std::string val) {
        this->dataMap[key]=val;
    }
    void setStringList(std::string key, std::vector<std::string>& strList) {
        this->listMap[key]=strList;
    }

    void setMapList(std::string key, std::vector<std::map<std::string,std::string> >& mapList) {
        this->maplistMap[key]=mapList;
    }

    std::string getString(const std::string &key) {
        return this->dataMap[key];
    }

    std::vector<std::string> getListMap(const std::string &key) {
        return this->listMap[key];
    };

    std::vector<std::map<std::string, std::string>> getMapListMap(const std::string &key) {
        return this->maplistMap[key];
    };

    std::string fillTemplate(const std::string &html_template) {
        auto tokens = getTokens(html_template);
        return render(tokens, dataMap);
    }

    std::string render(std::vector<std::string> tokens, std::map<std::string, std::string> context) {
        std::vector<std::string> stk;
        std::vector<std::string> result;
        auto is_if = false, is_for = false;
        int times = 0, match_times = 0;

        for (auto item : tokens) {
            auto prefix = item.substr(0, 2);

            if (prefix != "{{" && prefix != "{%") {
                if (!is_for && !is_if) {
                    result.push_back(item);
                } else {
                    stk.push_back(item);
                }
            } else if (prefix == "{{") {
                if (!is_for && !is_if) {
                    result.push_back(context[getLabel(item)]);
                } else {
                    stk.push_back(item);
                }
            } else if (prefix == "{%") {
                auto expression = item.substr(2, item.size()-4);
                std::istringstream iss(expression);
                std::vector<std::string> tokens {std::istream_iterator<std::string>{iss},
                                                 std::istream_iterator<std::string>{}};
                if (tokens.front() == "if") {
                    stk.push_back(item);
                    if (!is_for) {
                        is_if = true;
                        ++times;
                    }
                } else if (tokens.front() == "for") {
                    stk.push_back(item);
                    if (!is_if) {
                        is_for = true;
                        ++times;
                    }
                }

                if (tokens.front() == "endif") {
                    stk.push_back(item);
                    if (!is_for) {
                        ++match_times;
                    }
                    if (match_times == times) {
                        result.push_back(IfBlock(stk, context));
                        stk.clear();
                        is_if = false, is_for = false;
                        times = 0, match_times = 0;
                    }

                } else if (tokens.front() == "endfor") {
                    stk.push_back(item);
                    if (!is_if) {
                        ++match_times;
                    }
                    if (match_times == times) {
                        result.push_back(ForBlock(stk, context));
                        stk.clear();
                        is_if = false, is_for = false;
                        times = 0, match_times = 0;
                    }
                }
            } else {

            }
        }

        std::string result_str;
        for (auto str : result) {
            result_str += str;
        }
        return result_str;
    }

    bool IfEngine(const std::string &cond_str) {
        if (getString(cond_str) == "true") {
            return true;
        } else {
            return false;
        }
    }

    std::string IfBlock(std::vector<std::string> stk, std::map<std::string, std::string> context) {
        std::istringstream iss(stk.front());
        std::vector<std::string> if_lst {std::istream_iterator<std::string>{iss},
                                                 std::istream_iterator<std::string>{}};
        auto cond = IfEngine(if_lst[2]);
        if (!cond) {
            return std::string();
        } else {
            stk.erase(stk.begin());
            return render(stk, context);
        }
    }

    std::string ForBlock(std::vector<std::string> stk, std::map<std::string, std::string> context) {
        auto for_engine = getLabel(stk.front());
        std::istringstream iss(for_engine);
        std::vector<std::string> for_engine_lst {std::istream_iterator<std::string>{iss},
                                         std::istream_iterator<std::string>{}};

        if (for_engine_lst.size() != 4 || for_engine_lst[0] != "for" || for_engine_lst[2] != "in") {
            throw std::exception();
        }

        auto iter_name = for_engine_lst[1];
        auto for_obj = getListMap(for_engine_lst.back());
        std::string result;

        stk.erase(stk.begin());
        stk.pop_back();
        for (auto x : for_obj) {
            context[iter_name] = x;
            result += render(stk, context);
        }
        return result;
    }

    std::string getLabel(std::string &str) {
        str = str.substr(2, str.size() - 4);
        auto begin = str.find_first_not_of(' ');
        auto end = str.find_last_not_of(' ');
        if (begin == std::string::npos || end == std::string::npos) {
            return "";
        }
        return str.substr(begin, end - begin + 1);
    }

    void printData() {
        for(auto it = dataMap.begin(); it != dataMap.end(); it++) {
            std::cout<<it->first<<":"<<it->second<<std::endl;
        }

        for(auto it=listMap.begin();it!=listMap.end();it++){
            std::cout<<it->first<<":"<<std::endl;
            for(auto nit=it->second.begin();nit!=it->second.end();nit++){
                std::cout<<*nit<<std::endl;
            }
        }

        for(auto it=maplistMap.begin();it!=maplistMap.end();it++){
            std::cout<<it->first<<":"<<std::endl;
             for(auto nit=it->second.begin();nit!=it->second.end();nit++){
                 for(auto mit=nit->begin();mit!=nit->end();mit++){
                        std::cout<<mit->first<<":"<<mit->second<<std::endl;
                 }
            }
        }
    }

    std::vector<std::string> getTokens(const std::string &html) {
        std::vector<std::string> result;
        auto n = html.size();
        auto last_begin = 0;

        for (int i = 0; i < n; ++i) {
            auto open = html.substr(i, 2);
            if (open == "{{" || open == "{%") {
                result.push_back(html.substr(last_begin, i - last_begin));

                std::string close_str = (open == "{{") ? "}}" : "%}";
                auto end = html.find(close_str, i);
                if (end == std::string::npos) {
//                    throw std::exception();
                    return result;
                } else {
                    result.push_back(html.substr(i, end - i + 2));
                    i = end + 1;
                    last_begin = i + 1;
                }
            }
        }
        result.push_back(html.substr(last_begin + 1, n - last_begin));
        return result;
    }
};


#endif
