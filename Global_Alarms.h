// Global_Alarms.h: interface for the Global_Alarms class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GLOBAL_ALARMS_H__CC067699_D84C_420B_8121_1CD0BA34C564__INCLUDED_)
#define AFX_GLOBAL_ALARMS_H__CC067699_D84C_420B_8121_1CD0BA34C564__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
/*
#include <map>
#include <string>
using namespace std;

class AlarmTable
{
public:
    enum { idNotFound = -1 };
    AlarmTable () : _id (0) {}
    int ForceAdd (char const * str);
    int Find (char const * str) const;
private:
    map<string, int> _dictionary;
    int _id;
};
*/
class Global_Alarms  
{
public:
	Global_Alarms();
	virtual ~Global_Alarms();

	
private:
    //AlarmTable alarm_table;
};



#endif // !defined(AFX_GLOBAL_ALARMS_H__CC067699_D84C_420B_8121_1CD0BA34C564__INCLUDED_)
