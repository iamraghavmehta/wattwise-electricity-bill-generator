# WattWise - Electricity Bill Generator

An industrial-grade, modular C utility for calculating consumer electricity tariffs, tiered energy slabs, regulatory surcharges, and itemized billing invoices.

![WattWise Architecture](https://img.shields.io/badge/Language-C99-00599C?logo=c&logoColor=white)
![Compiler](https://img.shields.io/badge/Compiler-GCC%206.3%2B-green)
![License](https://img.shields.io/badge/License-MIT-blue)

## Highlights & Concepts Demonstrated

- **Modular C Design**: Decoupled interface (include/billing.h), business computation logic (src/billing.c), and user interface flow (src/main.c).
- **Control Flow & Loops**: Interactive CLI session supporting continuous bill generation with summary statistics.
- **Robust Input Validation**: Guard clauses validating alphanumeric consumer IDs, character-only names, and positive numeric ranges.
- **Tiered Tariff Architecture**:
  - **Domestic**: Progressive slab rates from INR 3.25 to INR 8.90 with INR 50 meter charge.
  - **Commercial**: Commercial rates from INR 7.10 to INR 11.50 with 7% surcharge and 12% state duty.
  - **Industrial**: High-load industrial rate structure with 8% surcharge and 15% duty.
  - **Prompt Payment Incentive**: Automatic 2% discount calculation for prompt settlement.

## Project Structure

`	ext
wattwise-electricity-bill-generator/
|-- include/
|   -- billing.h          # Function signatures and data structures
|-- src/
|   |-- billing.c          # Tariff slabs and calculation routines
|   -- main.c             # Interactive CLI engine and session tracker
|-- Makefile               # Automated compilation script
|-- index.html             # GitHub Pages interactive web simulator
|-- style.css              # Terminal-inspired responsive layout
|-- app.js                 # Browser simulation of the C billing engine
-- README.md              # Project documentation
`

## Compilation and Execution

### Using GCC:
`ash
gcc -Wall -Wextra -std=c99 -Iinclude src/billing.c src/main.c -o wattwise
./wattwise
`

### Using Make:
`ash
make
make run
`

## Interactive Web Mirror

A live GitHub Pages demonstration is available at:
https://iamraghavmehta.github.io/wattwise-electricity-bill-generator/

*Note: The web demo simulates the underlying C billing logic in client-side JavaScript for interactive evaluation.*
