#include "SolverControler.h"
#include <fstream>
#include <iostream>
#include <windows.h>
#include <tchar.h>

/// <summary>
/// Check if a file end with a specific suffix
/// </summary>
/// <param name="str">String to check</param>
/// <param name="suffix">Suffix to found at the end</param>
/// <returns>True for yes</returns>
bool has_suffix(const std::string& str, const std::string& suffix)
{
    return str.size() >= suffix.size() &&
        str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}

wchar_t* charArrayToLPCWSTR(const char* charArray)
{
    wchar_t* wString = new wchar_t[4096];
    MultiByteToWideChar(CP_ACP, 0, charArray, -1, wString, 4096);
    return wString;
}

string LPCWSTRtoString(wchar_t* txt) {
    wstring ws(txt);
    return string(ws.begin(), ws.end());
}

SolverControler::SolverControler()
{
    solver = NULL;
    results = list<Result*>();
    instances = list<Instance*>();
}

SolverControler::~SolverControler()
{
    if (solver != NULL)
        delete solver;

    for (Result* res : results) {
        if (res != NULL)
            delete res;
    }
    results.clear();

    for (Instance* inst : instances) {
        if (inst != NULL)
            delete inst;
    }
    instances.clear();
}

void SolverControler::LaunchComputation()
{
    
}

bool SolverControler::ImportInstances(string dir)
{
    std::string pattern(dir);
    pattern.append("\\*");
    WIN32_FIND_DATA data;
    HANDLE hFind;
    if ((hFind = FindFirstFile(charArrayToLPCWSTR(pattern.c_str()), &data)) != INVALID_HANDLE_VALUE) {
        do {
            if (has_suffix(LPCWSTRtoString(data.cFileName), ".txt")) {
                try {
                    Instance* inst = new Instance(dir + "\\" + LPCWSTRtoString(data.cFileName));
                    instances.push_back(inst);
                }
                catch (exception exc) {
                    cout << "Error : " << exc.what();
                }
            }
        } while (FindNextFile(hFind, &data) != 0);
        FindClose(hFind);
    }
    return false;
}



bool SolverControler::ExportResults(string path)
{
    // No results
    if (results.size() == 0)
        return false;

    // Check if file already exist
    ifstream file;
    file.open(path);
    if (file) {
        cout << "Error when saving results : File already exist";
        return false;
    }

    // Check extension
    if (!has_suffix(path, ".txt")) {
        cout << "Error when saving results : need .txt extension";
        return false;
    }

    // Saving
    try {
        ofstream output(path);
        for (Result* res : results) {
            output << res->inst->id << res->inst->n << res->cout_total << res->cout_WIP << res->cout_FIN << res->cout_retard;
        }
        output.close();
        return true;
    }
    catch (exception e) {
        cout << e.what();
        return false;
    }
}

