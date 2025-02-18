#pragma once

#include <iostream>

class ASpell;

class ATarget {
    private:
        std::string _type;
    public:
        ATarget();
        virtual ~ATarget();
        ATarget(const ATarget &other);
        ATarget&operator=(const ATarget &other);
        std::string getType() const;
        virtual ATarget * clone() const = 0;
        ATarget(std::string type);
        void getHitBySpell(const ASpell &spellRef) const;
};

#include "ASpell.hpp"