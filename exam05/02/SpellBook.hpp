#pragma once

#include <map>

#include "ASpell.hpp"

class SpellBook {
    private:
        std::map<std::string, ASpell*> _spellBook;
        SpellBook(const SpellBook &other);
        SpellBook&operator=(const SpellBook &other);
    public:
        SpellBook();
        ~SpellBook();
        void learnSpell(ASpell * spellPtr);
        void forgetSpell(const std::string &spellName);
        ASpell * createSpell(const std::string &spellName);
};