#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EXITS 6
#define MAX_VEHICLE_TYPES 6

typedef struct {
    char id[20];
    char pass[20];
} Admin;

Admin admin = {"ad", "12"};

int vehicleCount[MAX_VEHICLE_TYPES] = {0};
int exitOpen[MAX_EXITS] = {1,1,1,1,1,1}; // 1=open, 0=closed

float totalIncome = 0;

char *vehicleNames[] = {"Car", "Bus", "Truck", "Bike", "Van", "Mini Truck"};    //Vehicles
char *exitNames[] = {"Gulistan", "Motijheel", "Janapath", "Sayedabad", "Shanir Akhra", "Chankharpool"}; //Exits
float exitDistances[] = {2.0, 4.0, 5.0, 6.0, 8.0, 10.0};    //Distances

void tollSystem();
void adminMenu();
int adminLogin();
void closeExitLocations();
void showHistory();
void changeCredentials();
void saveHistoryToFile();

int main()
{
    int opt1;  // first input
    do
    {
        printf("===============================\n");
        printf("===== Welcome to Flyover ======\n");
        printf("===============================\n");
        printf("=== 1. Toll System          ===\n");
        printf("=== 2. Administration Login ===\n");
        printf("=== 3. Exit                 ===\n");
        printf("===============================\n\n");

        printf("Select option: ");
        scanf("%d", &opt1);

        switch(opt1)
        {
            case 1:
                tollSystem();
                break;
            case 2:
                if (adminLogin())
                    adminMenu();
                break;
            case 3:
                saveHistoryToFile();  // save before exit

                printf("Application closed.\n");
                exit(0);

            default:
                printf("Invalid option!\n");
        }
    } while(1);

    return 0;
}

void tollSystem()   //Toll System
{
    int opt2, exitopt2;
    float paid, totalToll;

    do
    {
        printf("\n");
        printf("========= TOLL SYSTEM =========\n");
        for(int i=0; i < MAX_VEHICLE_TYPES; i++)
            {
                printf("===");
                printf(" %d. %s\n", i+1, vehicleNames[i]);

            }

        printf("=== 7. Back to Main Menu\n");
        printf("===============================\n\n");

        printf("Enter vehicle type: ");
        scanf("%d", &opt2);

        if(opt2 >= 1 && opt2 <= MAX_VEHICLE_TYPES)
        {
            printf("\n");
            printf("=========== Available Exits: ==========\n");

            for(int i = 0; i < MAX_EXITS; i++)
                {
                    printf("===");
                    printf(" %d. %s (%.1f km) \t[%s]\n", i+1, exitNames[i], exitDistances[i], exitOpen[i] ? "OPEN" : "CLOSED");
                }

            printf("=======================================\n\n");

            printf("Choose exit: ");
            scanf("%d", &exitopt2);

            if(exitopt2 >= 1 && exitopt2 <= MAX_EXITS)
            {
                if(exitOpen[exitopt2 - 1])
                {
                    float distance = exitDistances[exitopt2-1];

                    totalToll = (opt2 * opt2 * 10) + distance;  // formula for toll asked

                    printf("\nToll for %s to %s: %.2f\n", vehicleNames[opt2-1], exitNames[exitopt2-1], totalToll);

                    float paid = 0.0;

                    while (paid < totalToll - 0.0)      // Keep asking until toll is fully paid
                    {
                        float paid_now;

                        printf("Enter amount paid: ");
                        scanf("%f", &paid_now);

                        paid += paid_now;

                        if (paid < totalToll - 0.0)
                        {
                            printf("Insufficient payment! You still owe: %.2f\n", totalToll - paid);
                        }
                    }

                    if (paid > totalToll + 0.0)
                    {
                        printf("Payment accepted. Change: %.2f\nHave a safe journey!\n", paid - totalToll);
                    }
                    else
                    {
                        printf("Payment accepted. Change: 0.0 \nHave a safe journey!\n");
                    }

                    vehicleCount[opt2-1]++;
                    totalIncome += totalToll;
                }
                else
                {
                    printf("This exit is currently CLOSED. Please choose another.\n");
                }
            }
            else
            {
                printf("Invalid exit number!\n");
            }
        }
        else if(opt2 == 7)
        {
            return;
        }
        else
        {
            printf("Invalid option!\n");
        }
    } while(1);
}

int adminLogin()    // Admin Login
{
    char id[20], pass[20];

    for(int tries = 0; tries < 3; tries++)
    {
        printf("Enter ID: ");
        scanf("%s", id);

        printf("Enter Password: ");
        scanf("%s", pass);

        if(strcmp(id, admin.id) == 0 && strcmp(pass, admin.pass) == 0)
        {
            printf("=== Login successful! ===\n");
            return 1;
        }
        else
        {
            printf("Invalid credentials! Tries left: %d\n", 2-tries);
        }
    }

    return 0;
}

void adminMenu()    // Admin Menu
{
    int opt3;

    do
    {
        printf("====================================\n");
        printf("============== ADMIN MENU ==========\n");
        printf("====================================\n");
        printf("=== 1. Close/Open Exit Locations ===\n");
        printf("=== 2. View Vehicle History      ===\n");
        printf("=== 3. Change Credentials        ===\n");
        printf("=== 4. Back to Main Menu         ===\n");
        printf("====================================\n");

        printf("Enter option: ");
        scanf("%d", &opt3);

        switch(opt3)
        {
            case 1:
                closeExitLocations();
                break;
            case 2:
                showHistory();
                break;
            case 3:
                changeCredentials();
                break;
            case 4:
                return;
            default:
                printf("Invalid option!\n");
        }
    } while(1);
}


void closeExitLocations()       // Close Exits
{
    int exitNum;
    printf("\nExit Status:\n");

    for(int i=0; i<MAX_EXITS; i++)
    {
        printf("%d. %s\t\t[%s]\n", i+1, exitNames[i], exitOpen[i] ? "Open" : "Closed");
    }

    printf("Enter exit number to change status: ");
    scanf("%d", &exitNum);

    if(exitNum >= 1 && exitNum <= MAX_EXITS)
    {
        exitOpen[exitNum-1] = !exitOpen[exitNum-1];
        printf("%s is now %s.\n", exitNames[exitNum-1], exitOpen[exitNum-1] ? "Open" : "Closed");
    }
    else
    {
        printf("Invalid exit number!\n");
    }
}

void showHistory()      // Show Vehicle History
{
    printf("\nVehicle History:\n");

    for(int i=0; i<MAX_VEHICLE_TYPES; i++)
    {
        printf("%s: %d\n", vehicleNames[i], vehicleCount[i]);
    }

    printf("Total Income: %.2f\n", totalIncome);
}

void changeCredentials()    // Change Credentials
{
    printf("Enter new Admin ID: ");
    scanf("%s", admin.id);

    printf("Enter new Password: ");
    scanf("%s", admin.pass);

    printf("Credentials updated successfully.\n");
}

void saveHistoryToFile()    // Save History to File
{
    FILE *fp = fopen("toll_history.txt", "a");   // append "NOT REWRITTING"

    if(fp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    for(int i=0; i<MAX_VEHICLE_TYPES; i++)
    {
        fprintf(fp, "%s: %d\n", vehicleNames[i], vehicleCount[i]);
    }

    fprintf(fp, "Total Income: %.2f\n\n", totalIncome);

    fclose(fp);
}

