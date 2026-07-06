#include <stdio.h>
#include <stdlib.h>

// 

// Convension: các giá trị được để trong dấu ngoặc đơn ' là ngẫu nhiên, ko trùng lặp
// keyword: datatype của ô địa chỉ 

void main() {
  // tạo 1 biến a, gán biến a = 3, sau đó biến a sẽ được phân bổ 1 ô memory, gọi ô memory đó là 'A'
  // ô memory 'A' đó sẽ lưu value 3 vào trong nó
  int a = 3;

  // tạo 1 biến b. Biến b là con trỏ (pointer). Nên biến b chỉ có thể lưu address value của 1 ô memory (address value là ngẫu nhiên), ko phải là 1 giá trị đại số cố định
  // sau đó biến b sẽ được phân bổ (allocate) 1 ô địa chỉ memory 'B' ngẫu nhiên
  // ô memory 'B' đó sẽ lưu address value của ô memory 'A' vào trong nó
  int *b = &a;

  // Ở đây sẽ ra cùng 1 giá trị 
  // tại vì các bước phiên dịch thằng *&a sẽ từ phải qua trái:
  // đầu tiên phép '&' sẽ lấy địa chỉ thằng a, sau đó '*' sẽ lại trích xuất giá trị ở vị trí đó
  printf("%d, %d\n", a, *&a);

  int **c;
  // Ở đây c sẽ là con trỏ: "c points to the pointer b which points to the int a"
  c = &b;

  printf("%d, %d, %d\n", a, *b, *(*c));
}