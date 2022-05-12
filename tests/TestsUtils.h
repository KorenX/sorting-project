#ifndef __TESTS_UTILS_H__
#define __TESTS_UTILS_H__

#include <stdio.h>

#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */

#define ASSERT_EQ(a, b) if(a!=b) {printf("expected value " # a " which is %x to be equal to " # b " which is %x\n",a,b);return false;}
#define ASSERT_NE(a, b) if(a==b) {printf("expected value " # a " which is %x to be different than " # b " which is %x\n",a,b);return false;}
#define ASSERT_GE(a, b) if(a<b) {printf("expected value " # a " which is %x to be greater or equal to " # b " which is %x\n",a,b);return false;}
#define ASSERT_LE(a, b) if(a>b) {printf("expected value " # a " which is %x to be smaller or equal to " # b " which is %x\n",a,b);return false;}
#define ASSERT_GT(a, b) if(a<=b) {printf("expected value " # a " which is %x to be greater than " # b " which is %x\n",a,b);return false;}
#define ASSERT_LT(a, b) if(a>=b) {printf("expected value " # a " which is %x to be smaller than " # b " which is %x\n",a,b);return false;}
#define ASSERT_TRUE(a) ASSERT_EQ(a, true)
#define TEST_END return true

#define TEST_FAILED(test_function) printf("test named " # test_function  RED " failed\n" RESET)
#define TEST_SUCCEEDED(test_function) printf("test named " # test_function  GREEN " succeeded\n" RESET)
#define RUN_TEST(test_function) if(!test_function()) TEST_FAILED(test_function); else TEST_SUCCEEDED(test_function);
#define FINISH_RUNNING_TESTS printf("finished running tests\n")


#endif //__TESTS_UTILS_H__