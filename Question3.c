#include <stdio.h>

#define MAX_SENSORS 100
#define MAX_READINGS 100

// Function to input readings into the 2D array
void inputReadings(float readings[MAX_SENSORS][MAX_READINGS], int numSensors, int numReadings) {
    for (int i = 0; i < numSensors; i++) {
        printf("Enter readings for Sensor %d (%d readings):\n", i + 1, numReadings);
        for (int j = 0; j < numReadings; j++) {
            scanf("%f", &readings[i][j]);
        }
    }
}

// Function to analyze a single sensor's readings
void analyzeSensor(float readings[MAX_READINGS], int numReadings, float *avg) {
    float total = 0;
    float maxVal = readings[0];
    float minVal = readings[0];
    int critical = 0;
    int warning = 0;
    int currentStreak = 0;
    int maxStreak = 0;

    for (int j = 0; j < numReadings; j++) {
        float val = readings[j];
        total += val;

        if (val > maxVal) maxVal = val;
        if (val < minVal) minVal = val;

        if (val >= 40.0) {
            critical++;
        } else if (val >= 35.0 && val <= 39.0) {
            warning++;
        }

        // Streak calculation (temp >= 35)
        if (val >= 35.0) {
            currentStreak++;
            if (currentStreak > maxStreak) {
                maxStreak = currentStreak;
            }
        } else {
            currentStreak = 0;
        }
    }

    *avg = total / numReadings;

    printf("Total = %.2f, Avg = %.2f, Max = %.2f, Min = %.2f, Critical = %d, Warning = %d, Longest hot streak = %d\n",
           total, *avg, maxVal, minVal, critical, warning, maxStreak);
}

// Function to find the sensor index with the highest average temperature
int findHighestAverage(float averages[], int numSensors) {
    int maxIndex = 0;
    for (int i = 1; i < numSensors; i++) {
        if (averages[i] > averages[maxIndex]) {
            maxIndex = i;
        }
    }
    return maxIndex;
}

int main() {
    int numSensors, numReadings;
    float readings[MAX_SENSORS][MAX_READINGS];
    float averages[MAX_SENSORS];

    printf("Enter number of sensors: ");
    scanf("%d", &numSensors);
    printf("Enter number of hourly readings per sensor: ");
    scanf("%d", &numReadings);

    inputReadings(readings, numSensors, numReadings);

    printf("\n--- INDIVIDUAL SENSOR REPORTS ---\n");
    for (int i = 0; i < numSensors; i++) {
        printf("Sensor %d: ", i + 1);
        analyzeSensor(readings[i], numReadings, &averages[i]);
    }

    int highestIndex = findHighestAverage(averages, numSensors);
    printf("\nHighest average: Sensor %d (%.2f)\n", highestIndex + 1, averages[highestIndex]);

    return 0;
}