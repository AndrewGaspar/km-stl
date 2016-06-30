#include "stdafx.h"
#include "CppUnitTest.h"

#include "StateTracking.h"
#include "..\inc\optional"
#include "..\inc\utility"
#include "OptionalToString.h"

namespace tf = Microsoft::VisualStudio::CppUnitTestFramework;
using namespace tf;

namespace kmstltest
{
	TEST_CLASS(OptionalTests)
	{
	public:

		TEST_METHOD(InitOptional)
		{
			auto state = kstd::optional<StateTracker>();
			Assert::IsFalse(!!state);
		}

		TEST_METHOD(ConstructOptional)
		{
			auto one = kstd::make_optional(1);

			Assert::IsTrue(!!one);
			Assert::AreEqual(1, *one);
		}

		TEST_METHOD(OptionalAssign)
		{
			auto one = kstd::optional<int>();
			Assert::IsFalse(!!one);
			one = 1;
			Assert::IsTrue(!!one);
			Assert::AreEqual(1, *one);
		}

		TEST_METHOD(AssignNullOpt)
		{
			auto opt_state = kstd::optional<StateTracker>(kstd::in_place);
			Assert::IsTrue(!!opt_state);

			auto & state = *opt_state;
			Assert::AreEqual(ConstructedBy::Default, state.Constructor);
			Assert::AreEqual(ObjectState::Constructed, state.State);

			opt_state = kstd::nullopt;

			Assert::AreEqual(ObjectState::Destroyed, state.State);
		}

		TEST_METHOD(AssignT)
		{
			auto opt_state = kstd::optional<StateTracker>(kstd::in_place);
			Assert::IsTrue(!!opt_state);

			auto & state = *opt_state;
			Assert::AreEqual(ConstructedBy::Default, state.Constructor);
			Assert::AreEqual(ObjectState::Constructed, state.State);

			opt_state = StateTracker{};

			Assert::AreEqual(ObjectState::MovedInto, state.State);
		}

		TEST_METHOD(MoveOptional)
		{
			auto opt_state = kstd::optional<StateTracker>();
			Assert::IsFalse(!!opt_state);

			auto opt_state_2 = kstd::optional<StateTracker>(kstd::in_place);
			Assert::IsTrue(!!opt_state_2);

			opt_state = kstd::move(opt_state_2);
			Assert::IsTrue(!!opt_state);
			Assert::IsTrue(!!opt_state_2);

			Assert::AreEqual(ConstructedBy::Move, opt_state->Constructor);
			Assert::AreEqual(ObjectState::Constructed, opt_state->State);
			Assert::AreEqual(ObjectState::MovedFrom, opt_state_2->State);
		}

		TEST_METHOD(Equality)
		{
			auto opt_null = kstd::optional<int>(kstd::nullopt);
			auto opt_also_null = kstd::optional<int>(kstd::nullopt);
			auto opt_1 = kstd::make_optional(1);
			auto opt_also_1 = kstd::make_optional(1);
			auto opt_2 = kstd::make_optional(2);

			Assert::AreEqual(opt_null, opt_also_null);
			Assert::AreNotEqual(opt_null, opt_1);
			Assert::AreEqual(opt_1, opt_also_1);
			Assert::AreNotEqual(opt_1, opt_2);
		}

		TEST_METHOD(OptionalOrdering)
		{
			auto opt_null = kstd::optional<int>(kstd::nullopt);
			auto opt_1 = kstd::make_optional(1);
			auto opt_also_1 = kstd::make_optional(1);
			auto opt_2 = kstd::make_optional(2);

			Assert::IsFalse(opt_null > opt_null);
			Assert::IsFalse(opt_null < opt_null);
			Assert::IsTrue(opt_null >= opt_null);
			Assert::IsTrue(opt_null <= opt_null);

			Assert::IsFalse(opt_null > kstd::nullopt);
			Assert::IsFalse(opt_null < kstd::nullopt);
			Assert::IsTrue(opt_null >= kstd::nullopt);
			Assert::IsTrue(opt_null <= kstd::nullopt);

			Assert::IsFalse(kstd::nullopt > opt_null);
			Assert::IsFalse(kstd::nullopt < opt_null);
			Assert::IsTrue(kstd::nullopt >= opt_null);
			Assert::IsTrue(kstd::nullopt <= opt_null);

			Assert::IsFalse(kstd::nullopt > opt_1);
			Assert::IsFalse(kstd::nullopt >= opt_1);
			Assert::IsTrue(kstd::nullopt < opt_1);
			Assert::IsTrue(kstd::nullopt <= opt_1);

			Assert::IsFalse(opt_null > 1);
			Assert::IsFalse(opt_null >= 1);
			Assert::IsTrue(opt_null < 1);
			Assert::IsTrue(opt_null <= 1);

			Assert::IsFalse(opt_null > opt_1);
			Assert::IsFalse(opt_null >= opt_1);
			Assert::IsTrue(opt_null < opt_1);
			Assert::IsTrue(opt_null <= opt_1);

			Assert::IsFalse(opt_1 < opt_null);
			Assert::IsFalse(opt_1 <= opt_null);
			Assert::IsTrue(opt_1 > opt_null);
			Assert::IsTrue(opt_1 >= opt_null);

			Assert::IsFalse(opt_1 > opt_1);
			Assert::IsFalse(opt_1 < opt_1);
			Assert::IsTrue(opt_1 >= opt_1);
			Assert::IsTrue(opt_1 <= opt_1);

			Assert::IsFalse(opt_1 > 1);
			Assert::IsFalse(opt_1 < 1);
			Assert::IsTrue(opt_1 >= 1);
			Assert::IsTrue(opt_1 <= 1);

			Assert::IsFalse(1 > opt_1);
			Assert::IsFalse(1 < opt_1);
			Assert::IsTrue(1 >= opt_1);
			Assert::IsTrue(1 <= opt_1);

			Assert::IsFalse(opt_1 > opt_2);
			Assert::IsFalse(opt_1 >= opt_2);
			Assert::IsTrue(opt_1 < opt_2);
			Assert::IsTrue(opt_1 <= opt_2);

			Assert::IsFalse(opt_1 > 2);
			Assert::IsFalse(opt_1 >= 2);
			Assert::IsTrue(opt_1 < 2);
			Assert::IsTrue(opt_1 <= 2);

			Assert::IsFalse(1 > opt_2);
			Assert::IsFalse(1 >= opt_2);
			Assert::IsTrue(1 < opt_2);
			Assert::IsTrue(1 <= opt_2);
		}

		TEST_METHOD(OptionalSwap)
		{
			auto opt_null = kstd::optional<int>();
			auto opt_init = kstd::make_optional(1);

			Assert::IsFalse(bool(opt_null));
			Assert::IsTrue(bool(opt_init));
			Assert::IsTrue(1 == opt_init);

			kstd::swap(opt_null, opt_init);

			Assert::IsFalse(bool(opt_init));
			Assert::IsTrue(bool(opt_null));
			Assert::IsTrue(1 == opt_null);
		}
	};
}