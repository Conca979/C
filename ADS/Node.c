#include <stdio.h>
#include <stdlib.h>

// Định nghĩa cấu trúc của một Node trong Linked List
typedef struct Node {
  int val;             // Thành phần dữ liệu (4 bytes)
  struct Node *next;   // Con trỏ lưu địa chỉ của Node tiếp theo (8 bytes)
} Node;                // Sử dụng typedef để đặt bí danh là 'Node', tránh lặp lại từ khóa 'struct'

// Trường hợp 1: Khai báo thủ công từng Node một trong hàm main (Cấp phát tĩnh trên Stack)
int main() {
    // 1. Khởi tạo con trỏ quản lý danh sách liên kết
    Node *head = NULL; 
    // Khai báo con trỏ 'head' kiểu Node*. Ban đầu gán bằng NULL (0x0) để biểu diễn danh sách rỗng.

    // 2. Cấp phát tĩnh 3 Node trên Stack
    Node A; // Trình biên dịch giữ 16 bytes trên Stack cho Node A tại địa chỉ 00000076F9DFFD70
    Node B; // Trình biên dịch giữ 16 bytes trên Stack cho Node B tại địa chỉ 00000076F9DFFD60
    Node C; // Trình biên dịch giữ 16 bytes trên Stack cho Node C tại địa chỉ 00000076F9DFFD50

    // 3. Gán giá trị dữ liệu cho từng Node
    A.val = 1; // Gán thành phần 'val' của Node A bằng 1
    B.val = 2; // Gán thành phần 'val' của Node B bằng 2
    C.val = 3; // Gán thành phần 'val' của Node C bằng 3

    // 4. Thực hiện liên kết các Node bằng con trỏ
    printf("%p\n", &A); 
    // In địa chỉ của Node A (Kết quả chạy thực tế: 00000076F9DFFD70)
    
    head = &A;          
    // Cho con trỏ 'head' lưu địa chỉ của A. Lúc này, 'head' chính thức trỏ vào phần tử đầu tiên (Node A).

    printf("%p\n", &B); 
    // In địa chỉ của Node B (Kết quả chạy thực tế: 00000076F9DFFD60)

    A.next = &B;        
    // Gán địa chỉ của B cho con trỏ 'next' của A. Node A và Node B đã được liên kết với nhau.

    printf("%p\n", &C); 
    // In địa chỉ của Node C (Kết quả chạy thực tế: 00000076F9DFFD50)

    B.next = &C;        
    // Gán địa chỉ của C cho con trỏ 'next' của B. Node B và Node C đã được liên kết với nhau.

    C.next = NULL;      
    // Gán con trỏ 'next' của C bằng NULL. Đây là Node cuối cùng (Tail Node), đánh dấu điểm kết thúc của chuỗi.

    // 5. Truy cập và in dữ liệu gián tiếp qua con trỏ 'head'
    // Toán tử mũi tên '->' thực hiện đồng thời 2 bước: giải tham chiếu (*) và truy cập thành viên (.)
    
    printf("A.val = %d\n", head->val);
    // head->val tương đương (*head).val. Truy cập trực tiếp vào giá trị của Node A thông qua head. Kết quả: 1.

    printf("B.val = %d\n", head->next->val);
    // head->next lấy địa chỉ của B (&B). Tiếp tục truy cập ->val để lấy giá trị của Node B. Kết quả: 2.

    printf("C.val = %d\n", head->next->next->val);
    // head->next->next lấy địa chỉ của C (&C). Tiếp tục truy cập ->val để lấy giá trị của Node C. Kết quả: 3.

    return 0;
}