#pragma once

namespace tf = Microsoft::VisualStudio::CppUnitTestFramework;

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
    Destroyed,
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

    ~StateTracker() 
    {
        State = ObjectState::Destroyed;
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

