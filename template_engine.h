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

    std::string lstrip(const std::string &str, const std::string &rm) {
        auto beg = str.find_first_not_of(rm);
        if (beg == std::string::npos) {
            return "";
        } else {
            return str.substr(beg);
        }
    }

    std::string rstrip(const std::string &str, const std::string &rm) {
        auto end = str.find_last_not_of(rm);
        if (end == std::string::npos) {
            return "";
        } else {
            return str.substr(0, end+1);
        }
    }

    std::string strip(const std::string &str, const std::string &rm) {
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
    using Template = std::string;
    using Environment = Json;

    using vstring::split;
    using vstring::rstrip;
    using vstring::lstrip;
    using vstring::strip;
    using vstring::lower;
    using vstring::upper;
    using vstring::end_with;
    using vstring::start_with;

    class Tokenizer {
    public:

    private:

    };

    class Render {
    public:

    private:

    };

    void TemplateRender(std::string html_tpl, Json data) {

    }
};

#endif //VOGRO_TPL_TEMPLATE_ENGINE_H
