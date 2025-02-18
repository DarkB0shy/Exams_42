#include "ASpell.hpp"

ASpell::ASpell() {};

ASpell::~ASpell() {};

ASpell::ASpell(const ASpell &other) {*this = other;}

ASpell  &ASpell::operator=(const ASpell &other) {
    _name = other._name;
    _effects = other._effects;
    return *this;
}

ASpell::ASpell(std::string name, std::string effects) : _name(name), _effects(effects) {}

std::string ASpell::getName() const {return _name;}

std::string ASpell::getEffects() const {return _effects;}

void    ASpell::launch(const ATarget &tarRef) const {
    tarRef.getHitBySpell(*this);
}