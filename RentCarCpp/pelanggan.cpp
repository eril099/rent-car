#include "pelanggan.h"

Pelanggan::Pelanggan(QString n, QString k, QString kon) {
    nama = n;
    ktp = k;
    kontak = kon;
}

Pelanggan::Pelanggan() {
    nama = "";
    ktp = "";
    kontak = "";
}
