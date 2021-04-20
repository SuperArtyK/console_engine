/*
	ArtyK's Console (Game) Engine. Console engine for apps and games
	Copyright (C) 2021  Artemii Kozhemiak

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

//////////////////////////////////////////////////////////////////////////
// this file contains the logger class, for logging data to file.
// should not cause everything to break
//////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef FILELOG
#define FILELOG

//#include "include.hpp"//includes EVERYTHING that I need
#include <iostream>
#include <thread>
#include <fstream>
#include <vector>
#include <string>

//#include "screen.hpp"

using std::vector;
using std::string;
using std::atomic;




class filelog {
public:
	atomic<bool> m_bDev_cout;//for debug information; outputs the info to main console
	//WARN: MAY CAUSE MEMORY LEAK IF MORE THAN 1 THREADS ARE OUTPUTTING!
	atomic<bool> m_bDev_log;//for debug information; outputs debug filelog info to current log

	filelog();

	filelog(std::string l_strPathtolog);
	//int changelogpath(std::string newlogpath);
	//filelog& operator=(std::string differentpath);

	~filelog() {
		if (m_bThreadstarted)
			stoplogging();
	}
	void debugConOut(std::string, int, std::string, int x = -1, int y = -1);//outputs debug messages to console

	int writetolog(std::string l_strMessg = "", int l_iType = 0, std::string l_strProg_module = "main", bool debuglog = false);
	int stoplogging();
	int startlogging();
	void setwritecoords(int x, int y) {	m_x = x; m_y = y;}
private:
	int m_x, m_y;

	//functions
	atomic<bool> m_bStoplog;//flag that for stopping/opening logging session
	int mainthread();

	//date/time
	const std::string currentDateTime();
	std::string logdate();
	int createdir(const char* pathtofile);
	int openfile();
	int closefile();

	//misc
	size_t objsize() {
		size_t temp = sizeof(*this) + m_strMessg.capacity() + m_iLogtype.capacity() + m_strProg_module.capacity();
		return temp;
	}
	bool vectorcheck() {
		return (!m_strMessg.empty() && !m_iLogtype.empty() && !m_strProg_module.empty());
	}

	//vars
	std::string m_strDatentime;//stores date/time data
	std::string m_strFilename;
	std::fstream m_fstFilestr;//file "editor"
	std::string m_strLogpath;//log path variable
	bool m_bThreadstarted;
	std::thread m_trdLogthread;

	//const int mpr_cst_iMaxmessgcount = 256;
// 	std::string mpr_arr_strMessg[256];

	//logging vars
	vector<std::string> m_strMessg;// = vector<std::string>(1, "Starting new logging session");
// 	int mpr_arr_iLogtype[256];
//  	std::string mpr_arr_strProg_module[256];
	uint64_t m_ullMessgcount;
	vector<int> m_iLogtype;// = vector<int>(1, 0);
	vector <std::string> m_strProg_module;// = vector<std::string>(1, "main");

	//misc
	long double m_ldEntrycount;
	//long double mpr_ldWriteiterat = 0;
};
inline  filelog g_flgDeflogger;//default logger
//wont be moved to global_vars.hpp
//will probably cause infinite recursion for compiler
//I dont want that

#endif
