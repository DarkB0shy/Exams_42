#include "Warlock.hpp"

Warlock::Warlock(std::string name, std::string title) : _name(name), _title(title) {
    std::cout << _name << ": hello everyone!" << std::endl;
};

Warlock::~Warlock() {
    std::cout << _name << ": I will see you in my next youtube video!" << std::endl;
};

const std::string &Warlock::getName() const {return _name;}

const std::string &Warlock::getTitle() const {return _title;}

void    Warlock::setTitle(const std::string &title) {_title = title;}

void    Warlock::introduce() const {
    std::cout << _name << " is introducing himself as " << _title << std::endl;
}