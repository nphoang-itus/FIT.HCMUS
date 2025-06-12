Stack (ngăn xếp) là một cấu trúc dữ liệu rất quen thuộc và có nhiều ứng dụng quan trọng trong tin học.
Stack chứa một danh sách các phần tử, tương tự như mảng, danh sách liên kết, nhưng hoạt động theo cơ chế LIFO (Last In First Out, phần tử nào đưa vào sau cùng thì phải được lấy ra đầu tiên và ngược lại).
Trong môn Kỹ thuật lập trình, Cấu trúc dữ liệu, sinh viên đã được giới thiệu về Stack và có 2 cách cài đặt stack là dùng mảng hoặc dùng danh sách liên kết. 
Lưu ý: sinh viên không được sử dụng các lớp stack, queue có sẵn trong C++.

#### a)	(0.5 điểm) Hãy khai báo một lớp trừu tượng (abstract class) đóng vai trò như một interface, đặt tên là IStack, để quản lý một stack chứa các số nguyên, có 4 hàm thuần ảo:
##### i.	void push(x): thêm 1 phần tử vào trong stack.
##### ii.	int pop(): xóa một phần tử trên đỉnh stack, ra khỏi stack, trả về phần tử được xóa.
##### iii.	int size(): cho biết số phần tử hiện tại đang có trong stack.
##### iv.	void clear(): xóa rỗng stack.
 
#### b)	(0.5 điểm) Hãy khai báo một lớp StackByLinkedList, kế thừa interface IStack ở trên, trong đó sẽ cài đặt stack bằng cách sử dụng một danh sách liên kết đơn bên trong.
 
#### c)	(1 điểm) Hãy cài đặt các hàm push(x), pop(), size(), clear() và các hàm liên quan cho class StackByLinkedList.
 
#### d)	(1 điểm) Thao tác pop() có thể bị lỗi khi stack hiện tại đang rỗng. Hãy chỉnh sửa lại hàm int pop() bằng cách áp dụng cơ chế xử lý ngoại lệ (exception handling) đơn giản. Viết một đoạn code trong hàm main() để minh họa sử dụng hàm pop() trong trường hợp bình thường và trong trường hợp lỗi (và sử dụng exception handling để xử lý).