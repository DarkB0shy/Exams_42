#include "ATarget.hpp"

ATarget::ATarget() {};

ATarget::~ATarget() {};

ATarget::ATarget(const ATarget &other) {*this = other;}

ATarget  &ATarget::operator=(const ATarget &other) {
    _type = other._type;
    return *this;
}

ATarget::ATarget(std::string type) : _type(type) {}

std::string ATarget::getType() const {return _type;}

void    ATarget::getHitBySpell(const ASpell &spellRef) const {
    std::cout << _type << " has been " << spellRef.getEffects() << "! Damn!" << std::endl;
}