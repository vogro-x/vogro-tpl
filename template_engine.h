//
// Created by xvvx on 18-9-2.
//

#ifndef VOGRO_TPL_TEMPLATE_ENGINE_H

#define VOGRO_TPL_TEMPLATE_ENGINE_H

#include <string.h>

#include <algorithm>
#include <string>
#include <vector>
#include <iostream>

#include "nlohmann/json.hpp"

namespace vstring {

    std::vector<std::string> split(const std::string &str, const std::string &delim) {
        std::vector<std::string> result;
        std::string::size_type pos1, pos2;

        pos1 = 0;
        pos2 = str.find(delim);

        while(std::string::npos != pos2) {
            result.push_back(str.substr(pos1, pos2-pos1));

            pos1 = pos2 + delim.size();
            pos2 = str.find(delim, pos1);
        }
        if(pos1 != str.length())
            result.push_back(str.substr(pos1));
        return result;
    }

    std::vector<std::string> split(const std::string &str) {
        return split(str, " ");
    }

    std::string join(const std::vector<std::string> &strs, const std::string &seq) {
        std::string result;
        for (size_t i = 0; i < strs.size()-1; ++i) {
            result += (strs[i] + seq);
        }
        result += strs.back();
        return result;
    }

    std::string lstrip(const std::string &str, const std::string &rm = "\r\t ") {
        auto beg = str.find_first_not_of(rm);
        if (beg == std::string::npos) {
            return "";
        } else {
            return str.substr(beg);
        }
    }

    std::string rstrip(const std::string &str, const std::string &rm = "\r\t ") {
        auto end = str.find_last_not_of(rm);
        if (end == std::string::npos) {
            return "";
        } else {
            return str.substr(0, end+1);
        }
    }

    std::string strip(const std::string &str, const std::string &rm = "\n\t ") {
        return rstrip(lstrip(str, rm), rm);
    }

    bool start_with(const std::string &str, const std::string &prefix) {
        return str.size() >= prefix.size() && str.substr(0, prefix.size()) == prefix;
    }

    bool end_with(const std::string &str, const std::string &suffix) {
        return str.size() >= suffix.size() && str.substr(str.size() - suffix.size(), suffix.size()) == suffix;
    }

    std::string upper(const std::string &str) {
        std::string result;
        for (auto c : str) {
            result += toupper(c);
        }
        return result;
    }

    std::string lower(const std::string &str) {
        std::string result;
        for (auto c : str) {
            result += tolower(c);
        }
        return result;
    }
};

namespace vtpl {

    using Json = nlohmann::json;

    using std::string;
    using std::vector;
    using std::unordered_map;

    using vstring::split;
    using vstring::rstrip;
    using vstring::lstrip;
    using vstring::strip;
    using vstring::lower;
    using vstring::upper;
    using vstring::end_with;
    using vstring::start_with;
    using vstring::join;

    vector<string> ParseToLines(string html_tpl) {
        std::vector<std::string> result;
        size_t n = html_tpl.size(),  last_begin = 0;
        unordered_map<string, string> open_close_m = { {"{{", "}}"},  {"{%", "%}"}, {"{#", "#}"} };

        for (size_t i = 0; i < n; ++i) {
            auto open = html_tpl.substr(i, 2);
            if (open == "{{" || open == "{%" || open == "{#") {
                auto token = strip(html_tpl.substr(last_begin, i - last_begin));
                if (!token.empty()) {
                    result.push_back(token);
                }
                string close_str = open_close_m[open];
                auto end = html_tpl.find(close_str, i);
                if (end == std::string::npos) {
//                    throw std::exception();
                    return result;
                } else {
                    result.push_back(html_tpl.substr(i, end - i + 2));
                    i = end + 1;
                    last_begin = i + 1;
                }
            }
        }
        result.push_back(html_tpl.substr(last_begin + 1, n - last_begin));
        return result;
    }


    class Environment: public Json {
    private:
        template <typename T>
        auto GetData(const T &data, size_t index, const vector<string> &keys) {
            if (keys.size() - 1 == index) {
                return data[keys[index]];
            } else {
                return GetData(data[keys[index]], index+1, keys);
            }
        }

    public:

        auto Get(const string &key) {
            auto keys = split(key, ".");
            return GetData((*this), 0, keys);
        }
    };

    class Template {
    public:
        Template(const string &html_tpl):
                html_tpl_(html_tpl) {

        }

        string render(Environment &data) {
            std::vector<std::string> stk;
            std::vector<std::string> result;
            auto lines = ParseToLines(html_tpl_);
            auto is_if = false, is_for = false;
            int times = 0, match_times = 0;

            for (auto item : lines) {
                auto prefix = item.substr(0, 2);

                if (prefix != "{{" && prefix != "{%") {
                    if (!is_for && !is_if) {
                        result.push_back(item);
                    } else {
                        stk.push_back(item);
                    }
                } else if (prefix == "{{") {
                    if (not is_for and not is_if) {
                        auto key = strip(item.substr(2, item.size()-4));
                        result.push_back(data.Get(key));
//                        result.push_back("{{" + key + "}}");
                    } else {
                        stk.push_back(item);
                    }
                } else if (prefix == "{%") {
                    auto tokens = split(strip(item.substr(2, item.size()-4)));

                    if (tokens.front() == "if") {
//                        stk.push_back(item);
                        if (!is_for) {
                            is_if = true;
                            ++times;
                        }
                    } else if (tokens.front() == "for") {
//                        stk.push_back(item);
                        result.push_back("fuck it\n\n");

                        if (!is_if) {
                            is_for = true;
                            ++times;
                        }
                    }

                    if (tokens.front() == "endif") {
//                        stk.push_back(item);
                        if (!is_for) {
                            ++match_times;
                        }
                        if (match_times == times) {
//                            result.push_back(IfBlock(stk, context));
//                            stk.clear();
                            is_if = false, is_for = false;
                            times = 0, match_times = 0;
                        }

                    } else if (tokens.front() == "endfor") {
//                        stk.push_back(item);
                        if (!is_if) {
                            ++match_times;
                        }
                        if (match_times == times) {
//                            result.push_back(ForBlock(stk, context));
//                            stk.clear();
                            is_if = false, is_for = false;
                            times = 0, match_times = 0;
                        }
                    }
                } else {

                }
            }
            return join(result, "\n");
        }

    private:
        string html_tpl_;
    };

    string TemplateRender(string html_tpl, Environment data) {
        Template tpl = Template(html_tpl);
        return tpl.render(data);
    }
};

#endif //VOGRO_TPL_TEMPLATE_ENGINE_H
