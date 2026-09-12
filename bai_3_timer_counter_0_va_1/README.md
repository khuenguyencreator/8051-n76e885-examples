# Bài 3 — Timer/Counter 0 và 1 trên N76E885

## Mục đích

Minh hoạ 2 cách dùng phổ biến của Timer 0:

- `timer_0_vd1.c` — Dùng Timer 0 ở **Mode 1 (16-bit timer)**, clock từ thạch anh phụ
  32.768 kHz (qua `AUXR1`/`CKEN`), tạo hàm `delay1sec()` chính xác bằng cách polling
  cờ tràn `TF0`. LED nhấp nháy chu kỳ 2 giây.
- `timer_0_vd2.c` — Dùng Timer 0 ở **Mode 2 (8-bit auto-reload)** kết hợp tính năng
  **Timer Output Toggle** của N76E885 (bit `T0OE` trong thanh ghi `P1M1`, xem datasheet
  N76E885 Rev 1.02 trang 40): phần cứng tự động toggle chân T0 (P2.0) mỗi khi Timer 0
  tràn, CPU không cần can thiệp trong vòng lặp — khác với cách dùng Timer 0 chuẩn của
  8051 truyền thống.

## Sơ đồ đấu nối

- `timer_0_vd1.c`: P0.4 nối LED (active-low) như bài 2.
- `timer_0_vd2.c`: quan sát tín hiệu toggle trực tiếp trên chân **P2.0** bằng
  oscilloscope/logic analyzer (không dùng LED ở ví dụ này).

## Cách chạy thử

1. Mở `.cbp` tương ứng trong thư mục con của ví dụ đó (ví dụ `timer_0_vd1/timer_0_vd1.cbp`) bằng Code::Blocks (đã cấu hình compiler SDCC).
2. Build và nạp vào board N76E885.
3. Với `timer_0_vd1.c`: quan sát LED nhấp nháy đều mỗi 2 giây (nhờ clock thạch anh
   32.768 kHz nên chính xác, không phụ thuộc dao động nội RC).
4. Với `timer_0_vd2.c`: đo tần số sóng vuông trên P2.0 bằng oscilloscope để kiểm
   chứng chu kỳ toggle theo giá trị nạp lại `TH0`.
