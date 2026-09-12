# Bài 8 — I2C trên N76E885

## Mục đích

Minh hoạ module I2C phần cứng của N76E885 (`I2CON`, `I2DAT`, `I2STAT`,
`I2CLK`, bit-addressable qua `I2CEN`/`STA`/`STO`/`SI`/`AA`), giao tiếp với
RTC **DS3231** để ghi và đọc giờ/phút/giây qua bus I2C.

`i2c_ds3231_vd.c`:
- Khởi tạo I2C ở tốc độ ~100kHz (`I2CLK = 0x36`, công thức
  `Fsys / (4 x (I2CLK+1))`).
- Ghi giờ cố định `10:30:00` vào DS3231 một lần lúc khởi động
  (`ds3231_set_time()`).
- Vòng lặp chính liên tục đọc thanh ghi giây (địa chỉ `0x00`) bằng repeated
  START (`ds3231_read_seconds()`), rồi nháy LED theo giá trị giây chẵn/lẻ —
  chứng minh dữ liệu đọc về là "sống" từ chip RTC thật, không phải delay phần
  mềm.

## Sơ đồ đấu nối

- **SDA = P2.3**, **SCL = P0.6** (2 chân cố định của module I2C trên
  N76E885, không thể đổi sang chân khác).
- Cả 2 chân cấu hình **open-drain**, bắt buộc phải có điện trở kéo lên
  (pull-up) ra VDD bên ngoài (thường 4.7kΩ) vì I2C hoạt động theo kiểu
  wired-AND.
- DS3231: `SDA`/`SCL` nối tương ứng, `VCC` nối 3.3V/5V tuỳ module, `GND`
  nối GND chung với N76E885.
- P0.4: LED (active-low) như bài 2.

## Cách chạy thử

1. Mở `i2c_ds3231_vd/i2c_ds3231_vd.cbp` bằng Code::Blocks (compiler SDCC).
2. Build, nạp vào board N76E885.
3. Quan sát LED nháy theo nhịp giây (đổi trạng thái mỗi giây) — nếu nháy đều
   nghĩa là đọc/ghi I2C với DS3231 thành công.
4. Muốn xác nhận thêm: dùng module DS3231 có pin lưu điện (CR2032) — tắt
   nguồn N76E885 rồi bật lại, LED vẫn tiếp tục nháy đúng nhịp vì DS3231 tự
   chạy tiếp thời gian, không bị reset về `10:30:00`.
