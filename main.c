#include <stdio.h>
#include "csv.h"
#include "winegrower.h"


void winegrowerData_print_src(tWinegrowerData data) {
    char buffer[1024];
    int i;
    if (winegrowerData_len(data) > 0) {
        for(i = 0 ; i < winegrowerData_len(data) ; i++) {
            winegrowerData_get(data, i, buffer);
            printf("%d;%s\n", i, buffer);
        }
    }    
}

int main(int argc, char **argv)
{    
    tCSVData test_data;      
    tWinegrowerData wgData;
    tWinegrower wg;
    int i;
 
    // Define test data

    // New entries
    const char* test_data_str1 = \
                "01/12/2023;12345678N;01234567890123;TA;TA12345678001;1184.00\n" \
                "10/12/2023;55755010C;23456789012345;MO;MO55755010001;2500.10\n" \
                "15/01/2024;87654321B;56789012345678;PR;PR87654321001;4800.50\n";

    // Entry already existent
    const char* test_data_str2 = \
                "15/01/2024;87654321B;56789012345678;PR;PR87654321001;500.00\n" \
                "22/02/2024;55755010C;23456789012345;PR;PR55755010002;1520.00\n"; 

    // Initialize the winegrowers' data
    winegrowerData_init(&wgData);


    /////// Add 3 new winegrowers ////////

    // Read the data in CSV format
    csv_init(&test_data);
    csv_parse(&test_data, test_data_str1, "WINEGROWER");

    // Add data
    for(i = 0; i < csv_numEntries(test_data); i++) {
        // Get the winegrower from the entry
        winegrower_parse(&wg, csv_getEntry(test_data, i)[0]);
        // Add new winegrower to the list 
        winegrowerData_add(&wgData, wg);
    }
    // List current winegrowers
    printf("\n");
    winegrowerData_print_src(wgData);
    printf("\n");
    // Remove old data
    csv_free(&test_data);
  
 
    /////// Add 1 already existent winegrower ////////

   // Read the data in CSV format
    csv_init(&test_data);
    csv_parse(&test_data, test_data_str2, "WINEGROWER");
    // Add data
    for(i = 0; i < csv_numEntries(test_data); i++) {
        // Get the winegrower from the entry
        winegrower_parse(&wg, csv_getEntry(test_data, i)[0]);
        // Add new winegrower to the list 
        winegrowerData_add(&wgData, wg);
    }
    // List current winegrowers
    printf("\n");
    winegrowerData_print_src(wgData);
    printf("\n");
    // Remove old data
    csv_free(&test_data);

  /////// Delete existent winegrower ////////

    // Delete winegrower from the list 
    winegrowerData_del(&wgData, "23456789012345");
    // List current winegrowers
    printf("\n");
    winegrowerData_print_src(wgData);
    printf("\n");

  /////// Delete non-existent winegrower ////////

    // Delete winegrower from the list 
    winegrowerData_del(&wgData, "23456789012345");
    // List current winegrowers
    printf("\n");
    winegrowerData_print_src(wgData);
    printf("\n");
    
    
    printf("\nPress key to end...\n");
    getchar();
	return 0;
}
