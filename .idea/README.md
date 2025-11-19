# Đồ án CARO

Đây là kho lưu mã nguồn của đồ án, tuyệt đối không được chia sẻ mã nguồn lung tung hay phát tán cho bất cứ nhóm nào khác.

Quy định:
- Không tùy tiện sửa code trên branch chính, nếu muốn sửa thì phải hỏi;
- Khi muốn sửa code, hãy tạo một branch mới và code trên đó để không ảnh hưởng đến code của người khác, khi đã hoàn thành thì hãy tạo pull request để merge vào branch chính.

# Quy ước code

## Cấm sử dụng `using namespace std;`

Namespace là không gian tên trong C++, nó được tạo ra để tránh việc khai báo trùng tên biến, hàm, hoặc đối tượng v.v. bằng cách gộp chúng
vào một không gian tên. Ví dụ, hai hàm cùng tên ở hai namespace khác nhau khi sử dụng sẽ không gây ra xung đột bởi máy có thể phân biệt chúng.
`namespace std` là vùng không gian tên chứa toàn bộ tên của các đối tượng trong bộ thư viện chuẩn của C++.
Thêm dòng lệnh `using namespace std;` có khả năng gây xung đột và ta không nên sử dụng nó.

Đọc thêm ở: https://www.programiz.com/cpp-programming/std-namespace

## Cấm sử dụng mô hình lập trình hướng đối tượng

Đây là yêu cầu của đồ án.

Ví dụ:
```cpp
// CẤM!
class Matrix {
	...
};

int main() {
	...
	Matrix mat {};
	mat.change(...);
	...
}

// Thay vào đó, hãy sử dụng kiểu cấu trúc:
struct Matrix { // <- Cái này OK!
	...
};

void change(Matrix &mat) {
	...
}

int main() {
	Matrix mat;
	change(mat);
}
```

## Hãy sử dụng `std::array` thay cho mảng kiểu C
Tốt nhất, đừng bao giờ đụng tới mảng kiểu C vì nó cũ, lạc hậu, và đặc biệt nhất là **nguy hiểm**.

Để giải quyết cho những vấn đề và mảng kiểu C, người ta đã tạo ra `std::array`.

[Lý do](https://stackoverflow.com/a/77106115) vì sao thì vô vàn, nhưng 2 lý do chính ở đây có vẻ là quan trọng nhất:

### 1. An toàn hơn
Mảng kiểu C cho phép bạn truy cập những phần tử nằm ngoài nó và điều đó **cực kỳ nguy hiểm**.

Ví dụ, code dưới đây chạy như thường mà không bị lỗi:
```cpp
int main() {
	int p[5];
	std::cout << p[7]; // <- giá trị in ra sẽ là một giá trị rác, không đoán trước được hành vi
}
```

<img width="1062" height="409" alt="image" src="https://gist.github.com/user-attachments/assets/0e64dd42-a11c-46d6-aa79-652443a49f7c" />


Nhưng đối với `std::array`, điều tương tự sẽ khiến chương trình báo lỗi.
```cpp
int main() {
	std::array<int, 5> array {};
	std::cout << array.at(7); // <- lỗi, chương trình tự ngắt
}
```

<img width="1328" height="866" alt="image" src="https://gist.github.com/user-attachments/assets/ce2eee5e-b89e-408b-9987-700f1e4b6efb" />

Không chỉ vậy mà ta còn có thể viết thêm code để xử lý trường hợp lỗi, có thể dùng để thông báo ở đoạn code nào gây nên lỗi đó.
```cpp
int main() {
	std::array<int, 5> array {};

	try {
		std::cout << array.at(7);
	} catch(std::out_of_range &e) {
		std::cerr << "ERROR! Index out of range!!!" << '\n';
		std::cerr << e.what();
	}
}
```

<img width="1227" height="570" alt="image" src="https://gist.github.com/user-attachments/assets/b6f910b7-a164-4aa3-8dad-4fe1fc7d9366" />

Điều này hữu dụng khi code trở nên rất dài và việc truy vết xem lỗi nằm ở đâu sẽ rất vất vả, thế nên sử dụng theo cách này sẽ tiết kiếm được rất nhiều thời gian.

### 2. Sử dụng tiện và an toàn hơn khi truyền vào hàm để xử lý
Màng kiểu C sẽ tự động bị phân rã thành con trỏ khi truyền vào hàm dưới dạng tham số. Đây là điều ta không nên bao giờ làm bởi nếu không biết rõ mình đang làm gì thì code dễ bug.
<br>
Thay vào đó, hãy sử dụng `std::array`:
```cpp
std::array<int, 5> array {};

void f(std::array<int, 5>& array) {
	// làm gì đó với array...
}
```

## Quy ước đặt tên
- Tên biến phải được đặt theo kiểu snake\_case;
- Tên hằng số (`const`) phải được viết hoa toàn bộ và dùng snake\_case;
- Tên hàm phải được đặt theo kiểu camelCase;
- Tên của kiểu cấu trúc phải được đặt theo PascalCase.
- Mọi tên đều sử dụng tiếng Anh;
- Tên biến phải phản ánh rõ nó dùng để làm gì;
- Têm hàm phải phản ánh rõ nó làm gì;
- Thà đặt dài nhưng nói lên được mục đích thay vì đặt ngắn mà ý nghĩa mơ hồ;

- **Hãy viết sao cho code nhìn vào có thể hiểu ngay mà không cần một dòng comment để giải thích nó làm gì;**
- Nếu thật sự cần comment, hãy viết lý do vì sao lại thiết kế như vậy.

Tham khảo ở: https://www.freecodecamp.org/news/snake-case-vs-camel-case-vs-pascal-case-vs-kebab-case-whats-the-difference/

Ví dụ
```cpp
// ở đây classroom được coi như là một từ nên ta viết như một từ
struct Classroom {
	const size_t NUMBER_OF_STUDENTS = 1001;
	std::array<int, NUMBER_OF_STUDENTS> student_ids {};
	...
};

void fillStudentIDsWithZero(Classroom &classroom) {
	for (auto &id : classroom.student_ids) {
		id = 0;
	}
}

void assignStudentIDAtIndex(ClassRoom &classroom, const int ID, const size_t index) {
	try {
		student_ids.at(index) = ID;
	} catch (std::out_of_range &e) {
		std::cerr << "Unable to assign student ID at index: " << index << '\n';
		std::cerr << e.what();
	}
}

int main() {
	Classroom classroom_25ctt3 {};
	fillStudentIDSWithZero(classroom_25ctt3);
	assignStudentIDAtIndex(classroom_25ctt3, 25126969, 6);
	assignStudentIDAtIndex(classroom_25ctt3, 25124204, 9);
	...

	return 0;
}
```