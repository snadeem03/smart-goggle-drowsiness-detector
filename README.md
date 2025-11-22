# Smart Goggle for Eye Drowsiness Detection

A wearable safety device built using **ESP32** and **Arduino IDE** that detects eye drowsiness in real time using IR sensors.  
If the user's eyes remain closed for **3 seconds**, the system automatically activates a **buzzer alert** to warn the user and prevent accidents.

---

## 🚀 Features
- Real-time **eye drowsiness detection**
- **3-second continuous eye closure** triggers alert
- Built using **ESP32 + IR sensor**
- Lightweight design that fits on regular goggles
- Adjustable IR threshold based on environment
- Simple code structure and easy to extend

---

## 🛠️ Technologies & Hardware Used
- **ESP32**
- **Arduino IDE**
- **IR Sensor Module**
- **Buzzer**
- Jumper wires
- Smart goggle frame

---

## ⚙️ How It Works
1. IR sensor continuously tracks eye reflection.
2. When eyes are open → IR values stay above threshold.  
3. When eyes stay closed → IR values drop.
4. If closed for **3 seconds**, buzzer activates to alert the user.

---

## 🔧 Setup & Installation

### **Upload Steps**
1. Open **Arduino IDE**
2. Install **ESP32 Board Package**
3. Select **ESP32 Dev Module**
4. Connect device via USB
5. Upload the sketch
6. Adjust **IR threshold value** in the code to match your environment

---

## 📁 Folder Structure
