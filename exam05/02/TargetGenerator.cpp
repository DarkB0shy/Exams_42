#include "TargetGenerator.hpp"

TargetGenerator::TargetGenerator () {};

TargetGenerator::~TargetGenerator () {
    std::map<std::string, ATarget*>::iterator it_begin = _tarMap.begin();
    std::map<std::string, ATarget*>::iterator it_end = _tarMap.end();
    while (it_begin != it_end) {
        delete it_begin->second;
        ++it_begin;
    }
    _tarMap.clear();
}

void    TargetGenerator::learnTargetType(ATarget * tarPtr) {
    if (tarPtr) {
        if (_tarMap.find(tarPtr->getType()) == _tarMap.end())
            _tarMap[tarPtr->getType()] = tarPtr->clone();
    }
}

void    TargetGenerator::forgetTargetType(const std::string &tarType) {
    if (_tarMap.find(tarType) != _tarMap.end()) {
        delete _tarMap[tarType];
        _tarMap.erase(_tarMap.find(tarType));
    }
}

ATarget * TargetGenerator::createTarget(const std::string &tarType) {
    if (_tarMap.find(tarType) != _tarMap.end())
        return _tarMap[tarType];
    return NULL;
}