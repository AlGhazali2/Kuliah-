// Array untuk menyimpan data
let data = [];

// Fungsi untuk menangani pengiriman form
document.getElementById("dataForm").addEventListener("submit", function(event) {
    event.preventDefault(); // Menghindari pengiriman form dan reload halaman

    // Ambil data dari input
    let nama = document.getElementById("nama").value;
    let tanggal_lahir = document.getElementById("tanggal_lahir").value;
    let parameter = document.getElementById("Domisili").value;

    // Simpan data ke array
    data.push({ nama, tanggal_lahir, parameter });

    // Update tabel dengan data terbaru
    updateTable();
});

// Fungsi untuk mengupdate tabel
function updateTable() {
    // Ambil tabel
    const table = document.getElementById("dataTable");

    // Hapus semua baris dalam tabel kecuali header
    while (table.rows.length > 1) {
        table.deleteRow(1);
    }

    // Tambahkan data baru ke tabel
    data.forEach(item => {
        const row = table.insertRow();
        row.insertCell(0).textContent = item.nama;
        row.insertCell(1).textContent = item.tanggal_lahir;
        row.insertCell(2).textContent = item.Domisili;
    });
}
