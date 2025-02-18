#pragma once

#include <iostream>
#include <map>

#include "ASpell.hpp"

class Warlock {
    private:
        std::string _name;
        std::string _title;
        std::map<std::string, ASpell*> _spellBook;
        Warlock();
        Warlock(const Warlock &other);
        Warlock&operator=(const Warlock &other);
    public:
        Warlock(std::string name, std::string title);
        ~Warlock();
        const std::string &getName() const;
        const std::string &getTitle() const;
        void setTitle(const std::string &title);
        void introduce() const;
        void learnSpell(ASpell * spellPtr);
        void forgetSpell(std::string spellName);
        void launchSpell(std::string spellName, ATarget &tarRef);
};