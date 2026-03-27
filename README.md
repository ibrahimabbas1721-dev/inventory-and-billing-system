# 🧾 Billing & Inventory Management System
### Built with C++ | Multi-File Architecture | Role-Based Access

![C++](https://img.shields.io/badge/Language-C%2B%2B-blue?style=for-the-badge&logo=cplusplus)
![OOP](https://img.shields.io/badge/Paradigm-OOP-green?style=for-the-badge)
![Architecture](https://img.shields.io/badge/Architecture-Multi--File-orange?style=for-the-badge)
![Status](https://img.shields.io/badge/Status-Complete-brightgreen?style=for-the-badge)

---

## 📌 About The Project

A fully functional console-based **Billing & Inventory Management System** built in C++. This project simulates a real-world retail/shop management system with **role-based access control**, **product inventory**, **bill generation**, and **sales reporting** — all structured across multiple files using proper software design principles.

---

## 👥 Role-Based Access Control

| Feature | Admin | Cashier |
|---|:---:|:---:|
| List Products | ✅ | ✅ |
| Create Bill | ✅ | ✅ |
| View/Print Saved Bill | ✅ | ✅ |
| Add Product | ✅ | ❌ |
| Update Product | ✅ | ❌ |
| Delete Product | ✅ | ❌ |
| Add / Delete Users | ✅ | ❌ |
| View Sales Report | ✅ | ❌ |

---

## 🧠 C++ Concepts & Skills Demonstrated
```
✅ OOP — Multiple classes, encapsulation, header files
✅ Multi-File Architecture — auth, inventory, ui, product, user modules
✅ File Handling (fstream) — persistent data, bills, sales reports
✅ Pointers — User* for session management
✅ Role-Based Access Control — real-world software pattern
✅ Modular Design — each class handles one responsibility
```

---

## 🗂️ Project Structure
```
billingSystem/
├── bills/                       # Saved customer bills
├── data/                        # Product & user data files
├── sales_reports/               # Generated sales reports
├── main.cpp                     # Entry point & role-based menu
├── auth.cpp / auth.h            # Authentication & user management
├── inventory.cpp / inventory.h  # Inventory & billing logic
├── billingSystem.cpp            # Core billing logic
├── product.h / user.h / ui.h   # Class & UI definitions
```

---

## 🚀 How To Run
```bash
git clone https://github.com/your-username/billing-system.git
cd billing-system
g++ main.cpp auth.cpp inventory.cpp billingSystem.cpp -o billingSystem
./billingSystem
```

---

## 🎯 What I Learned

- Splitting a C++ project across **multiple files** with headers
- Using **pointers to objects** (`User*`) for session management
- Implementing **role-based access control**
- **File I/O** with `fstream` for data persistence
- Proper **folder structure** for a real project

---

## 🔮 Future Improvements

- [ ] Password hashing for security
- [ ] Input validation across all forms
- [ ] Date/time stamping on bills and reports
- [ ] SQLite database instead of flat files

---

## 👨‍💻 Author

**Ibrahim** — CS Student | Aspiring Software Developer

> *"Building real-world projects to go from student to placement-ready developer."*