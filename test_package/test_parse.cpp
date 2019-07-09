/*
 * Tests for tinyxml2 Conan package
 * Parse XML
 * Dmitriy Vetutnev, Odant 2019
*/


#include <tinyxml2.h>

#include <string>
#include <fstream>
#include <iostream>
#include <cassert>


int main(int, char**) {
    const std::string content = ""
"<?xml version='1.0' encoding='utf-8'?>"
"<Root>"
"    <NodeA attr=\"42\"/>"
"    <NodeB property=\"kIkos\"/>"
"</Root>"
;
    tinyxml2::XMLError err;
    tinyxml2::XMLDocument doc;
    err = doc.Parse(content.data(), content.length());
    if (err != tinyxml2::XML_SUCCESS) {
        std::cout << "Failed parse content. err: " << tinyxml2::XMLDocument::ErrorIDToName(err);
    }

    const tinyxml2::XMLElement* root = doc.RootElement();
    assert(root != nullptr);
    std::cout << "root name: " << root->Name() << std::endl;

    const tinyxml2::XMLElement* nodeA = root->FirstChildElement();
    assert(nodeA != nullptr);
    std::cout << "First node name: " << nodeA->Name() << std::endl;
    const char* attr = nullptr;
    err = nodeA->QueryStringAttribute("attr", &attr);
    assert(err == tinyxml2::XML_SUCCESS);
    assert(attr != nullptr);
    std::cout << "attr: " << attr << std::endl;

    const tinyxml2::XMLElement* nodeB = nodeA->NextSiblingElement();
    assert(nodeB != nullptr);
    std::cout << "Second node name: " << nodeB->Name() << std::endl;
    const char* property = nullptr;
    err = nodeB->QueryStringAttribute("property", &property);
    assert(err == tinyxml2::XML_SUCCESS);
    assert(property != nullptr);
    std::cout << "property: " << property << std::endl;

    return EXIT_SUCCESS;
}
