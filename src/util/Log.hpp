#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <exception>

using std::exception;

namespace Log
{

	const std::string DEBUG = " [DEBUG] ";
	const std::string INFO = " [INFO] ";
	const std::string WARN = " [WARN] ";
	const std::string ERROR = " [ERROR] ";
	
	const bool IS_DEBUG = std::getenv("DEBUG")!=NULL; 
	
	std::string now()
	{
		std::time_t current_time;
		std::time(&current_time);
		char now[25];	
		std::strftime(now, sizeof(now), 
			"%FT%T%z",std::localtime(&current_time));		
		
		return std::string(now);	
	}

	void log(std::string msg, std::string level)
	{
		std::clog << now() << level  << msg << std::endl; 		
	}

	void log_ex(std::string msg, exception &e)
	{
		std::clog << now() << ERROR << msg 
		<< "\n\t" << e.what() << std::endl;
	}

	void log_d(std::string msg)
	{
		if(IS_DEBUG)
		{
			log(msg, DEBUG);
		}
	}
	
	std::string to_string(int i){ return std::to_string(i); }
	std::string to_string(long i){ return std::to_string(i); }
	std::string to_string(long long i){ return std::to_string(i); }
	std::string to_string(unsigned i){ return std::to_string(i); }
	std::string to_string(unsigned long i){ return std::to_string(i); }
	std::string to_string(unsigned long long i){ return std::to_string(i); }
	std::string to_string(float i){ return std::to_string(i); }
	std::string to_string(double i){ return std::to_string(i); }
	std::string to_string(long double i){ return std::to_string(i); }

	void debug(){ log_d(""); }
	void debug(int msg){ log_d(to_string(msg)); }
	void debug(long msg){ log_d(to_string(msg)); }
	void debug(long long msg){ log_d(to_string(msg)); }
	void debug(unsigned msg){ log_d(to_string(msg)); }
	void debug(unsigned long msg){ log_d(to_string(msg)); }
	void debug(unsigned long long msg){ log_d(to_string(msg)); }
	void debug(float msg){ log_d(to_string(msg)); }
	void debug(double msg){ log_d(to_string(msg)); }
	void debug(long double msg){ log_d(to_string(msg)); }
	void debug(std::string msg){ log_d(msg); }
	
	void info(){ log("",INFO); }
	void info(int msg){ log(to_string(msg),INFO); }
	void info(long msg){ log(to_string(msg),INFO); }
	void info(long long msg){ log(to_string(msg),INFO); }
	void info(unsigned msg){ log(to_string(msg),INFO); }
	void info(unsigned long msg){ log(to_string(msg),INFO); }
	void info(unsigned long long msg){ log(to_string(msg),INFO); }
	void info(float msg){ log(to_string(msg),INFO); }
	void info(double msg){ log(to_string(msg),INFO); }
	void info(long double msg){ log(to_string(msg),INFO); }
	void info(std::string msg){ log(msg,INFO); }
	
	void warn(){ log("",WARN); }
	void warn(int msg){ log(to_string(msg),WARN); }
	void warn(long msg){ log(to_string(msg),WARN); }
	void warn(long long msg){ log(to_string(msg),WARN); }
	void warn(unsigned msg){ log(to_string(msg),WARN); }
	void warn(unsigned long msg){ log(to_string(msg),WARN); }
	void warn(unsigned long long msg){ log(to_string(msg),WARN); }
	void warn(float msg){ log(to_string(msg),WARN); }
	void warn(double msg){ log(to_string(msg),WARN); }
	void warn(long double msg){ log(to_string(msg),WARN); }
	void warn(std::string msg){ log(msg,WARN); }	
	
	void error(){ log("",ERROR); }
	void error(int msg){ log(to_string(msg),ERROR); }
	void error(long msg){ log(to_string(msg),ERROR); }
	void error(long long msg){ log(to_string(msg),ERROR); }
	void error(unsigned msg){ log(to_string(msg),ERROR); }
	void error(unsigned long msg){ log(to_string(msg),ERROR); }
	void error(unsigned long long msg){ log(to_string(msg),ERROR); }
	void error(float msg){ log(to_string(msg),ERROR); }
	void error(double msg){ log(to_string(msg),ERROR); }
	void error(long double msg){ log(to_string(msg),ERROR); }
	void error(std::string msg){ log(msg,ERROR); }
	
	void error(exception &ex){ log_ex("",ex); }
	void error(int msg, exception &ex)
		{ log_ex(to_string(msg),ex); }
	void error(long msg, exception &ex)
		{ log_ex(to_string(msg),ex); }
	void error(long long msg, exception &ex)
		{ log_ex(to_string(msg),ex); }
	void error(unsigned msg, exception &ex)
		{ log_ex(to_string(msg),ex); }
	void error(unsigned long msg, exception &ex)
		{ log_ex(to_string(msg),ex); }
	void error(unsigned long long msg, exception &ex)
		{ log_ex(to_string(msg),ex); }
	void error(float msg, exception &ex)
		{ log_ex(to_string(msg),ex); }
	void error(double msg, exception &ex)
		{ log_ex(to_string(msg),ex); }
	void error(long double msg, exception &ex)
		{ log_ex(to_string(msg),ex); }
	void error(std::string msg, exception &ex)
		{ log_ex(msg,ex); }
}