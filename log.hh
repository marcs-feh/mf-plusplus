#include "types.hh"

#include <time.h>
#include <stdio.h>

#define eprint(...) fprintf(stderr, __VA_ARGS__)

// TODO: allow logging at files, use custom string type

enum Log_Severity {
	LogSv_Ok,
	LogSv_Info,
	LogSv_Warn,
	LogSv_Error,
	LogSv_Fatal,
};

static void log_msg(const char* msg, Log_Severity sv, bool use_time, const char* file, i32 line){
	if(use_time){
		time_t cur_time = time(NULL);
		struct tm date  = *localtime(&cur_time);
		eprint("[%d-%02d-%02d %02d:%02d:%02d] ",
				   date.tm_year + 1900, date.tm_mon + 1, date.tm_mday,
			     date.tm_hour, date.tm_min, date.tm_sec);
	}

	eprint("[");
	switch(sv){
		case LogSv_Ok:    eprint("\e[0;32mOK   \e[0m"); break;
		case LogSv_Info:  eprint("\e[0;35mINFO \e[0m"); break;
		case LogSv_Warn:  eprint("\e[0;33mWARN \e[0m"); break;
		case LogSv_Error: eprint("\e[0;31mERROR\e[0m"); break;
		case LogSv_Fatal: eprint("\e[1;31mFATAL\e[0m"); break;
	}
	if(file != nullptr && line != 0){
		eprint(" %s:%d", file, line);
	}
	eprint("] %s\n", msg);
}

#ifdef LOG_USE_TIME
#define log_ok(msg)    log_msg(msg, LogSv_Ok, true, __FILE__, __LINE__)
#define log_info(msg)  log_msg(msg, LogSv_Info, true, __FILE__, __LINE__)
#define log_warn(msg)  log_msg(msg, LogSv_Warn, true, __FILE__, __LINE__)
#define log_error(msg) log_msg(msg, LogSv_Error, true, __FILE__, __LINE__)
#define log_fatal(msg) log_msg(msg, LogSv_Fatal, true, __FILE__, __LINE__)
#else
#define log_ok(msg)    log_msg(msg, LogSv_Ok, false, __FILE__, __LINE__)
#define log_info(msg)  log_msg(msg, LogSv_Info, false, __FILE__, __LINE__)
#define log_warn(msg)  log_msg(msg, LogSv_Warn, false, __FILE__, __LINE__)
#define log_error(msg) log_msg(msg, LogSv_Error, false, __FILE__, __LINE__)
#define log_fatal(msg) log_msg(msg, LogSv_Fatal, false, __FILE__, __LINE__)
#endif

