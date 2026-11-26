#ifndef BILLING_H
#define BILLING_H

typedef enum {
    CONN_DOMESTIC = 1,
    CONN_COMMERCIAL = 2,
    CONN_INDUSTRIAL = 3
} ConnectionType;

typedef struct {
    char consumerId[20];
    char consumerName[60];
    ConnectionType category;
    double unitsConsumed;
    double energyCharges;
    double fixedCharges;
    double regulatorySurcharge;
    double stateDuty;
    double grossTotal;
    double earlyBirdDiscount;
    double netPayable;
} BillRecord;

/* Validation Functions */
int validateConsumerId(const char *id);
int validateConsumerName(const char *name);
int validateUnits(double units);
int validateCategory(int cat);

/* Billing Engine */
void calculateBill(BillRecord *bill);
const char* getCategoryName(ConnectionType cat);

/* Output Display */
void printBillInvoice(const BillRecord *bill);
void printSummaryReport(int totalBills, double totalRevenue, double totalUnits);

#endif /* BILLING_H */
