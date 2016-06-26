#include "stdafx.h"
#include "CppUnitTest.h"

#include "StateTracking.h"
#include "..\inc\memory"

namespace tf = Microsoft::VisualStudio::CppUnitTestFramework;
using namespace tf;

namespace kmstltest
{
    TEST_CLASS(MemoryTests)
    {
    public:
        struct Range
        {

        };

        TEST_METHOD(UninitializedCopy)
        {
            const size_t N = 3;

            StateTracker original[N];
            for (auto & state : original)
            {
                Assert::AreEqual(ConstructedBy::Default, state.Constructor);
                Assert::AreEqual(ObjectState::Constructed, state.State);
            }

            uint8_t copy[N * sizeof(StateTracker)];
            auto copy_begin = reinterpret_cast<StateTracker*>(kstd::begin(copy));
            auto copy_end = reinterpret_cast<StateTracker*>(kstd::end(copy));

            auto end = kstd::uninitialized_copy(kstd::begin(original), kstd::end(original), copy_begin);

            Assert::IsTrue(copy_end == end);
            for (auto it = copy_begin; it != copy_end; it++)
            {
                Assert::AreEqual(ConstructedBy::Copy, it->Constructor);
                Assert::AreEqual(ObjectState::Constructed, it->State);
            }
        }

        TEST_METHOD(UninitializedCopyN)
        {
            const size_t N = 3;

            StateTracker original[N];
            for (auto & state : original)
            {
                Assert::AreEqual(ConstructedBy::Default, state.Constructor);
                Assert::AreEqual(ObjectState::Constructed, state.State);
            }

            uint8_t copy[N * sizeof(StateTracker)];
            auto copy_begin = reinterpret_cast<StateTracker*>(kstd::begin(copy));
            auto copy_end = reinterpret_cast<StateTracker*>(kstd::end(copy));

            auto end = kstd::uninitialized_copy_n(kstd::begin(original), N, copy_begin);

            Assert::IsTrue(copy_end == end);
            for (auto it = copy_begin; it != copy_end; it++)
            {
                Assert::AreEqual(ConstructedBy::Copy, it->Constructor);
                Assert::AreEqual(ObjectState::Constructed, it->State);
            }
        }

        TEST_METHOD(UninitializedFill)
        {
            uint8_t buffer[3 * sizeof(StateTracker)];
            auto buffer_begin = reinterpret_cast<StateTracker*>(kstd::begin(buffer));
            auto buffer_end = reinterpret_cast<StateTracker*>(kstd::end(buffer));

            kstd::uninitialized_fill(buffer_begin, buffer_end, StateTracker{});

            for (auto it = buffer_begin; it != buffer_end; it++)
            {
                Assert::AreEqual(ConstructedBy::Copy, it->Constructor);
                Assert::AreEqual(ObjectState::Constructed, it->State);
            }
        }

        TEST_METHOD(UninitializedFillN)
        {
            const size_t N = 3;

            uint8_t buffer[N * sizeof(StateTracker)];
            auto buffer_begin = reinterpret_cast<StateTracker*>(kstd::begin(buffer));
            auto buffer_end = reinterpret_cast<StateTracker*>(kstd::end(buffer));

            auto end = kstd::uninitialized_fill_n(buffer_begin, N, StateTracker{});

            Assert::IsTrue(buffer_end == end);
            for (auto it = buffer_begin; it != buffer_end; it++)
            {
                Assert::AreEqual(ConstructedBy::Copy, it->Constructor);
                Assert::AreEqual(ObjectState::Constructed, it->State);
            }
        }

        TEST_METHOD(Destroy)
        {
            uint8_t buffer[3 * sizeof(StateTracker)];
            auto buffer_begin = reinterpret_cast<StateTracker*>(kstd::begin(buffer));
            auto buffer_end = reinterpret_cast<StateTracker*>(kstd::end(buffer));

            kstd::uninitialized_value_construct(buffer_begin, buffer_end);

            for (auto it = buffer_begin; it != buffer_end; it++)
            {
                Assert::AreEqual(ConstructedBy::Default, it->Constructor);
                Assert::AreEqual(ObjectState::Constructed, it->State);
            }

            kstd::destroy(buffer_begin, buffer_end);

            for (auto it = buffer_begin; it != buffer_end; it++)
            {
                Assert::AreEqual(ConstructedBy::Default, it->Constructor);
                Assert::AreEqual(ObjectState::Destroyed, it->State);
            }
        }

        TEST_METHOD(DestroyN)
        {
            const size_t N = 3;

            uint8_t buffer[N * sizeof(StateTracker)];
            auto buffer_begin = reinterpret_cast<StateTracker*>(kstd::begin(buffer));
            auto buffer_end = reinterpret_cast<StateTracker*>(kstd::end(buffer));

            auto end = kstd::uninitialized_value_construct_n(buffer_begin, N);

            Assert::IsTrue(buffer_end == end);

            for (auto it = buffer_begin; it != buffer_end; it++)
            {
                Assert::AreEqual(ConstructedBy::Default, it->Constructor);
                Assert::AreEqual(ObjectState::Constructed, it->State);
            }

            end = kstd::destroy_n(buffer_begin, N);

            Assert::IsTrue(buffer_end == end);

            for (auto it = buffer_begin; it != buffer_end; it++)
            {
                Assert::AreEqual(ConstructedBy::Default, it->Constructor);
                Assert::AreEqual(ObjectState::Destroyed, it->State);
            }
        }

        TEST_METHOD(UninitializedMove)
        {
            const size_t N = 3;

            StateTracker original[N];
            for (auto & state : original)
            {
                Assert::AreEqual(ConstructedBy::Default, state.Constructor);
                Assert::AreEqual(ObjectState::Constructed, state.State);
            }

            uint8_t destination[N * sizeof(StateTracker)];
            auto dest_begin = reinterpret_cast<StateTracker*>(kstd::begin(destination));
            auto dest_end = reinterpret_cast<StateTracker*>(kstd::end(destination));

            auto end = kstd::uninitialized_move(kstd::begin(original), kstd::end(original), dest_begin);

            Assert::IsTrue(dest_end == end);
            for (auto & state : original)
            {
                Assert::AreEqual(ObjectState::MovedFrom, state.State);
            }

            for (auto it = dest_begin; it != dest_end; it++)
            {
                Assert::AreEqual(ConstructedBy::Move, it->Constructor);
                Assert::AreEqual(ObjectState::Constructed, it->State);
            }
        }

        TEST_METHOD(UninitializedMoveN)
        {
            const size_t N = 3;

            StateTracker original[N];
            for (auto & state : original)
            {
                Assert::AreEqual(ConstructedBy::Default, state.Constructor);
                Assert::AreEqual(ObjectState::Constructed, state.State);
            }

            uint8_t destination[N * sizeof(StateTracker)];
            auto dest_begin = reinterpret_cast<StateTracker*>(kstd::begin(destination));
            auto dest_end = reinterpret_cast<StateTracker*>(kstd::end(destination));

            auto end = kstd::uninitialized_move_n(kstd::begin(original), N, dest_begin);

            Assert::IsTrue(dest_end == end);
            for (auto & state : original)
            {
                Assert::AreEqual(ObjectState::MovedFrom, state.State);
            }

            for (auto it = dest_begin; it != dest_end; it++)
            {
                Assert::AreEqual(ConstructedBy::Move, it->Constructor);
                Assert::AreEqual(ObjectState::Constructed, it->State);
            }
        }
    };
}