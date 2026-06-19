package rentcar;
import java.time.LocalDate;
import java.time.temporal.ChronoUnit;

public class Pemesanan {
    private String idPemesanan;
    private Pelanggan penyewa;
    private Kendaraan mobilDisewa;
    private LocalDate tanggalAmbil;
    private LocalDate tanggalKembali;
    private Boolean statusSelesai;

    public Pemesanan(String idPemesanan, Pelanggan penyewa, Kendaraan mobilDisewa, LocalDate tanggalAmbil, LocalDate tanggalKembali) {
        this.idPemesanan = idPemesanan;
        this.penyewa = penyewa;
        this.mobilDisewa = mobilDisewa;
        this.tanggalAmbil = tanggalAmbil;
        this.tanggalKembali = tanggalKembali;
        this.statusSelesai = false;
    }
    
    public long hitungDurasiSewa(){
        return ChronoUnit.DAYS.between(tanggalAmbil, tanggalKembali);
    }

    public String getIdPemesanan() {
        return idPemesanan;
    }

    public Pelanggan getPenyewa() {
        return penyewa;
    }

    public Kendaraan getMobilDisewa() {
        return mobilDisewa;
    }

    public LocalDate getTanggalAmbil() {
        return tanggalAmbil;
    }

    public LocalDate getTanggalKembali() {
        return tanggalKembali;
    }

    public Boolean isStatusSelesai() {
        return statusSelesai;
    }

    public void setStatusSelesai(Boolean statusSelesai) {
        this.statusSelesai = statusSelesai;
    }

}
