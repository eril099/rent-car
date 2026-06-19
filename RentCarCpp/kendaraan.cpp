#include "kendaraan.h"

Kendaraan::Kendaraan(QString m, QString t, double tarif) {
    merk = m;
    tipe = t;
    tarifPerHari = tarif;
    isTersedia = true;
}

Kendaraan::Kendaraan() {
    merk = "";
    tipe = "";
    tarifPerHari = 0;
    isTersedia = true;
}
