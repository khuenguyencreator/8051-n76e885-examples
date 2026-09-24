# 8051 N76E885 Examples

Code minh hoạ cho serie blog "Lập trình Nuvoton" trên chip **Nuvoton N76E885**
(8051 lõi 1T), build bằng **SDCC** + **Code::Blocks** (không dùng Keil C51).

## Cấu trúc

- `bai_1_header_file/` — Header SFR dùng chung (`N76E885.h`, `Define.h`) cho
  toàn bộ các bài.
- `bai_2_gpio/` → `bai_11_1wire_ds18b20/` — Mỗi thư mục tương ứng 1 bài viết
  trên blog, gồm `README.md` (mô tả mục đích, sơ đồ đấu nối, cách chạy thử)
  và các thư mục con là ví dụ code (ví dụ `gpio_vd1/`), mỗi ví dụ có 1 file
  `.c` và 1 file project Code::Blocks (`.cbp`).

## Cách tải về và sử dụng

1. Tải repo:
   ```
   git clone https://github.com/khuenguyencreator/8051-n76e885-examples.git
   ```
2. Cài [SDCC](https://sdcc.sourceforge.net/) — trình biên dịch C cho 8051
   (Windows: `winget install SDCC.SDCC`).
3. Cài [Code::Blocks](https://www.codeblocks.org/downloads/binaries/) — IDE để
   mở và build project (Windows: `winget install CodeBlocks.CodeBlocks`).
4. Trong Code::Blocks, vào Settings > Compiler, đảm bảo có compiler **SDCC**
   trỏ đúng đường dẫn cài đặt (nếu Code::Blocks chưa tự nhận, tạo compiler mới
   trỏ tới `sdcc.exe`).
5. Mở file `.cbp` của ví dụ muốn chạy (ví dụ
   `bai_2_gpio/gpio_vd1/gpio_vd1.cbp`), Build (Ctrl+F9), rồi nạp file `.hex`
   vào board N76E885.

## Liên kết

- 📖 Bài viết hướng dẫn chi tiết: [khuenguyencreator.com](https://khuenguyencreator.com)
- 📚 Các repo khác: [github.com/khuenguyencreator](https://github.com/khuenguyencreator)

Nếu thấy hữu ích, hãy bấm ⭐ **Star** để ủng hộ nhé! Có lỗi hoặc thắc mắc, bạn tạo **Issue** trong repo này hoặc để lại bình luận trên blog.
