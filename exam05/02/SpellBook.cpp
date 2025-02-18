#include "SpellBook.hpp"

SpellBook::SpellBook () {};

SpellBook::~SpellBook () {
    std::map<std::string, ASpell*>::iterator it_begin = _spellBook.begin();
    std::map<std::string, ASpell*>::iterator it_end = _spellBook.end();
    while (it_begin != it_end) {
        delete it_begin->second;
        ++it_begin;
    }
    _spellBook.clear();
}

void    SpellBook::learnSpell(ASpell * spellPtr) {
    if (spellPtr) {
        if (_spellBook.find(spellPtr->getName()) == _spellBook.end())
            _spellBook[spellPtr->getName()] = spellPtr->clone();
    }
}

void    SpellBook::forgetSpell(const std::string &spellName) {
    if (_spellBook.find(spellName) != _spellBook.end()) {
        delete _spellBook[spellName];
        _spellBook.erase(_spellBook.find(spellName));
    }
}

ASpell * SpellBook::createSpell(const std::string &spellName) {
    if (_spellBook.find(spellName) != _spellBook.end())
        return _spellBook[spellName];
    return NULL;
}