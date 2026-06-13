package rentcar;

public class Kendaraan {
    private String merk;
    private String tipe;
    private double tarifPerHari;
    private String statusKendaraan;

    public Kendaraan(String merk, String tipe, double tarifPerHari) {
        this.merk = merk;
        this.tipe = tipe;
        this.tarifPerHari = tarifPerHari;
        this.statusKendaraan = "Tersedia";
    }

    public String getMerk() {
        return merk;
    }

    public void setMerk(String merk) {
        this.merk = merk;
    }

    public String getTipe() {
        return tipe;
    }

    public void setTipe(String tipe) {
        this.tipe = tipe;
    }

    public double getTarifPerHari() {
        return tarifPerHari;
    }

    public void setTarifPerHari(double tarifPerHari) {
        this.tarifPerHari = tarifPerHari;
    }

    public String getStatusKendaraan() {
        return statusKendaraan;
    }

    public void setStatusKendaraan(String statusKendaraan) {
        this.statusKendaraan = statusKendaraan;
    }
    
   
}
