# Bài 6 — Serial Port (UART) trên N76E885

## Mục đích

Minh hoạ UART thứ 2 của N76E885 (`SCON_1`/`SBUF_1`, các tín hiệu có hậu tố
`_1`), dùng Timer 3 làm bộ tạo tốc độ Baud (19200 bps).

- `serial_port_uart_vd1.c` — Chỉ gửi (TX): gửi chuỗi `"Hello, world!"` 1 lần
  khi khởi động.
- `serial_port_uart_vd2.c` — Gửi + nhận (TX/RX): nhận ký tự qua UART, gõ `y`
  để bật LED, `n` để tắt LED.
- `serial_port_uart_vd3.c` — Kết hợp bài 5 (giải mã hồng ngoại NEC qua Input
  Capture) với UART: khi nhận được mã từ remote, gửi mã hex (address, mã đảo
  của address, command, mã đảo của command) ra UART để debug/quan sát trên
  máy tính.

## Sơ đồ đấu nối

- P2.4 (RXD_1) và P2.5 (TXD_1): nối tới module USB-UART (ví dụ CP2102, FTDI)
  để giao tiếp với máy tính. Chú ý chéo TX/RX: TXD_1 của board nối RX của
  module USB-UART và ngược lại.
- `serial_port_uart_vd2.c`: thêm LED P0.4 (active-low) như bài 2.
- `serial_port_uart_vd3.c`: thêm mắt thu hồng ngoại ở P2.2 như bài 5.

## Cách chạy thử

1. Mở `.cbp` tương ứng trong thư mục con của ví dụ đó (ví dụ `serial_port_uart_vd1/serial_port_uart_vd1.cbp`) bằng Code::Blocks (compiler SDCC).
2. Build, nạp vào board N76E885.
3. Mở phần mềm terminal (PuTTY, Tera Term, Arduino Serial Monitor...) ở tốc độ
   **19200 8N1**.
4. `vd1`: thấy dòng chữ "Hello, world!" xuất hiện 1 lần sau khi cấp nguồn.
5. `vd2`: gõ `y`/`n` trên terminal để bật/tắt LED.
6. `vd3`: bấm nút trên remote hồng ngoại, quan sát mã hex được in ra terminal.
