#include <dataref.h>
#include <tools.h>
#include <iostream>
#include <console.h>

std::map<std::string, Dataref::Value> Dataref::data = std::map<std::string, Dataref::Value>();

std::string Dataref::get(const std::string& id) {
	if (data.find(id) != data.end()) {
		if (data[id].m_value->type() == typeid(int)) {
			std::string value = Tools::toString<int>(std::any_cast<int>(*data[id].m_value));
			CONSOLE->writeln("get '" + id + "' value: " + value);
			return value;
		}
		
		if (data[id].m_value->type() == typeid(float)) {
			std::string value = Tools::toString<float>(std::any_cast<float>(*data[id].m_value));
			CONSOLE->writeln("get '" + id + "' value: " + value);
			return value;
			}
			
		if (data[id].m_value->type() == typeid(std::string)) {
			std::string value = std::any_cast<std::string>(*data[id].m_value);
			CONSOLE->writeln("get '" + id + "' value: " + value);
			return value;
		}
	} else
		CONSOLE->writeln(id + ": unknown value");
		
	return std::string();
}

Dataref::Value::Value(Dataref::AccessType access, std::any* value, std::function<void()> func)
: m_access(access), m_value(value), m_func(func) {
}

void Dataref::set(const std::string& id, const std::string& value) {
	if (data.find(id) != data.end()) {
		if (data[id].m_value->type() == typeid(int) ||
			data[id].m_value->type() == typeid(float)) {
			if (Tools::isNumber(value)) {
				Dataref::set<float>(id, Tools::fromString<float>(value));
			}
			else {
				CONSOLE->writeln(id + ": inconsistent types");
				return;
			}
		} else
			if (data[id].m_value->type() == typeid(std::string))
				Dataref::set<std::string>(id, value);
			else {
				CONSOLE->writeln(id + ": unauthorized type (only NUMERIC/ALPHANUMERIC allowed)");
				return;
			}
				
		CONSOLE->writeln("set '" + id + "' to " + value);
	}
}

bool Dataref::isValidType(std::any value) {
	return 	value.type() == typeid(int) ||
			value.type() == typeid(float) ||
			value.type() == typeid(std::string);
}