/*
 * Tests for tinyxml2 Conan package
 * create XML
 * Dmitriy Vetutnev, Odant 2019
*/


#include <tinyxml2.h>

#include <string>
#include <iostream>
#include <cassert>


int main(int, char**) {
    // Declaration
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLDeclaration* declaration = doc.NewDeclaration();
    assert(doc.InsertFirstChild(declaration) != nullptr);

    // Root
    tinyxml2::XMLElement* root = doc.NewElement("Packages");
    assert(doc.InsertEndChild(root) != nullptr);

    // Package odaServer
    tinyxml2::XMLElement* packageServer = doc.NewElement("Package");
    assert(root->InsertEndChild(packageServer));
    packageServer->SetAttribute("name", "odaServer");
    packageServer->SetAttribute("version", "2.7.13.96");
    packageServer->SetAttribute("type", "Application");

    tinyxml2::XMLElement* systemInfoServer = doc.NewElement("SystemInfo");
    assert(packageServer->InsertEndChild(systemInfoServer));
    systemInfoServer->SetAttribute("os", "Linux");
    systemInfoServer->SetAttribute("arch", "x86_64");
    systemInfoServer->SetAttribute("compiler", "gcc_6");

    tinyxml2::XMLElement* entryPoint = doc.NewElement("EntryPoint");
    assert(packageServer->InsertEndChild(entryPoint));
    entryPoint->SetAttribute("value", "{PACKAGE_FOLDER}/odaServer");

    tinyxml2::XMLElement* requiredOpenssl = doc.NewElement("Required");
    assert(packageServer->InsertEndChild(requiredOpenssl));
    requiredOpenssl->SetAttribute("name", "OpenSSL");
    requiredOpenssl->SetAttribute("version", "1.1.1b");
    requiredOpenssl->SetAttribute("versionStricly", true);

    // Package OpenSSL
    tinyxml2::XMLElement* packageOpenssl = doc.NewElement("Package");
    assert(root->InsertEndChild(packageOpenssl));
    packageOpenssl->SetAttribute("name", "OpenSSL");
    packageOpenssl->SetAttribute("version", "1.1.1b");
    packageOpenssl->SetAttribute("type", "Internal");

    tinyxml2::XMLElement* systemInfoOpenssl = doc.NewElement("SystemInfo");
    assert(packageOpenssl->InsertEndChild(systemInfoOpenssl));
    systemInfoOpenssl->SetAttribute("os", "Linux");
    systemInfoOpenssl->SetAttribute("arch", "x86_64");
    systemInfoOpenssl->SetAttribute("compiler", "gcc_6");

    // Package odaWeb
    tinyxml2::XMLElement* packageWeb = doc.NewElement("Package");
    assert(root->InsertEndChild(packageWeb));
    packageWeb->SetAttribute("name", "odaWeb");
    packageWeb->SetAttribute("version", "2.9.11.55");
    packageWeb->SetAttribute("type", "Plugin");

    tinyxml2::XMLElement* installTo = doc.NewElement("InstallTo");
    assert(packageWeb->InsertEndChild(installTo));
    installTo->SetAttribute("name", "odaServer");
    installTo->SetAttribute("version", "2.1.0.0");

    tinyxml2::XMLElement* cmdArgument = doc.NewElement("CmdArgument");
    assert(packageWeb->InsertEndChild(cmdArgument));
    cmdArgument->SetAttribute("name", "--web");
    cmdArgument->SetAttribute("value", "{PACKAGE_FOLDER}");

    // Get result as text
    tinyxml2::XMLPrinter printer;
    doc.Print(&printer);
    std::cout << printer.CStr();

    return EXIT_SUCCESS;
}