
## ESP32
ESP32 merupakan micro controller yang dapat terhubung ke internet melalui wifi. ESP32 banyak digunakan untuk menghubungkan hardware yang dapat dikendalikan jarak jauh lewat internet. Keunggulan ini yang membuat saya tertarik terhadap ESP32. Dimana saya dapat bertukar data lewat internet antara hardware dan device saya.

> Walau begitu masih banyak kekurangan dari ESP32 yang dimana waktu compile nya sangat lama menurut saya.

## Tujuan 
Disini tujuan saya dari project ini adalah menghubungkan semua perangkat ke internet dan juga kita dapat tahu apa value yang dihasilkan dari hardware tsb secara realtime dimana kita bisa mengatur berapa lama data akan di kirim.

> Sebelum menjalankan program, jangan lupa setup dahulu arduino IDE untuk ESP32 agar dapat berjalan dan dicompile dengan baik

## Cara Kerja
Cara kerja dari perangkat ini sangat simple, dimana kita menyediakan backend untuk menyimpan data dan juga front_end untuk menampilkan data. 

Untuk alat dan bahan yang digunakan antara lain:
- kabel Male to Male: 2
- kabel Female to Male: 6
- kabel Female to Female: 2
- ESP32
- Sensor Soil
- LED Trafic or 3 led RGB
- BreadBoard menyesuaikan

### Sensor soil to ESP32: 
- AO (analog output) -> pin D34
- VCC -> pin v3.3
- GND -> GND

### Trafic LED to ESP32:
- GND -> GND
- G (green) -> pin D14
- Y (yellow) -> pin D12
- R (red) -> pin D13

