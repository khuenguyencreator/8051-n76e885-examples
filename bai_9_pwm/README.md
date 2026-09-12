# Bài 9 — PWM trên N76E885

## Mục đích

N76E885 có module PWM **riêng của Nuvoton** (không phải PWM giả lập bằng
Timer như 8051 chuẩn): 4 cặp kênh PWM0~PWM7, chu kỳ 12-bit dùng chung
(`PWMPH`/`PWMPL`), mỗi cặp có thanh ghi duty riêng 12-bit
(`PWM01H/L`, `PWM23H/L`, `PWM45H/L`, `PWM67H/L`), có double-buffer (`LOAD`)
để đổi duty/chu kỳ không bị glitch.

`pwm_led_breathing_vd.c`: dùng kênh **PWM0 (P1.0)** ở **independent mode**
(mode mặc định — PG0/2/4/6 mới thực sự xuất xung PWM, PG1/3/5/7 giữ mức cao),
tạo hiệu ứng LED "thở" (breathing) bằng cách tăng/giảm dần giá trị duty mỗi
10ms.

- Tần số PWM ~1kHz: `PWMDIV = 1/32`, `PWMP = 690` (giả định `Fsys` mặc định
  ~22.1184MHz — clock nội HIRC của N76E885).
- Minh hoạ đúng trình tự khởi tạo theo datasheet: `CLRPWM` (xoá bộ đếm 12-bit)
  → nạp `PWMPH/PWMPL` + duty ban đầu → `PWMRUN = 1` (chạy).
- Minh hoạ cơ chế double-buffer: mỗi lần đổi duty phải set `LOAD` rồi chờ
  hardware tự xoá bit này mới được đổi tiếp (áp dụng ở đầu chu kỳ tiếp theo,
  tránh giật hình khi đổi duty).

## Sơ đồ đấu nối

- **P1.0 (PWM0)**: nối LED qua điện trở hạn dòng (~330Ω) xuống GND (LED
  active-high ở ví dụ này vì dùng trực tiếp độ rộng xung, không đảo như
  `ON_LED`/`OFF_LED` các bài trước).
- Có thể quan sát dạng sóng PWM trực tiếp trên P1.0 bằng oscilloscope để thấy
  duty cycle thay đổi dần theo hiệu ứng breathing.

## Cách chạy thử

1. Mở `pwm_led_breathing_vd/pwm_led_breathing_vd.cbp` bằng Code::Blocks
   (compiler SDCC).
2. Build, nạp vào board N76E885.
3. Quan sát LED sáng dần rồi tắt dần liên tục (hiệu ứng "thở").
4. Thử đổi `PWM_PERIOD` hoặc `PWMDIV` trong code để thay đổi tần số PWM, build
   lại và quan sát sự khác biệt.
