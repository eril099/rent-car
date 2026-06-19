#include "fleetmanager.h"

fleetManager::fleetManager() {}

void fleetManager::tambahArmada(const Kendaraan& mobil) {
    daftarArmada.append(mobil);
}

Kendaraan* fleetManager::getPointerMobil(int index) {
    if (index >= 0 && index < daftarArmada.size()) {
        return &daftarArmada[index];
    }
    return nullptr;
}