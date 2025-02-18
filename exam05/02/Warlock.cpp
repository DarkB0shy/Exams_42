#include "Warlock.hpp"

Warlock::Warlock(std::string name, std::string title) : _name(name), _title(title) {
    std::cout << _name << ": hello everyone!" << std::endl;
};

Warlock::~Warlock() {
    std::cout << _name << ": I will see you in my next youtube video!" << std::endl;
    // std::map<std::string, ASpell*>::iterator it_begin = _spellBook.begin();
    // std::map<std::string, ASpell*>::iterator it_end = _spellBook.end();
    // while (it_begin != it_end) {
    //     delete it_begin->second;
    //     ++it_begin;
    // }
    // _spellBook.clear();
};

const std::string &Warlock::getName() const {return _name;}

const std::string &Warlock::getTitle() const {return _title;}

void    Warlock::setTitle(const std::string &title) {_title = title;}

void    Warlock::introduce() const {
    std::cout << _name << " is introducing himself as " << _title << std::endl;
}

void    Warlock::learnSpell(ASpell * spellPtr) {
    // if (spellPtr) {
    //     if (_spellBook.find(spellPtr->getName()) == _spellBook.end())
    //         _spellBook[spellPtr->getName()] = spellPtr->clone();
    // }
    _spellBook.learnSpell(spellPtr);
}

void    Warlock::forgetSpell(std::string spellName) {
    // if (_spellBook.find(spellName) != _spellBook.end()) {
    //     delete _spellBook[spellName];
    //     _spellBook.erase(_spellBook.find(spellName));
    // }
    _spellBook.forgetSpell(spellName);
}

void    Warlock::launchSpell(std::string spellName, ATarget &tarRef) {
    // if (_spellBook.find(spellName) != _spellBook.end())
    //     _spellBook[spellName]->launch(tarRef);
    if (_spellBook.createSpell(spellName))
        _spellBook.createSpell(spellName)->launch(tarRef);
}