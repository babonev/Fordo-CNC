/*!
 * @file      main.cpp
 * @brief     Class to manage a stepper motor
 * @details
 * @author    Boyan Bonev
 * @version   0.1
 * @date      02.Nov.2016
 *
 * @copyright
 ******************************************************************************/

#include <stdio.h>
#include <conio.h>
#include <string.h>
#include "Std_Types.h"
#include "CSequenceReader.h"

#define GCODE_FILE              ".\\examples\\simple_form2_0.rou"
#define TEST_LINE_PATH          ".\\Test\\"

int main()
{
    FILE *fGCodeFileHandle;
    char buff[255];
    uint16 idxLine;

    CSequenceReader parser;

    fGCodeFileHandle = fopen(GCODE_FILE, "r");

    if ( fGCodeFileHandle )
    {
        parser.init();

        printf("file: %s\n\n", GCODE_FILE );

        idxLine = 0;
        while ( fgets(buff, sizeof(buff), fGCodeFileHandle) != NULL )
        {
            idxLine++;
            printf("%d: %s", idxLine, buff );

            parser.process((uint8*)buff, strlen(buff));
        }

        fclose(fGCodeFileHandle);
    }
    else
    {
        printf("ERROR: Probably input file not found!\n%s\n", GCODE_FILE);
    }


    return 0;
}
