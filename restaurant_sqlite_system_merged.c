
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <time.h>

void initialize_database(sqlite3 *db);
void add_customer(sqlite3 *db);
void add_address(sqlite3 *db);
void add_order(sqlite3 *db);
void display_customers(sqlite3 *db);
void display_orders(sqlite3 *db);

void main_menu(sqlite3 *db) {
    int choice;
    do {
        printf("\n\n===== RESTAURANT SUCCESS SYSTEM =====\n");
        printf("1. Add Customer\n");
        printf("2. Add Address\n");
        printf("3. Place Order\n");
        printf("4. View Customers\n");
        printf("5. View Orders\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();  // consume newline

        switch (choice) {
            case 1: add_customer(db); break;
            case 2: add_address(db); break;
            case 3: add_order(db); break;
            case 4: display_customers(db); break;
            case 5: display_orders(db); break;
            case 6: printf("Exiting...\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 6);
}

int main() {
    sqlite3 *db;
    if (sqlite3_open("restaurant.db", &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    initialize_database(db);
    main_menu(db);

    sqlite3_close(db);
    return 0;
}

void initialize_database(sqlite3 *db) {
    const char *sql =
        "CREATE TABLE IF NOT EXISTS customers ("
        "cust_id INTEGER PRIMARY KEY,"
        "cust_firstname TEXT,"
        "cust_lastname TEXT);"

        "CREATE TABLE IF NOT EXISTS address ("
        "add_id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "delivery_address1 TEXT,"
        "delivery_address2 TEXT,"
        "delivery_city TEXT,"
        "delivery_zipcode TEXT);"

        "CREATE TABLE IF NOT EXISTS item ("
        "item_id TEXT PRIMARY KEY,"
        "sku TEXT,"
        "item_name TEXT,"
        "item_cat TEXT,"
        "item_size TEXT,"
        "item_price REAL);"

        "CREATE TABLE IF NOT EXISTS orders ("
        "row_id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "order_id TEXT,"
        "created_at TEXT,"
        "item_id TEXT,"
        "quantity INTEGER,"
        "cust_id INTEGER,"
        "delivery INTEGER,"
        "add_id INTEGER,"
        "FOREIGN KEY (item_id) REFERENCES item(item_id),"
        "FOREIGN KEY (cust_id) REFERENCES customers(cust_id),"
        "FOREIGN KEY (add_id) REFERENCES address(add_id));";

    char *err_msg = NULL;
    int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    }
}

void add_customer(sqlite3 *db) {
    int id;
    char fname[50], lname[50];
    printf("Enter Customer ID: "); scanf("%d", &id);
    printf("First Name: "); scanf("%s", fname);
    printf("Last Name: "); scanf("%s", lname);

    char sql[256];
    sprintf(sql, "INSERT INTO customers VALUES (%d, '%s', '%s');", id, fname, lname);
    char *err_msg = NULL;
    int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Insert customer failed: %s\n", err_msg);
        sqlite3_free(err_msg);
    } else {
        printf("Customer added.\n");
    }
}

void add_address(sqlite3 *db) {
    char line1[200], line2[200], city[50], zip[20];
    printf("Delivery Address Line 1: "); fgets(line1, sizeof(line1), stdin);
    printf("Delivery Address Line 2: "); fgets(line2, sizeof(line2), stdin);
    printf("City: "); fgets(city, sizeof(city), stdin);
    printf("Zipcode: "); fgets(zip, sizeof(zip), stdin);

    char sql[1024];
    sprintf(sql, "INSERT INTO address (delivery_address1, delivery_address2, delivery_city, delivery_zipcode) "
                 "VALUES ('%s', '%s', '%s', '%s');", line1, line2, city, zip);
    char *err_msg = NULL;
    int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Insert address failed: %s\n", err_msg);
        sqlite3_free(err_msg);
    } else {
        printf("Address added.\n");
    }
}

void add_order(sqlite3 *db) {
    char order_id[20], item_id[10], datetime[64];
    int quantity, cust_id, delivery, add_id;
    time_t now = time(NULL);
    strftime(datetime, sizeof(datetime), "%Y-%m-%d %H:%M:%S", localtime(&now));

    printf("Order ID: "); scanf("%s", order_id);
    printf("Item ID: "); scanf("%s", item_id);
    printf("Quantity: "); scanf("%d", &quantity);
    printf("Customer ID: "); scanf("%d", &cust_id);
    printf("Delivery? (1=Yes, 0=No): "); scanf("%d", &delivery);
    printf("Address ID (if delivery): "); scanf("%d", &add_id);

    char sql[512];
    sprintf(sql,
        "INSERT INTO orders (order_id, created_at, item_id, quantity, cust_id, delivery, add_id) "
        "VALUES ('%s', '%s', '%s', %d, %d, %d, %d);",
        order_id, datetime, item_id, quantity, cust_id, delivery, add_id);

    char *err_msg = NULL;
    int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Insert order failed: %s\n", err_msg);
        sqlite3_free(err_msg);
    } else {
        printf("Order placed.\n");
    }
}

void display_customers(sqlite3 *db) {
    const char *sql = "SELECT * FROM customers;";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        printf("Customers:\n");
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            printf("ID: %d, Name: %s %s\n",
                   sqlite3_column_int(stmt, 0),
                   sqlite3_column_text(stmt, 1),
                   sqlite3_column_text(stmt, 2));
        }
    }
    sqlite3_finalize(stmt);
}

void display_orders(sqlite3 *db) {
    const char *sql = "SELECT order_id, created_at, item_id, quantity, cust_id, delivery, add_id FROM orders;";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        printf("Orders:\n");
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            printf("Order ID: %s, Date: %s, Item: %s, Qty: %d, CustID: %d, Delivery: %d, Address ID: %d\n",
                sqlite3_column_text(stmt, 0),
                sqlite3_column_text(stmt, 1),
                sqlite3_column_text(stmt, 2),
                sqlite3_column_int(stmt, 3),
                sqlite3_column_int(stmt, 4),
                sqlite3_column_int(stmt, 5),
                sqlite3_column_int(stmt, 6));
        }
    }
    sqlite3_finalize(stmt);


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

// Function declarations
void add_item(sqlite3 *db);
void view_items(sqlite3 *db);
void add_inventory(sqlite3 *db);
void view_inventory(sqlite3 *db);

// Add item to the menu
void add_item(sqlite3 *db) {
    char item_id[10], sku[20], name[100], cat[100], size[10];
    float price;
    printf("Enter Item ID: "); scanf("%s", item_id);
    printf("SKU: "); scanf("%s", sku);
    printf("Item Name: "); getchar(); fgets(name, sizeof(name), stdin);
    printf("Category: "); fgets(cat, sizeof(cat), stdin);
    printf("Size: "); fgets(size, sizeof(size), stdin);
    printf("Price: "); scanf("%f", &price);

    char sql[512];
    sprintf(sql, "INSERT INTO item (item_id, sku, item_name, item_cat, item_size, item_price) "
                 "VALUES ('%s', '%s', '%s', '%s', '%s', %.2f);",
                 item_id, sku, name, cat, size, price);

    char *err_msg = NULL;
    int rc = sqlite3_exec(db, sql, NULL, NULL, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Insert item failed: %s\n", err_msg);
        sqlite3_free(err_msg);
    } else {
        printf("Item added successfully.\n");
    }
}

// View all menu items
void view_items(sqlite3 *db) {
    const char *sql = "SELECT * FROM item;";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        printf("\nMenu Items:\n");
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            printf("ID: %s, SKU: %s, Name: %s, Category: %s, Size: %s, Price: %.2f\n",
                sqlite3_column_text(stmt, 0),
                sqlite3_column_text(stmt, 1),
                sqlite3_column_text(stmt, 2),
                sqlite3_column_text(stmt, 3),
                sqlite3_column_text(stmt, 4),
                sqlite3_column_double(stmt, 5));
        }
    }
    sqlite3_finalize(stmt);
}

// Add inventory for a menu item
void add_inventory(sqlite3 *db) {
    char item_id[10];
    int quantity;
    printf("Enter Item ID: "); scanf("%s", item_id);
    printf("Enter Quantity: "); scanf("%d", &quantity);

    char sql[256];
    sprintf(sql, "INSERT INTO inventory (item_id, quantity) VALUES ('%s', %d);", item_id, quantity);

    char *err_msg = NULL;
    int rc = sqlite3_exec(db, sql, NULL, NULL, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Insert inventory failed: %s\n", err_msg);
        sqlite3_free(err_msg);
    } else {
        printf("Inventory updated.\n");
    }
}

// View inventory
void view_inventory(sqlite3 *db) {
    const char *sql = "SELECT i.item_id, it.item_name, i.quantity "
                      "FROM inventory i JOIN item it ON i.item_id = it.item_id;";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        printf("\nInventory:\n");
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            printf("Item ID: %s, Name: %s, Quantity: %d\n",
                sqlite3_column_text(stmt, 0),
                sqlite3_column_text(stmt, 1),
                sqlite3_column_int(stmt, 2));
        }
    }
    sqlite3_finalize(stmt);
}

}



#include <stdio.h>

void export_orders_to_csv(sqlite3 *db) {
    FILE *fp = fopen("orders_export.csv", "w");
    if (!fp) {
        printf("Failed to open CSV file for writing.\n");
        return;
    }

    fprintf(fp, "Order ID,Created At,Item ID,Quantity,Customer ID,Delivery,Address ID\n");

    const char *sql = "SELECT order_id, created_at, item_id, quantity, cust_id, delivery, add_id FROM orders;";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            fprintf(fp, "%s,%s,%s,%d,%d,%d,%d\n",
                sqlite3_column_text(stmt, 0),
                sqlite3_column_text(stmt, 1),
                sqlite3_column_text(stmt, 2),
                sqlite3_column_int(stmt, 3),
                sqlite3_column_int(stmt, 4),
                sqlite3_column_int(stmt, 5),
                sqlite3_column_int(stmt, 6));
        }
    }
    sqlite3_finalize(stmt);
    fclose(fp);
    printf("Orders exported to orders_export.csv\n");
}

void export_inventory_to_csv(sqlite3 *db) {
    FILE *fp = fopen("inventory_export.csv", "w");
    if (!fp) {
        printf("Failed to open CSV file for writing.\n");
        return;
    }

    fprintf(fp, "Item ID,Item Name,Quantity\n");

    const char *sql = "SELECT i.item_id, it.item_name, i.quantity "
                      "FROM inventory i JOIN item it ON i.item_id = it.item_id;";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            fprintf(fp, "%s,%s,%d\n",
                sqlite3_column_text(stmt, 0),
                sqlite3_column_text(stmt, 1),
                sqlite3_column_int(stmt, 2));
        }
    }
    sqlite3_finalize(stmt);
    fclose(fp);
    printf("Inventory exported to inventory_export.csv\n");
}
