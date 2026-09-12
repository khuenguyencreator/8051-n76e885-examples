# Bài 10 — SPI trên N76E885

## Mục đích

Minh hoạ module SPI phần cứng của N76E885 (`SPCR`, `SPSR`, `SPDR`) ở chế độ
Master, 4 chân cố định: **SPICK = P0.5**, **MOSI = P2.1**, **MISO = P2.2**,
**SS = P0.4**. Tốc độ chọn chậm nhất (`SPR[1:0] = 11`, chia 32) cho chắc ăn
khi đấu dây breadboard; SPI mode 0 (`CPOL=0, CPHA=0`), truyền MSB trước.

- `spi_hc595_vd/` — Điều khiển **74HC595** (thanh ghi dịch 8-bit → song
  song): tạo hiệu ứng đèn chạy (running light) trên 8 LED nối vào Q0-Q7.
  Không dùng chân `SS` của SPI (74HC595 dùng chân `RCLK` riêng để chốt dữ
  liệu, không phải giao thức chip-select chuẩn SPI).
- `spi_25q80_vd/` — Giao tiếp **Flash SPI NOR 25Q80** (W25Q80/GD25Q80...):
  đọc JEDEC ID, xoá sector, ghi 1 chuỗi test, đọc lại và so sánh, in kết quả
  qua UART1 (giống bài 6).

## Sơ đồ đấu nối

Chung cho cả 2 ví dụ:
- P0.5 (SPICK), P2.1 (MOSI), P2.2 (MISO): nối tương ứng tới chân `SCLK`,
  `SI`/`SER`/`MOSI`, `SO`/`MISO` của IC.

`spi_hc595_vd/`:
- **SER** (chân 14) → P2.1 (MOSI)
- **SRCLK** (chân 11) → P0.5 (SPICK)
- **RCLK** (chân 12) → **P1.0**
- **OE** (chân 13) nối GND (luôn cho phép xuất), **MR** (chân 10) nối VCC.
- Q0-Q7 (chân 15, 1-7): mỗi chân nối 1 LED qua điện trở hạn dòng xuống GND.

`spi_25q80_vd/`:
- **CS#** → P0.4 (SS), **CLK** → P0.5 (SPICK), **DI(MOSI)** → P2.1,
  **DO(MISO)** → P2.2.
- `VCC`/`GND` cấp nguồn đúng mức điện áp module flash yêu cầu (thường
  3.3V — kiểm tra module trước khi cấp 5V).
- Cần mở terminal **19200 8N1** để xem kết quả JEDEC ID và Write/Read OK.

## Cách chạy thử

1. Mở `.cbp` của ví dụ muốn chạy bằng Code::Blocks (compiler SDCC).
2. Build, nạp vào board N76E885.
3. `spi_hc595_vd`: quan sát LED sáng chạy đuổi qua Q0→Q7 rồi lặp lại.
4. `spi_25q80_vd`: mở terminal 19200 8N1, xem dòng `JEDEC ID: xx xx xx` và
   `Write/Read OK` (nếu ra `MISMATCH`, kiểm tra lại dây nối hoặc điện áp cấp
   cho flash).
