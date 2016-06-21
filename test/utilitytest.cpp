#include "stdafx.h"
#include "CppUnitTest.h"

#include "..\inc\utility"

namespace tf = Microsoft::VisualStudio::CppUnitTestFramework;
using namespace tf;

enum class ConstructedBy
{
    Default,
    Copy,
    Move,
};


enum class ObjectState
{
    Constructed,
    CopiedInto,
    MovedFrom,
    MovedInto,
};

enum class FunctionInvocation
{
    Copy = 0,
    Move = 1,
};

template<>
inline std::wstring tf::ToString<ConstructedBy>(ConstructedBy const & constructedBy)
{
    return std::to_wstring(static_cast<std::uint32_t>(constructedBy));
}

template<>
inline std::wstring tf::ToString<ObjectState>(ObjectState const & objectState)
{
    return std::to_wstring(static_cast<std::uint32_t>(objectState));
}

template<>
inline std::wstring tf::ToString<FunctionInvocation>(FunctionInvocation const & functionInvocation)
{
    return std::to_wstring(static_cast<std::uint32_t>(functionInvocation));
}

namespace kmstltest
{

    struct StateTracker
    {
        const ConstructedBy Constructor;
        ObjectState State = ObjectState::Constructed;

        constexpr StateTracker() : Constructor(ConstructedBy::Default)
        {

        }

        constexpr StateTracker(StateTracker const & other) : Constructor(ConstructedBy::Copy)
        {

        }

        StateTracker(StateTracker&& other) : Constructor(ConstructedBy::Move)
        {
            other.State = ObjectState::MovedFrom;
        }

        StateTracker & operator=(StateTracker const & other)
        {
            State = ObjectState::CopiedInto;
            return *this;
        }

        StateTracker & operator=(StateTracker&& other)
        {
            other.State = ObjectState::MovedFrom;
            State = ObjectState::MovedInto;
            return *this;
        }
    };

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