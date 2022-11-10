/*
 * test_llfifo.h includes all the declarations of functions used in test_cbfifo().
 * The details of each function is given below.
 *
 * Author: Harsh Beriwal
 * IDE Used: MCUXpresso IDE v11.6.0 [Build 8187] [2022-07-13]
 * Github Link: https://github.com/harshberiwal/PES_Assignment_6
 *
 * No leveraged code or files
 *
 */

#ifndef TEST_CBFIFO_H_
#define TEST_CBFIFO_H_

#define ONE 1

#define CHECK if(test_failed)return 0;
#define MAX_SIZE 4294967295

#endif /* TEST_CBFIFO_H_ */

/*
 * Thoroughly checks cbfifo.c
 *
 * Parameters:
 *   None
 *
 * Returns:
 *   If All tests are successful, it returns 1 otherwise 0 in case of any failed test.
 */
int test_cbfifo();


/*
 * Compares Dequeued Number of Elements with Expected
 *
 * Parameters:
 *   Val1 - Actual Number of ELements Dequeued
 *   Val2 - Expected Number of Elements to be Dequeued
 *
 * Returns:
 *   If both val1 and val2 matches, it prints passed otherwise fails and sets test_failed
 *   flag
 */
void test_cbfifo_dequeued(int val1, int val2);


/*
 * Compares Enqueues Return Value with Expected
 *
 * Parameters:
 *   Val1 - Actual Output
 *   Val2 - Expected Output
 *
 * Returns:
 *   If both val1 and val2 matches, it prints passed otherwise fails and sets test_failed
 *   flag
 */
void test_cbfifo_compare_return(int val_1, int val_2);


/*
 * Compares Actual Capacity with Expected capacity
 *
 * Parameters:
 *   Val1 - Actual capacity
 *   Val2 - Expected capacity
 *
 * Returns:
 *   If both val1 and val2 matches, it prints passed otherwise fails and sets test_failed
 *   flag
 */
void test_cbfifo_compare_capacity(int val_1, int val_2);


/*
 * Compares Actual Length with Expected Length
 *
 * Parameters:
 *   Val1 - Actual Length
 *   Val2 - Expected Length
 *
 * Returns:
 *   If both val1 and val2 matches, it prints passed otherwise fails and sets test_failed
 *   flag
 */
void test_cbfifo_compare_length(int val_1, int val_2);

/*
 * Compares Actual Dequeued Element with Expected Element char by char
 *
 * Parameters:
 *   Val1 - Actual Dequeued Element
 *   Val2 - Expected Dequeued Element
 *
 * Returns:
 *   If both val1 and val2 matches, it prints passed otherwise fails and sets test_failed
 *   flag
 */
void test_dequeued_elements(int val1, int val2);
