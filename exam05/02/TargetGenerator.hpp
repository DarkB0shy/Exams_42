#pragma once

#include <map>

#include "ATarget.hpp"

class TargetGenerator {
    private:
        std::map<std::string, ATarget*> _tarMap;
        TargetGenerator(const TargetGenerator &other);
        TargetGenerator&operator=(const TargetGenerator &other);
    public:
        TargetGenerator();
        ~TargetGenerator();
        void learnTargetType(ATarget * tarPtr);
        void forgetTargetType(const std::string &tarName);
        ATarget * createTarget(const std::string &tarName);
};