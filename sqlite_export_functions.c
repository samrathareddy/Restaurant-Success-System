
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
