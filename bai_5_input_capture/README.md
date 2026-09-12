# Bài 5 — Input Capture trên N76E885

## Mục đích

Minh hoạ module **Input Capture** (3 kênh, riêng của Nuvoton, không có ở 8051
chuẩn) kết hợp Timer 2 ở chế độ không tự động nạp lại (`CM_RL2 = 0`) để đo
khoảng thời gian giữa 2 cạnh tín hiệu — ứng dụng thực tế: **giải mã tín hiệu
hồng ngoại chuẩn NEC** từ remote điều khiển.

`input_capture_vd.c` dùng kênh input capture 2 (P2.2) bắt cạnh tín hiệu từ mắt
thu hồng ngoại, dùng máy trạng thái (`nec_t`/`necHandler()`) để giải mã từng
bit theo thời gian chuẩn NEC, sau đó điều khiển LED P0.4 theo mã lệnh nhận
được (`0x98` = bật, `0xD8` = tắt).

## Sơ đồ đấu nối

- P2.2: nối chân OUT của mắt thu hồng ngoại (ví dụ TSOP1738/VS1838B, ngõ ra
  active-low, cần đấu thêm tụ lọc nguồn theo datasheet mắt thu).
- P0.4: nối LED (active-low) như bài 2.
- Dùng remote điều khiển hồng ngoại chuẩn NEC bất kỳ (ví dụ remote TV thông
  dụng), đã biết trước địa chỉ (`address = 0x00`) và mã lệnh muốn dùng để test.

## Cách chạy thử

1. Mở `input_capture_vd/input_capture_vd.cbp` bằng Code::Blocks (compiler SDCC).
2. Build, nạp vào board N76E885.
3. Bấm nút trên remote có mã lệnh `0x98` để bật LED, `0xD8` để tắt LED.
4. Nếu dùng remote khác, cần bắt tín hiệu bằng oscilloscope/logic analyzer để
   xác định đúng `address`/`command` rồi sửa lại trong code.
