
# 🍽️ Restaurant Success System

A complete restaurant table booking and order management system written in C and powered by SQLite. This project supports command-line interaction, order processing, customer and inventory management, CSV/JSON data export, Docker containerization, GitHub Actions automation, and documentation via GitHub Pages.

---

## 🚀 Features

- ✅ Add & manage customers, addresses, and orders
- ✅ Maintain inventory for menu items
- ✅ View & export orders/inventory to CSV and JSON
- ✅ SQLite backend for data persistence
- ✅ Docker-ready for local and production use
- ✅ GitHub Actions CI/CD workflows:
  - Docker builds
  - Release exports
  - Multi-arch builds
- ✅ GitHub Pages documentation

---

## 🛠️ Technologies Used

- C (GCC)
- SQLite3
- Docker & Docker Compose
- GitHub Actions
- CSV/JSON for data exports

---

## 📂 File Structure

```
.
├── restaurant_sqlite_system_merged.c      # Full application source
├── sqlite_export_functions.c              # Export functions (CSV/JSON)
├── preload_data.sql                       # SQL to seed initial data
├── Dockerfile                             # Docker build instructions
├── docker-compose.yml                     # Compose file for container orchestration
├── .env                                   # Environment variables
├── orders_export.csv / .json              # Exported order data
├── inventory_export.csv / .json           # Exported inventory data
├── .github/workflows/                     # GitHub Actions CI/CD workflows
│   ├── build.yml
│   ├── release.yml
│   └── multi_arch_docker.yml
├── docs/index.md                          # GitHub Pages documentation
└── README.md                              # This file
```

---## ⚡ Quick Start

### 🔗 Clone the Repository

```bash
git clone https://github.com/samrathareddy/Restaurant-Success-System.git
cd Restaurant-Success-System
```

### 🛠️ Create Virtual Environment & Install Dependencies

> ⚠️ *Only needed if you use Python scripts or extend this with web/UI features*

```bash
python -m venv venv
source venv/bin/activate  # or venv\Scripts\activate on Windows
pip install -r requirements.txt
```

## 🧪 How to Run Locally

```bash
gcc restaurant_sqlite_system_merged.c -o restaurant_app -lsqlite3
./restaurant_app
```

---

## 🐳 Docker Usage

### Build and Run
```bash
docker build -t restaurant-app .
docker run -it --rm restaurant-app
```

### With Docker Compose
```bash
docker-compose up --build
```

---

## 💾 Preload Database (Optional)
```dockerfile
COPY preload_data.sql .
RUN sqlite3 restaurant.db < preload_data.sql
```

---

## 📤 Exporting Data

Functions in `sqlite_export_functions.c`:
- `export_orders_to_csv(db);`
- `export_inventory_to_csv(db);`

Files generated:
- `orders_export.csv` / `orders_export.json`
- `inventory_export.csv` / `inventory_export.json`

---

## 🤖 GitHub Actions CI/CD

| Workflow             | File                | Description                         |
|----------------------|---------------------|-------------------------------------|
| Build & Test         | `.github/workflows/build.yml`           | Compiles Docker image               |
| Release              | `.github/workflows/release.yml`         | Uploads data files to GitHub Releases |
| Multi-Arch Docker    | `.github/workflows/multi_arch_docker.yml`| Builds Docker image for multiple platforms |

---

## 🌐 GitHub Pages Documentation

Available in the `docs/` folder.  
To publish:
- Go to **Settings > Pages**
- Set source as `docs/` folder

---

## 🙌 Contributing

Contributions are welcome!  
Please open issues or pull requests to help improve the system.

---


## 💡 Use Cases

- Restaurant table reservation system
- Food order management & tracking
- Inventory stock control
- Offline kiosk-based or embedded systems
- Educational projects on systems programming & DB integration

---

## 👤 About the Author

**Samratha Reddy**  
Samratha Reddy is a graduate student at Cleveland State University. This project showcases skills in backend development, graph theory, data visualization, and full-stack integration.
📫 Email: samrathareddyk@gmail.com  
🔗 LinkedIn: [linkedin.com/in/samrathareddy](https://www.linkedin.com/in/samrathareddy)

---

## ⭐ Support This Project

If you found this repository helpful:

⭐ **Star this repo** → [Restaurant-Success-System on GitHub](https://github.com/samrathareddy/Restaurant-Success-System.git)

🛠️ Contributions and pull requests are warmly welcome!

