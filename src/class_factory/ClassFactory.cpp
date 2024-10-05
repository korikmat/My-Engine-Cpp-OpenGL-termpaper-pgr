//
// Created by korikmat on 17.05.2024.
//

#include <iostream>
#include "ClassFactory.h"

ClassFactory &ClassFactory::instance() {
    static ClassFactory instance;
    return instance;
}

void ClassFactory::registerClass(const std::string &type, CreateFunction func) {
    creators[type] = func;
}

ModelPtr ClassFactory::create(const std::string &type, std::string const &path, size_t ID, bool copy) {
    std::cout << "Creating object of type: " << type << std::endl;
    auto it = creators.find(type);
    if (it != creators.end()) {
        return it->second(path, ID, copy);
    }
    return nullptr;
}

