#include "pemesanan.h"

Pemesanan::Pemesanan(QString ambil, QString kembali, int hari, Kendaraan *mobil, Pelanggan *p) {
    tanggalAmbil = ambil;
    tanggalKembali = kembali;
    durasiHari = hari;
    mobilYangDisewakan = mobil;
    penyewa = p;
}

Pemesanan::Pemesanan() {
    tanggalAmbil = "";
    tanggalKembali = "";
    durasiHari = 0;
    mobilYangDisewakan = nullptr;
    penyewa = nullptr;
}