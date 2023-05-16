
<h1 align="center">
    Blood 'n Katana
</h1>

<td align="center">
      Blood and Katana là một dự án game đơn giản với vai trò là bài tập lớn của lớp học INT2215 (Lập trình nâng cao) thuộc chương trình giảng dạy của trường Đại học Công Nghệ - ĐHQGHN (VNU University of Engineering and Technology) 
</td>

## Ngôn Ngữ Lập Trình

- C++
- Thư viện đồ họa SDL2
- Parser TinyXML

## Tải Xuống

### Windows
1. Kéo dự án về tài khoản Github cá nhân bằng Fork
2. Clone dự án về máy tính local bằng lệnh `git clone https://github.com/[USER_NAME]/Blood-n-Katana`
3. Bạn có thể tải trực tiếp về nếu không muốn sử dụng github và command line
4. Tại đây bạn có 2 lựa chọn 
  - Mở thư mục và chạy tệp thực thi (BND.exe)
  - Sử dụng source code và compile:
    + Cài đặt [Visual Studio Code](https://code.visualstudio.com/download) 
    + Thư viện SDL2 đã được cài đặt sẵn bản 64bit, bản 32bit ở trong thư mục x86_bin
    + Parser TinyXML đã được cài đặt sẵn
    + Cài đặt [Mingw](https://www.mingw-w64.org/downloads/) 32 hoặc 64 bit
    + Compile code sử dụng lệnh `mingw32-make`

### MacOS và Linux
... chưa cập nhật ...

## Hướng Dẫn Chơi

### CONTROL:      

* A(Left Arrow) to Run left

* D(Right Arrow) to Run Right

* W(Up Arrow) to Jump

* S(Down Arrow) to Protect

* J(NP1) to Normal Attack

* K(NP2) to Heavy Attack

* L(NP3) to Quick Attack

                                                         
### GAMEPLAY:                             
* Objective:
    -Kill the Countess
    -Kill 10 Skeletons
* Game:
    -The Skeletons spawn randomly on the map
    -After you kill the 4th Skeleton the Countess will spawn
    -The Skeletons will spawn randomly around the Countess
    -You will lose if your HP reach 0
    
## Tính năng
Bắt đầu game mới
Tạm dừng nhạc
Tạm dừng game
Chơi lại sau khi kết thúc game
    
## Ý Tưởng
Thể loại game Roguelike kinh điển

## Vấn Đề Hiện Tại

- Code còn sử dụng một số Magic Number
- Một số phần chưa được chia Module thực sự triệt để
- Sử dụng thừa class, include thừa mứa
- Sử dụng Hitbox hình chữ nhật làm hạn chế khả năng đa dạng của map và các hành động của nhân vật

## Hướng đi trong tương lai 
- Thêm màn chơi và nhân vật, chiêu thức đa dạng
- Thêm Radio chọn nhạc phù hợp với mood của người chơi
- Cải thiện chuyển động và điều khiển của bot để thông minh hơn
- Cải thiện chuyển động của người chơi

## Kết luận

### Việc tự thực 1 dự án lập trình như thế này giúp mình mở mang thêm nhiều kiến thức:
- Hiểu được mô hình phát triển 1 phần mềm kiểu thác nước: Phân tích, thiết kế, lập trình, kiểm thử, bảo trì.
- Cách dùng git và github
- Tư duy đặt ra và giải quyết vấn đề
- Nắm rõ hơn về class, pointer, syntax C++
- Hiểu một phần về OOP
- Hiểu thêm cách lưu trữ dữ liệu bằng các kiểu file khác nhau
- Tìm và fix bug


## Nguồn Tham Khảo
- [Parser TinyXML](https://github.com/leethomason/tinyxml2)
- [Madsycode](https://www.youtube.com/playlist?list=PL-K0viiuJ2RctP5nlJlqmHGeh66-GOZR_)
- [craftpix.net](https://craftpix.net/)
- Nhạc [Gokuraku Joudo - GARNiDELiA](https://music.youtube.com/watch?v=-JzIBUHot4M&feature=share)

## Liên Hệ

- Email: thewdrag@gmail.com
- Facebook: https://www.facebook.com/Vinh.a.k.a.Complex1ty/

## Xin cảm ơn sự quan tâm của bạn đến project nho nhỏ của mình 😺
