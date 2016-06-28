#include "stdafx.h"
#include "CppUnitTest.h"

#include "..\inc\memory"

namespace tf = Microsoft::VisualStudio::CppUnitTestFramework;
using namespace tf;

namespace kmstltest
{
    TEST_CLASS(UniquePtrTests)
    {
    public:

        TEST_METHOD(ConstructUniquePtr)
        {
            auto ptr = kstd::unique_ptr<int>(new int());

            Assert::AreEqual(0, *ptr);
        }

        struct SignalsDeletion
        {
            bool & signal;

            SignalsDeletion(bool & signal) : signal(signal) { }

            ~SignalsDeletion() { signal = true; }
        };

        TEST_METHOD(DestroyUniquePtr)
        {
            auto signal = false;
            {
                auto ptr = kstd::unique_ptr<SignalsDeletion>(new SignalsDeletion(signal));
            }

            Assert::IsTrue(signal);
        }

        TEST_METHOD(CompareUniquePtr)
        {
            auto ptr1 = kstd::unique_ptr<int>(new int());
            auto ptr2 = kstd::unique_ptr<int>(new int());

            Assert::AreEqual(ptr1.get() < ptr2.get(), ptr1 < ptr2);
        }

        TEST_METHOD(CompareUnlikeUniquePtr)
        {
            struct A {};
            struct B : A {};

            auto ptr1 = kstd::unique_ptr<A>(new A());
            auto ptr2 = kstd::unique_ptr<B>(new B());

            Assert::AreEqual(ptr1.get() < ptr2.get(), ptr1 < ptr2);
        }
    };
}