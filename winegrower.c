#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "winegrower.h"

// Parse a tDate from string information
void date_parse(tDate* date, const char* text)
{
    // Check output data
    assert(date != NULL);
    
    // Check input date
    assert(text != NULL);
    assert(strlen(text) == DATE_LENGTH);
 
    // Parse the input date
    sscanf(text, "%d/%d/%d", &(date->day), &(date->month), &(date->year));
}

// Compare two tDate structures and return true if they contain the same value or false otherwise.
bool date_equals(tDate date1, tDate date2)
{
    return (date1.day == date2.day && date1.month == date2.month && date1.year == date2.year); 
}

// EX2: Implement your methods here...

// Initialize the winegrowers data
void winegrowerData_init(tWinegrowerData* data)
{
    data->nWinegrowers = 0;
}

// Get the number of registered winegrowers
int winegrowerData_len(tWinegrowerData data)
{
    return data.nWinegrowers;
}

// Get a winegrower data by the position in the list and output formated data
void winegrowerData_get(tWinegrowerData data, int index, char* buffer)
{
    assert( index >= 0 && index < data.nWinegrowers) ;

    // Valid index, proceed to format the data
    tWinegrower wg = data.winegrowersTable[index];

    snprintf(buffer, (size_t) 1024, "%02d/%02d/%04d;%s;%s;%s;%s;%.2f",
                wg.registrationDate.day, wg.registrationDate.month, wg.registrationDate.year,
                wg.document, wg.vineGrowerId, wg.DO, wg.vineyardplotid, wg.weight);

}

// Parse input data from CSVEntry
void winegrower_parse(tWinegrower* wg, tCSVEntry entry)
{
    assert(entry.numFields > 0);

    // Parse the date
    date_parse(&(wg->registrationDate), entry.fields[0]);

    // Copy the document
    strncpy(wg->document, entry.fields[1], DOCUMENT_LENGTH);
    wg->document[DOCUMENT_LENGTH + 1] = '\0';

    // Copy the vineGrowerId
    strncpy(wg->vineGrowerId, entry.fields[2], MAX_WINEGROWERSID);
    wg->vineGrowerId[MAX_WINEGROWERSID + 1] = '\0';

    // Copy the DO code
    strncpy(wg->DO, entry.fields[3], DOCODE_LENGTH);
    wg->DO[DOCODE_LENGTH + 1] = '\0';

    // Copy the vineyardplotid
    strncpy(wg->vineyardplotid, entry.fields[4], MAX_VINEYARDPLOTID);
    wg->vineyardplotid[MAX_VINEYARDPLOTID + 1] = '\0';

    // Parse the weight
    wg->weight = atof(entry.fields[5]);
}

// Add a new winegrower
void winegrowerData_add(tWinegrowerData* data, tWinegrower wg)
{
    assert(data->nWinegrowers < MAX_WINEGROWERS);
    
    // Check for existing winegrower with the same ID
    int matchIndex = _getIndexFromId(data, wg.vineGrowerId);

    if (matchIndex >= 0){
        data->winegrowersTable[matchIndex].weight += wg.weight;
        return;
    }

    // If no existing winegrower is found, add the new one
    if (data->nWinegrowers < MAX_WINEGROWERS) {
        data->winegrowersTable[data->nWinegrowers] = wg;
        data->nWinegrowers++;
    } else {
        printf("Unable to add winegrower: WinegrowerData is full.\n");
    }
}

// Remove a winegrower
void winegrowerData_del(tWinegrowerData* data, char* id) 
{
    int matchIndex = _getIndexFromId(data, id);

    // Search for the winegrower with the specified ID

    // If the winegrower is found, Shift all winegrowers 1 position and decrease the count
    if (matchIndex != -1) {
        for (int i = matchIndex; i < data->nWinegrowers - 1; i++) {
            data->winegrowersTable[i] = data->winegrowersTable[i + 1];
        }
        data->nWinegrowers--;
    } else {
        printf("No winegrower found with id: %s\n", id);
    }
}


// EX2: Implement any auxiliary method here...
int _getIndexFromId(tWinegrowerData* data, char* id){
    for (int i = 0; i < data->nWinegrowers; i++) {
        if (strcmp(data->winegrowersTable[i].vineGrowerId, id) == 0) {
            return i;
            break;
        }
    }

    return -1;
}
