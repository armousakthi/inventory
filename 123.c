#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITEMS 100
#define NAME_LENGTH 50

typedef struct {
    int id;
    char name[NAME_LENGTH];
    int quantity;
    float price;
} Item;

Item inventory[MAX_ITEMS];
int itemCount = 0;

// Function declarations
void addItem();
void viewInventory();
void searchItem();
void updateItem();
void deleteItem();
void calculateTotalValue();
void displayMenu();
int findItemByID(int id);

int main() {
    int choice;

    while (1) {
        displayMenu();
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a valid number.\n");
            while (getchar() != '\n'); // Clear input buffer
            continue;
        }

        switch (choice) {
            case 1: addItem(); break;
            case 2: viewInventory(); break;
            case 3: searchItem(); break;
            case 4: updateItem(); break;
            case 5: deleteItem(); break;
            case 6: calculateTotalValue(); break;
            case 7: 
                printf("Exiting the program. Goodbye!\n");
                return 0;
            default: printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}

void displayMenu() {
    printf("\n========== Inventory Management System ==========\n");
    printf("1. Add Item\n");
    printf("2. View Inventory\n");
    printf("3. Search Item\n");
    printf("4. Update Item\n");
    printf("5. Delete Item\n");
    printf("6. Calculate Total Inventory Value\n");
    printf("7. Exit\n");
    printf("=================================================\n");
}

void addItem() {
    if (itemCount >= MAX_ITEMS) {
        printf("Inventory is full. Cannot add more items.\n");
        return;
    }

    Item newItem;
    printf("Enter item ID: ");
    scanf("%d", &newItem.id);

    // Check for duplicate ID
    if (findItemByID(newItem.id) != -1) {
        printf("Item with ID %d already exists.\n", newItem.id);
        return;
    }

    printf("Enter item name: ");
    getchar(); // Clear newline character
    fgets(newItem.name, NAME_LENGTH, stdin);
    newItem.name[strcspn(newItem.name, "\n")] = '\0'; // Remove trailing newline

    printf("Enter item quantity: ");
    scanf("%d", &newItem.quantity);

    printf("Enter item price: ");
    scanf("%f", &newItem.price);

    inventory[itemCount++] = newItem;
    printf("Item added successfully.\n");
}

void viewInventory() {
    if (itemCount == 0) {
        printf("Inventory is empty.\n");
        return;
    }

    printf("\nID\tName\t\tQuantity\tPrice\n");
    printf("-----------------------------------------------\n");
    for (int i = 0; i < itemCount; i++) {
        printf("%d\t%-15s\t%d\t\t%.2f\n", inventory[i].id, inventory[i].name, inventory[i].quantity, inventory[i].price);
    }
}

void searchItem() {
    int id;
    printf("Enter item ID to search: ");
    scanf("%d", &id);

    int index = findItemByID(id);
    if (index == -1) {
        printf("Item with ID %d not found.\n", id);
        return;
    }

    printf("Item found:\n");
    printf("ID: %d\nName: %s\nQuantity: %d\nPrice: %.2f\n", 
            inventory[index].id, inventory[index].name, inventory[index].quantity, inventory[index].price);
}

void updateItem() {
    int id;
    printf("Enter item ID to update: ");
    scanf("%d", &id);

    int index = findItemByID(id);
    if (index == -1) {
        printf("Item with ID %d not found.\n", id);
        return;
    }

    printf("Enter new name: ");
    getchar(); // Clear newline character
    fgets(inventory[index].name, NAME_LENGTH, stdin);
    inventory[index].name[strcspn(inventory[index].name, "\n")] = '\0';

    printf("Enter new quantity: ");
    scanf("%d", &inventory[index].quantity);

    printf("Enter new price: ");
    scanf("%f", &inventory[index].price);

    printf("Item updated successfully.\n");
}

void deleteItem() {
    int id;
    printf("Enter item ID to delete: ");
    scanf("%d", &id);

    int index = findItemByID(id);
    if (index == -1) {
        printf("Item with ID %d not found.\n", id);
        return;
    }

    // Shift items to fill the gap
    for (int i = index; i < itemCount - 1; i++) {
        inventory[i] = inventory[i + 1];
    }
    itemCount--;
    printf("Item deleted successfully.\n");
}

void calculateTotalValue() {
    if (itemCount == 0) {
        printf("Inventory is empty.\n");
        return;
    }

    float totalValue = 0.0f;
    for (int i = 0; i < itemCount; i++) {
        totalValue += inventory[i].quantity * inventory[i].price;
    }

    printf("Total Inventory Value: %.2f\n", totalValue);
}

int findItemByID(int id) {
    for (int i = 0; i < itemCount; i++) {
        if (inventory[i].id == id) {
            return i;
        }
    }
    return -1;
}
