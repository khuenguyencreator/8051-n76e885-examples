# Bài 11 — 1-Wire với DS18B20 trên N76E885

## Mục đích

N76E885 **không có module 1-Wire phần cứng**, nên giao tiếp với cảm biến
nhiệt độ **DS18B20** phải bit-banging hoàn toàn bằng phần mềm trên 1 chân
GPIO (toggle mức 0/1 + delay theo đúng timing chuẩn 1-Wire: reset pulse,
write bit 0/1, read bit).

`ds18b20_vd.c`:
- Cài đặt đầy đủ `ow_reset()`, `ow_write_bit()`/`ow_read_bit()`,
  `ow_write_byte()`/`ow_read_byte()` theo timing chuẩn DS18B20.
- Đọc nhiệt độ bằng lệnh Skip ROM (`0xCC`, chỉ dùng được khi có **đúng 1**
  DS18B20 trên bus) + Convert T (`0x44`) + Read Scratchpad (`0xBE`).
- Kết hợp UART1 (giống bài 6) để in kết quả nhiệt độ dạng `25.6 C` ra terminal
  mỗi giây, thay vì chỉ nháy LED (khó biểu diễn số có phần thập phân).

**Lưu ý về timing:** hàm `delay_us()` là vòng lặp đếm thời gian gần đúng, phụ
thuộc vào compiler/clock thực tế — không phải delay chính xác tuyệt đối theo
micro giây. Timing của 1-Wire/DS18B20 có dung sai nhất định nên thường vẫn
chạy được, nhưng nếu `ow_reset()` luôn không phát hiện được thiết bị (không
có presence pulse), cần đo lại bằng oscilloscope/logic analyzer và tinh chỉnh
hằng số lặp trong `delay_us()`, hoặc chuyển sang dùng delay dựa trên timer
phần cứng cho chính xác.

## Sơ đồ đấu nối

- **P1.2 (DQ)**: nối chân DQ của DS18B20, cấu hình open-drain, **bắt buộc**
  có điện trở kéo lên (pull-up) ra VDD, thường 4.7kΩ.
- DS18B20: `VDD` nối 3.3V/5V tuỳ module, `GND` nối GND chung với N76E885,
  `DQ` nối P1.2 (không dùng chế độ parasite power ở ví dụ này — cấp nguồn
  bình thường qua chân VDD).
- Chỉ đấu **1 DS18B20** trên bus vì code dùng lệnh Skip ROM.

## Cách chạy thử

1. Mở `ds18b20_vd/ds18b20_vd.cbp` bằng Code::Blocks (compiler SDCC).
2. Build, nạp vào board N76E885.
3. Mở terminal (PuTTY, Tera Term...) ở tốc độ **19200 8N1**.
4. Quan sát nhiệt độ được in ra mỗi giây, ví dụ `25.6 C`. Áp tay vào cảm biến
   để thấy giá trị tăng lên, kiểm chứng dữ liệu đọc về là thật.
