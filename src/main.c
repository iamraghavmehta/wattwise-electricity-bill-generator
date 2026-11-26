#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/billing.h"

static void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

int main(void) {
    int totalBills = 0;
    double totalRevenue = 0.0;
    double totalUnits = 0.0;
    int choice = 1;

    printf("=================================================================\n");
    printf("        WATTWISE - Modular Electricity Billing Architecture      \n");
    printf("        Developed in Standard C (C99 / GCC Compatible)           \n");
    printf("=================================================================\n\n");

    while (choice != 3) {
        printf("--- SYSTEM CONSOLE MENU ---\n");
        printf("1. Calculate & Generate Consumer Invoice\n");
        printf("2. View Current Session Statistics\n");
        printf("3. Exit System\n");
        printf("Select an option (1-3): ");

        if (scanf("%d", &choice) != 1) {
            printf("\n[ERROR] Invalid input. Please enter a numerical option (1-3).\n\n");
            clearInputBuffer();
            choice = 0;
            continue;
        }
        clearInputBuffer();

        if (choice == 1) {
            BillRecord record;
            memset(&record, 0, sizeof(BillRecord));

            // Input: Consumer ID
            while (1) {
                printf("\nEnter Consumer ID (e.g., CON-1042): ");
                if (fgets(record.consumerId, sizeof(record.consumerId), stdin)) {
                    record.consumerId[strcspn(record.consumerId, "\r\n")] = '\0';
                    if (validateConsumerId(record.consumerId)) break;
                }
                printf("[ERROR] Invalid ID format. Must be 3-16 alphanumeric characters or hyphens.\n");
            }

            // Input: Consumer Name
            while (1) {
                printf("Enter Consumer Full Name: ");
                if (fgets(record.consumerName, sizeof(record.consumerName), stdin)) {
                    record.consumerName[strcspn(record.consumerName, "\r\n")] = '\0';
                    if (validateConsumerName(record.consumerName)) break;
                }
                printf("[ERROR] Invalid name. Use alphabetic characters, spaces, or dots only.\n");
            }

            // Input: Connection Category
            while (1) {
                int catChoice = 0;
                printf("Select Connection Tariff Category:\n");
                printf("  [1] Domestic / Residential\n");
                printf("  [2] Commercial Enterprise\n");
                printf("  [3] Industrial Heavy Load\n");
                printf("Choose tariff (1-3): ");
                if (scanf("%d", &catChoice) == 1 && validateCategory(catChoice)) {
                    record.category = (ConnectionType)catChoice;
                    clearInputBuffer();
                    break;
                }
                printf("[ERROR] Invalid category selection. Please enter 1, 2, or 3.\n");
                clearInputBuffer();
            }

            // Input: Units Consumed
            while (1) {
                printf("Enter Units Consumed (kWh): ");
                if (scanf("%lf", &record.unitsConsumed) == 1 && validateUnits(record.unitsConsumed)) {
                    clearInputBuffer();
                    break;
                }
                printf("[ERROR] Invalid unit quantity. Value must be a non-negative number.\n");
                clearInputBuffer();
            }

            // Perform Calculation
            calculateBill(&record);

            // Output Invoice
            printBillInvoice(&record);

            // Accumulate statistics
            totalBills++;
            totalRevenue += record.netPayable;
            totalUnits += record.unitsConsumed;

        } else if (choice == 2) {
            printSummaryReport(totalBills, totalRevenue, totalUnits);
        } else if (choice == 3) {
            printf("\nExiting WattWise. Final audit completed.\n");
            printSummaryReport(totalBills, totalRevenue, totalUnits);
        } else {
            printf("\n[ERROR] Unrecognized selection. Please choose 1, 2, or 3.\n\n");
        }
    }

    return 0;
}
