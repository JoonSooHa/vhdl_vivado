#include <stdio.h>
#include "mycounter.h"
#include "xparameters.h"
#include "xil_io.h"


unsigned int cnt_val;
int min, sec;

void watch()
{
    min = 0;
    sec = 0;

    printf("%02d : %02d\r", min, sec);
    MYCOUNTER_mWriteReg(XPAR_MYCOUNTER_0_S00_AXI_BASEADDR, 4, 1); // start counter

    for(int i=0; i<180; i++) {
        while(1) {
            cnt_val = (unsigned int)MYCOUNTER_mReadReg(XPAR_MYCOUNTER_0_S00_AXI_BASEADDR, 8); // read counter
            if(cnt_val >= 90000000) break;
        }

        if(++sec >= 60) {sec = 0; min++;}
        printf("%02d : %02d\n\r", min, sec);

        while(1) {
            cnt_val = (unsigned int)MYCOUNTER_mReadReg(XPAR_MYCOUNTER_0_S00_AXI_BASEADDR, 8); // read counter
            if (cnt_val < 90000000) break;
        }
    }
}

int main()
{
	char c;

	while(1) {
		printf("==== Menu Option ====\n\r");
		printf("r. clear counter\n\r");
		printf("s. start counter\n\r");
		printf("t. stop counter\n\r");
		printf("c. read current counter value\n\r");
        printf("w. watch(for 3 min)\n\r");
		printf("x. finish\n\r");
		printf("Select Menu : ");
		c = getchar();

		printf("==> Selected Menu : %c\n\r", c);

		if (c == 'r') {
			// clear counter
			MYCOUNTER_mWriteReg(XPAR_MYCOUNTER_0_S00_AXI_BASEADDR, 0, 1);
			MYCOUNTER_mWriteReg(XPAR_MYCOUNTER_0_S00_AXI_BASEADDR, 0, 0);
		} else if (c == 's') {
			MYCOUNTER_mWriteReg(XPAR_MYCOUNTER_0_S00_AXI_BASEADDR, 4, 1); // start counter
		} else if (c == 't') {
			MYCOUNTER_mWriteReg(XPAR_MYCOUNTER_0_S00_AXI_BASEADDR, 4, 0); // stop counter
		} else if (c == 'c') {
			cnt_val = (unsigned int)MYCOUNTER_mReadReg(XPAR_MYCOUNTER_0_S00_AXI_BASEADDR, 8); // read counter
			printf("current counter value is %10u\n\r", cnt_val);
		} else if (c == 'w') {
            watch();
        } else if (c == 'x') {
			break;
		} else {
			printf("WRONG COMMAND\n\r");
		}
	}

	printf("program finished\n\r");
    return 0;
}
