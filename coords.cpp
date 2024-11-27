#include "coords.h"

std::ostream& operator<<(std::ostream& flux, const Coords& c) {
    flux<<"("<<c.getX()<<", "<<c.getY()<<")";
    return flux;
}