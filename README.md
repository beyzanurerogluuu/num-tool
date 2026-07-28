# numtool

Sayı teorisi işlemlerini metin tabanlı komutlarla çalıştıran, C dilinde yazılmış bir komut satırı aracı. Bir giriş dosyasındaki komutları okur, her birini işler ve sonuçları hem ekrana hem de bir çıkış dosyasına yazar.

## Özellikler

`numtool`, aşağıdaki komutları destekler:

| Komut | Açıklama | Örnek | Sonuç |
|---|---|---|---|
| `GCD a b` | İki sayının en büyük ortak bölenini hesaplar | `GCD 48 18` | `6` |
| `POW base exp mod` | Modüler üs alma (hızlı üs alma algoritması) | `POW 2 10 1000` | `24` |
| `PRIME n` | Bir sayının asal olup olmadığını kontrol eder | `PRIME 29` | `YES` |
| `INV a m` | a'nın mod m'e göre çarpımsal tersini bulur (genişletilmiş Öklid) | `INV 3 11` | `4` |
| `PHI n` | Euler'in totient (phi) fonksiyonunu hesaplar | `PHI 36` | `12` |
| `CHECK a m` | a * a⁻¹ ≡ 1 (mod m) eşitliğini doğrular | `CHECK 1234567 1000000007` | `CORRECT` |

Girdi dosyasında birden fazla komut noktalı virgül (`;`) ile aynı satıra yazılabilir, ve `#` ile başlayan satırlar yorum olarak kabul edilir.

Geçersiz girdiler ve tanımsız işlemler için hata kodları döner: `ERROR_INVALID_INPUT`, `ERROR_INVALID_COMMAND`, `ERROR_NO_INVERSE`.

## Derleme

```bash
make
```

Bu komut `main.c`, `parser.c`, `math_utils.c` ve `records.c` dosyalarını derleyip `numtool` çalıştırılabilir dosyasını oluşturur.

Derleme çıktılarını temizlemek için:

```bash
make clean
```

## Kullanım

```bash
./numtool <giris_dosyasi> <cikis_dosyasi>
```

Örnek:

```bash
./numtool input.txt output.txt
```

`input.txt` içindeki komutlar sırayla işlenir; sonuçlar hem terminale basılır hem de `output.txt` dosyasına yazılır.

### Örnek girdi (`input.txt`)

```
GCD 48 18; POW 2 10 1000
PRIME 29
INV 3 11; PHI 36
```

### Örnek çıktı (`output.txt`)

```
GCD 48 18 -> 6
POW 2 10 1000 -> 24
PRIME 29 -> YES
INV 3 11 -> 4
PHI 36 -> 12
```

## Proje Yapısı

```
numtool/
├── main.c          # Program giriş noktası, dosya G/Ç işlemleri
├── parser.c/.h      # Komut satırlarını ayrıştırma ve işleme
├── math_utils.c/.h  # Sayı teorisi fonksiyonları (GCD, mod pow, asallık testi, vb.)
├── records.c/.h     # Dinamik boyutlanan komut kaydı listesi
├── Makefile
└── input.txt        # Örnek girdi dosyası
```

## Gereksinimler

- GCC (veya C11 destekli başka bir derleyici)
- POSIX uyumlu bir ortam (Linux, macOS, WSL)
