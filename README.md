
# Brick Banger
- Giới Thiệu Game

 Đây là trò chơi phá gạch đã phổ biến từ rất lâu, người chơi điều khiển đĩa bay đỡ phóng và phá những viên gạch.
 Giới thiệu về vòng chơi phổ thông:
-Quả bóng sẽ bay theo bất kỳ hướng nào mà bạn chạm vào

-Tìm đúng chính xác vị trí và góc độ tối ưu để phá từng viên gạch

-Lên cấp bằng cách phá bỏ các viên gạch trên màn hình

-Khi phá gạch bạn chớ để gạch chạm vào phần đáy


-  Bắt đầu game
-  Các thành phần trong game
-  Cách chơi
-  Thư viện đã sử dụng
-  Nguồn tham khảo
-  Sự khác biệt và cải tiến
 
   
    

## Bắt đầu game
## 
Bấm vào New game để bắt đầu 
![Screenshot 2024-08-10 004023](https://github.com/user-attachments/assets/b2710f74-c8b5-42e8-89a3-1a342e3c80ae)


Bạn có thể chọn mục editor để chọn level muốn chơi 
![Screenshot 2024-08-10 004123](https://github.com/user-attachments/assets/614d2951-1ccf-4689-9783-dca6271e5446)

hoặc tự custom màn chơi mới

![Screenshot 2024-08-10 004138](https://github.com/user-attachments/assets/79979faa-d2b0-475e-95eb-db4d890aa9e9)
## Các Thành Phần Game
Background
![Screenshot 2024-08-10 003900](https://github.com/user-attachments/assets/71ff5cb4-d166-4aeb-b18e-cd51c21c3aa0)

Bóng: Lúc bình thường (màu xanh) - lúc nhặt được ultimate (màu đỏ)
![Screenshot 2024-08-10 003925](https://github.com/user-attachments/assets/1959cbbd-f243-4139-8295-8976d690fabd)

Bảng tọa độ (Border)
![Screenshot 2024-08-10 003936](https://github.com/user-attachments/assets/ca122cf9-e03a-47ac-88ad-e75c1369f895)

Các màu và 12 level của gạch
![Screenshot 2024-08-10 003948](https://github.com/user-attachments/assets/92e39848-8a53-4179-a27b-779b05bb337d)

Các ultimate
![Screenshot 2024-08-10 004002](https://github.com/user-attachments/assets/eb976dd4-1702-443c-b8fb-386e0780f77d)

## Cách chơi

- Cách 1: Điều khiển bằng Chuột
Điều hướng sang 2 bên bằng con chuột, bắn quả bóng đi bằng chuột trái

- Cách 2: Điều khiển bằng Bàn Phím
Điều hướng sang 2 bên bằng 2 phím mũi tên <-- và -->, bắn quả bóng đi bằng bút Space
## Quá trình phát triển

1.Những hình ảnh thô 

![Screenshot 2024-08-02 014747](https://github.com/user-attachments/assets/ad542caf-0e90-45e3-9cb9-74f818b20471)

2.Chạy được đĩa bay - chưa code xong phần quỹ đạo bay

![Screenshot 2024-08-02 014801](https://github.com/user-attachments/assets/6d443ecc-5374-42e2-9bfc-923cb30c2590)

3.Hoàn thành quỹ đạo bay, góc bật

![Screenshot 2024-08-02 014817](https://github.com/user-attachments/assets/67cb49ee-3d4d-44d7-9911-dd3cc5682503)

4.Hoàn thiện game - hoàn thành tính năng tự custom level gạch và level màn chơi

![Screenshot 2024-08-09 024933](https://github.com/user-attachments/assets/96c7d1cd-0595-4e5a-95bd-79a6ef530423)
## Source Code

- Folder Resources:
Chứa tất cả các hình ảnh của game bao gồm cả font chữ, Bóng, đĩa bay, ultimate....

- Folder header: include tất cả các thư viện, using name space, khai báo tất cả các hàm

- Folder Source: Chứa code game, lời gọi file, cài đặt config


## Thư viện đã sử dụng
- Sử dụng thư viện SFML 2.6.1
- Sử dụng nhiều class, vector, tách file, nạp chồng toán tử, ...
- Xử lý thời gian, thao tác chuột và bàn phím, âm thanh, hình ảnh, chữ.
- Dùng các kiến thức toán học để tính toán được các góc bật và chạm bóng
- Tạo menu và các nút ấn di chuyển giữa các menu
- Sử dụng các kĩ thuật edit và cắt ghép để có thể lấy được hình ảnh từ game gốc
## Nguồn tham khảo
- Tham khảo cách tách file và cách load hình ảnh và map trên "Blogluyencode" - "Tech28" - "CLB lap trinh PTIT"

- Tham khảo các game, hướng dẫn làm game trên: "gamedevspot.net" - "https://www.youtube.com/watch?v=2Aix57fpRME&list=PLjJmj2FyqToa3kzYqusZxiVHfCg3dpOLu&index=1"

- Tham khảo code hương bay và góc tiếp xúc của bóng: "https://www.youtube.com/watch?v=zYFV7jpaxec"

- Tham khảo hướng dẫn làm game sử dụng sfml: "https://www.youtube.com/watch?v=mdp9neFHXY8&list=PL8YBKOHPqM68Ia0LE590qq0w6jKR0fJvd&index=1"

- Tham khảo code và học một số ultimate của bóng: "https://github.com/khoavpt/Brick-Breaker?tab=readme-ov-file"

- Hình ảnh và các vật thể trong game tự phát triển và vẽ trên nền đồ họa sfml


## Sự khác biệt và cải tiến

- Custom được map

- Custom được Level của các viên gạch

- Add thêm các ultimate

- Add thêm các sound riêng cho các hành động
