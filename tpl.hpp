#ifndef __TPL_HPP__
#define __TPL_HPP__

#include <iostream>
#include <string>
#include <map>

class Template {
    private:
    std::string sourceString;
    std::map<std::string,std::string> dataMap; //{{  name }}
    std::map<std::string,std::vector<std::string> > listMap; //{% for i in data %} {{ i }} {{% endfor %}}
    std::map<std::string,std::vector<std::map<std::string,std::string> > >maplistMap; //{% for i in data %} {{ i.item1 }} {{% endfor %}}

    public:
    Template(std::string src):sourceString(src){};
    void setString(std::string key,std::string val){
        this->dataMap[key]=val;
    }
    void setStringList(std::string key,std::vector<std::string>& strList){
        this->listMap[key]=strList;
    }

    void setMapList(std::string key,std::vector<std::map<std::string,std::string> >& mapList){
        this->maplistMap[key]=mapList;
    }

    void printData(){
        for(auto it=dataMap.begin();it!=dataMap.end();it++){
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
};


#endif
