#include "stdafx.h"
#include "CppUnitTest.h"

#include "StateTracking.h"
#include "..\inc\utility"

namespace tf = Microsoft::VisualStudio::CppUnitTestFramework;
using namespace tf;

namespace kmstltest
{
	TEST_CLASS(UtilityTests)
	{
	public:

		TEST_METHOD(MoveTest)
		{
            StateTracker a;
            Assert::AreEqual(ConstructedBy::Default, a.Constructor);

            auto b = ::kstd::move(a);
            Assert::AreEqual(ConstructedBy::Move, b.Constructor);
            Assert::AreEqual(ObjectState::MovedFrom, a.State);
		}

        TEST_METHOD(MoveAssignment)
        {
            StateTracker a, b;
            Assert::AreEqual(ConstructedBy::Default, a.Constructor);
            Assert::AreEqual(ConstructedBy::Default, b.Constructor);

            b = ::kstd::move(a);
            Assert::AreEqual(ObjectState::MovedInto, b.State);
            Assert::AreEqual(ObjectState::MovedFrom, a.State);
        }

        FunctionInvocation ForwardTarget(StateTracker const & value)
        {
            auto result = value;
            return FunctionInvocation::Copy;
        }

        FunctionInvocation ForwardTarget(StateTracker&& value)
        {
            auto result = ::kstd::move(value);
            return FunctionInvocation::Move;
        }

        template<typename T>
        FunctionInvocation ForwardIt(T&& value)
        {
            return ForwardTarget(::kstd::forward<T>(value));
        }

        TEST_METHOD(ForwardTest)
        {
            StateTracker a;
            Assert::AreEqual(FunctionInvocation::Copy, ForwardIt(a));

            Assert::AreEqual(FunctionInvocation::Move, ForwardIt(::kstd::move(a)));
            Assert::AreEqual(ObjectState::MovedFrom, a.State);
        }
	};
}