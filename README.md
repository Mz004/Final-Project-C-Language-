# Veterinarian Clinic System

This repository contains the implementation of a **Veterinarian Clinic System** developed as a final project for my C programming course in the first semester. The system allows a veterinary clinic to manage patient (pet) records and appointments, built through a series of milestones that gradually add more features.

---

## Table of Contents
1. [Introduction](#introduction)
2. [Milestone Overview](#milestone-overview)
   - [Milestone 1](#milestone-1)
   - [Milestone 2](#milestone-2)
   - [Milestone 3](#milestone-3)
3. [How to Use](#how-to-use)
4. [Academic Integrity Warning](#academic-integrity-warning)

---

## Introduction

The **Veterinarian Clinic System** is designed to help veterinary clinics manage patient information (pets) and schedule appointments efficiently. This project was broken down into three critical milestones to help manage the workload and stay on track with deadlines. Each milestone builds upon the previous one, progressively adding functionality and components to the system.

By the end of **Milestone 3**, the system allows for the following:
- Managing patient contact information
- Scheduling and managing appointments
- Importing patient and appointment data from external files

---

## Milestone Overview

### Milestone 1
**Focus**: Implementing helper functions

In this milestone, I developed several helper functions that simplify logic and eliminate redundancy in the later stages. These functions are thoroughly tested for reliability using a unit tester program (`a1ms1.c`). The unit tester verifies that the helper functions work correctly by comparing the returned results against expected outputs.

### Milestone 2
**Focus**: Managing patient (pet) records

Milestone 2 involves building the core structure of the veterinary clinic system. I defined new data structures to represent patient (pet) records and implemented several functions responsible for managing patient data. These functions interact with the clinic's menu system to perform tasks such as adding, updating, and viewing patient records.

A new module called `clinic` was introduced in this milestone, where all clinic-centric components and code for managing the patients reside.

### Milestone 3
**Focus**: Appointment management and file handling

In the final milestone, the system's functionality is extended to include appointment scheduling and management. Additional data structures and functions are introduced to manage appointments. Furthermore, the system now supports importing patient and appointment information from text data files, making it more robust and usable in real-world scenarios.

---

## How to Use

To use the **Veterinarian Clinic System**, follow these steps:

1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/veterinarian-clinic-system.git
   ```
2. Navigate to the repository directory and compile the program using a C compiler (e.g., GCC):

    ```bash
    gcc main.c clinic.c a1ms1.c -o vet_clinic_system
    ```
3. Run the program:

    ```bash
    ./vet_clinic_system
    ```
4. Follow the on-screen menu to manage patient records and appointments.

## Academic Integrity Warning
This repository is intended solely for reference purposes and is not to be copied, or misused in any form. The code and materials within this repository are the intellectual property of the author and are provided as a reference for learning and understanding.

### Important Notice
Any unauthorized use, reproduction, or distribution of this content is strictly prohibited. Engaging in such actions may violate academic integrity policies, and intended misuse can result in academic consequences.
