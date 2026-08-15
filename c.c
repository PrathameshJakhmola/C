#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_ITEMS 100
#define FILE_NAME "lost_found.dat"

typedef struct
{
    int id;
    char itemName[50];
    char category[30];
    char location[50];
    char finderName[50];
    char contact[20];
    char date[20];
    int claimed;
} LostItem;

LostItem items[MAX_ITEMS];
int itemCount = 0;


/* Function Prototypes */

void loadData();
void saveData();
void addItem();
void displayItems();
void searchItem();
void searchLocation();
void claimItem();
void deleteItem();
void displaySingleItem(LostItem item);
void clearInputBuffer();
void toLowerCase(char str[]);
void pauseScreen();


/* Main Function */

int main()
{
    int choice;

    loadData();

    while (1)
    {
        printf("\n");
        printf("===============================================\n");
        printf("        CAMPUS LOST & FOUND SYSTEM\n");
        printf("===============================================\n");
        printf("1. Report Found Item\n");
        printf("2. View All Items\n");
        printf("3. Search Item\n");
        printf("4. Search by Location\n");
        printf("5. Mark Item as Claimed\n");
        printf("6. Delete Item\n");
        printf("7. Exit\n");
        printf("===============================================\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);
        clearInputBuffer();

        switch (choice)
        {
            case 1:
                addItem();
                break;

            case 2:
                displayItems();
                break;

            case 3:
                searchItem();
                break;

            case 4:
                searchLocation();
                break;

            case 5:
                claimItem();
                break;

            case 6:
                deleteItem();
                break;

            case 7:
                saveData();
                printf("\nThank you for using Campus Lost & Found System!\n");
                return 0;

            default:
                printf("\nInvalid choice! Please enter a number from 1 to 7.\n");
        }
    }

    return 0;
}


/* Clear Input Buffer */

void clearInputBuffer()
{
    int c;

    while ((c = getchar()) != '\n' && c != EOF)
    {
        /* Clear unwanted input */
    }
}


/* Convert String to Lowercase */

void toLowerCase(char str[])
{
    int i;

    for (i = 0; str[i] != '\0'; i++)
    {
        str[i] = (char)tolower((unsigned char)str[i]);
    }
}


/* Add New Item */

void addItem()
{
    if (itemCount >= MAX_ITEMS)
    {
        printf("\nStorage limit reached!\n");
        return;
    }

    LostItem newItem;

    newItem.id = itemCount + 1;
    newItem.claimed = 0;

    printf("\n===============================================\n");
    printf("             REPORT FOUND ITEM\n");
    printf("===============================================\n");

    printf("Enter item name: ");
    fgets(newItem.itemName, sizeof(newItem.itemName), stdin);
    newItem.itemName[strcspn(newItem.itemName, "\n")] = '\0';

    printf("Enter category: ");
    fgets(newItem.category, sizeof(newItem.category), stdin);
    newItem.category[strcspn(newItem.category, "\n")] = '\0';

    printf("Enter found location: ");
    fgets(newItem.location, sizeof(newItem.location), stdin);
    newItem.location[strcspn(newItem.location, "\n")] = '\0';

    printf("Enter finder name: ");
    fgets(newItem.finderName, sizeof(newItem.finderName), stdin);
    newItem.finderName[strcspn(newItem.finderName, "\n")] = '\0';

    printf("Enter contact number: ");
    fgets(newItem.contact, sizeof(newItem.contact), stdin);
    newItem.contact[strcspn(newItem.contact, "\n")] = '\0';

    printf("Enter date (DD/MM/YYYY): ");
    fgets(newItem.date, sizeof(newItem.date), stdin);
    newItem.date[strcspn(newItem.date, "\n")] = '\0';

    items[itemCount] = newItem;
    itemCount++;

    saveData();

    printf("\n-----------------------------------------------\n");
    printf("Item successfully registered!\n");
    printf("Your Item ID is: %d\n", newItem.id);
    printf("-----------------------------------------------\n");

    pauseScreen();
}


/* Display Single Item */

void displaySingleItem(LostItem item)
{
    printf("\n-----------------------------------------------\n");
    printf("Item ID       : %d\n", item.id);
    printf("Item Name     : %s\n", item.itemName);
    printf("Category      : %s\n", item.category);
    printf("Location      : %s\n", item.location);
    printf("Finder Name   : %s\n", item.finderName);
    printf("Contact       : %s\n", item.contact);
    printf("Date          : %s\n", item.date);

    if (item.claimed == 1)
    {
        printf("Status        : CLAIMED\n");
    }
    else
    {
        printf("Status        : AVAILABLE\n");
    }

    printf("-----------------------------------------------\n");
}


/* Display All Items */

void displayItems()
{
    int i;

    printf("\n===============================================\n");
    printf("                 ALL ITEMS\n");
    printf("===============================================\n");

    if (itemCount == 0)
    {
        printf("No items have been registered yet.\n");
        pauseScreen();
        return;
    }

    for (i = 0; i < itemCount; i++)
    {
        displaySingleItem(items[i]);
    }

    pauseScreen();
}


/* Search Item */

void searchItem()
{
    char search[50];
    char itemCopy[50];
    char searchCopy[50];

    int i;
    int found = 0;

    printf("\n===============================================\n");
    printf("                 SEARCH ITEM\n");
    printf("===============================================\n");

    printf("Enter item name to search: ");
    fgets(search, sizeof(search), stdin);
    search[strcspn(search, "\n")] = '\0';

    strcpy(searchCopy, search);
    toLowerCase(searchCopy);

    for (i = 0; i < itemCount; i++)
    {
        strcpy(itemCopy, items[i].itemName);
        toLowerCase(itemCopy);

        if (strstr(itemCopy, searchCopy) != NULL)
        {
            displaySingleItem(items[i]);
            found = 1;
        }
    }

    if (!found)
    {
        printf("\nNo matching item found.\n");
    }

    pauseScreen();
}


/* Search by Location */

void searchLocation()
{
    char search[50];
    char locationCopy[50];
    char searchCopy[50];

    int i;
    int found = 0;

    printf("\n===============================================\n");
    printf("              SEARCH BY LOCATION\n");
    printf("===============================================\n");

    printf("Enter location: ");
    fgets(search, sizeof(search), stdin);
    search[strcspn(search, "\n")] = '\0';

    strcpy(searchCopy, search);
    toLowerCase(searchCopy);

    for (i = 0; i < itemCount; i++)
    {
        strcpy(locationCopy, items[i].location);
        toLowerCase(locationCopy);

        if (strstr(locationCopy, searchCopy) != NULL)
        {
            displaySingleItem(items[i]);
            found = 1;
        }
    }

    if (!found)
    {
        printf("\nNo items found at this location.\n");
    }

    pauseScreen();
}


/* Mark Item as Claimed */

void claimItem()
{
    int id;
    int i;
    int found = 0;

    printf("\n===============================================\n");
    printf("             MARK ITEM AS CLAIMED\n");
    printf("===============================================\n");

    printf("Enter Item ID: ");
    scanf("%d", &id);
    clearInputBuffer();

    for (i = 0; i < itemCount; i++)
    {
        if (items[i].id == id)
        {
            found = 1;

            if (items[i].claimed == 1)
            {
                printf("\nThis item has already been claimed.\n");
            }
            else
            {
                items[i].claimed = 1;
                saveData();

                printf("\nItem successfully marked as CLAIMED!\n");
            }

            break;
        }
    }

    if (!found)
    {
        printf("\nItem ID not found.\n");
    }

    pauseScreen();
}


/* Delete Item */

void deleteItem()
{
    int id;
    int i;
    int j;
    int found = 0;

    printf("\n===============================================\n");
    printf("                DELETE ITEM\n");
    printf("===============================================\n");

    printf("Enter Item ID: ");
    scanf("%d", &id);
    clearInputBuffer();

    for (i = 0; i < itemCount; i++)
    {
        if (items[i].id == id)
        {
            found = 1;

            for (j = i; j < itemCount - 1; j++)
            {
                items[j] = items[j + 1];
            }

            itemCount--;

            /*
             * Reassign IDs after deletion
             */
            for (j = 0; j < itemCount; j++)
            {
                items[j].id = j + 1;
            }

            saveData();

            printf("\nItem deleted successfully.\n");

            break;
        }
    }

    if (!found)
    {
        printf("\nItem ID not found.\n");
    }

    pauseScreen();
}


/* Save Data to File */

void saveData()
{
    FILE *file;

    file = fopen(FILE_NAME, "wb");

    if (file == NULL)
    {
        printf("\nError: Unable to save data.\n");
        return;
    }

    fwrite(&itemCount, sizeof(int), 1, file);

    fwrite(items, sizeof(LostItem), itemCount, file);

    fclose(file);
}


/* Load Data from File */

void loadData()
{
    FILE *file;

    file = fopen(FILE_NAME, "rb");

    if (file == NULL)
    {
        itemCount = 0;
        return;
    }

    fread(&itemCount, sizeof(int), 1, file);

    if (itemCount > MAX_ITEMS)
    {
        itemCount = 0;
        fclose(file);
        return;
    }

    fread(items, sizeof(LostItem), itemCount, file);

    fclose(file);
}


/* Pause Screen */

void pauseScreen()
{
    printf("\nPress ENTER to continue...");
    getchar();
}