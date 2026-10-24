
#include <stdio.h>

int main() {
    int rows, seatsPerRow, k;
    int seats[100][100];
    int totalFree = 0;
    int freeCount;
    int middle, found = 0;
    int bookedRow = -1, startSeat = -1;

    
    printf("Enter number of rows: ");
    scanf("%d", &rows);

    printf("Enter number of seats per row: ");
    scanf("%d", &seatsPerRow);

    if (rows <= 0 || rows > 100 ||
        seatsPerRow <= 0 || seatsPerRow > 100) {
        printf("Invalid number of rows or seats.\n");
        return 0;
    }

    
    printf("Enter seating status (0 = available, 1 = booked):\n");

    for (int i = 0; i < rows; i++) {
        printf("Row %d:\n", i);

        for (int j = 0; j < seatsPerRow; j++) {
            scanf("%d", &seats[i][j]);

            if (seats[i][j] != 0 && seats[i][j] != 1) {
                printf("Invalid status. Enter only 0 or 1.\n");
                return 0;
            }
        }
    }

    
    printf("\n--- Seating Arrangement ---\n");
    printf("    ");

    for (int j = 0; j < seatsPerRow; j++) {
        printf("%d ", j);
    }
    printf("\n");

    for (int i = 0; i < rows; i++) {
        printf("R%d  ", i);

        for (int j = 0; j < seatsPerRow; j++) {
            if (seats[i][j] == 0) {
                printf("_ ");
            } else {
                printf("X ");
            }
        }
        printf("\n");
    }

    
    printf("\n--- Seat Availability Report ---\n");

    for (int i = 0; i < rows; i++) {
        freeCount = 0;

        for (int j = 0; j < seatsPerRow; j++) {
            if (seats[i][j] == 0) {
                freeCount++;
            }
        }

        printf("Free seats in Row %d: %d\n", i, freeCount);
        totalFree += freeCount;
    }

    printf("Total free seats: %d\n", totalFree);

    
    printf("\nEnter number of customers (k): ");
    scanf("%d", &k);

    if (k <= 0 || k > seatsPerRow) {
        printf("Invalid group size. It must be between 1 and %d.\n",
               seatsPerRow);
        return 0;
    }

    
    if (totalFree < k) {
        printf("Booking unsuccessful: Not enough free seats.\n");
    } else {
        
        middle = rows / 2;

        for (int distance = 0; distance < rows && found == 0;
             distance++) {

            
            
            for (int direction = 0; direction < 2 && found == 0;
                 direction++) {

                int row;

                if (distance == 0) {
                    if (direction == 1) {
                        continue;
                    }
                    row = middle;
                } else {
                    if (direction == 0) {
                        row = middle - distance;
                    } else {
                        row = middle + distance;
                    }
                }

                if (row < 0 || row >= rows) {
                    continue;
                }

                
                int count = 0;

                for (int j = 0; j < seatsPerRow; j++) {
                    if (seats[row][j] == 0) {
                        count++;

                        if (count == k) {
                            bookedRow = row;
                            startSeat = j - k + 1;
                            found = 1;
                            break;
                        }
                    } else {
                        count = 0;
                    }
                }
            }
        }

        
        if (found == 1) {
            for (int j = startSeat; j < startSeat + k; j++) {
                seats[bookedRow][j] = 1;
            }

            printf("\nBooking successful!\n");
            printf("Group of %d seated in Row %d, Seats %d to %d\n",
                   k, bookedRow, startSeat, startSeat + k - 1);
        } else {
           
            printf("\nBooking unsuccessful: No row contains %d "
                   "consecutive available seats.\n", k);
        }
    }

   
    printf("\n--- Updated Seating Arrangement ---\n");
    printf("    ");

    for (int j = 0; j < seatsPerRow; j++) {
        printf("%d ", j);
    }
    printf("\n");

    for (int i = 0; i < rows; i++) {
        printf("R%d  ", i);

        for (int j = 0; j < seatsPerRow; j++) {
            if (seats[i][j] == 0) {
                printf("_ ");
            } else {
                printf("X ");
            }
        }
        printf("\n");
    }

    
    totalFree = 0;

    for (int i = 0; i < rows; i++) {
        freeCount = 0;

        for (int j = 0; j < seatsPerRow; j++) {
            if (seats[i][j] == 0) {
                freeCount++;
            }
        }

        printf("Free seats in Row %d: %d\n", i, freeCount);
        totalFree += freeCount;
    }

    printf("Total remaining free seats: %d\n", totalFree);

    return 0;
}
