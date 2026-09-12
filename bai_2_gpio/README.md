# Bài 2 — GPIO trên N76E885

## Mục đích

Minh hoạ cách cấu hình chân GPIO của N76E885 (thanh ghi `PxM1`/`PxM2` để chọn
mode: quasi-bidirectional, push-pull, input-only, open-drain) và đọc/ghi trạng
thái chân qua các `__sbit`.

- `gpio_vd1.c` — Cấu hình P0.4 (LED1) ở mode quasi-bidirectional, nhấp nháy LED mỗi 500ms.
- `gpio_vd2.c` — Thêm nút nhấn ở P0.0 (mode quasi-bidirectional, dùng làm input). Nhấn
  nút để LED nhấp nháy nhanh 3 lần.
- `gpio_vd3.c` — Dùng chung 1 chân P0.4 vừa làm LED (output) vừa làm nút nhấn (input),
  minh hoạ cách chuyển đổi qua lại giữa 2 chức năng trên cùng 1 pin.
- `gpio_vd4.c` — Giống `gpio_vd1.c` nhưng cấu hình P0.4 ở mode push-pull thay vì
  quasi-bidirectional, để so sánh sự khác biệt giữa 2 mode.

## Sơ đồ đấu nối

- P0.4: nối LED (qua điện trở hạn dòng ~330Ω) xuống GND. Mức 0 = LED sáng
  (`ON_LED = 0`), mức 1 = LED tắt (`OFF_LED = 1`), do LED đấu kiểu cực dương
  nối VCC (active-low).
- P0.0 (chỉ dùng ở `gpio_vd2.c`): nối nút nhấn, đầu còn lại nối GND. Dùng
  điện trở pull-up nội (quasi-bidirectional) nên không cần điện trở ngoài,
  nhấn nút = mức 0 (`PRESSED = 0`).

## Cách chạy thử

1. Mở file `.cbp` tương ứng (ví dụ `gpio_vd1/gpio_vd1.cbp`) bằng Code::Blocks.
2. Đảm bảo Code::Blocks đã có compiler SDCC (Settings > Compiler > SDCC),
   trỏ đúng đường dẫn cài SDCC trên máy.
3. Build (Ctrl+F9), nạp file `.hex`/`.ihx` sinh ra vào N76E885 bằng công cụ
   nạp của Nuvoton (Nu-Link / ICP tool).
4. Quan sát LED nhấp nháy; với `gpio_vd2.c`/`gpio_vd3.c`, thử nhấn nút để
   thấy phản ứng của LED.
