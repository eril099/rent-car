#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QFormLayout>
#include <QLineEdit>
#include <QSpinBox>
#include <QDialogButtonBox>
#include <QDateEdit>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::Stretch);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::refreshTabelMobil()
{
    ui->tableWidget->setRowCount(0);
    for (int i = 0; i < managerPusat.getDaftarArmada().size(); i++) {
        Kendaraan mobil = managerPusat.getDaftarArmada()[i];
        ui->tableWidget->insertRow(i);
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(mobil.getMerk()));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(mobil.getTipe()));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem("Rp." + QString::number(mobil.getTarifPerHari(), 'f', 0)));
        QString statusText = mobil.getIsTersedia() ? "Tersedia" : "Disewa";
        ui->tableWidget->setItem(i, 3, new QTableWidgetItem(statusText));
    }
}

void MainWindow::on_btnTambahMobil_clicked()
{
    QDialog formTambah(this);
    formTambah.setWindowTitle("Tambah Armada Mobil Baru");
    QFormLayout *layout = new QFormLayout(&formTambah);

    QLineEdit *txtMerk = new QLineEdit(&formTambah);
    txtMerk->setPlaceholderText("Contoh: Honda, Toyota, Suzuki");
    QLineEdit *txtTipe = new QLineEdit(&formTambah);
    txtTipe->setPlaceholderText("Contoh: Civic, Avanza, Ertiga");

    QDoubleSpinBox *spinTarif = new QDoubleSpinBox(&formTambah);
    spinTarif->setRange(100000, 100000000);
    spinTarif->setSingleStep(50000);
    spinTarif->setValue(500000);
    spinTarif->setDecimals(0);
    spinTarif->setPrefix("Rp. ");

    layout->addRow("Merk Kendaraan:", txtMerk);
    layout->addRow("Tipe Kendaraan:", txtTipe);
    layout->addRow("Tarif / Hari:", spinTarif);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &formTambah);
    layout->addRow(buttonBox);

    connect(buttonBox, QDialogButtonBox::accepted, &formTambah, QDialog::accept);
    connect(buttonBox, QDialogButtonBox::rejected, &formTambah, QDialog::reject);

    if (formTambah.exec() == QDialog::Accepted) {
        if (txtMerk->text().isEmpty() || txtTipe->text().isEmpty()) {
            QMessageBox::critical(this, "Gagal", "Armada gagal! Merk dan Tipe wajib diisi.");
            return;
        }
        QString merkInput = txtMerk->text();
        QString tipeInput = txtTipe->text();
        double tarifInput = spinTarif->value();

        Kendaraan mobilBaru(merkInput, tipeInput, tarifInput);
        managerPusat.tambahArmada(mobilBaru);
        refreshTabelMobil();

        QMessageBox::information(this, "Sukses", "Mobil " + merkInput + " " + tipeInput + " Berhasil Ditambah ke database!");
    }
}
void MainWindow::on_btnSewaMobil_clicked()
{
    int barisTerpilih = ui->tableWidget->currentRow();
    if (barisTerpilih < 0) {
        QMessageBox::warning(this, "Peringatan", "Silahkan pilih dahulu mobil yang ingin disewa!");
        return;
    }

    if (managerPusat.getDaftarArmada()[barisTerpilih].getIsTersedia()) {
        QDialog formSewa(this);
        formSewa.setWindowTitle("Formulir Penyewaan Mobil");
        QFormLayout *layout = new QFormLayout(&formSewa);
        QLineEdit *txtNama = new QLineEdit(&formSewa);
        QLineEdit *txtKtp = new QLineEdit(&formSewa);
        QLineEdit *txtKontak = new QLineEdit(&formSewa);
        QDateEdit *dateAmbil = new QDateEdit(&formSewa);
        dateAmbil->setCalendarPopup(true);
        dateAmbil->setDate(QDate::currentDate());
        QSpinBox *spinDurasi = new QSpinBox(&formSewa);
        spinDurasi->setRange(1,100);
        spinDurasi->setValue(1);

        QLabel *lblTglKembaliOtomatis = new QLabel(QDate::currentDate().addDays(1).toString("dd-MM-yyyy"), &formSewa);
        auto updateTanggalKembali = [dateAmbil, spinDurasi, lblTglKembaliOtomatis]() {
            QDate tglAmbil = dateAmbil->date();
            int durasi = spinDurasi->value();
            QDate tglKembali = tglAmbil.addDays(durasi);
            lblTglKembaliOtomatis->setText(tglKembali.toString("dd-MM-yyyy"));
        };

        connect(dateAmbil, &QDateEdit::dateChanged, updateTanggalKembali);
        connect(spinDurasi, QOverload<int>::of(&QSpinBox::valueChanged), updateTanggalKembali);

        layout->addRow("Nama Lengkap:", txtNama);
        layout->addRow("Nomor KTP:", txtKtp);
        layout->addRow("Nomor Kontak/HP:", txtKontak);
        layout->addRow("Tanggal Ambil:", dateAmbil);
        layout->addRow("Durasi (Hari):", spinDurasi);
        layout->addRow("Tanggal Kembali:", lblTglKembaliOtomatis);

        QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &formSewa);
        layout->addRow(buttonBox);
        connect(buttonBox, &QDialogButtonBox::accepted, &formSewa, &QDialog::accept);
        connect(buttonBox, &QDialogButtonBox::rejected, &formSewa, &QDialog::reject);

        if (formSewa.exec() == QDialog::Accepted) {
            if (txtNama->text().isEmpty() || txtKtp->text().isEmpty() || txtKontak->text().isEmpty()) {
                QMessageBox::critical(this, "Gagal", "Transaksi dibatalkan data pelanggan wajib diisi lengkap!");
                return;
            }
            QString namaInput = txtNama->text();
            QString ktpInput = txtKtp->text();
            QString kontakInput = txtKontak->text();
            QString tglAmbilInput = dateAmbil->date().toString("dd-MM-yyyy");
            QString tglKembaliInput = lblTglKembaliOtomatis->text();
            int durasiInput = spinDurasi->value();

            Pelanggan* pelangganBaru = new Pelanggan(namaInput, ktpInput, kontakInput);
            daftarPelanggan.append(pelangganBaru);
            Kendaraan* mobilTerpilih = managerPusat.getPointerMobil(barisTerpilih);
            managerPusat.setKetersediaanMobil(barisTerpilih, false);
            Pemesanan transaksiBaru(tglAmbilInput, tglKembaliInput, durasiInput, mobilTerpilih, pelangganBaru);
            daftarPemesanan.append(transaksiBaru);
            refreshTabelMobil();

            QString nota = "---Nota Rental Mobil---\n\n"
                           "Pelanggan   : " + pelangganBaru->getNama() + " (" + pelangganBaru->getKtp() + ") \n"
                            "Kontak     : " + pelangganBaru->getKontak() + " \n"
                            "Mobil      : " + mobilTerpilih->getMerk() + " " + mobilTerpilih->getTipe() + "\n "
                            "Durasi     : " + QString::number(transaksiBaru.getDurasiHari()) + " Hari (" + tglAmbilInput + "  s/d  " + tglKembaliInput + ")\n "
                            "Biaya      : " + ui->tableWidget->item(barisTerpilih, 2)->text() + "/hari\n\n"
                            "STATUS     : BERHASIL BOOKING!";

            QString logRiwayatSewa = "[" + tglAmbilInput + "] - [" + tglKembaliInput + "] " + pelangganBaru->getNama() + " | " + mobilTerpilih->getMerk() + " " + mobilTerpilih->getTipe() + " Booking";
            ui->listRiwayat->addItem(logRiwayatSewa);
            databaseNota.append(nota);
            QMessageBox::information(this, "Transaksi Sukses", nota);
        }
    } else {
        QMessageBox::critical(this, "Gagal", "Maaf, mobil ini sudah disewa oleh pelanggan lain!");
    }
}



void MainWindow::on_btnKembalikanMobil_clicked()
{
    int barisTerpilih = ui->tableWidget->currentRow();
    if (barisTerpilih < 0) {
        QMessageBox::warning(this, "Peringatan", "Silahkan pilih dahulu mobil yang ingin dikembalikan!");
        return;
    }

    if (!managerPusat.getDaftarArmada()[barisTerpilih].getIsTersedia()) {
        Pemesanan* transaksiAktif = nullptr;
        for (int i = daftarPemesanan.size() - 1; i >= 0; i--) {
            if (daftarPemesanan[i].getMobilYangDisewakan() == &managerPusat.getDaftarArmada()[barisTerpilih] && !daftarPemesanan[i].getMobilYangDisewakan()->getIsTersedia()) {
                transaksiAktif = &daftarPemesanan[i];
                break;
            }
        }
        if (!transaksiAktif) return;

        double tarifHarian = transaksiAktif->getMobilYangDisewakan()->getTarifPerHari();
        double totalAwal = transaksiAktif->getDurasiHari() * tarifHarian;

        QStringList opsiStatus;
        opsiStatus << "Tepat Waktu" << "Terlambat" << "Lebih Awal";
        bool okStatus;
        QString statusPilihan = QInputDialog::getItem(this, "Status Pengembalian", "Pilih Kondisi Pengembalian Mobil:", opsiStatus, 0, false, &okStatus);
        if (!okStatus) return;

        int hariTerlambat = 0;
        int hariLebihAwal = 0;
        double potonganLebihAwal = 0;
        double denda = 0;
        int durasiFix = transaksiAktif->getDurasiHari();
        QDate tglFixKembali = QDate::fromString(transaksiAktif->getTanggalKembali(), "dd-MM-yyyy");

        if (statusPilihan == "Terlambat") {
            bool okHari;
            hariTerlambat = QInputDialog::getInt(this, "From Pengembalian", "Masukkan Jumlaah Hari Keterlambat:", 1, 1, 30, 1, &okHari);
            if (!okHari) return;
            denda = hariTerlambat * (tarifHarian * 1.50);
            tglFixKembali = tglFixKembali.addDays(hariTerlambat);
        } else if (statusPilihan == "Lebih Awal") {
            bool okHari;
            hariLebihAwal = QInputDialog::getInt(this, "Form Pengembalian Awal", "Lebih Cepat Berapa Hari:", 1, 1, transaksiAktif->getDurasiHari() - 1, 1, &okHari);
            if (!okHari) return;
            potonganLebihAwal = hariLebihAwal * tarifHarian;
            durasiFix -= hariLebihAwal;
            totalAwal = durasiFix * tarifHarian;
            tglFixKembali = tglFixKembali.addDays(-hariLebihAwal);
        }

        double diskon = 0;
        if (durasiFix >= 5) {
            diskon = totalAwal * 0.10;
        }

        double totalHarusDibayar = totalAwal - diskon + denda;

        QMessageBox::StandardButton konfirmasi;
        konfirmasi = QMessageBox::question(this, "Konfirmasi Pembayaran", "Total Tagihan: Rp " + QString::number(totalHarusDibayar, 'f', 0) + "\n\n Pelanggan Sudah Membayar Tagihan?", QMessageBox::Yes | QMessageBox::No);
        if (konfirmasi == QMessageBox::No)  {
            QMessageBox::warning(this, "Pembayaran Tertunda", "Pembayaran Dibatallkan, Pastikan Pelanggan Sudah Membayar Tagihan");
            return;

        }

        Pembayaran prosesBayar(totalAwal, diskon, denda);
        managerPusat.setKetersediaanMobil(barisTerpilih, true);
        refreshTabelMobil();

        QString info = "";
        if (hariLebihAwal > 0) info = "Kembali Lebih Awal: " + QString::number(hariLebihAwal) + " Hari\n";
        if (hariTerlambat > 0) info = "Keterlambatan: " + QString::number(hariTerlambat) + " Hari\n";
        QString txtFixKembali = tglFixKembali.toString("dd-MM-yyyy");

        QString notaLunas = "--- NOTA PELUNASAN + DENDA & DISKON ---\n\n"
                            "Pelanggan: " + transaksiAktif->getPenyewa()->getNama() + "\n"
                            "Mobil: " + transaksiAktif->getMobilYangDisewakan()->getMerk() + " " + transaksiAktif->getMobilYangDisewakan()->getTipe() + "\n"
                            "Kembali: " + txtFixKembali + "\n"
                            "Durasi Awal: " + QString::number(transaksiAktif->getDurasiHari()) + " Hari\n"
                            + info +
                            "Durasi Akhir: " + QString::number(durasiFix) + " Hari\n"
                            "----------------------------------------\n"
                            "Biaya Sewa: Rp " + QString::number(prosesBayar.getTotalAwal(), 'f', 0) + "\n"
                            "Potongan Diskon: Rp " + QString::number(prosesBayar.getDiskon(), 'f', 0) + " (10%)\n"
                            "Biaya Denda: Rp " + QString::number(prosesBayar.getDenda(), 'f', 0) + "\n"
                            "----------------------------------------\n"
                            "TOTAL TAGIHAN: Rp " + QString::number(prosesBayar.getTotalAkhir(), 'f', 0) + "\n"
                            "STATUS: LUNAS & TERIMA KASIH!";
        QString logRiwayatTransaksi = "[" + txtFixKembali + "] " + transaksiAktif->getPenyewa()->getNama() + " | " + transaksiAktif->getMobilYangDisewakan()->getMerk() + " " + transaksiAktif->getMobilYangDisewakan()->getTipe() + " Total: Rp." + QString::number(prosesBayar.getTotalAkhir(), 'f',0 ) + " Lunas";
        ui->listRiwayat->addItem(logRiwayatTransaksi);
        databaseNota.append(notaLunas);
        QMessageBox::information(this, "Pembayaran Sukses", notaLunas);
    }
    else {
        QMessageBox::warning(this, "Info", "Mobil ini sudah beara di garasi");
    }
}
void MainWindow::on_listRiwayat_doubleClicked(const QModelIndex &item)
{
    int barisTerpilih = ui->listRiwayat->currentRow();
    if (barisTerpilih >= 0 && barisTerpilih < databaseNota.size()) {
        QString notaDipilih = databaseNota[barisTerpilih];
        QMessageBox::information(this, "Detail Transaksi", notaDipilih);
    }
}
