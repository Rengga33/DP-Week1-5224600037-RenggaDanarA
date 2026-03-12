In your README.md, answer:
1. What is the invariant structure in your program?
2. Which parts are mutable?
3. When you replaced the InputGenerator, why didn’t RunSession change?
4. What would happen if scoring logic was placed inside RunSession?
Clarity of explanation matters more than complexity.

Answer

1. Apa struktur invariant dalam program ini?

Invariant adalah urutan fase yang terkunci di dalam `RunSession`. Setiap ronde harus
menjalankan enam fase ini secara berurutan tanpa pengecualian:

1. Generate input
2. Hitung base score
3. Hitung reward
4. Update uang
5. Fase toko
6. Lanjut ke ronde berikutnya

Urutan ini dikunci di dalam `RunSession::runOneRound()` dan tidak bisa
diubah dari luar. Tidak peduli generator, scorer, atau reward rule mana
yang dipakai, alur permainan selalu melewati keenam langkah ini dalam
urutan yang sama. Kepastian itulah yang membuat bagian lain dari sistem
aman untuk dimodifikasi.


2. Bagian mana saja yang mutable?

Bagian yang mutable adalah implementasi yang diinjeksikan ke dalam `RunSession`:

| Sistem | Interface | Pilihan implementasi |
|---|---|---|
| Input generation | `IInputGenerator` | `RandomInputGenerator`, `WeightedRandomInputGenerator`, `FixedInputGenerator` |
| Scoring | `IScoringRule` | `SimpleScoring`, `BonusOddScoring` |
| Reward | `IRewardRule` | `SimpleReward`, `FlatBonusReward`, `EvenRoundDoubleReward`, `HalvingReward` |
| Toko | `ShopSystem` | Daftar penawaran dan kebijakan beli di dalam `ShopSystem` |

Semua bagian di atas bisa diganti, diperluas, atau dihapus tanpa menyentuh
`RunSession`. Satu-satunya tempat yang perlu diubah hanyalah `main.cpp`,
tempat objek-objek konkret dideklarasikan.


3. Kenapa RunSession tidak berubah saat InputGenerator diganti?

Karena `RunSession` sejak awal tidak pernah tahu generator mana yang sedang dipakai.

`RunSession` hanya menyimpan referensi ke interface abstrak `IInputGenerator`
dan memanggil satu method darinya:

```cpp
TurnInput input = generator_.generate(currentRound_);
```

`RunSession` tidak peduli apakah tipe konkret di balik referensi itu adalah
`RandomInputGenerator`, `WeightedRandomInputGenerator`, atau yang lainnya.
Mengganti implementasi di `main.cpp` tidak terlihat oleh `RunSession` —
tanda tangan method-nya tetap sama, sehingga pemanggilan tetap bisa
dikompilasi dan dijalankan tanpa perubahan apa pun di dalam `RunSession`.

Inilah manfaat nyata dari pemrograman berbasis interface, bukan tipe konkret.
Pemanggil terpisah dari detail implementasi.

---

4. Apa yang terjadi jika logika scoring diletakkan di dalam RunSession?

Dua masalah akan langsung muncul.

Melanggar pemisahan tanggung jawab. `RunSession` seharusnya hanya mengatur
*urutan* permainan, bukan *aturan* permainan. Mencampur keduanya dalam satu
class berarti satu file kini bertanggung jawab atas dua hal yang berbeda.
Jika salah satunya perlu diubah, kita harus membuka dan mengedit `RunSession`
— meskipun struktur loop-nya sudah benar dan tidak perlu disentuh.

Setiap perubahan aturan memaksa kita menulis ulang core loop. Ingin mencoba
menggandakan skor di ronde ganjil? Kita buka `RunSession`, cari baris scoring,
lalu edit — dengan risiko tidak sengaja mengubah urutan fase atau logika uang
yang ada di sekitarnya. Semakin banyak logika yang ditumpuk dalam satu class,
semakin banyak hal yang bisa rusak dari satu perubahan kecil.

Desain yang sekarang menghindari kedua masalah tersebut. Scoring ada di `ScoreSystem`,
reward ada di `RewardSystem`, dan `RunSession` tidak pernah disentuh selama
semua modifikasi berlangsung. Invariant terlindungi justru karena tidak ada
satu pun hal yang perlu berubah di dalamnya.
