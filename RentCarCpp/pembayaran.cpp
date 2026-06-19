#include "pembayaran.h"

Pembayaran::Pembayaran(double awal, double potong, double charge) {
    totalAwal = awal;
    diskon = potong;
    denda = charge;
    totalAkhir = totalAwal - diskon + denda;
}

Pembayaran::Pembayaran() {
    totalAwal = 0;
    diskon = 0;
    denda = 0;
    totalAkhir = 0;
}