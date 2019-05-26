#include <stdio.h>
#include "mycounter.h"
#include "xparameters.h"
#include "xil_io.h"
#include "xintc.h"
#include "xil_exception.h"
#include "xstatus.h"

unsigned int cnt_val;
int min = 0, sec = 0;

static XIntc InterruptController;

int initialize_interrupt();
void counter_handler(void *CallbackRef);
void watch();

int main()
{
	char c;

	initialize_interrupt();

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

int initialize_interrupt()
{
	int status;

	status = XIntc_Initialize(&InterruptController, XPAR_INTC_0_DEVICE_ID);
    if(status != XST_SUCCESS)
    	return XST_FAILURE;

    status = XIntc_Connect(&InterruptController, XPAR_INTC_0_MYCOUNTER_0_VEC_ID, (XInterruptHandler)counter_handler, (void *)0);
    if(status != XST_SUCCESS)
		return XST_FAILURE;

    status = XIntc_Start(&InterruptController, XIN_REAL_MODE);
    if(status != XST_SUCCESS)
		return XST_FAILURE;

    Xil_ExceptionInit();
    Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT, (Xil_ExceptionHandler)XIntc_InterruptHandler, &InterruptController);
    Xil_ExceptionEnable();

    return XST_SUCCESS;
}

void counter_handler(void *CallbackRef)
{
	static int int_cnt = 0;

	if(++int_cnt == 120) {
		XIntc_Disable(&InterruptController, XPAR_INTC_0_MYCOUNTER_0_VEC_ID);
		int_cnt = 0;
	}

	printf("%02d : %02d\n\r", min, sec);
	if(++sec >= 60) {sec = 0; min++;}
}

void watch()
{
	min = 0; sec = 0;

    MYCOUNTER_mWriteReg(XPAR_MYCOUNTER_0_S00_AXI_BASEADDR, 4, 1); // start counter
    XIntc_Enable(&InterruptController, XPAR_INTC_0_MYCOUNTER_0_VEC_ID);
}
