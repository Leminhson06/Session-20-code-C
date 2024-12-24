#include <stdio.h>
#include <string.h>

#define MAX_PRODUCTS 100

struct Product {
    int id;
    char name[100];
    float purchasePrice;
    float sellingPrice;
    
    int quantity;
};
void printProduct(struct Product p) {
    printf("Mã sản phẩm: %d\n", p.id);
    printf("Tên sản phẩm: %s\n", p.name);
    printf("Giá nhập: %.2f\n", p.purchasePrice);
    printf("Giá bán: %.2f\n", p.sellingPrice);
    printf("Số lượng: %d\n", p.quantity);
    printf("-----------------------------\n");
}
void inputProduct(struct Product *p) {
    printf("Nhập mã sản phẩm: ");
    scanf("%d", &p->id);
    getchar();
    printf("Nhập tên sản phẩm: ");
    fgets(p->name, sizeof(p->name), stdin);
    printf("Nhập giá nhập: ");
    scanf("%f", &p->purchasePrice);
    printf("Nhập giá bán: ");
    scanf("%f", &p->sellingPrice);
    printf("Nhập số lượng: ");
    scanf("%d", &p->quantity);
}
void displayProducts(struct Product products[], int count) {
    if (count == 0) {
        printf("Chưa có sản phẩm nào trong danh sách.\n");
        return;
    }
    for (int i = 0; i < count; i++) {
        printProduct(products[i]);
    }
}

void addProduct(struct Product products[], int *count, struct Product newProduct) {
    for (int i = 0; i < *count; i++) {
        if (products[i].id == newProduct.id) {
            products[i].quantity += newProduct.quantity;
            return;
        }
    }
    if (*count < MAX_PRODUCTS) {
        products[*count] = newProduct;
        (*count)++;
    } else {
        printf("Danh sách sản phẩm đã đầy!\n");
    }
}

void updateProduct(struct Product products[], int count, int productId) {
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (products[i].id == productId) {
            printf("Cập nhật thông tin sản phẩm:\n");
            inputProduct(&products[i]);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Không tìm thấy sản phẩm với mã %d\n", productId);
    }
}
void sortProductsByPrice(struct Product products[], int count, int ascending) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if ((ascending && products[i].sellingPrice > products[j].sellingPrice) || 
                (!ascending && products[i].sellingPrice < products[j].sellingPrice)) {
                struct Product temp = products[i];
                products[i] = products[j];
                products[j] = temp;
            }
        }
    }
    printf("Danh sách sản phẩm đã được sắp xếp theo giá.\n");
}
void searchProductByName(struct Product products[], int count, const char *name) {
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strstr(products[i].name, name) != NULL) {
            printProduct(products[i]);
            found = 1;
        }
    }
    if (!found) {
        printf("Không tìm thấy sản phẩm với tên chứa \"%s\"\n", name);
    }
}
void sellProduct(struct Product products[], int *count, int productId, int quantity, float *revenue) {
    int found = 0;
    for (int i = 0; i < *count; i++) {
        if (products[i].id == productId) {
            if (products[i].quantity == 0) {
                printf("Sản phẩm đã hết hàng.\n");
                return;
            }
            if (quantity > products[i].quantity) {
                printf("Không còn đủ hàng.\n");
            } else {
                // Giảm số lượng sản phẩm trong kho và tăng doanh thu
                products[i].quantity -= quantity;
                *revenue += quantity * products[i].sellingPrice;
                printf("Đã bán %d sản phẩm %s. Doanh thu tăng %.2f.\n", quantity, products[i].name, quantity * products[i].sellingPrice);
            }
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Không tìm thấy sản phẩm với mã %d\n", productId);
    }
}

int main() {
    struct Product products[MAX_PRODUCTS];
    int count = 0;
    float revenue = 0.0;
    int choice, quantity, productId;
    struct Product newProduct;
    char searchName[100];

    while (1) {
        // Hiển thị menu
        printf("\nMENU\n");
        printf("1. Nhập số lượng và thông tin sản phẩm.\n");
        printf("2. Hiển thị danh sách sản phẩm.\n");
        printf("3. Nhập sản phẩm.\n");
        printf("4. Cập nhật thông tin sản phẩm.\n");
        printf("5. Sắp xếp sản phẩm theo giá (Tăng/giảm).\n");
        printf("6. Tìm kiếm sản phẩm.\n");
        printf("7. Bán sản phẩm (có thể nhập số lượng cần bán).\n");
        printf("8. Doanh thu hiện tại.\n");
        printf("9. Thoát\n");
        printf("Lựa chọn của bạn: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Nhập số lượng sản phẩm: ");
                scanf("%d", &count);
                for (int i = 0; i < count; i++) {
                    printf("Nhập thông tin sản phẩm thứ %d:\n", i + 1);
                    inputProduct(&products[i]);
                }
                break;

            case 2:
                displayProducts(products, count);
                break;

            case 3:
                printf("Nhập thông tin sản phẩm cần nhập:\n");
                inputProduct(&newProduct);
                addProduct(products, &count, newProduct);
                break;

            case 4:
                printf("Nhập mã sản phẩm cần cập nhật: ");
                scanf("%d", &productId);
                updateProduct(products, count, productId);
                break;

            case 5:
                printf("Chọn kiểu sắp xếp (1: Tăng, 2: Giảm): ");
                scanf("%d", &choice);
                if (choice == 1) {
                    sortProductsByPrice(products, count, 1);  
                } else if (choice == 2) {
                    
                } else {
                    printf("Lựa chọn không hợp lệ.\n");
                }
                break;

            case 6:
                getchar(); 
                printf("Nhập tên sản phẩm cần tìm: ");
                fgets(searchName, sizeof(searchName), stdin);
                searchName[strcspn(searchName, "\n")] = 0;  
                searchProductByName(products, count, searchName);
                break;

            case 7:
                printf("Nhập mã sản phẩm cần bán: ");
                scanf("%d", &productId);
                printf("Nhập số lượng cần bán: ");
                scanf("%d", &quantity);
                sellProduct(products, &count, productId, quantity, &revenue);
                break;

            case 8:
                printf("Doanh thu hiện tại: %.2f\n", revenue);
                break;

            case 9:
                printf("Thoát chương trình.\n");
                return 0;

            default:
                printf("Lựa chọn không hợp lệ.\n");
        }
    }

    return 0;
}
