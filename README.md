# Entity-Component-System

[![C++17](https://img.shields.io/badge/C%2B%2B-17-blue.svg)](https://en.cppreference.com/w/cpp/17)
[![CMake](https://img.shields.io/badge/CMake-3.14%2B-green.svg)](https://cmake.org/)
[![SFML](https://img.shields.io/badge/SFML-2.6.1-orange.svg)](https://www.sfml-dev.org/)

A clean, modern implementation of an **Entity-Component System (ECS)** built from scratch in **C++17**, using the **SFML** library for rendering and window management. The primary goal of this repository is to demonstrate excellence in software architecture, decoupling, and game development best practices, while avoiding the use of heavy, off-the-shelf libraries (such as EnTT).

---

## ECS Architecture

This project addresses the classic issues associated with deep, rigid inheritance hierarchies in traditional Object-Oriented Programming (OOP) by employing the **Composition over Inheritance** pattern:

* **Entity (`Entity`):** A simple numeric identifier (`std::uint32_t`) that holds neither logic nor data on its own.
* **Component (`Component`):** Pure data structures (e.g., `PositionComponent`, `VelocityComponent`, `SpriteComponent`) with no coupled behavior.
* **System (`MovementSystem`, `RenderSystem`):** Classes focused exclusively on behavioral logic. Systems iterate over entities that possess the specific combination of components required.
* **Registry (`Registry`):** The central manager responsible for registering entities, allocating component pools, and coordinating the data lifecycle. ---

## Installation and Compilation Guide

The project uses **CMake** along with the `FetchContent` feature, meaning the **SFML dependency is automatically downloaded and integrated** during configuration, eliminating the need for complex manual system-level installations.

### Prerequisites
* A C++17-compatible compiler (GCC, Clang, or MSVC)
* CMake (version 3.14 or higher)
* Git
