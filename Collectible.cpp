#include "Collectible.h"

Collectible::Collectible(int p, bool isPower) 
    : collected(false), points(p), powerPellet(isPower) {
}