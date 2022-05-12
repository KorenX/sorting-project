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
#define FINISH_RUNNING_TESTS(tests_group) printf("finished running tests " #tests_group "\n")

#define RANDOM_TESTS_AMOUNT 11
#define RANDOM_TEST_FAILED(test_function, i) printf("test named " # test_function " number %u"  RED " failed\n" RESET, i)
#define RANDOM_TEST_SUCCEEDED(test_function, i) printf("test named " # test_function " number %u"  GREEN " succeeded\n" RESET, i)
#define RUN_RANDOM_TEST(test_function, amount) for (size_t i = 0; i < amount; i++){if(!test_function()) RANDOM_TEST_FAILED(test_function, i); else RANDOM_TEST_SUCCEEDED(test_function, i);}

#endif //__TESTS_UTILS_H__