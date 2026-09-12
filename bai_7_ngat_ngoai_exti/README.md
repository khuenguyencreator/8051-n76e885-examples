# Bài 7 — Ngắt ngoài (External Interrupt) trên N76E885

## Mục đích

N76E885 có 2 chân ngắt ngoài chuẩn 8051: **INT0** (P0.0) và **INT1** (P0.1),
cấu hình cạnh xuống/mức thấp qua các bit `IT0`/`IT1` (thanh ghi `TCON`), bật
qua `EX0`/`EX1` (thanh ghi `IE`). Khác với bài 2 (polling nút nhấn trong vòng
lặp `while`), ở đây CPU không cần chủ động kiểm tra trạng thái chân — phần
cứng tự nhảy vào hàm ngắt (ISR) khi có cạnh xuống.

- `exti_int0_vd/` — Dùng **INT0** (P0.0): mỗi lần nhấn nút, ISR đảo trạng thái
  LED ngay lập tức, `main()` không làm gì cả.
- `exti_int1_vd/` — Dùng **INT1** (P0.1): minh hoạ "đếm xung" — ISR chỉ tăng 1
  biến đếm (`pulse_count`) rồi thoát ngay (nguyên tắc: ISR càng ngắn càng
  tốt), `main()` mỗi 3 giây đọc số xung đã đếm được và nháy LED đúng số lần
  đó. Minh hoạ cách đọc/an toàn với biến `volatile` dùng chung giữa ISR và
  `main()` (tạm tắt `EA` khi đọc).

## Sơ đồ đấu nối

- P0.4: LED (active-low) như bài 2.
- `exti_int0_vd/`: nút nhấn ở P0.0, đầu còn lại nối GND (dùng pull-up nội,
  không cần điện trở ngoài).
- `exti_int1_vd/`: nút nhấn (hoặc nguồn xung bất kỳ, ví dụ tín hiệu từ cảm
  biến/encoder) ở P0.1, đầu còn lại nối GND.

## Cách chạy thử

1. Mở `.cbp` của ví dụ muốn chạy (ví dụ `exti_int0_vd/exti_int0_vd.cbp`)
   bằng Code::Blocks (compiler SDCC).
2. Build, nạp vào board N76E885.
3. `exti_int0_vd`: nhấn nút ở P0.0, quan sát LED đổi trạng thái ngay mỗi lần
   nhấn.
4. `exti_int1_vd`: nhấn nút ở P0.1 vài lần trong vòng 3 giây, sau đó quan sát
   LED nháy đúng số lần đã nhấn.
