#pragma once
#include <SFML/System/Clock.hpp>
#include "stack_actions.hpp"
#include <SFML/Window/Event.hpp>
#include <map>
#include <functional>
#include "stateid.hpp"
#include "state.hpp"

class StateStack
{
public:
	explicit StateStack(State::Context context);
	template<typename T>
	void RegisterState(StateID state_id);
	template <typename T, typename Param1>
	void RegisterState(StateID state_id, Param1 arg1);
	void Update(sf::Time dt);
	void Draw();
	void HandleEvent(const sf::Event& event);

	void PushState(StateID state_id);
	void PopState();
	void ClearStack();
	bool IsEmpty() const;

private:
	State::Ptr CreateState(StateID state_id);
	void ApplyPendingChanges();

private:
	struct PendingChange
	{
		explicit PendingChange(StackActions action, StateID state_id = StateID::kNone);
		StackActions action;
		StateID state_id;
	};

private:
	//TODO is vector the right data structure here - list?
	std::vector<State::Ptr> m_stack;
	std::vector<PendingChange> m_pending_list;
	State::Context m_context;
	std::map<StateID, std::function<State::Ptr()>> m_state_factory;
};

template<typename T>
void StateStack::RegisterState(StateID state_id)
{
	m_state_factory[state_id] = [this]()
		{
			return State::Ptr(new T(*this, m_context));
		};
}

template <typename T, typename Param1>
void StateStack::RegisterState(StateID state_id, Param1 arg1)
{
	m_state_factory[state_id] = [this, arg1]()
		{
			return State::Ptr(new T(*this, m_context, arg1));
		};
}

