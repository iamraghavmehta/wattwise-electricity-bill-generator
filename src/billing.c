#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "../include/billing.h"

int validateConsumerId(const char *id) {
    if (!id || strlen(id) < 3 || strlen(id) > 16) return 0;
    for (int i = 0; id[i] != '\0'; i++) {
        if (!isalnum(id[i]) && id[i] != '-') return 0;
    }
    return 1;
}

int validateConsumerName(const char *name) {
    if (!name || strlen(name) < 2 || strlen(name) > 50) return 0;
    int hasChar = 0;
    for (int i = 0; name[i] != '\0'; i++) {
        if (isalpha(name[i])) hasChar = 1;
        else if (name[i] != ' ' && name[i] != '.') return 0;
    }
    return hasChar;
}

int validateUnits(double units) {
    return (units >= 0.0 && units <= 100000.0);
}

int validateCategory(int cat) {
    return (cat >= 1 && cat <= 3);
}

const char* getCategoryName(ConnectionType cat) {
    switch (cat) {
        case CONN_DOMESTIC:   return "Domestic / Residential";
        case CONN_COMMERCIAL: return "Commercial Enterprise";
        case CONN_INDUSTRIAL: return "Industrial Heavy Load";
        default:              return "Standard Tariff";
    }
}

void calculateBill(BillRecord *bill) {
    double u = bill->unitsConsumed;
    double energy = 0.0;
    double fixed = 0.0;
    double surchargeRate = 0.05; // 5%
    double dutyRate = 0.09;      // 9%

    if (bill->category == CONN_DOMESTIC) {
        fixed = 50.00;
        if (u <= 100.0) {
            energy = u * 3.25;
        } else if (u <= 250.0) {
            energy = (100.0 * 3.25) + ((u - 100.0) * 4.75);
        } else if (u <= 450.0) {
            energy = (100.0 * 3.25) + (150.0 * 4.75) + ((u - 250.0) * 6.80);
        } else {
            energy = (100.0 * 3.25) + (150.0 * 4.75) + (200.0 * 6.80) + ((u - 450.0) * 8.90);
        }
    } else if (bill->category == CONN_COMMERCIAL) {
        fixed = 160.00;
        surchargeRate = 0.07;
        dutyRate = 0.12;
        if (u <= 150.0) {
            energy = u * 7.10;
        } else if (u <= 400.0) {
            energy = (150.0 * 7.10) + ((u - 150.0) * 9.20);
        } else {
            energy = (150.0 * 7.10) + (250.0 * 9.20) + ((u - 400.0) * 11.50);
        }
    } else { // Industrial
        fixed = 450.00;
        surchargeRate = 0.08;
        dutyRate = 0.15;
        if (u <= 500.0) {
            energy = u * 9.80;
        } else {
            energy = (500.0 * 9.80) + ((u - 500.0) * 13.60);
        }
    }

    bill->energyCharges = energy;
    bill->fixedCharges = fixed;
    bill->regulatorySurcharge = energy * surchargeRate;
    bill->stateDuty = (energy + fixed) * dutyRate;
    bill->grossTotal = energy + fixed + bill->regulatorySurcharge + bill->stateDuty;
    bill->earlyBirdDiscount = bill->grossTotal * 0.02; // 2% prompt incentive
    bill->netPayable = bill->grossTotal - bill->earlyBirdDiscount;
}

void printBillInvoice(const BillRecord *bill) {
    printf("\n=================================================================\n");
    printf("                  WATTWISE UTILITY SERVICES                       \n");
    printf("               OFFICIAL CONSUMER ELECTRICITY BILL                 \n");
    printf("=================================================================\n");
    printf(" Consumer ID   : %-20s  Date Generated: 2026-11-26\n", bill->consumerId);
    printf(" Consumer Name : %-20s  Category      : %s\n", bill->consumerName, getCategoryName(bill->category));
    printf(" Units Consumed: %-10.2f kWh          Billing Cycle : Monthly\n", bill->unitsConsumed);
    printf("-----------------------------------------------------------------\n");
    printf(" CHARGE BREAKDOWN                                     AMOUNT (INR)\n");
    printf("-----------------------------------------------------------------\n");
    printf(" 1. Energy Charges (Tiered Slab Calculation)   :  Rs %10.2f\n", bill->energyCharges);
    printf(" 2. Fixed Infrastructure / Meter Charge        :  Rs %10.2f\n", bill->fixedCharges);
    printf(" 3. Regulatory Surcharge                       :  Rs %10.2f\n", bill->regulatorySurcharge);
    printf(" 4. State Electricity Duty & Taxes             :  Rs %10.2f\n", bill->stateDuty);
    printf("-----------------------------------------------------------------\n");
    printf(" GROSS INVOICE TOTAL                           :  Rs %10.2f\n", bill->grossTotal);
    printf(" Prompt Settlement Incentive (2.0%% Discount)   : -Rs %10.2f\n", bill->earlyBirdDiscount);
    printf("=================================================================\n");
    printf(" NET AMOUNT PAYABLE                            :  Rs %10.2f\n", bill->netPayable);
    printf("=================================================================\n");
    printf(" Please settle before the 15th to avail prompt settlement discount.\n\n");
}

void printSummaryReport(int totalBills, double totalRevenue, double totalUnits) {
    printf("\n=======================================================\n");
    printf("             WATTWISE SESSION SUMMARY REPORT            \n");
    printf("=======================================================\n");
    printf(" Total Invoices Generated  : %d\n", totalBills);
    printf(" Total Energy Metered      : %.2f kWh\n", totalUnits);
    printf(" Total Gross Revenue       : Rs %.2f\n", totalRevenue);
    if (totalBills > 0) {
        printf(" Average Bill Amount       : Rs %.2f\n", totalRevenue / totalBills);
    }
    printf("=======================================================\n\n");
}
