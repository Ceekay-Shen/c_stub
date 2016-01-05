#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <stdint.h>
#include <string.h>
#include <sys/mman.h>

/* func2
 * -
 *     func1
 *     -
 *      ----
 *          ----------
 *          EIP
 */

void func2()
{
	printf("stub_fun\n");
}

void func1()
{
	printf("fun\n");
}

int main(int argc, char *argv[])
{
	char buf[6];
	long page_size = getpagesize();


	mprotect((void *)((uint64_t)func1 & ~(page_size - 1)), page_size, PROT_READ | PROT_WRITE | PROT_EXEC);

	memcpy(buf, func1, 6);

	*(char *)func1 = 0xE8; //callq
	uint32_t offset = (char *)func2 - (char *)func1 - 5;
	memcpy(func1 + 1, &offset, sizeof(uint32_t));
        *(char *)(func1+5) = 0xC3; //retq

	func1();
	memcpy(func1, buf, 6);
	func1();

	mprotect((void *)((uint64_t)func1 & ~(page_size - 1)), page_size, PROT_READ | PROT_EXEC);
    
	return 0;
}

