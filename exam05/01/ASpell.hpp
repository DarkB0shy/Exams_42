#pragma once

#include <iostream>

class ATarget;

class ASpell {
    private:
        std::string _name;
        std::string _effects;
    public:
        ASpell();
        virtual ~ASpell();
        ASpell(const ASpell &other);
        ASpell&operator=(const ASpell &other);
        std::string getName() const;
        std::string getEffects() const;
        virtual ASpell * clone() const = 0;
        ASpell(std::string name, std::string effects);
        void launch(const ATarget &tarRef) const;
};

#include "ATarget.hpp"