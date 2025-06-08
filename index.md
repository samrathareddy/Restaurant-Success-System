
# 🍽️ Restaurant Success System

Welcome to the official documentation for the Restaurant Success System.

## 📦 Overview

A complete restaurant reservation and order management application written in C with SQLite integration. It includes a terminal-based interface, Docker containerization, and data export tools (CSV/JSON).

---

## 🚀 Quick Start

### 🔧 Build Locally
```bash
gcc restaurant_sqlite_system_merged.c -o restaurant_app -lsqlite3
./restaurant_app
```

### 🐳 Run with Docker
```bash
docker build -t restaurant-app .
docker run -it --rm restaurant-app
```

---

## 📂 File Structure

- `restaurant_sqlite_system_merged.c` – Core source code
- `preload_data.sql` – Preloaded customer/order data
- `Dockerfile` – For container builds
- `README.md` – Project overview
- `orders_export.*` / `inventory_export.*` – Exported data

---

## 📤 Exporting Data

Run these functions from the C app:
- `export_orders_to_csv(db);`
- `export_inventory_to_csv(db);`

---

## 💬 Contact

Created by **Samratha Reddy**  
Email: samrathareddyk@gmail.com

---

> This documentation is automatically published with GitHub Pages.
