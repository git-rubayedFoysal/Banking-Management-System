# 🏦 Banking Management System

[![C++](https://img.shields.io/badge/Language-C++-blue?logo=c%2B%2B&style=for-the-badge)](https://isocpp.org/)
[![Version](https://img.shields.io/badge/Version-1.0-green?style=for-the-badge)](#)
[![License](https://img.shields.io/badge/License-Educational-lightgrey?style=for-the-badge)](#)

> A simple practice banking app where you can create accounts, save money, and keep track of your transactions.

---

## 📑 Table of Contents

- [⚡ Quick Setup](#-quick-setup-4-steps)
- [💡 What Can You Do?](#-what-can-you-do)
- [🎮 How to Use](#-how-to-use)
- [📁 Where Stuff Gets Saved](#-where-stuff-gets-saved)
- [📝 What Your Files Look Like](#-what-your-files-look-like)
- [🛠️ Having Problems?](#️-having-problems)
- [⚠️ Important](#️-important)
- [🖥️ Works On?](#️-works-on)
- [🔧 Technical Details](#-technical-details)
- [🚀 Future Ideas](#-future-ideas)
- [📜 License](#-license)
- [❓ Help](#-help)

---

## ⚡ Quick Setup (4 Steps)

**Step 1 - Create folders:**
```bash
mkdir accounts transactions data admin
```

**Step 2 - Initialize counter:**
```bash
echo "1000000" > data/acc_counter.txt
```

**Step 3 - Compile:**
```bash
g++ main.cpp -o main
```

**Step 4 - Run:**
```bash
./main
```

Done! 🎉

---

## 💡 What Can You Do?

### Customer Features
- ✅ Create a new account
- ✅ Set a 4-digit PIN (password)
- ✅ Deposit money
- ✅ Withdraw money
- ✅ Check your balance
- ✅ View all your transactions
- ✅ Close your account

### Admin Features
- ✅ Create other admin accounts
- ✅ View all customer accounts
- ✅ Delete accounts if needed
- ✅ Reset customer PINs
- ✅ See total money in system

---

## 🎮 How to Use

**Main Menu:**
```
1. Create New Account
2. Login
3. Admin Mode
4. Exit
```

**After Login (Your Menu):**
```
1. See Account Details
2. Deposit Money
3. Withdraw Money
4. Check Balance
5. View Transactions
6. Delete Account
7. Logout
```

---

## 📁 Where Stuff Gets Saved

| What | Location | Contains |
|------|----------|----------|
| Your Account | `accounts/1000000.txt` | Name, balance, PIN |
| Transactions | `transactions/1000000_history.txt` | Deposits & withdrawals |
| Admin Info | `admin/admins.txt` | Admin usernames & PINs |
| Counter | `data/acc_counter.txt` | Next account number |

---

## 📝 What Your Files Look Like

**Account File:**
```
Account Number: 1000000
Name: John Doe
PIN: 31000031
Balance: 50000
Date Created: 28-01-2026 10:30:45
```

**Transaction History:**
```
[28-01-2026 10:30:45] Account Created - Saved: 50000
[28-01-2026 10:35:12] Deposit: +10000 (Now have: 60000)
[28-01-2026 10:40:33] Withdrawal: -5000 (Now have: 55000)
```

---

## 🛠️ Having Problems?

### "g++ not found"
Your computer doesn't have C++ compiler.

**Fix:**
- Windows: Download from [mingw-w64.org](https://www.mingw-w64.org/)
- Mac: `brew install gcc`
- Linux: `sudo apt-get install g++`

### "Folders don't exist"
**Fix:**
```bash
mkdir accounts transactions data admin
```

### "Counter file missing"
**Fix:**
```bash
echo "1000000" > data/acc_counter.txt
```

### "Wrong account number or PIN"
- Account number = 7 digits (like 1000000)
- PIN = 4 digits (like 1234)

### "Not enough money"
Deposit more money first or withdraw less.

### "Symbols not showing (৳)"
Turn on UTF-8 in your terminal settings.

---

## ⚠️ Important

**This is for learning only!**

- ❌ NOT safe for real money
- ❌ Passwords stored simply (not secure)
- ❌ Files are plain text (not protected)
- ❌ No real security features

**Don't use with real money!** 🚫

---

## 🖥️ Works On?

| OS | Status |
|----|--------|
| Windows | ✅ Yes |
| Mac | ✅ Yes |
| Linux | ✅ Yes |

**Needs:** C++ compiler (GCC/G++) 7.0 or newer

---

## 🔧 Technical Details

| Item | Details |
|------|---------|
| Language | C++ |
| Storage | Text files |
| Account IDs | Start at 1000000 |
| Dates | DD-MM-YYYY HH:MM:SS |
| Money | Bengali Taka (৳) |
| PIN Hash | `(pin * 3700 * 13 + 99) ^ (pin >> 21)` |

---

## 🚀 Future Ideas

- 🔐 Real database
- 🛡️ Real security & encryption
- 💳 Transfer between accounts
- 📱 Mobile app
- 🌐 Web version
- 📊 Spending charts

---

## 📜 License

Free to use for learning. Use, modify, and share as you like!

---

## ❓ Help

1. Read the troubleshooting section above
2. Make sure all folders exist
3. Make sure C++ is installed
4. Follow the 4 setup steps

---

**Version 1.0 • Created Jan 28, 2026 • Status: ✅ Works**
