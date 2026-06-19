#ifndef FLEETMANAGER_H
#define FLEETMANAGER_H
#include <QList>
#include "kendaraan.h"

class fleetManager
{
public:
    fleetManager();
    void tambahArmada(const Kendaraan& mobil);
    const QList<Kendaraan>& getDaftarArmada() const { return daftarArmada; }
    void setKetersediaanMobil(int index, bool status) {
        if(index >= 0 && index < daftarArmada.size()) {
            daftarArmada[index].setIsTersedia(status);
        }
    }
    Kendaraan* getPointerMobil(int index);


private:
    QList<Kendaraan> daftarArmada;
};

#endif // FLEETMANAGER_H
