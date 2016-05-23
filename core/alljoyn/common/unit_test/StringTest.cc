/******************************************************************************
 *
 * Copyright AllSeen Alliance. All rights reserved.
 *
 *    Contributed by Qualcomm Connected Experiences, Inc.,
 *    with authorization from the AllSeen Alliance, Inc.
 *    
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *    
 *        http://www.apache.org/licenses/LICENSE-2.0
 *    
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 *    
 *    Pursuant to Section 1 of the License, the work of authorship constituting
 *    a Work and any Contribution incorporated in the Work shall mean only that
 *    Contributor's code submissions authored by that Contributor.  Any rights
 *    granted under the License are conditioned upon acceptance of these
 *    clarifications.
 ******************************************************************************/
#include <gtest/gtest.h>
#include <qcc/String.h>

#include <sstream>

TEST(StringTest, constructor) {
    const char* testStr = "abcdefgdijk";

    qcc::String s(testStr);
    ASSERT_STREQ(testStr, s.c_str());
    ASSERT_EQ(::strlen(testStr), s.size());
}

TEST(StringTest, find_first_of) {
    const char* testStr = "abcdefgdijk";
    qcc::String s(testStr);

    /* Test find_first_of */
    ASSERT_EQ(static_cast<size_t>(3), s.find_first_of('d'));
    ASSERT_EQ(static_cast<size_t>(3), s.find_first_of('d', 3));
    ASSERT_EQ(static_cast<size_t>(3), s.find_first_of("owed", 3));
    ASSERT_EQ(+qcc::String::npos, s.find_first_of('d', 8));
}

TEST(StringTest, find_last_of) {
    const char* testStr = "abcdefgdijk";
    qcc::String s(testStr);

    /* Test find_last_of */
    ASSERT_EQ(static_cast<size_t>(7), s.find_last_of('d'));
    ASSERT_EQ(static_cast<size_t>(7), s.find_last_of('d', 7));  // Old qcc::String difference
    ASSERT_EQ(static_cast<size_t>(3), s.find_last_of('d', 6));
    /*
     * unusual use of the unary operator '+' makes gcc compiler see qcc::String::npos as a rvalue
     * this prevents an 'undefined reference' compiler error when building with gcc.
     */
    ASSERT_EQ(+qcc::String::npos, s.find_last_of('d', 2));
}

TEST(StringTest, find_first_not_of) {
    const char* testStr = "abcdefgdijk";
    qcc::String s(testStr);

    /* Test find_*_not_of */
    qcc::String ss = "xyxyxyx" + s + "xy";
    ASSERT_EQ(static_cast<size_t>(7), ss.find_first_not_of("xy"));
    ASSERT_EQ(static_cast<size_t>(17), ss.find_last_not_of("xy"));
}

TEST(StringTest, empty) {
    const char* testStr = "abcdefgdijk";
    qcc::String s(testStr);

    /* Test empty */
    ASSERT_FALSE(s.empty());
    s.clear();
    ASSERT_TRUE(s.empty());
    ASSERT_EQ(static_cast<size_t>(0), s.size());
}

TEST(StringTest, operator_equals) {
    qcc::String s;
    /* Test operator= */
    s = "123456";
    ASSERT_STREQ("123456", s.c_str());
}

TEST(StringTest, copyConstructor) {
    /* test copy constructor */
    qcc::String s2 = "abcdefg";
    qcc::String t2 = s2;
    ASSERT_TRUE(t2 == s2);
    ASSERT_TRUE(t2 == "abcdefg");
}

TEST(StringTest, append) {
    /* Test append */
    qcc::String pre = "abcd";
    qcc::String post = "efgh";
    pre.append(post);
    ASSERT_STREQ("abcdefgh", pre.c_str());
    ASSERT_EQ(::strlen("abcdefgh"), pre.size());
    ASSERT_STREQ("efgh", post.c_str());
    ASSERT_EQ(::strlen("efgh"), post.size());

    pre.append("ijklm", 4);
    ASSERT_EQ(::strlen("abcdefghijkl"), pre.size());
    ASSERT_STREQ("abcdefghijkl", pre.c_str());
}

TEST(StringTest, erase) {
    qcc::String pre("abcdefghijkl");
    /* Test erase */
    pre.erase(4, 2);
    ASSERT_STREQ("abcdghijkl", pre.c_str());

    /*
     * Test erasing past the end of the string. It should stop at the string
     * size.
     */
    pre.erase(pre.size() - 1, 100);
    ASSERT_STREQ("abcdghijk", pre.c_str());

    /*
     * Test erasing after the end of the string. It should be a no-op and should
     * not trigger any crash.
     */
    pre.erase(pre.size(), 2);
    ASSERT_STREQ("abcdghijk", pre.c_str());

    //pre.erase(pre.size() + 1, 100);  // Causes out_of_range exception for std::string
    //ASSERT_STREQ("abcdghijk", pre.c_str());
}

TEST(StringTest, resize) {
    qcc::String pre("abcdefghijk");
    ASSERT_EQ(static_cast<size_t>(11), pre.size());
    /* Test resize */
    pre.resize(4, 'x');
    ASSERT_EQ(static_cast<size_t>(4), pre.size());
    ASSERT_STREQ("abcd", pre.c_str());

    pre.resize(8, 'x');
    ASSERT_EQ(static_cast<size_t>(8), pre.size());
    ASSERT_STREQ("abcdxxxx", pre.c_str());
}

TEST(StringTest, reserve) {
    qcc::String pre("abcdxxxx");

    /* Test reserve */
    pre.reserve(100);
    const char* preAppend = pre.c_str();
    pre.append("y", 92);
    ASSERT_STREQ(preAppend, pre.c_str());
}

TEST(StringTest, insert) {
    /* Test insert */
    qcc::String s5 = "abcdijkl";
    s5.insert(4, "efgh");
    ASSERT_STREQ("abcdefghijkl", s5.c_str());
}

TEST(StringTest, logicOperators) {
    /* Test operator== and operator!= */
    qcc::String s5 = "abcdefghijkl";
    qcc::String s6 = "abcdefghijkl";
    ASSERT_TRUE(s5 == s6);
    ASSERT_FALSE(s5 != s6);

    /* Test operator< */
    ASSERT_FALSE(s5 < s6);
    ASSERT_FALSE(s6 < s5);
    s6.append(1, 'm');
    ASSERT_TRUE(s5 < s6);
    ASSERT_FALSE(s6 < s5);
}

TEST(StringTest, threeParamConstructor) {
    /* Test String(size_t, char) */
    qcc::String s3(8, 's');
    ASSERT_STREQ("ssssssss", s3.c_str());
    ASSERT_EQ(::strlen("ssssssss"), s3.size());
}

TEST(StringTest, arrayOperator1) {
    /* test copy constructor and char& operator[] */
    qcc::String s2 = "abcdefg";
    qcc::String t2 = s2;
    t2[1] = 'B';
    ASSERT_STREQ("abcdefg", s2.c_str());
    ASSERT_STREQ("aBcdefg", t2.c_str());
}

TEST(StringTest, arrayOperator2) {
    /* Test const char& operator[] */
    const char* testChars = "abcdefgh";
    qcc::String s7 = testChars;
    const char* orig = s7.c_str();
    ASSERT_EQ(::strlen(testChars), s7.size());
    for (size_t i = 0; i < s7.size(); ++i) {
        char c = s7[i];
        ASSERT_EQ(c, testChars[i]);
    }
    ASSERT_STREQ(orig, s7.c_str());
}

TEST(StringTest, arrayOperator3) {
    const char* testStr = "abcdefgdijk";
    qcc::String s = testStr;
    ASSERT_EQ('a', s[0]);
    ASSERT_EQ('k', s[10]);
}
TEST(StringTest, iterators) {
    const char* testChars = "abcdefgh";

    /* Test iterators */
    qcc::String s4(strlen(testChars), 'x');
    qcc::String::iterator it = s4.begin();
    for (size_t i = 0; i < s4.size(); ++i) {
        *it++ = testChars[i];
    }
    qcc::String::const_iterator cit = s4.begin();
    ASSERT_EQ(strlen(testChars), s4.size());
    size_t i = 0;
    while (cit != s4.end()) {
        ASSERT_EQ(*cit++, testChars[i++]);
    }
    ASSERT_EQ(strlen(testChars), i);
}

TEST(StringTest, substr) {
    const char* testStr = "abcdefgdijk";
    qcc::String s(testStr);

    /* Test substr */
    qcc::String s2 = s.substr(0, 4) + "1234";
    ASSERT_TRUE(s2 == "abcd1234");
    ASSERT_TRUE(s2.substr(4, 1) == "1");
    //ASSERT_TRUE(s2.substr(1000, 1) == ""); // std::string throws an exception
    ASSERT_TRUE(s2.substr(0, 0) == "");
    ASSERT_EQ(0, s.compare(1, 2, s2, 1, 2));
}

TEST(StringTest, plusEqualsOperator) {
    /* Test += */
    qcc::String s = "";
    for (size_t i = 0; i < 1000; ++i) {
        s += "foo";
        ASSERT_EQ(3 * (i + 1), s.size());
    }

    /* Test resize */
    s.erase(3, s.size() - 6);
    ASSERT_EQ(static_cast<size_t>(6), s.size());
    ASSERT_TRUE(s == "foofoo");
    s.resize(s.size() + 3, 'x');
    ASSERT_TRUE(s == "foofooxxx");
}


#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif
#if defined(QCC_OS_GROUP_WINDOWS)
#pragma warning(push)
#pragma warning(disable: 4996)
#endif
TEST(StringTest, secure_clear) {
    const char* secret = "secret data";
    const char* clear =  "\0\0\0\0\0\0\0\0\0\0\0";
    qcc::String s1(secret);
    auto secretSize = s1.size();
    ASSERT_EQ(0, memcmp(s1.data(), secret, s1.size()));

    s1.secure_clear();
    ASSERT_EQ(secretSize, s1.size());
    ASSERT_EQ(0, memcmp(s1.data(), clear, s1.size()));
}
#if defined(QCC_OS_GROUP_WINDOWS)
#pragma warning(pop)
#endif
#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif


/* ASACORE-1058 */
TEST(StringTest, assignDoesNotAppend) {
    const char* before = "012345678901234567890123456789012345";
    const char* after = "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdef";
    qcc::String t(before);
    t.assign(after);
    ASSERT_STREQ(after, t.c_str());
}


static std::string StdStringFunction(const std::string& ss)
{
    return ss + "s";
}

static qcc::String QccStringFunction(const qcc::String& qs)
{
    return qs + "q";
}

TEST(StringTest, stdStringIop) {
    // Most of the test cases here are actually compile-time compatibility tests.
    qcc::String qs1("s1");
    qcc::String qs2("s2");

    std::string ss1("s1");
    std::string ss2("s2");

    // Mixed comparison
    ASSERT_TRUE(qs1 == ss1);
    ASSERT_FALSE(qs1 == ss2);
    ASSERT_TRUE(qs1 < ss2);
    ASSERT_TRUE(qs2 > ss1);

    // Mixed copy constructor
    qcc::String tqs = ss1;
    std::string tss = qs1;
    ASSERT_STREQ(qs1.c_str(), tqs.c_str());  // verify contents
    ASSERT_STREQ(ss1.c_str(), tss.c_str());  // verify contents

    // Mixed assignment
    tqs = ss2;
    tss = qs2;
    ASSERT_STREQ(qs2.c_str(), tqs.c_str());  // verify contents
    ASSERT_STREQ(ss2.c_str(), tss.c_str());  // verify contents

    // Mixed append
    tqs.append(ss1);
    tss.append(qs1);
    ASSERT_STREQ("s2s1", tqs.c_str());
    ASSERT_STREQ("s2s1", tss.c_str());

    // Mixed +
    tqs = qs1 + ss1;
    tss = qs1 + ss1;
    ASSERT_STREQ("s1s1", tqs.c_str());
    ASSERT_STREQ("s1s1", tss.c_str());
    tqs = ss2 + qs2;
    tss = ss2 + qs2;
    ASSERT_STREQ("s2s2", tqs.c_str());
    ASSERT_STREQ("s2s2", tss.c_str());

    // Mixed function parameters
    ASSERT_STREQ("s1s", StdStringFunction(qs1).c_str());
    ASSERT_STREQ("s2q", QccStringFunction(ss2).c_str());

    // Mixed compare methods
    ASSERT_EQ(0, ss1.compare(qs1));
    ASSERT_EQ(0, qs2.compare(ss2));

    // IO stream tests
    std::ostringstream oss;
    oss << qs1 << ss2;
    oss << ss1 << qs2;
    ASSERT_STREQ("s1s2s1s2", oss.str().c_str());
}
