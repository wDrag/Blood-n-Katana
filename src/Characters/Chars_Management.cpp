#include "Characters/Chars_Management.h"

CM* CM::s_Instance = nullptr;

void CM::StatsParser(std::string source, std::string value){
    TiXmlDocument xml;
    xml.LoadFile(source);
    if (xml.Error()){
        std::cerr << "Failed to load: " << source << '\n';
    }
    TiXmlElement* root = xml.RootElement();
     for(TiXmlElement * e = root -> FirstChildElement(); e!= nullptr; e = e -> NextSiblingElement()){
        if (e -> Value() != value) continue;
        Stats c;
        for (TiXmlElement * e1 = e -> FirstChildElement(); e1 != nullptr; e1 = e1 -> NextSiblingElement()){
            if (e1 -> Value() == "Stats"){
                c.HP = std::stoi(e1 -> Attribute("HP"));
                c.ATK = std::stoi(e1 -> Attribute("ATK"));
            }
            if (e1 -> Value() == "Attack_1"){
                c.mod1 = std::stoi(e1 -> Attribute("mod"));
            }
            if (e1 -> Value() == "Attack_2"){
                c.mod2 = std::stoi(e1 -> Attribute("mod"));
            }
            if (e1 -> Value() == "Attack_2"){
                c.mod2 = std::stoi(e1 -> Attribute("mod"));
            }
        }
        m_CharMap[value] = c;
    }
}

void CM::StatsClean(){
    m_CharMap.clear();
}