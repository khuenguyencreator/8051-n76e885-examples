# Bài 4 — Timer 2 và Timer 3 trên N76E885

## Mục đích

Timer 2 và Timer 3 là 2 timer 16-bit riêng của dòng Nuvoton N76E885 (không có ở
8051 chuẩn), có thanh ghi nạp lại/so sánh (`RCMP2H/L`, `RH3/RL3`) và bộ chia tần
số (prescaler) riêng.

- `timer_2_vd.c` — Dùng Timer 2 ở **compare mode** (`CM_RL2 = 1`), tạo hàm
  `delay1ms()` polling cờ `TF2` khi giá trị đếm khớp `RCMP2H/L`. Prescaler
  (`T2DIV`) được set về `1/1`.
- `timer_3_vd.c` — Dùng Timer 3 ở chế độ tự tràn với prescaler `1/128`
  (`T3CON` bit 0..2), tạo hàm `delay100ms()` polling cờ tràn `TF3` (bit 4 của
  `T3CON`).

Cả 2 ví dụ đều nhấp nháy LED P0.4 để trực quan hoá.

## Sơ đồ đấu nối

- P0.4: nối LED (active-low) như bài 2.

## Cách chạy thử

1. Mở `.cbp` tương ứng trong thư mục con của ví dụ đó (ví dụ `timer_2_vd/timer_2_vd.cbp`) bằng Code::Blocks (compiler SDCC).
2. Build, nạp vào board N76E885.
3. Quan sát LED nhấp nháy: `timer_2_vd.c` chu kỳ ~1s (2 x 500ms), `timer_3_vd.c`
   chu kỳ ~1s (2 x 5x100ms).
4. Có thể đo trực tiếp bằng oscilloscope trên P0.4 để kiểm chứng chu kỳ chính xác.
