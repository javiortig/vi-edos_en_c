#ifndef __WINEGROWER_H__
#define __WINEGROWER_H__
#include "csv.h"

typedef struct {    
    int day; 
    int month;
    int year;
} tDate;

// Parse a tDate from string information
void date_parse(tDate* date, const char* text);

// Compare two tDate structures and return true if they contain the same value or false otherwise.
bool date_equals(tDate date1, tDate date2);

// Ex 1: Define data types here...

///////////////////////////

// Length of the date
#define DATE_LENGTH 10
#define DOCUMENT_LENGTH 9
#define DOCODE_LENGTH 2
#define MAX_WINEGROWERS 200
#define MAX_WINEGROWERSID 14
#define MAX_VINEYARDPLOTID 13

typedef struct {
    char document[DOCUMENT_LENGTH + 1];
    char vineGrowerId[MAX_WINEGROWERSID + 1];
    tDate registrationDate;
    char DO[DOCODE_LENGTH + 1];
    char vineyardplotid[MAX_VINEYARDPLOTID + 1];
    float weight;

} tWinegrower;

typedef struct {
    tWinegrower winegrowersTable[MAX_WINEGROWERS];
    int nWinegrowers;
} tWinegrowerData;

//////////////////////////////////

// Ex 2: Define your methods here ....

// Initialize the list of winegrowers
void winegrowerData_init(tWinegrowerData* data);

// Get the number of registered winegrowers
int winegrowerData_len(tWinegrowerData data);

// Get a winegrower by the position in the list
// void winegrowerData_get(tWinegrowerData data, int index, char* buffer);

// Parse input from CSVEntry
void winegrower_parse(tWinegrower* wg, tCSVEntry entry);

// ...

// Add a new winegrower to the list
void winegrowerData_add(tWinegrowerData* data, tWinegrower wg);

// Remove a winegrower from the list
void winegrowerData_del(tWinegrowerData* data, char *id);

////////////////////////////////////////////

int _getIndexFromId(tWinegrowerData* data, char* id);

#endif
