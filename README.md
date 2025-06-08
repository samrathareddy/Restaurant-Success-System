
# 🍽️ Restaurant Success System – by Samratha Reddy

A complete restaurant table booking and order management system written in C and powered by SQLite. This project supports command-line interaction, order processing, customer and inventory management, CSV/JSON data export, and Docker containerization.

---

## 🚀 Features

- ✅ Add & manage customers, addresses, and orders
- ✅ Maintain inventory for menu items
- ✅ View & export orders/inventory to CSV and JSON
- ✅ SQLite backend for data persistence
- ✅ Docker-ready build for easy deployment

---

## 🛠️ Technologies Used

- C (GCC)
- SQLite3
- Docker
- Shell (for deployment)
- CSV/JSON for data exports

---

## 📦 File Structure

```
.
├── restaurant_sqlite_system_merged.c      # Full application source
├── sqlite_export_functions.c              # Export functions (CSV/JSON)
├── preload_data.sql                       # SQL to seed initial data
├── Dockerfile                             # Docker build instructions
├── orders_export.csv / .json              # Exported sample order data
├── inventory_export.csv / .json           # Exported inventory data
└── README.md                              # This file
```

---

## 🧪 How to Run (Locally)

```bash
gcc restaurant_sqlite_system_merged.c -o restaurant_app -lsqlite3
./restaurant_app
```

---

## 🐳 Run with Docker

```bash
docker build -t restaurant-app .
docker run -it --rm restaurant-app
```

---

## 💾 Preload Database

To preload the database with sample data:
```Dockerfile
COPY preload_data.sql .
RUN sqlite3 restaurant.db < preload_data.sql
```

---

## 📤 Export Data

Use these C functions:
- `export_orders_to_csv(db);`
- `export_inventory_to_csv(db);`

They will generate:
- `orders_export.csv` / `orders_export.json`
- `inventory_export.csv` / `inventory_export.json`

---

## 🙌 Contributing

Contributions are welcome! Feel free to submit pull requests or report issues.

---

## 🧑‍💻 Author

Created by **Samratha Reddy**

