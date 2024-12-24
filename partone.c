#include <stdio.h>
#include <string.h>

#define MAX_BOOKS 100
struct Book {
    int id;
    char title[100];
    char author[100];
    float price;
    char genre[50];
};
void printBook(struct Book b) {
    printf("Mã sách: %d\n", b.id);
    printf("Tên sách: %s\n", b.title);
    printf("Tác giả: %s\n", b.author);
    printf("Giá tiền: %.2f\n", b.price);
    printf("Thể loại: %s\n", b.genre);
}
void inputBook(struct Book *b) {
    printf("Nhập mã sách: ");
    scanf("%d", &b->id);
    getchar(); 
    printf("Nhập tên sách: ");
    fgets(b->title, sizeof(b->title), stdin);
    printf("Nhập tác giả: ");
    fgets(b->author, sizeof(b->author), stdin);
    printf("Nhập giá tiền: ");
    scanf("%f", &b->price);
    getchar(); // Đọc ký tự newline
    printf("Nhập thể loại: ");
    fgets(b->genre, sizeof(b->genre), stdin);
}

void displayBooks(struct Book books[], int count) {
    if (count == 0) {
        printf("Chưa có sách nào trong danh sách.\n");
        return;
    }
    for (int i = 0; i < count; i++) {
        printBook(books[i]);
    }
}

void addBookAtPosition(struct Book books[], int *count, int position, struct Book newBook) {
    if (*count >= MAX_BOOKS) {
        printf("Danh sách sách đã đầy!\n");
        return;
    }
    if (position < 0 || position > *count) {
        printf("Vị trí không hợp lệ!\n");
        return;
    }

    for (int i = *count; i > position; i--) {
        books[i] = books[i - 1];
    }
    books[position] = newBook;
    (*count)++;
}

void deleteBookById(struct Book books[], int *count, int bookId) {
    int found = 0;
    for (int i = 0; i < *count; i++) {
        if (books[i].id == bookId) {
            for (int j = i; j < *count - 1; j++) {
                books[j] = books[j + 1];
            }
            (*count)--;
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Không tìm thấy sách với mã sách %d\n", bookId);
    }
}

void updateBookById(struct Book books[], int count, int bookId) {
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (books[i].id == bookId) {
            printf("Cập nhật thông tin sách:\n");
            inputBook(&books[i]);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Không tìm thấy sách với mã sách %d\n", bookId);
    }
}

void sortBooksByPrice(struct Book books[], int count, int ascending) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if ((ascending && books[i].price > books[j].price) || (!ascending && books[i].price < books[j].price)) {
                struct Book temp = books[i];
                books[i] = books[j];
                books[j] = temp;
            }
        }
    }
    printf("Danh sách sách đã được sắp xếp theo giá.\n");
}

void searchBookByTitle(struct Book books[], int count, const char *title) {
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strstr(books[i].title, title) != NULL) {
            printBook(books[i]);
            found = 1;
        }
    }
    if (!found) {
        printf("Không tìm thấy sách với tên chứa \"%s\"\n", title);
    }
}

int main() {
    struct Book books[MAX_BOOKS];
    int count = 0;
    int choice;
    int position, bookId;
    struct Book newBook;
    char searchTitle[100];

    while (1) {
        printf("\nMENU\n");
        printf("1. Nhập số lượng và thông tin sách.\n");
        printf("2. Hiển thị thông tin sách.\n");
        printf("3. Thêm sách vào vị trí.\n");
        printf("4. Xóa sách theo mã sách.\n");
        printf("5. Cập nhật thông tin sách theo mã sách.\n");
        printf("6. Sắp xếp sách theo giá (Tăng/giảm).\n");
        printf("7. Tìm kiếm sách theo tên sách.\n");
        printf("8. Thoát\n");
        printf("Lựa chọn của bạn: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Nhập số lượng sách: ");
                scanf("%d", &count);
                for (int i = 0; i < count; i++) {
                    printf("Nhập thông tin sách thứ %d:\n", i + 1);
                    inputBook(&books[i]);
                }
                break;

            case 2:
                displayBooks(books, count);
                break;

            case 3:
                printf("Nhập vị trí cần thêm sách (0 đến %d): ", count);
                scanf("%d", &position);
                if (position < 0 || position > count) {
                    printf("Vị trí không hợp lệ.\n");
                    break;
                }
                printf("Nhập thông tin sách cần thêm:\n");
                inputBook(&newBook);
                addBookAtPosition(books, &count, position, newBook);
                break;

            case 4:
                printf("Nhập mã sách cần xóa: ");
                scanf("%d", &bookId);
                deleteBookById(books, &count, bookId);
                break;

            case 5:
                printf("Nhập mã sách cần cập nhật: ");
                scanf("%d", &bookId);
                updateBookById(books, count, bookId);
                break;

            case 6:
                printf("Chọn kiểu sắp xếp (1: Tăng, 2: Giảm): ");
                scanf("%d", &choice);
                if (choice == 1) {
                    sortBooksByPrice(books, count, 1);  // Sắp xếp tăng dần
                } else if (choice == 2) {
                    sortBooksByPrice(books, count, 0);  // Sắp xếp giảm dần
                } else {
                    printf("Lựa chọn không hợp lệ.\n");
                }
                break;

            case 7:
                getchar(); // Đọc ký tự newline còn sót lại
                printf("Nhập tên sách cần tìm: ");
                fgets(searchTitle, sizeof(searchTitle), stdin);
                searchTitle[strcspn(searchTitle, "\n")] = 0;  // Xóa ký tự newline
                searchBookByTitle(books, count, searchTitle);
                break;

            case 8:
                printf("Thoát chương trình.\n");
                return 0;

            default:
                printf("Lựa chọn không hợp lệ.\n");
        }
    }

    return 0;
}
