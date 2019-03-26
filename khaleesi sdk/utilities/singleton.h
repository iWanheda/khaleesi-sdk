#pragma once

template<typename t>
class singleton {
protected:
	singleton() { };
	~singleton() { };

	singleton(const singleton&) = delete;
	singleton& operator=(const singleton&) = delete;

	singleton(singleton&&) = delete;
	singleton& operator=(singleton&&) = delete;
public:
	static t& get() {
		static t inst{ };
		return inst;
	}
};