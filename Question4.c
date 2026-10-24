#include <stdio.h>

// Function 1: Get valid festival days (1 to 7)
int getValidDays() {
    int days;
    do {
        printf("Enter number of festival days (1-7): ");
        scanf("%d", &days);
        if (days < 1 || days > 7) {
            printf("Invalid input. Please enter a number between 1 and 7.\n");
        }
    } while (days < 1 || days > 7);
    return days;
}

// Function 2: Calculate daily sales and print day summary
float calculateDailySales(int dayNumber) {
    int numOrders;
    float amount, totalSales = 0, highestOrder = 0;

    printf("\n--- Day %d ---\n", dayNumber);
    printf("Enter number of orders: ");
    scanf("%d", &numOrders);

    for (int i = 1; i <= numOrders; i++) {
        do {
            printf("Enter amount for Order %d (Rs. > 0): ", i);
            scanf("%f", &amount);
            if (amount <= 0) {
                printf("Invalid amount. Sales amount must be greater than zero.\n");
            }
        } while (amount <= 0);

        totalSales += amount;
        if (amount > highestOrder) {
            highestOrder = amount;
        }
    }

    float avgOrder = totalSales / numOrders;
    printf("Total sales: Rs. %.2f\n", totalSales);
    printf("Average order: Rs. %.2f\n", avgOrder);
    printf("Highest order: Rs. %.2f\n", highestOrder);

    return totalSales;
}

// Function 3: Find the day with highest sales
int findHighestSalesDay(float dailySales[], int numberOfDays) {
    int bestDay = 0;
    for (int i = 1; i < numberOfDays; i++) {
        if (dailySales[i] > dailySales[bestDay]) {
            bestDay = i;
        }
    }
    return bestDay + 1; // 1-based day index
}

// Function 4: Display bar chart of daily sales (* per Rs. 100)
void displayBarChart(float dailySales[], int numberOfDays) {
    printf("\n***** DAILY SALES BAR CHART *****\n");
    for (int i = 0; i < numberOfDays; i++) {
        int stars = (int)(dailySales[i] / 100);
        printf("Day %d: ", i + 1);
        for (int j = 0; j < stars; j++) {
            printf("*");
        }
        printf(" (Rs. %.2f)\n", dailySales[i]);
    }
}

int main() {
    int numberOfDays = getValidDays();
    float dailySales[7];
    float totalFestivalSales = 0;

    for (int i = 0; i < numberOfDays; i++) {
        dailySales[i] = calculateDailySales(i + 1);
        totalFestivalSales += dailySales[i];
    }

    int highestDay = findHighestSalesDay(dailySales, numberOfDays);

    printf("\n***** FESTIVAL SUMMARY *****\n");
    printf("Total festival sales: Rs. %.2f\n", totalFestivalSales);
    printf("Day with highest sales: Day %d\n", highestDay);
    printf("Highest daily sales: Rs. %.2f\n", dailySales[highestDay - 1]);

    displayBarChart(dailySales, numberOfDays);

    return 0;
}