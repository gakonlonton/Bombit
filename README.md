# Bombit
Một dự án nhỏ cho bài tập lớn khóa học Lập trình nâng cao.

## Hướng dẫn cài đặt và chạy chương trình
- Bước 1: Download tệp nén của repo này về máy.
- Bước 2: Giải nén tệp vừa tải.
- Bước 3: Chạy chương trình bằng cách copy file `Bomb IT.exe` trong `bin/Debug/Bomb IT.exe` hoặc mở project với phần mềm `Codeblock` và sử dụng chức năng `Build and Run` (F9).

## Mô tả chung về trò chơi
- Trò chơi được lấy cảm hứng từ trò `Bomb Online`, người chơi sẽ điều khiển nhân vật của mình đặt bom với mục tiêu tiêu diệt tất cả các người chơi máy để tiến tới level cao hơn. Có chế độ chơi đơn (1 người) hoặc chơi đôi (2 người).
- Trong suốt quá trình chơi, người chơi có thể di chuyển nhân vật, đặt bom để phá vỡ các bức tường trắng hoặc tiêu diệt người chơi máy, hoặc thu thập các vật phẩm giúp gia tăng sức mạnh của bản thân.

## Các chức năng đã cài đặt
- Có chế độ chơi dành cho 2 người.
- Có thể chơi lại nhiều lần.
- Người chơi máy sẽ sinh ngẫu nhiên sau mỗi lần chơi.
- Có chức năng máy có thể đặt bom như người chơi.
- Có âm thanh menu, âm thanh loading và âm thanh khi chơi.

_Demo_

- [Video Demo](https://youtu.be/ZGt3GjvbOgk)
 ![Menu](https://user-images.githubusercontent.com/91715559/170541441-102285aa-5e1c-40a3-b568-0bcfa2f26810.png)
 ![Game Mode](https://user-images.githubusercontent.com/91715559/170541797-7a466ced-0875-4664-a18c-782551138bfa.png)
 ![Gameplay](https://user-images.githubusercontent.com/91715559/170542480-01608008-92e8-48bd-a85f-f5a350666a10.png)

## Các kĩ thuật đã sử dụng
- **Xử lý chuột:** 
  - Bắt phím với `SDL_PollEvent()`
  - Xử lý sự kiện với `SDL_Event`
- **Con trỏ:**
- **Class:**
  - Các Class `Display` quản lý phần hiển thị lên màn hình.
  - Các Class `Entity` quản lý thông số của các đối tượng có trong trò chơi như: **Player**, **Enemy**, **Bomb**, **Pickup**,...
  - Các Class `Manager` quản lý cách hoạt động của các đối tượng có trong trò chơi như: **Player**, **Enemy**, **Bomb**, **Pickup**,...
  - Các Class `Destroyer` quản lý chức năng phá hủy/tiêu diệt trong game như **Phá tường**,...
  - Các Class `System` xử lý các thông số hệ thống và delay hoạt ảnh, bộ đếm giờ,...
- **Đồ hoạ:**
  - Thư viện `SDL_image.h` để load và hiển thị ảnh và chi tiết trong trò chơi.
  - Thư viện `SDL_mixer.h` xử lý và phát âm thanh nền.
  - Thư viện `SDL_ttf.h` để tải và hiển thị font chữ riêng cho trò chơi.

## Định hướng phát triển game
- Nâng cấp Máy trở nên thông minh hơn
- Thêm Cài đặt tùy chỉnh các yếu tố trong game như Âm lượng, độ sáng, độ khó tăng dần.
- Thêm nhiều Level.
- Thêm các Nâng cấp mới: Bom nổ rộng, Máy di chuyển chậm hơn,...

## Tự đánh giá: 9.5/10
- Dự án lần này đã giúp em học thêm rất nhiều điều mới, từ khâu quản lý các đối tượng trong game, tìm tòi các thư viện mới và cách sử dụng chúng, quản lý và chia file các code cho khoa học, bug code cũng như giúp em cải thiện cách code của mình. Dự án cũng giúp em rèn luyện phẩm chất của một developer như kiên trì, tỉ mỉ và ham học hỏi. Em xin được gửi lời cảm ơn sâu sắc tới các thầy Đỗ Minh Khá, thầy Trần Quốc Long và thầy Nguyễn Việt Anh đã giảng dạy và giúp đỡ em hoàn thành dự án này. Em xin tiếp thu tất cả những góp ý của mọi người để cải thiện các khuyết điểm và hoàn thành bản thân.
