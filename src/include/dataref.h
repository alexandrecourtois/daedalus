#ifndef DATAREF_H
#define DATAREF_H

#include <any>
#include <map>
#include <string>
#include <console.h>
#include <tools.h>

class Dataref {
public:
		enum AccessType { rw, ro };
		
		struct Value {
			Value() { }
			Value(AccessType access, std::any* value, std::function<void()> func);
			
			AccessType	m_access;
			std::any*	m_value;
			std::function<void()> m_func;
		};
private:
	static std::map<std::string, Value> data;

public:
	static bool isValidType(std::any value);
	
	template <typename T> static void set(const std::string& id, AccessType access, std::any value, T** ptr, std::function<void()> f = nullptr) {
		if (data.find(id) != data.end())
			CONSOLE->writeln(id + ": already exists");
		else
			if (isValidType(value))
				if (value.type() == typeid(T)) {
					data[id] = Value(access, new std::any(value), f);
					
					if (ptr)
						*ptr = std::any_cast<T>(data[id].m_value);
					
					if (f)
						f();
					
					CONSOLE->writeln("set '" + id + "' to " + Tools::toString<T>(*std::any_cast<T>(data[id].m_value)));
				}
				else
					CONSOLE->writeln(id + ": inconsistent types (NUMERIC <> ALPHANUMERIC)");
			else
				CONSOLE->writeln(id + ": unauthorized type (only NUMERIC/ALPHANUMERIC allowed)");
	}
	
	template <typename T> static void set(const std::string& id, std::any value) {
		if (data.find(id) == data.end())
			Dataref::set<T>(id, AccessType::ro, value, nullptr);
		else
			if (data[id].m_access == AccessType::rw) {
				if (data[id].m_value->type() == value.type())
					*data[id].m_value = value;
				else
					CONSOLE->writeln(id + ": inconsistent value type (NUMERIC <> ALPHANUMERIC)");
			} else
				CONSOLE->writeln(id + ": read-only");		
	}
	
	static void set(const std::string& id, const std::string& value);
	
	template <typename T> static T get(const std::string& id) {
		if (data.find(id) != data.end())
			return std::any_cast<T>(*data[id].m_value);
		else {
			CONSOLE->writeln(id + ": unknown value");
			return T();
		}
	}
	
	template <typename T> static T* getPtr(const std::string& id) {
		if (data.find(id) != data.end())
			return std::any_cast<T>(data[id].m_value);
		else {
			CONSOLE->writeln(id + ": unknown value");
			return nullptr;
		}
	}
	
	static std::string get(const std::string& id);
};

#define	RW				Dataref::AccessType::rw
#define RO				Dataref::AccessType::ro
#define newData_f		Dataref::set<float>
#define newData_i		Dataref::set<int>
#define newData_s		Dataref::set<std::string>
#define updateCode		nullptr,[this]()

#endif // DATAREF_H